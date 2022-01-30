#include "syn/nodes/incomplete/expressions/block.hpp"
#include "syn/nodes/expressions.hpp" // To complete circular dependencies.

#include <string>
#include <utility>

#include "esl/category.hpp"
#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"
#include "esl/zip.hpp"

#include "context/main.hpp"
#include "context/branching.hpp"
#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "interface/values.hpp"
#include "sem/translation.hpp"
#include "syn/categories/statement.hpp"
#include "config.hpp"

namespace cynth::syn {

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;
    using interface::NameExtractionResult;
    using interface::StatementProcessingResult;
    using interface::TypeNameExtractionResult;
    using sem::CompleteType;
    using sem::CompleteValue;
    using sem::FunctionDefinition;
    using sem::NoReturn;
    using sem::ResolvedValue;
    using sem::ReturnedValues;
    using sem::Returned;
    using sem::TypedExpression;

    DisplayResult node::Block::display () const {
        using Target = target::nested<target::component_vector, target::category>;
        return statements.empty()
            ? "{}"
            : "{\n" + esl::join(";\n", interface::display || Target{} <<= statements) + "\n}";
    }

    namespace {

        // TODO: These helper functions are huge.
        // Can I split them up and place them in some corresponding semantic structures?

        constexpr bool stop = true;  // break
        constexpr bool next = false; // continue

        struct BlockResult {
            esl::tiny_vector<Returned> returned; // Empty => Returning void.
            bool always  = false;
            bool runtime = false;
        };

        esl::optional_result<BlockResult> processBlock (
            context::Main & ctx,
            esl::component_vector<category::Statement> const & statements
        ) {
            auto before = ctx.count();
            BlockResult blockResult = {};
            bool never = true;

            for (auto const & statement: statements) {
                using Result = esl::result<bool>;

                auto result = [] (NoReturn) -> Result {
                    return next;

                } | [&] (sem::Return ret) -> Result {
                    never = false;

                    if (blockResult.returned.empty())
                        blockResult.returned.reserve(ret.returned.size());
                        // TODO: Resize?
                    else if (blockResult.returned.size() > ret.returned.size())
                        return esl::result_error{"Returning more values than last time."};
                    else if (blockResult.returned.size() < ret.returned.size())
                        return esl::result_error{"Returning less values than last time."};

                    for (auto const & [i, returned]: esl::enumerate(ret.returned)) {
                        auto returnedType = interface::returnedType(returned);
                        bool init = i >= blockResult.returned.size();

                        if (init) {
                            // First return:
                            [&] (ReturnedValues const & values) {
                                // TODO: tiny_vector(begin_it, end_it) results in segfaults.
                                // I don't think it's implemented directly and maybe the inherited implementation
                                // from std::vector kicks in and breaks this.
                                ReturnedValues copy;
                                copy.insert_back(values.begin(), values.end());
                                blockResult.returned.push_back(Returned{copy});

                            } | [&] (CompleteType const &) {
                                blockResult.returned.push_back(Returned{
                                    returnedType
                                });
                                blockResult.runtime = true;

                            } || target::category{} <<= args(returned);
                            continue;
                        }

                        // Some returns already encountered:
                        auto & entry  = blockResult.returned[i];
                        auto lastType = interface::returnedType(entry);
                        // Note: Conversion to comon types upon return will not be supported in the first version.
                        if (!(interface::sameTypes || target::category{} <<= args(lastType, returnedType)))
                            return esl::result_error{"Returning incompatible types."};

                        [&] (ReturnedValues const & values, ReturnedValues & entry) {
                            entry.insert_back(values.begin(), values.end());

                        } | [&] (ReturnedValues const & values, CompleteType &) {
                            ReturnedValues copy;
                            copy.insert_back(values.begin(), values.end());
                            entry = Returned{copy};

                        } | [&] (CompleteType const &, ReturnedValues const &) {
                            // Ignore those. (Some previous compile-time return would have already eliminated this one.)

                        } | [&] (CompleteType const &, auto const &) {
                            blockResult.runtime = true;
                            entry = returnedType;

                        } || target::category{} <<= args(returned, entry);
                    }

                    if (ret.always)
                        blockResult.always = true;

                    return ret.always ? stop : next;

                } || target::optional_result{} <<=
                    interface::processStatement(ctx) || target::category{} <<= statement;

                if (!result) return result.error();
                if (*result == stop) break;
            }

            if (ctx.count() != before)
                // If any local statements added, enforce the run-time state.
                blockResult.runtime = true;

            if (never)
                return {};

            return blockResult;
        };

