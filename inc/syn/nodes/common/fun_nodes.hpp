#pragma once

#include <optional>
#include <string>

#include "esl/tiny_vector.hpp"

#include "context/main.hpp"
#include "sem/compound.hpp"
#include "sem/declarations.hpp"
#include "sem/types.hpp"
#include "sem/values.hpp"

namespace cynth::syn::fun_nodes {

    struct CaptureResult {
        sem::Closure closure;
        std::optional<std::string> closureType;
        std::optional<std::string> closureVariable;
    };

    esl::result<CaptureResult> capture (
        context::Main & ctx,
        std::vector<std::string> const & names,
        std::vector<std::string> const & typeNames
    );

    esl::result<sem::value::Function> process (
        context::Main               & ctx,
        category::Type        const & output,
        category::Declaration const & input,
        category::Expression  const & body
    );

}
