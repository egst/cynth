#include "syn/nodes/incomplete/statements/return.hpp"
#include "syn/nodes/statements.hpp" // To complete circular dependencies.

#include "esl/category.hpp"
#include "esl/string.hpp"
#include "esl/lift.hpp"
#include "esl/sugar.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/nodes.hpp"
#include "sem/compound.hpp"

namespace cynth::syn {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::DisplayResult;
    using interface::NameExtractionResult;
    using interface::StatementProcessingResult;
    using interface::TypeNameExtractionResult;
    using sem::CompleteValue;
    using sem::TypedExpression;
    using sem::Returned;
    using sem::ReturnVector;

    DisplayResult node::Return::display () const {
        return "return " + (interface::display || target::category{} <<= *value);
    }

    StatementProcessingResult node::Return::processStatement (context::Main & ctx) const {
        std::size_t i = 0; // TODO: This would be better expressed with a range-based for loop and esl::enumerate.
        bool runtime = false;

        return [&, runtime] (auto const & result) -> sem::Return {
            if (runtime || !ctx.empty()) {
                auto jump = c::returnJump();

                /***
                goto ret;
                ***/
                ctx.insertStatement(jump);
            }
            // Otherwise, a) there were no run-time operations or values used
            // and b) the return statement terminates processing of any further statements in the current block,
            // so there is no need to insert a goto statement. If it was inserted,
            // the whole block couln't be used as a comp-time value, because it has some local statements.

            return {
                .returned = result,
                .always   = true
            };

        } || target::result{} <<= [&] (auto const & x) {

            // TODO: Lift can't handle nested vectors and optional results for some reason (hence the two nested lambda calls).
            return [&] (CompleteValue const & value) {
                return [&] (sem::value::Function const & fun) -> Returned {
                    // Partially run-time function:
                    //auto closure = fun.closureVariable.value_or("{}");
                    auto closure = fun.closureVariable.value_or(c::emptyValue());
                    auto branch  = ctx.branching.nextBranch();
                    auto ret     = c::returnFunction(i, branch, closure);

                    /***
                    result.e<i>.branch = <branch>;
                    result.e<i>.data.v<branch> = <ctx>;
                    ***/
                    ctx.insertStatement(ret);

                    ++i;
                    return esl::init<ReturnVector>(CompleteValue{sem::value::Function{fun.definition}});

                } | [&] (auto const &) -> Returned {
                    // Comp-time value:
                    ++i;
                    return esl::init<ReturnVector>(value);

                } || target::category{} <<= value;

            } | [&] (TypedExpression const & expr) -> Returned {
                // Run-time value:
                auto ret = c::returnValue(i, expr.expression);
                //runtime = true; // TODO: Was this removed at some point? Why?

                /***
                result.e<i> = <expr>;
                ***/
                ctx.insertStatement(ret);

                ++i;
                return expr.type;

            } || target::nested<target::tiny_vector, target::category>{} <<= x;

        } || target::result{} <<=
            interface::processExpression(ctx) || target::category{} <<=
            *value;
    }

    NameExtractionResult node::Return::extractNames (context::Lookup & ctx) const {
        return interface::extractNames(ctx) || target::category{} <<= *value;
    }

    TypeNameExtractionResult node::Return::extractTypeNames (context::Lookup & ctx) const {
        return interface::extractTypeNames(ctx) || target::category{} <<= *value;
    }

}