        struct BlockExpressionResult {
            esl::tiny_vector<ResolvedValue> resolved;
            esl::tiny_vector<std::string>   declarations;
            esl::tiny_vector<std::pair<std::size_t, CompleteValue>> returns; // comp-time returns
        };

        esl::result<BlockExpressionResult> processBlockExpression (
            context::Main & ctx,
            std::string const * tupleVar,
            esl::tiny_vector<Returned> const & returned
        ) {
            BlockExpressionResult blockResult;

            for (auto const & [i, entry]: esl::enumerate(returned)) {
                auto name         = c::tupleElementName(i);
                auto tupleElement = tupleVar ? c::tupleElement(*tupleVar, i) : "<result>";
                // TODO: Take care of nullptr tupleVar properly...

                auto result = [&, i = i] (ReturnedValues const & values) {
                    return [&] (sem::type::Function const & type) -> esl::result<void> {
                        // Partially run-time function values:
                        if (values.size() == 0) // Implemetation error.
                            return esl::result_error{"Returning no values in a function-typed block return."};
                        return [&] (auto functions) -> esl::result<void> {
                            if (functions.size() == 1) {
                                auto const & fun = functions.front();
                                if (!fun.runtimeClosure()) {
                                    // A single function with no run-time capture:
                                    blockResult.resolved.push_back(CompleteValue{fun});

                                    // TODO: Find a better way to solve this:
                                    auto dummyClosure = c::declaration(
                                        "struct { int branch; union { struct cth_empty v0; } data; }",
                                        name
                                    );
                                    blockResult.declarations.push_back(dummyClosure);

                                    return {};
                                }

                                // A single function with run-time capture:
                                /*
                                auto decl = c::declaration(*fun.definition.closureType, name);
                                auto copy = sem::value::Function{fun.definition, tupleElement};
                                blockResult.declarations.push_back(decl);
                                blockResult.resolved.push_back(CompleteValue{copy});
                                return {};
                                */
                                // Note: For now, this case is handled the same as multiple functions.
                                // TODO: Find a way to optimize this case.
                                // I need to think of an appropriate way to let the return statement know, that
                                // it doesn't need to return the branch number.
                            }

                            // Multiple functions combined in a run-time switch function:

                            auto & def = ctx.global.storeValue<FunctionDefinition>(FunctionDefinition{
                                .implementation = FunctionDefinition::Switch{esl::make_component_vector(functions)},
                                .type           = type,
                                .closureType    = c::closureType(c::id(ctx.global.nextId()))
                                //.name           = c::functionName(c::id(ctx.global.nextId()))
                            });
                            auto newFun = sem::value::Function{def, tupleElement};
                            //auto decl = c::declaration(*def.closureType, name);
                            // TODO: Solve the problem with `struct closure_type` vs `closure_type`.
                            auto decl = c::declaration(c::structure(*def.closureType), name);
                            blockResult.declarations.push_back(decl);
                            blockResult.resolved.push_back(CompleteValue{newFun});

                            // TODO: This will complicate things with passing functions as arguments in the future.
                            // This is done only because the closure type needs to be defined.
                            // I should find a way to do this without fully defining the function.
                            ctx.defineFunction(def);

                            return {};

                        } || target::result{} <<= esl::unite_results <<=
                            [] (auto value) { return std::move(value).template get<sem::value::Function>(); } ||
                            target::tiny_vector{} <<= std::move(values);

                    } | [&, i = i] (auto const &) -> esl::result<void> {
                        // Compile-time value:
                        // This only happens when there is only one possible return value independent from any runtime conditions.
                        // Update: Nope, this also happens when there is a certain comp-time value return
                        // but it's after some possible run-time value returns. In such cases, the result value needs
                        // to be set to this comp-time value up front.
                        if (values.size() > 1) // Implementation error.
                            return esl::result_error{"Returning multiple values in a compile-time block return."};
                        if (values.size() == 0)
                            return {}; // Returning void.
                        auto const & value = values.front();
                        blockResult.resolved.push_back(value);
                        blockResult.returns.emplace_back(i, value);
                        blockResult.declarations.push_back("");

                        // TODO: What about arrays? (value copy...)
                        // Well, they should be returned as pointers, so I don't think anything special needs to be done.
                        // (They are only copied when returned from a function.)
                        return {};

                    } || target::category{} <<= interface::returnedValuesType <<= values;

                } | [&] (CompleteType const & type) {
                    return [&] (auto transl) -> esl::result<void> {
                        // A run-time value:
                        auto decl = c::declaration(transl, name);
                        blockResult.declarations.push_back(decl);
                        blockResult.resolved.push_back(TypedExpression{
                            .type       = type,
                            .expression = tupleElement
                        });
                        return {};

                    } || target::result{} <<= interface::translateType || target::category{} <<= type;

                } || target::category{} <<= entry;

                if (!result) return result.error();
            }

            return blockResult;
        }

    }

