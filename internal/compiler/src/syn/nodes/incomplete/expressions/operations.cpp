#include "syn/nodes/incomplete/expressions/operations.hpp"
#include "syn/nodes/expressions.hpp" // To complete circular dependencies.

// TODO: Cleanup when done.

#include "esl/category.hpp"
#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"

#include "config.hpp"
#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "interface/values.hpp"
#include "sem/compound.hpp"
#include "sem/operations.hpp"
#include "sem/translation.hpp"
#include "sem/values.hpp"
#include "syn/nodes/common/array_nodes.hpp"

namespace cynth::syn {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;
    using interface::NameExtractionResult;
    using interface::TypeNameExtractionResult;
    using interface::TargetResolutionResult;
    using sem::CompleteValue;
    using sem::ResolvedValue;
    using sem::TypedExpression;

    namespace {

        template <typename Type, typename Value>
        constexpr auto bin = [] (context::Main & ctx, auto const & compOp, auto const & runOp) {
            return [&] (ResolvedValue firstArg, ResolvedValue secondArg) {
                return [&] (CompleteValue firstArg, CompleteValue secondArg) {
                    // Both comp-time arguments:
                    return [&] (Value firstArg, Value secondArg) -> esl::result<ResolvedValue> {
                        auto result = compOp(firstArg.get(), secondArg.get());
                        return ResolvedValue{CompleteValue{Value{result}}};

                    } | [] (auto, auto) -> esl::result<ResolvedValue> {
                        // TODO: Separate the case of two different numeric types for a better error message.
                        return esl::result_error{"Invalid operands in a binary operator"};

                    } || target::category{} <<= args(std::move(firstArg), std::move(secondArg));

                } | [&] (auto firstArg, auto secondArg) {
                    // At least one run-time argument:
                    return [&] (auto firstArg, auto secondArg) {
                        return [&] (Type, Type) -> esl::result<ResolvedValue> {
                            auto result = runOp(Type{}, firstArg.expression, secondArg.expression);
                            return ResolvedValue{TypedExpression{Type{}, result}};

                        } | [] (auto, auto) -> esl::result<ResolvedValue> {
                            // TODO: Separate the case of two different numeric types for a better error message.
                            return esl::result_error{"Invalid operands in a binary operator"};

                        } || target::category{} <<= args(firstArg.type, secondArg.type);

                    } || target::result{} <<= args(
                        interface::translateDirectResolvedValue(ctx)(firstArg),
                        interface::translateDirectResolvedValue(ctx)(secondArg)
                    );

                } || target::category{} <<= args(std::move(firstArg), std::move(secondArg));
            };
        };

        constexpr auto binArith = [] (context::Main & ctx, auto const & compOp, auto const & runOp) {
            return [&] (ResolvedValue firstArg, ResolvedValue secondArg) {
                return [&] (CompleteValue firstArg, CompleteValue secondArg) {
                    // Both comp-time arguments:
                    return [&] <interface::numericValue Value> (
                        Value firstArg, Value secondArg
                    ) -> esl::result<ResolvedValue> {
                        auto result = compOp(firstArg.get(), secondArg.get());
                        return ResolvedValue{CompleteValue{Value{result}}};

                    } | [] (auto, auto) -> esl::result<ResolvedValue> {
                        // TODO: Separate the case of two different numeric types for a better error message.
                        return esl::result_error{"Invalid operators in a binary arithmetic operator."};

                    } || target::category{} <<= args(std::move(firstArg), std::move(secondArg));

                } | [&] (auto firstArg, auto secondArg) {
                    // At least one run-time argument:
                    return [&] (auto firstArg, auto secondArg) {
                        return [&] <interface::numericType Type> (Type, Type) -> esl::result<ResolvedValue> {
                            auto result = runOp(Type{}, firstArg.expression, secondArg.expression);
                            return ResolvedValue{TypedExpression{Type{}, result}};

                        } | [] (auto, auto) -> esl::result<ResolvedValue> {
                            // TODO: Separate the case of two different numeric types for a better error message.
                            return esl::result_error{"Invalid operators in a binary arithmetic operator."};

                        } || target::category{} <<= args(firstArg.type, secondArg.type);

                    } || target::result{} <<= args(
                        interface::translateDirectResolvedValue(ctx)(firstArg),
                        interface::translateDirectResolvedValue(ctx)(secondArg)
                    );

                } || target::category{} <<= args(std::move(firstArg), std::move(secondArg));
            };
        };

