#include "syn/nodes/incomplete/expressions/subscript.hpp"
#include "syn/nodes/expressions.hpp" // To complete circular dependencies.

#include "esl/category.hpp"
#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "sem/types.hpp"
#include "sem/values.hpp"
#include "syn/nodes/common/array_nodes.hpp"

namespace cynth::syn {

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;
    using interface::TargetResolutionResult;
    using sem::CompleteValue;
    using sem::ResolvedValue;
    using sem::TypedExpression;
    using sem::TypedTargetExpression;
    using sem::ArrayAllocation;

    DisplayResult node::Subscript::display () const {
        using Target = target::nested<target::component_vector, target::category>;
        return
            (interface::display || target::category{} <<= *container) + " [" +
            esl::join(", ", interface::display || Target{} <<= location) + "]";
    }

    ExpressionProcessingResult node::Subscript::processExpression (context::Main & ctx) const {
        return [&] (auto elemsResult, auto container) {
            return [&] (sem::type::Array const & type) -> ExpressionProcessingResult {
                if (elemsResult.arraySize == 0) {
                    // Whole array:
                    return [&] (CompleteValue const & container) -> ExpressionProcessingResult {
                        // Comp-time container:
                        auto arrayResult = container.template get<sem::value::Array>();
                        if (!arrayResult) return arrayResult.error();
                        auto arrayType = arrayResult->valueType;
                        arrayType.constant = false;
                        interface::loseConstness || target::category{} <<= *arrayType.type;
                        return [&] (ArrayAllocation * alloc) -> ExpressionProcessingResult {
                            auto & copyAlloc = ctx.function.storeValue(*alloc);
                            return esl::init<esl::tiny_vector>(ResolvedValue{CompleteValue{
                                sem::value::Array{&copyAlloc, arrayType}
                            }});

                        } | [&] (std::string const & alloc) -> ExpressionProcessingResult {
                            return [&] (auto translType) {
                                auto allocName = array_nodes::arrayAllocation(ctx, translType, elemsResult.arraySize);
                                array_nodes::bulkArrayInitialization(ctx, allocName, alloc);
                                return esl::init<esl::tiny_vector>(ResolvedValue{CompleteValue{
                                    sem::value::Array{allocName, arrayType}
                                }});

                            } || target::result{} <<= interface::translateTypeSpecifier || target::category{} <<=
                                *type.type;

                        } || target::variant{} <<= arrayResult->allocation;

                    } | [&] (TypedExpression const & container) -> ExpressionProcessingResult {
                        // Run-time container:
                        auto typeResult = container.type.template get<sem::type::Array>();
                        if (!typeResult)
                            return esl::result_error{"Only arrays can be subscripted."};
                        auto arrayType = *typeResult;
                        arrayType.constant = false;
                        interface::loseConstness || target::category{} <<= *arrayType.type;
                        return [&] (auto translType) {
                            auto allocName = array_nodes::arrayAllocation(ctx, translType, elemsResult.arraySize);
                            array_nodes::bulkArrayInitialization(ctx, allocName, container.expression);
                            return esl::init<esl::tiny_vector>(ResolvedValue{CompleteValue{
                                sem::value::Array{allocName, arrayType}
                            }});

                        } || target::result{} <<= interface::translateTypeSpecifier || target::category{} <<= *type.type;

                    } || target::category{} <<= container;

                } else if (elemsResult.arraySize == 1) {
                    // A single element:
                    auto index = elemsResult.values.front();
                    return esl::init<esl::tiny_vector> || target::result{} <<=
                        array_nodes::processSubscript(ctx, index, container);

                } else {
                    // A subarray: (unsupported yet)
                    return esl::result_error{"Subarray subscripts are nut supported yet."};
                    // Note: This shouldn't be too complicated, but it's not really essential right now.
                }

            } | [&] (sem::type::In const & type) -> ExpressionProcessingResult {
                if (elemsResult.arraySize != 0)
                    return esl::result_error{"Input types can only be subscripted with an empty subscript."};

                return [&] (CompleteValue const & container) -> ExpressionProcessingResult {
                    // Comp-time container:
                    auto inResult = container.template get<sem::value::In>();
                    if (!inResult) return inResult.error();
                    return esl::init<esl::tiny_vector>(ResolvedValue{TypedExpression{
                        .type       = *type.type,
                        .expression = inResult->allocation
                    }});

                } | [&] (TypedExpression const & container) -> ExpressionProcessingResult {
                    // Run-time container:
                    auto value = c::dereference(container.expression);
                    return esl::init<esl::tiny_vector>(ResolvedValue{TypedExpression{
                        .type       = *type.type,
                        .expression = value
                    }});

                } || target::category{} <<= container;

            } | [] (auto const &) -> ExpressionProcessingResult {
                return esl::result_error{"Only arrays and input values can be subscripted."};

            } || target::category{} <<= interface::resolvedValueType(container);

        } || target::result{} <<= args(
            array_nodes::processElements(ctx, location),
            esl::single || target::result{} <<=
                interface::processExpression(ctx) || target::category{} <<= *container
        );
    }