    ExpressionProcessingResult node::Block::processExpression (context::Main & outerScope) const {
        context::Branching branching;
        auto blockScope = outerScope.makeBranchingChild(branching);

        auto tupleVar = c::tupleVariableName(c::id(outerScope.nextId()));

        return [] (NoReturn) -> ExpressionProcessingResult {
            return esl::result_error{"Block expression never returns."};

        } | [&] (BlockResult blockResult) -> ExpressionProcessingResult {
            if (!blockResult.always)
                return esl::result_error{"Block expression does not always return."};
                // Note: This actually includes the case when it never returns.
                // Update: Does it really? The "never" case should be handled by the NoReturn overload above.

            // Fully compile-time block expression:
            if (!blockResult.runtime) {
                esl::tiny_vector<ResolvedValue> result;
                for (auto const & entry: blockResult.returned) {
                    auto returnedResult = entry.template get<ReturnedValues>();
                    if (!returnedResult) // Implementation error.
                        return esl::result_error{"Unknown value of a compile-time return."};
                    auto const & returned = *returnedResult;
                    if (returned.size() == 0)
                        return {}; // Returning void.
                    if (returned.size() > 1) // Implementation error.
                        return esl::result_error{"More than one compile-time return."};
                    result.push_back(returned.front());
                }
                return result;
            }

            // At least partially run-time block expression:
            return [&] (auto blockResult) -> ExpressionProcessingResult {
                auto head = c::blockExpressionBegin(tupleVar);
                auto ret  = c::indented(c::blockExpressionReturn());
                auto end  = c::statement(c::blockExpressionEnd());
                std::vector<std::string> compReturns;
                compReturns.reserve(blockResult.returns.size());
                for (auto const & [i, val]: blockResult.returns) {
                    auto tr = interface::translateValue(blockScope) || target::category{} <<= val;
                    if (!tr) return tr.error();
                    compReturns.push_back(c::indented(c::statement(c::returnValue(i, tr->expression))));
                    auto trt = interface::translateType || target::category{} <<= tr->type;
                    if (!trt) return trt.error();
                    blockResult.declarations[i] = c::declaration(*trt, c::tupleElementName(i));
                }
                auto rets = c::join("", compReturns);
                auto init = c::indented(c::returnInitFromDeclarations(blockResult.declarations));

                /***
                __auto_type <tupvar> = ({
                    __label__ ret;
                    struct result {
                        <type1> e0;
                        <type2> e1;
                        // ...
                    } result;
                    result.e<i> = <compvalI> # for every comp-time returns
                    <body>
                    ret: result;
                });
                ***/
                outerScope.insertStatement(head);
                outerScope.insertStatement(init);
                outerScope.insertStatement(rets);
                outerScope.mergeChild(blockScope);
                outerScope.insertStatement(ret);
                outerScope.insertStatement(end);

                return blockResult.resolved;
            } || target::result{} <<= processBlockExpression(outerScope, &tupleVar, blockResult.returned);

        } || target::optional_result{} <<= processBlock(blockScope, statements);
    }

    namespace {