        constexpr auto unArith = [] (context::Main & ctx, auto const & compOp, auto const & runOp) {
            return [&] (ResolvedValue arg) {
                return [&] (CompleteValue arg) {
                    // Comp-time argument:
                    return [&] <interface::numericValue Value> (Value arg) -> esl::result<ResolvedValue> {
                        auto result = compOp(arg.get());
                        return ResolvedValue{CompleteValue{Value{result}}};

                    } | [] (auto) -> esl::result<ResolvedValue> {
                        return esl::result_error{"Invalid operand in a unary arithmetic operator."};

                    } || target::category{} <<= std::move(arg);

                } | [&] (auto arg) {
                    // Run-time argument:
                    return [&] (auto arg) {
                        return [&] <interface::numericType Type> (Type) -> esl::result<ResolvedValue> {
                            auto result = runOp(Type{}, arg.expression);
                            return ResolvedValue{TypedExpression{Type{}, result}};

                        } | [] (auto) -> esl::result<ResolvedValue> {
                            return esl::result_error{"Invalid operand in a unary arithmetic operator."};

                        } || target::category{} <<= arg.type;

                    } || target::result{} <<= interface::translateDirectResolvedValue(ctx)(arg);

                } || target::category{} <<= std::move(arg);
            };
        };

        constexpr auto binComp = [] (context::Main & ctx, auto const & compOp, auto const & runOp) {
            return [&] (ResolvedValue firstArg, ResolvedValue secondArg) {
                return [&] (CompleteValue firstArg, CompleteValue secondArg) {
                    // Both comp-time arguments:
                    return [&] <interface::simpleValue Value> (
                        Value firstArg, Value secondArg
                    ) -> esl::result<ResolvedValue> {
                        auto result = compOp(firstArg.get(), secondArg.get());
                        return ResolvedValue{CompleteValue{sem::value::Bool{result}}};

                    } | [] (auto, auto) -> esl::result<ResolvedValue> {
                        return esl::result_error{"Invalid operands in a comparison operator."};

                    } || target::category{} <<= args(std::move(firstArg), std::move(secondArg));

                } | [&] (auto firstArg, auto secondArg) {
                    // At least one run-time argument:
                    return [&] (auto firstArg, auto secondArg) {
                        return [&] <interface::simpleType Type> (Type, Type) -> esl::result<ResolvedValue> {
                            auto result = runOp(Type{}, firstArg.expression, secondArg.expression);
                            return ResolvedValue{TypedExpression{sem::type::Bool{}, result}};

                        } | [] (auto, auto) -> esl::result<ResolvedValue> {
                            return esl::result_error{"Invalid operands in a comparison operator."};

                        } || target::category{} <<= args(firstArg.type, secondArg.type);

                    } || target::result{} <<= args(
                        interface::translateDirectResolvedValue(ctx)(firstArg),
                        interface::translateDirectResolvedValue(ctx)(secondArg)
                    );

                } || target::category{} <<= args(std::move(firstArg), std::move(secondArg));
            };
        };

        constexpr auto binLog = [] (context::Main & ctx, auto const & compOp, auto const & runOp) {
            return [&] (ResolvedValue firstArg, ResolvedValue secondArg) {
                return [&] (CompleteValue firstArg, CompleteValue secondArg) {
                    // Both comp-time arguments:
                    return [&] (sem::value::Bool firstArg, sem::value::Bool secondArg) -> esl::result<ResolvedValue> {
                        auto result = compOp(firstArg.get(), secondArg.get());
                        return ResolvedValue{CompleteValue{sem::value::Bool{result}}};

                    } | [] (auto, auto) -> esl::result<ResolvedValue> {
                        return esl::result_error{"Invalid operands in a binary logical operator."};

                    } || target::category{} <<= args(std::move(firstArg), std::move(secondArg));

                } | [&] (auto firstArg, auto secondArg) {
                    // At least one run-time argument:
                    return [&] (auto firstArg, auto secondArg) {
                        return [&] (sem::type::Bool, sem::type::Bool) -> esl::result<ResolvedValue> {
                            auto result = runOp(sem::type::Bool{}, firstArg.expression, secondArg.expression);
                            return ResolvedValue{TypedExpression{sem::type::Bool{}, result}};

                        } | [] (auto, auto) -> esl::result<ResolvedValue> {
                            return esl::result_error{"Invalid operands in a binary logical operator."};

                        } || target::category{} <<= args(firstArg.type, secondArg.type);

                    } || target::result{} <<= args(
                        interface::translateDirectResolvedValue(ctx)(firstArg),
                        interface::translateDirectResolvedValue(ctx)(secondArg)
                    );

                } || target::category{} <<= args(std::move(firstArg), std::move(secondArg));
            };
        };

