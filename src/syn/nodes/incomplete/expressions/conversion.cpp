#include "syn/nodes/incomplete/expressions/conversion.hpp"
#include "syn/nodes/expressions.hpp" // To complete circular dependencies.

#include "esl/lift.hpp"
#include "esl/sugar.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/nodes.hpp"

namespace cynth::syn {

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;

    DisplayResult node::Conversion::display () const {
    }

    ExpressionProcessingResult node::Conversion::processExpression (context::Main & ctx) const {
    }

}

/*
    display_result syn::node::Conversion::display () const {
        return interface::display(type) + util::parenthesized(interface::display(argument));
    }

    syn::evaluation_result syn::node::Conversion::evaluate (sem::context & ctx) const {
        auto from = syn::evaluate(ctx)(argument);
        auto to   = sem::complete(ctx)(syn::eval_type(ctx)(type));
        if (to.size() == 0)
            return syn::make_evaluation_result(result_error{"Cannot use the void type in an explicit conversion."});
        if (from.size() == 0)
            return syn::make_evaluation_result(result_error{"Cannot use the void value in an explicit conversion."});
        if (to.size() > from.size())
            return syn::make_evaluation_result(result_error{"Too little values in a conversion."});
        if (to.size() < from.size())
            return syn::make_evaluation_result(result_error{"Too many values in a conversion."});
        auto result = sem::convert(ctx)(from, to);
        if (!result)
            return syn::make_evaluation_result(result.error());
        return *result;
    }
*/
