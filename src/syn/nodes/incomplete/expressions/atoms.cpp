#include "syn/nodes/incomplete/expressions/atoms.hpp"
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

namespace cynth::syn {

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;
    using interface::NameExtractionResult;
    using interface::TargetResolutionResult;
    using interface::TypeNameExtractionResult;
    using sem::CompleteValue;
    using sem::ResolvedValue;
    using sem::Integral;
    using sem::TypedName;
    using sem::TypedExpression;
    using sem::TypedTargetExpression;

    //// Bool ////

    DisplayResult node::Bool::display () const {
        return value ? "true" : "false";
    }

    ExpressionProcessingResult node::Bool::processExpression (context::Main &) const {
        return esl::init<esl::tiny_vector>(ResolvedValue{CompleteValue{sem::value::Bool{value}}});
    }

    //// Float ////

    DisplayResult node::Float::display () const {
        return std::to_string(value);
    }

    ExpressionProcessingResult node::Float::processExpression (context::Main &) const {
        return esl::init<esl::tiny_vector>(ResolvedValue{CompleteValue{sem::value::Float{value}}});
    }

    //// Int ////

    DisplayResult node::Int::display () const {
        return std::to_string(value);
    }

    ExpressionProcessingResult node::Int::processExpression (context::Main &) const {
        return esl::init<esl::tiny_vector>(ResolvedValue{CompleteValue{sem::value::Int{value}}});
    }

    //// Name ////

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

        return esl::unite_results <<= [] (CompleteValue const &) -> esl::result<TypedTargetExpression> {
            return esl::result_error{"Cannot assign to compconst values."};

        } | [] (TypedName const & name) -> esl::result<sem::TypedTargetExpression> {
            return TypedTargetExpression{name.type, name.name};

        } || target::nested<target::tiny_vector, target::category>{} <<= *value;
    }

    NameExtractionResult node::Name::extractNames (context::Lookup & ctx) const {
        if (!ctx.findValue(*name))
            return esl::init<std::vector>(*name);
        return {};
    }

    //// String ////

    DisplayResult node::String::display () const {
        return "\"" + *value + "\"";
    }

    ExpressionProcessingResult node::String::processExpression (context::Main &) const {
        return esl::result_error{"Strings are not supported yet."};
    }

    //// Tuple ////

    DisplayResult node::Tuple::display () const {
        using Target = target::nested<target::component_vector, target::category>;
        return "(" + esl::join(", ", interface::display || Target{} <<= values) + ")";
    }

    ExpressionProcessingResult node::Tuple::processExpression (context::Main & ctx) const {
        return esl::insert_nested_cat || target::result{} <<=
            esl::unite_results <<=
            interface::processExpression(ctx) || target::nested<target::component_vector, target::category>{} <<=
            values;
    }

    TargetResolutionResult node::Tuple::resolveTarget (context::Main & ctx) const {
        return esl::insert_nested_cat || target::result{} <<=
            esl::unite_results <<=
            interface::resolveTarget(ctx) || target::nested<target::component_vector, target::category>{} <<=
            values;
    }

    NameExtractionResult node::Tuple::extractNames (context::Lookup & ctx) const {
        return esl::insert_nested_cat || target::result{} <<=
            esl::unite_results <<=
            interface::extractNames(ctx) || target::nested<target::component_vector, target::category>{} <<=
            values;
    }

    TypeNameExtractionResult node::Tuple::extractTypeNames (context::Lookup & ctx) const {
        return esl::insert_nested_cat || target::result{} <<=
            esl::unite_results <<=
            interface::extractTypeNames(ctx) || target::nested<target::component_vector, target::category>{} <<=
            values;
    }

}