        void emulationStep (context::Main & ctx) {
            auto const & gens = ctx.global.getGenerators();

            ctx.insertStatement(c::indented(c::inlineComment("Evaluate:")));
            for (auto const & [i, gen]: esl::enumerate(gens)) {
                auto eval =
                    c::statement(c::definition(
                        c::floatingType(),
                        std::string{} + "sample_" + std::to_string(i),
                        c::tupleElement(c::inlineCall(gen.function, gen.closure + (gen.time ? ", time" : "")), 0)
                    ));

                /***
                sample_<i> = <generator>(time); // Float (Int) generator
                sample_<i> = <generator>();     // Float ()    generator
                ...
                ***/
                ctx.insertStatement(c::indented(eval));
            }

            // TODO: Use c::bufferData and c::bufferOffset.

            ctx.insertStatement(c::indented(c::inlineComment("Write:")));
            for (auto const & [i, gen]: esl::enumerate(gens)) {
                auto write =
                    c::statement(c::assignment(
                        "sample_" + std::to_string(i),
                        c::arraySubscript(
                            c::memberAccess(gen.buffer, "data"),
                            c::mod(
                                c::expression(c::add(c::memberAccess(gen.buffer, "offset"), c::integralLiteral(1))),
                                c::integralLiteral(gen.size)
                            )
                        )
                    ));

                /***
                <buff>.data[(<buff>.offset + 1) % <size>] = sample_<i>;
                <buff>.data[(<buff>.offset + 1) % <size>] = sample_<i>;
                ...
                ***/
                ctx.insertStatement(c::indented(write));
            }

            ctx.insertStatement(c::indented(c::inlineComment("Step:")));
            for (auto const & gen: gens) {
                // TODO: Use the constructs from translation.hpp.
                auto step =
                    c::statement(c::assignment(
                        c::mod(
                            c::expression(c::add(c::memberAccess(gen.buffer, "offset"), c::integralLiteral(1))),
                            c::integralLiteral(gen.size)
                        ),
                        c::memberAccess(gen.buffer, "offset")
                    ));

                /***
                <buff>.offset = (<buff>.offset + 1) % <size>;
                ...
                ***/
                ctx.insertStatement(c::indented(step));
            }
        }

