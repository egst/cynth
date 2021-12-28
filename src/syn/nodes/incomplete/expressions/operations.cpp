
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
#include "sem/operations.hpp"
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

    namespace {

        constexpr auto add = [] (context::Main & ctx) { return binArith(ctx, sem::add, sem::add);  };
        constexpr auto sub = [] (context::Main & ctx) { return binArith(ctx, sem::sub, sem::sub);  };
        constexpr auto mul = [] (context::Main & ctx) { return binArith(ctx, sem::mul, sem::mul);  };
        constexpr auto div = [] (context::Main & ctx) { return binArith(ctx, sem::div, sem::div);  };
        constexpr auto pow = [] (context::Main & ctx) { return binArith(ctx, sem::pow, sem::pow);  };
        constexpr auto mod = [] (context::Main & ctx) { return binArith(ctx, sem::mod, sem::fmod); };

        constexpr auto plus  = [] (context::Main & ctx) { return unArith(ctx, sem::plus,  sem::plus);  };
        constexpr auto minus = [] (context::Main & ctx) { return unArith(ctx, sem::minus, sem::minus); };

        constexpr auto eq = [] (context::Main & ctx) { return compare(ctx, sem::eq); };
        constexpr auto ne = [] (context::Main & ctx) { return compare(ctx, sem::ne); };
        constexpr auto gt = [] (context::Main & ctx) { return compare(ctx, sem::gt); };
        constexpr auto lt = [] (context::Main & ctx) { return compare(ctx, sem::lt); };
        constexpr auto ge = [] (context::Main & ctx) { return compare(ctx, sem::ge); };
        constexpr auto le = [] (context::Main & ctx) { return compare(ctx, sem::le); };

    }

    DisplayResult node::Add::display () const {
        return "(" + interface::display(left_argument) + " + " + interface::display(right_argument) + ")";
    }

    ExpressionProcessingResult node::Add::processExpression (context::Main & ctx) const {
        auto r = [] (auto left, auto right) -> int {
            ESL_INSPECT(left);
            return 0;

        } || target::nested<target::result, target::tiny_vector>{} <<= args(
            interface::processExpression(ctx) || target::category{} <<= *leftArgument,
            interface::processExpression(ctx) || target::category{} <<= *rightArgument
        );
        ESL_INSPECT(r);
    }

}