        constexpr auto unLog = [] (context::Main & ctx, auto const & compOp, auto const & runOp) {
            return [&] (ResolvedValue arg) {
                return [&] (CompleteValue arg) {
                    // Both comp-time arguments:
                    return [&] (sem::value::Bool arg) -> esl::result<ResolvedValue> {
                        auto result = compOp(arg.get());
                        return ResolvedValue{CompleteValue{sem::value::Bool{result}}};

                    } | [] (auto) -> esl::result<ResolvedValue> {
                        return esl::result_error{"Invalid operand in a unary logical operator."};

                    } || target::category{} <<= args(std::move(arg));

                } | [&] (auto arg) {
                    // At least one run-time argument:
                    return [&] (auto arg) {
                        return [&] (sem::type::Bool) -> esl::result<ResolvedValue> {
                            auto result = runOp(sem::type::Bool{}, arg.expression);
                            return ResolvedValue{TypedExpression{sem::type::Bool{}, result}};

                        } | [] (auto) -> esl::result<ResolvedValue> {
                            return esl::result_error{"Invalid operand in a unary logical operator."};

                        } || target::category{} <<= args(arg.type);

                    } || target::result{} <<= interface::translateDirectResolvedValue(ctx)(arg);

                } || target::category{} <<= args(std::move(arg));
            };
        };

    }

    //// Add ////

    DisplayResult node::Add::display () const {
        return
            "(" + (interface::display || target::category{} <<= *leftArgument) + " + " +
            (interface::display || target::category{} <<= *rightArgument) + ")";
    }

    ExpressionProcessingResult node::Add::processExpression (context::Main & ctx) const {
        return esl::unite_results || target::result{} <<=
            [&] (auto left, auto right) -> esl::result<ResolvedValue> {
                return binArith(ctx, sem::comptime::add, sem::runtime::add)(std::move(left), std::move(right));

            } || target::nested<target::result, target::tiny_vector>{} <<= args(
                interface::processExpression(ctx) || target::category{} <<= *leftArgument,
                interface::processExpression(ctx) || target::category{} <<= *rightArgument
            );
    }

    NameExtractionResult node::Add::extractNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    TypeNameExtractionResult node::Add::extractTypeNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractTypeNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractTypeNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    //// And ////

    DisplayResult node::And::display () const {
        return
            "(" + (interface::display || target::category{} <<= *leftArgument) + " && " +
            (interface::display || target::category{} <<= *rightArgument) + ")";
    }

    ExpressionProcessingResult node::And::processExpression (context::Main & ctx) const {
        return esl::unite_results || target::result{} <<=
            [&] (auto left, auto right) -> esl::result<ResolvedValue> {
                return binLog(ctx, sem::comptime::land, sem::runtime::land)(std::move(left), std::move(right));

            } || target::nested<target::result, target::tiny_vector>{} <<= args(
                interface::processExpression(ctx) || target::category{} <<= *leftArgument,
                interface::processExpression(ctx) || target::category{} <<= *rightArgument
            );
    }

    NameExtractionResult node::And::extractNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    TypeNameExtractionResult node::And::extractTypeNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractTypeNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractTypeNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    //// Div ////

    DisplayResult node::Div::display () const {
        return
            "(" + (interface::display || target::category{} <<= *leftArgument) + " / " +
            (interface::display || target::category{} <<= *rightArgument) + ")";
    }

    ExpressionProcessingResult node::Div::processExpression (context::Main & ctx) const {
        return esl::unite_results || target::result{} <<=
            [&] (auto left, auto right) -> esl::result<ResolvedValue> {
                return binArith(ctx, sem::comptime::div, sem::runtime::div)(std::move(left), std::move(right));

            } || target::nested<target::result, target::tiny_vector>{} <<= args(
                interface::processExpression(ctx) || target::category{} <<= *leftArgument,
                interface::processExpression(ctx) || target::category{} <<= *rightArgument
            );
    }

    NameExtractionResult node::Div::extractNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    TypeNameExtractionResult node::Div::extractTypeNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractTypeNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractTypeNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    //// Eq ////