        void emulationLoop (context::Main & ctx) {
            auto newLine = c::newLine();
            // Handling a stop signal (^C):
            ctx.global.insertFunction(esl::reindent(4 * 4, "", newLine, R"code(
                volatile bool cth_stop = false; // TODO: Should I use sig_atomic_t instead?
                void cth_stop_handler (int _) {
                    cth_stop = true;
                }
            )code"));

            ctx.insertStatement(esl::reindent(4 * 4, "", newLine, R"code(
                int time = 0; // samples (TODO: Should I start further away from zero?)
                double tick_time  = 1 / sample_rate; // ms

                signal(SIGINT, cth_stop_handler);

                while (!cth_stop) {
                    clock_t start, end;

                    start = clock();

            )code"));

            emulationStep(ctx);

            ctx.insertStatement(esl::reindent(4 * 4, "", newLine, R"code(
                    ++time;

                    end = clock();

                    double elapsed = ((double) (end - start)) / CLOCKS_PER_SEC * 1000; // ms
                    double remains = tick_time - elapsed;
                    if (remains > 0) {
            )code"));

            auto wait = platform == Platform::windows
                ? "Sleep(remains);"
                : "sleep(remains / 1000);";

            ctx.insertStatement(c::indented(wait, 2));

            ctx.insertStatement(esl::reindent(4 * 4, "", newLine, R"code(
                    }
                }

            )code"));
        }

        void emulationDebug (context::Main & ctx) {
            auto newLine = c::newLine();
            auto const & gens = ctx.global.getGenerators();
            ctx.insertStatement(c::inlineComment("Debug:"));
            for (auto const & gen: gens) {
                // TODO: Use the constructs from translation.hpp.
                auto debug =
                    "printf(\"Buffer `" + gen.buffer + "` stopped at %i.\\n\", " + gen.buffer + ".offset);" + newLine +
                    "for (int i = 0; i < " + c::integralLiteral(gen.size) + "; ++i) {" + newLine +
                    "    printf(\"%f\\n\", " + gen.buffer + ".data[i]);" + newLine +
                    "}";

                /***
                printf("Buffer `<buff>` stopped at %i.\n", <buffval>.offset);
                for (int i = 0; i < <size>; ++i) {
                    printf("%f\n", <bufval>.data[i]);
                }
                ...
                ***/
                ctx.insertStatement(debug);
            }
        }

        void emulationSuccess (context::Main & ctx) {
            auto newLine = c::newLine();
            ctx.insertStatement(esl::reindent(4 * 4, "", newLine, R"code(
                return 0;
            )code"));
        }

    }

    ExpressionProcessingResult node::Block::processProgram (context::Main & mainScope) const {
        context::Branching branching;
        auto initScope  = mainScope.makeBranchingChild(branching);
        auto blockScope = initScope.makeBranchingChild(branching);

        // TODO... Ignoring any initialization return value for now.
        auto result = [&] (NoReturn) -> ExpressionProcessingResult {
            return esl::init<esl::tiny_vector>(
                ResolvedValue{CompleteValue{sem::value::Bool{true}}}
            );

        } | [&] (BlockResult blockResult) -> ExpressionProcessingResult {
            return [&] (auto blockResult) -> ExpressionProcessingResult {
                return blockResult.resolved;
            } || target::result{} <<= processBlockExpression(mainScope, nullptr, blockResult.returned);

        } || target::optional_result{} <<= processBlock(blockScope, statements);

        //auto init        = c::returnInitFromDeclarations(blockResult.declarations, true);
        auto init        = c::returnInitFromDeclarations(std::vector<std::string>{}, true);
        auto begin       = c::blockBegin();
        auto end         = c::end();
        auto ret         = c::mainReturn();
        //auto indent    = c::indentation();
        auto newLine     = c::newLine();
        auto initFunName = c::global("init");
        auto initHead    = c::inlineFunctionBegin("void", initFunName);
        auto inits       = c::join("", mainScope.global.initializations);

        /***
        struct result {
            <type1> e0;
            <type2> e1;
            // ...
        } result;
        {
            <body>
        }
        ret:
        ***/
        initScope.insertStatement(c::inlineComment("Initialization:"));
        initScope.insertStatement(init);
        initScope.insertStatement(begin);
        initScope.mergeChild(blockScope);
        initScope.insertStatement(end);
        initScope.insertStatement(ret);
        initScope.insertStatement("printf(\"Synthesizer initialized.\\n\"); " + c::inlineComment("TODO"));

        auto initLocal = c::join("", initScope.statements);
        auto initAlloc = c::join("", initScope.function.data);
        auto initFun = c::join("",
            initHead,
            c::indented(c::join("",
                inits,
                initAlloc,
                initLocal
            )),
            end
        );
        mainScope.global.insertFunction(initFun);

        // TODO: Initialization output.

        auto srate = "double sample_rate = " + std::to_string(sampleRate) + "; // kHz";

        if (synthOutput == SynthOutput::debug) {
            mainScope.insertStatement(c::statement(c::inlineCall(initFunName)));
            mainScope.insertStatement(srate);
            emulationLoop(mainScope);
            emulationDebug(mainScope);
            emulationSuccess(mainScope);

        } else { // Note: SynthOutput::dynamic not supported yet.
            mainScope.insertStatement(srate);
            emulationStep(mainScope);
            emulationSuccess(mainScope);
        }

        return result;
    }

    StatementProcessingResult node::Block::processStatement (context::Main & outerScope) const {
        auto blockScope = outerScope.makeScopeChild();

        return [&] (NoReturn) -> StatementProcessingResult {
            return NoReturn{};

        } | [&] (BlockResult blockResult) -> StatementProcessingResult {

            if (blockResult.runtime) {
                // At least partially run-time block statement:

                auto head = c::blockBegin();
                auto end  = c::end();

                /***
                {
                    <body>
                }
                ***/
                outerScope.insertStatement(head);
                outerScope.mergeChild(blockScope);
                outerScope.insertStatement(end);
            }

            return sem::Return{
                .returned = blockResult.returned,
                .always   = blockResult.always
            };

        } || target::optional_result{} <<= processBlock(blockScope, statements);
    }

    NameExtractionResult node::Block::extractNames (context::Lookup & outerScope) const {
        auto nestedScope = outerScope.makeChild();
        return esl::insert_nested_cat || target::result{} <<=
            esl::unite_results <<=
            interface::extractNames(nestedScope) || target::nested<target::component_vector, target::category>{} <<=
            statements;
    }

    TypeNameExtractionResult node::Block::extractTypeNames (context::Lookup & outerScope) const {
        auto nestedScope = outerScope.makeChild();
        return esl::insert_nested_cat || target::result{} <<=
            esl::unite_results <<=
            interface::extractTypeNames(nestedScope) || target::nested<target::component_vector, target::category>{} <<=
            statements;
    }

}