    TargetResolutionResult node::Subscript::resolveTarget (context::Main & ctx) const {
        return [&] (auto elemsResult, auto container) {
            return [&] (sem::type::Array const & type) -> TargetResolutionResult {
                if (type.constval())
                    return esl::result_error{"Cannot assign to constant array values."};
                if (elemsResult.arraySize == 0) {
                    // Whole array:
                    auto lvalue = container.expression;
                    /***
                    <arr>
                    ***/
                    return esl::init<esl::tiny_vector>(TypedTargetExpression{
                        .type       = type,
                        //.size       = type.size,
                        .expression = lvalue
                    });

                } else if (elemsResult.arraySize == 1) {
                    // A single element:
                    return [&] (auto index) -> TargetResolutionResult {
                        // Note: There is no implicit conversion of subscript indices (for now):
                        if (!(interface::sameType(sem::type::Int{}) || target::category{} <<= index.type))
                            return esl::result_error{"Subscript index must be an integer."};
                        auto lvalue = c::arraySubscript(container.expression, index.expression);
                        /***
                        <arr>[<i>]
                        ***/
                        return esl::init<esl::tiny_vector>(TypedTargetExpression{
                            .type       = *type.type,
                            //.size       = 1,
                            .expression = lvalue
                        });

                    } || target::result{} <<=
                        interface::translateResolvedValue(ctx) || target::category{} <<= elemsResult.values.front();

                } else {
                    // A subarray: (unsupported yet)
                    return esl::result_error{"Assignment to a subarray is not supported yet."};
                    // Note: Subarray of consecutive elements could be relatively simple to implement,
                    // but a generic subarray would require a slightly more complex interface.
                }

            } | [&] (sem::type::Out const & type) -> TargetResolutionResult {
                if (elemsResult.arraySize != 0)
                    return esl::result_error{"Output typed targets can only be subscripted with an empty subscript."};

                auto lvalue = c::dereference(container.expression);
                /***
                *<out>
                ***/
                return esl::init<esl::tiny_vector>(TypedTargetExpression{
                    .type       = *type.type,
                    //.size       = 1,
                    .expression = lvalue
                });

            } | [] (auto const &) -> TargetResolutionResult {
                return esl::result_error{"Only arrays and output targets can be subscripted."};

            } || target::category{} <<= container.type;

        } || target::result{} <<= args(
            array_nodes::processElements(ctx, location),
            interface::translateResolvedValue(ctx) || target::result{} <<=
                esl::single || target::result{} <<=
                interface::processExpression(ctx) || target::category{} <<= *container
        );
    }

}

/*
    display_result syn::node::subscript::display () const {
        return interface::display(container) + " [" + util::join(", ", interface::display(location)) + "]";
    }

    // TODO: This implementation only allows the simple c-like subscript a[i] with a single index on a single (non-tuple) value.
    syn::evaluation_result syn::node::Subscript::evaluate (sem::context & ctx) const {
        //syn::evaluate(container);
        //return sem::get<bool>(lift::single_evaluation{sem::convert(sem::type::Bool{})}(util::single(location)));
        auto location_result = sem::array_elems(ctx, location);
        if (!location_result)
            return syn::make_evaluation_result(location_result.error());
        auto [locations, location_type] = *location_result;

        // TODO: Check the location_type?
        // Simplification: only the first location is taken.
        // (the util::single(locastions) part is the simplification.
        // lift::result{util::single} corresponds to an intended behaviour, not a simplification.)
        //auto r = sem::convert(sem::type::Int{})(util::single(locations));

        auto index_result = sem::get<integral> (
            sem::convert(ctx)(sem::type::Int{})(lift::result{util::single}(util::single(locations)))
        );
        if (!index_result)
            return syn::make_evaluation_result(index_result.error());
        integral index = *index_result;

        // Simplification: only the first container is taken:
        using result_type = result<tuple_vector<sem::value::complete>>;
        auto result = lift::single_evaluation{util::overload {
            [&ctx, index] (sem::value::Array const & a) -> result_type {
                integral size = a.size;
                if (index >= size)
                    return {result_error{"Subscript index out of bounds."}};
                if (index < 0)
                    return {result_error{"Negative subscripts not supported yet."}};
                auto results = sem::convert(ctx)(a.value->value[index], a.type);
                if (!results)
                    return results.error();
                return util::unite_results(*results);
            },
            [] (auto const &) -> result_type {
                return {result_error{"Cannot subscript a non-array value."}};
            }
        }} (util::single(syn::evaluate(ctx)(container)));
        if (!result)
            return syn::make_evaluation_result(result.error());

        return lift::tuple_vector{make_result}(*result);
    }

    syn::target_eval_result syn::node::Subscript::eval_target (sem::context & ctx) const {
        // Only the first container is taken. (This is the intended behaviour, not a simplification.)
        auto container_result = lift::result{util::single}(syn::eval_target(ctx)(container));
        if (!container_result)
            return syn::make_target_eval_result(container_result.error());

        auto location_result = sem::array_elems(ctx, location);
        if (!location_result)
            return syn::make_target_eval_result(location_result.error());
        auto [locations, location_type] = *std::move(location_result);

        if (locations.size() == 0)
            return syn::make_target_eval_result(sem::any_target{sem::subscript_target {
                .container = *container_result,
                .location  = {}
            }});

        // Simplification: Only the first location is taken.
        auto index_result = util::unite_results (
            sem::convert(ctx)(sem::type::Int{})(lift::component{util::single}(locations))
        );
        if (!index_result)
            return syn::make_target_eval_result(index_result.error());

        return syn::make_target_eval_result(sem::any_target{sem::subscript_target {
            .container = *container_result,
            .location  = *index_result
        }});
    }
*/