    DisplayResult node::Eq::display () const {
        return
            "(" + (interface::display || target::category{} <<= *leftArgument) + " == " +
            (interface::display || target::category{} <<= *rightArgument) + ")";
    }

    ExpressionProcessingResult node::Eq::processExpression (context::Main & ctx) const {
        return esl::unite_results || target::result{} <<=
            [&] (auto left, auto right) -> esl::result<ResolvedValue> {
                return binComp(ctx, sem::comptime::eq, sem::runtime::eq)(std::move(left), std::move(right));

            } || target::nested<target::result, target::tiny_vector>{} <<= args(
                interface::processExpression(ctx) || target::category{} <<= *leftArgument,
                interface::processExpression(ctx) || target::category{} <<= *rightArgument
            );
    }

    NameExtractionResult node::Eq::extractNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    TypeNameExtractionResult node::Eq::extractTypeNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractTypeNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractTypeNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    //// Ge ////

    DisplayResult node::Ge::display () const {
        return
            "(" + (interface::display || target::category{} <<= *leftArgument) + " >= " +
            (interface::display || target::category{} <<= *rightArgument) + ")";
    }

    ExpressionProcessingResult node::Ge::processExpression (context::Main & ctx) const {
        return esl::unite_results || target::result{} <<=
            [&] (auto left, auto right) -> esl::result<ResolvedValue> {
                return binComp(ctx, sem::comptime::ge, sem::runtime::ge)(std::move(left), std::move(right));

            } || target::nested<target::result, target::tiny_vector>{} <<= args(
                interface::processExpression(ctx) || target::category{} <<= *leftArgument,
                interface::processExpression(ctx) || target::category{} <<= *rightArgument
            );
    }

    NameExtractionResult node::Ge::extractNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    TypeNameExtractionResult node::Ge::extractTypeNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractTypeNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractTypeNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    //// Gt ////

    DisplayResult node::Gt::display () const {
        return
            "(" + (interface::display || target::category{} <<= *leftArgument) + " > " +
            (interface::display || target::category{} <<= *rightArgument) + ")";
    }

    ExpressionProcessingResult node::Gt::processExpression (context::Main & ctx) const {
        return esl::unite_results || target::result{} <<=
            [&] (auto left, auto right) -> esl::result<ResolvedValue> {
                return binComp(ctx, sem::comptime::gt, sem::runtime::gt)(std::move(left), std::move(right));

            } || target::nested<target::result, target::tiny_vector>{} <<= args(
                interface::processExpression(ctx) || target::category{} <<= *leftArgument,
                interface::processExpression(ctx) || target::category{} <<= *rightArgument
            );
    }

    NameExtractionResult node::Gt::extractNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    TypeNameExtractionResult node::Gt::extractTypeNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractTypeNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractTypeNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    //// Le ////

    DisplayResult node::Le::display () const {
        return
            "(" + (interface::display || target::category{} <<= *leftArgument) + " <= " +
            (interface::display || target::category{} <<= *rightArgument) + ")";
    }

    ExpressionProcessingResult node::Le::processExpression (context::Main & ctx) const {
        return esl::unite_results || target::result{} <<=
            [&] (auto left, auto right) -> esl::result<ResolvedValue> {
                return binComp(ctx, sem::comptime::le, sem::runtime::le)(std::move(left), std::move(right));

            } || target::nested<target::result, target::tiny_vector>{} <<= args(
                interface::processExpression(ctx) || target::category{} <<= *leftArgument,
                interface::processExpression(ctx) || target::category{} <<= *rightArgument
            );
    }

    NameExtractionResult node::Le::extractNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    TypeNameExtractionResult node::Le::extractTypeNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractTypeNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractTypeNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    //// Lt ////

    DisplayResult node::Lt::display () const {
        return
            "(" + (interface::display || target::category{} <<= *leftArgument) + " < " +
            (interface::display || target::category{} <<= *rightArgument) + ")";
    }

    ExpressionProcessingResult node::Lt::processExpression (context::Main & ctx) const {
        return esl::unite_results || target::result{} <<=
            [&] (auto left, auto right) -> esl::result<ResolvedValue> {
                return binComp(ctx, sem::comptime::lt, sem::runtime::lt)(std::move(left), std::move(right));

            } || target::nested<target::result, target::tiny_vector>{} <<= args(
                interface::processExpression(ctx) || target::category{} <<= *leftArgument,
                interface::processExpression(ctx) || target::category{} <<= *rightArgument
            );
    }

