#include "syn/nodes/incomplete/expressions/array.hpp"
#include "syn/nodes/expressions.hpp" // To complete circular dependencies.

// TODO: Cleanup when done.

#include "esl/category.hpp"
#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"

#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "sem/compound.hpp"
#include "sem/numeric_types.hpp"
#include "sem/translation.hpp"
#include "sem/values.hpp"
#include "syn/nodes/common/array_nodes.hpp"

// TMP
#include "esl/debug.hpp"
#include "esl/macros.hpp"

namespace cynth::syn {

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;
    using interface::TargetResolutionResult;
    using sem::CompleteValue;
    using sem::ResolvedValue;
    using sem::Integral;
    using sem::TypedName;
    using sem::TypedExpression;
    using sem::TypedTargetExpression;

    DisplayResult node::Bool::display () const {
        return value ? "true" : "false";
    }

    ExpressionProcessingResult node::Bool::processExpression (context::Main &) const {
        return esl::init<esl::tiny_vector>(ResolvedValue{CompleteValue{sem::value::Bool{value}}});
    }

    DisplayResult node::Float::display () const {
        return std::to_string(value);
    }

    ExpressionProcessingResult node::Float::processExpression (context::Main &) const {
        return esl::init<esl::tiny_vector>(ResolvedValue{CompleteValue{sem::value::Float{value}}});
    }

    DisplayResult node::Int::display () const {
        return std::to_string(value);
    }

    ExpressionProcessingResult node::Int::processExpression (context::Main &) const {
        return esl::init<esl::tiny_vector>(ResolvedValue{CompleteValue{sem::value::Int{value}}});
    }

    DisplayResult node::Name::display () const {
        return *name;
    }

    ExpressionProcessingResult node::Name::processExpression (context::Main & ctx) const {
        auto value = ctx.lookup.findValue(*name);
        if (!value)
            return esl::result_error{"Name not found."};

        return [] (CompleteValue const & value) -> ResolvedValue {
            return value;

        } | [] (TypedName const & name) -> ResolvedValue {
            return TypedExpression{name.type, name.name};

        } || target::nested<target::tiny_vector, target::category>{} <<= *value;
    }

    TargetResolutionResult node::Name::resolveTarget (context::Main & ctx) const {
        auto value = ctx.lookup.findValue(*name);
        if (!value)
            return esl::result_error{"Name not found."};

        return esl::unite_results <<= [] (CompleteValue const & value) -> esl::result<TypedTargetExpression> {
            return esl::result_error{"Cannot sasign to compconst values."};

        } | [] (TypedName const & name) -> esl::result<sem::TypedTargetExpression> {
            return TypedTargetExpression{name.type, name.name};

        } || target::nested<target::tiny_vector, target::category>{} <<= *value;
    }

    DisplayResult node::String::display () const {
        return "\"" + *value + "\"";
    }

    ExpressionProcessingResult node::String::processExpression (context::Main &) const {
        return esl::result_error{"Strings are not supported yet."};
    }

    DisplayResult node::Tuple::display () const {
        using Target = target::nested<target::component_vector, target::category>;
        return "(" + esl::join(", ", interface::display || Target{} <<= values) + ")";
    }

    ExpressionProcessingResult node::Tuple::processExpression (context::Main & ctx) const {
        ExpressionProcessingResult::value_type result;
        [&] (auto && decls) {
            for (auto && tuple: decls) for (auto && value: tuple) {
                result.push_back(std::move(value));
            }

        } || target::result{} <<= esl::unite_results <<=
            interface::processExpression(ctx) || target::nested<target::component_vector, target::category>{} <<=
            values;
        return result;
    }

    TargetResolutionResult node::Tuple::resolveTarget (context::Main & ctx) const {
        TargetResolutionResult::value_type result;
        [&] (auto && decls) {
            for (auto && tuple: decls) for (auto && value: tuple) {
                result.push_back(std::move(value));
            }

        } || target::result{} <<= esl::unite_results <<=
            interface::resolveTarget(ctx) || target::nested<target::component_vector, target::category>{} <<=
            values;
        return result;
    }

}
