#pragma once

#include <string>
#include <vector>

#include "esl/tiny_vector.hpp"
#include "esl/result.hpp"
#include "esl/concepts.hpp"
#include "esl/containers.hpp"
#include "esl/functional.hpp"

#include "sem/values.hpp"
#include "sem/types.hpp"
#include "sem/targets.hpp"

namespace cynth::ast {

    using ExecutionResult                  = esl::optional_result<esl::tiny_vector<sem::CompleteValue>>;
    using SingleEvaluationResult           = esl::result<sem::CompleteValue>;
    using EvaluationResult                 = esl::result<esl::tiny_vector<sem::CompleteValue>>;
    using TypeEvaluationResult             = esl::result<esl::tiny_vector<sem::IncompleteType>>;
    using ArrayElementEvaluationResult     = esl::result<esl::tiny_vector<sem::CompleteValue>>; // TODO
    using DeclarationEvaluationResult      = esl::result<esl::tiny_vector<sem::IncompleteDeclaration>>;
    using RangeDeclarationEvaluationResult = esl::result<esl::tiny_vector<sem::IncompleteRangeDeclaration>>;
    using TargetEvaluationResult           = esl::result<esl::tiny_vector<sem::Target>>;
    using TranslationResult                = esl::result<esl::tiny_vector<sem::TypedValue>>;

}