    NameExtractionResult node::Lt::extractNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    TypeNameExtractionResult node::Lt::extractTypeNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractTypeNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractTypeNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    //// Minus ////

    DisplayResult node::Minus::display () const {
        return "(-" + (interface::display || target::category{} <<= *argument) + ")";
    }

    ExpressionProcessingResult node::Minus::processExpression (context::Main & ctx) const {
        return esl::unite_results || target::result{} <<=
            [&] (auto arg) -> esl::result<ResolvedValue> {
                return unArith(ctx, sem::comptime::minus, sem::runtime::minus)(std::move(arg));

            } || target::nested<target::result, target::tiny_vector>{} <<=
                interface::processExpression(ctx) || target::category{} <<= *argument;
    }

    NameExtractionResult node::Minus::extractNames (context::Lookup & ctx) const {
        return interface::extractNames(ctx) || target::category{} <<= *argument;
    }

    TypeNameExtractionResult node::Minus::extractTypeNames (context::Lookup & ctx) const {
        return interface::extractTypeNames(ctx) || target::category{} <<= *argument;
    }

    //// Mod ////

    DisplayResult node::Mod::display () const {
        return
            "(" + (interface::display || target::category{} <<= *leftArgument) + " % " +
            (interface::display || target::category{} <<= *rightArgument) + ")";
    }

    ExpressionProcessingResult node::Mod::processExpression (context::Main & ctx) const {
        return esl::unite_results || target::result{} <<=
            [&] (auto left, auto right) -> esl::result<ResolvedValue> {
                return binArith(ctx, sem::comptime::mod, sem::runtime::mod)(std::move(left), std::move(right));

            } || target::nested<target::result, target::tiny_vector>{} <<= args(
                interface::processExpression(ctx) || target::category{} <<= *leftArgument,
                interface::processExpression(ctx) || target::category{} <<= *rightArgument
            );
    }

    NameExtractionResult node::Mod::extractNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    TypeNameExtractionResult node::Mod::extractTypeNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractTypeNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractTypeNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    //// Mul ////

    DisplayResult node::Mul::display () const {
        return
            "(" + (interface::display || target::category{} <<= *leftArgument) + " * " +
            (interface::display || target::category{} <<= *rightArgument) + ")";
    }

    ExpressionProcessingResult node::Mul::processExpression (context::Main & ctx) const {
        return esl::unite_results || target::result{} <<=
            [&] (auto left, auto right) -> esl::result<ResolvedValue> {
                return binArith(ctx, sem::comptime::mul, sem::runtime::mul)(std::move(left), std::move(right));

            } || target::nested<target::result, target::tiny_vector>{} <<= args(
                interface::processExpression(ctx) || target::category{} <<= *leftArgument,
                interface::processExpression(ctx) || target::category{} <<= *rightArgument
            );
    }

    NameExtractionResult node::Mul::extractNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    TypeNameExtractionResult node::Mul::extractTypeNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractTypeNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractTypeNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    //// Ne ////

    DisplayResult node::Ne::display () const {
        return
            "(" + (interface::display || target::category{} <<= *leftArgument) + " != " +
            (interface::display || target::category{} <<= *rightArgument) + ")";
    }

    ExpressionProcessingResult node::Ne::processExpression (context::Main & ctx) const {
        return esl::unite_results || target::result{} <<=
            [&] (auto left, auto right) -> esl::result<ResolvedValue> {
                return binComp(ctx, sem::comptime::ne, sem::runtime::ne)(std::move(left), std::move(right));

            } || target::nested<target::result, target::tiny_vector>{} <<= args(
                interface::processExpression(ctx) || target::category{} <<= *leftArgument,
                interface::processExpression(ctx) || target::category{} <<= *rightArgument
            );
    }

    NameExtractionResult node::Ne::extractNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    TypeNameExtractionResult node::Ne::extractTypeNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractTypeNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractTypeNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    //// Not ////

    DisplayResult node::Not::display () const {
        return "(!" + (interface::display || target::category{} <<= *argument) + ")";
    }

    ExpressionProcessingResult node::Not::processExpression (context::Main & ctx) const {
        return esl::unite_results || target::result{} <<=
            [&] (auto arg) -> esl::result<ResolvedValue> {
                return unLog(ctx, sem::comptime::lnot, sem::runtime::lnot)(std::move(arg));

            } || target::nested<target::result, target::tiny_vector>{} <<=
                interface::processExpression(ctx) || target::category{} <<= *argument;
    }

    NameExtractionResult node::Not::extractNames (context::Lookup & ctx) const {
        return interface::extractNames(ctx) || target::category{} <<= *argument;
    }

    TypeNameExtractionResult node::Not::extractTypeNames (context::Lookup & ctx) const {
        return interface::extractTypeNames(ctx) || target::category{} <<= *argument;
    }

    //// Or ////

    DisplayResult node::Or::display () const {
        return
            "(" + (interface::display || target::category{} <<= *leftArgument) + " || " +
            (interface::display || target::category{} <<= *rightArgument) + ")";
    }

    ExpressionProcessingResult node::Or::processExpression (context::Main & ctx) const {
        return esl::unite_results || target::result{} <<=
            [&] (auto left, auto right) -> esl::result<ResolvedValue> {
                return binLog(ctx, sem::comptime::lor, sem::runtime::lor)(std::move(left), std::move(right));

            } || target::nested<target::result, target::tiny_vector>{} <<= args(
                interface::processExpression(ctx) || target::category{} <<= *leftArgument,
                interface::processExpression(ctx) || target::category{} <<= *rightArgument
            );
    }

    NameExtractionResult node::Or::extractNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    TypeNameExtractionResult node::Or::extractTypeNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractTypeNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractTypeNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    //// Plus ////

    DisplayResult node::Plus::display () const {
        return "(+" + (interface::display || target::category{} <<= *argument) + ")";
    }

    ExpressionProcessingResult node::Plus::processExpression (context::Main & ctx) const {
        return esl::unite_results || target::result{} <<=
            [&] (auto arg) -> esl::result<ResolvedValue> {
                return unArith(ctx, sem::comptime::plus, sem::runtime::plus)(std::move(arg));

            } || target::nested<target::result, target::tiny_vector>{} <<=
                interface::processExpression(ctx) || target::category{} <<= *argument;
    }

    NameExtractionResult node::Plus::extractNames (context::Lookup & ctx) const {
        return interface::extractNames(ctx) || target::category{} <<= *argument;
    }

    TypeNameExtractionResult node::Plus::extractTypeNames (context::Lookup & ctx) const {
        return interface::extractTypeNames(ctx) || target::category{} <<= *argument;
    }

    //// Pow ////

    DisplayResult node::Pow::display () const {
        return
            "(" + (interface::display || target::category{} <<= *leftArgument) + " ** " +
            (interface::display || target::category{} <<= *rightArgument) + ")";
    }

    ExpressionProcessingResult node::Pow::processExpression (context::Main & ctx) const {
        return esl::unite_results || target::result{} <<=
            [&] (auto left, auto right) -> esl::result<ResolvedValue> {
                // Note: I won't implement integer exponentiation in the first version.
                return bin<sem::type::Float, sem::value::Float>(ctx, sem::comptime::pow, sem::runtime::pow)
                    (std::move(left), std::move(right));

            } || target::nested<target::result, target::tiny_vector>{} <<= args(
                interface::processExpression(ctx) || target::category{} <<= *leftArgument,
                interface::processExpression(ctx) || target::category{} <<= *rightArgument
            );
    }

    NameExtractionResult node::Pow::extractNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    TypeNameExtractionResult node::Pow::extractTypeNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractTypeNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractTypeNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    //// Sub ////

    DisplayResult node::Sub::display () const {
        return
            "(" + (interface::display || target::category{} <<= *leftArgument) + " - " +
            (interface::display || target::category{} <<= *rightArgument) + ")";
    }

    ExpressionProcessingResult node::Sub::processExpression (context::Main & ctx) const {
        return esl::unite_results || target::result{} <<=
            [&] (auto left, auto right) -> esl::result<ResolvedValue> {
                return binArith(ctx, sem::comptime::sub, sem::runtime::sub)(std::move(left), std::move(right));

            } || target::nested<target::result, target::tiny_vector>{} <<= args(
                interface::processExpression(ctx) || target::category{} <<= *leftArgument,
                interface::processExpression(ctx) || target::category{} <<= *rightArgument
            );
    }

    NameExtractionResult node::Sub::extractNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractNames(ctx) || target::category{} <<= *rightArgument
        );
    }

    TypeNameExtractionResult node::Sub::extractTypeNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractTypeNames(ctx) || target::category{} <<= *leftArgument,
            interface::extractTypeNames(ctx) || target::category{} <<= *rightArgument
        );
    }

}
