#pragma once

namespace esl {

    /**
     *  Place `esl::inspector<Type>{}` or `esl::inspector<decltype(value)>{}`
     *  somewhere to see the corresponding type in an error message.
     *  For less verbose syntax, use the ESL_INSPECT and ESL_INSPECT_TYPE macros from `esl/macros.hpp`.
     */
    template <typename Type> requires (false) struct inspector {};

    /** Same as esl::inspector, but for constepr values. */
    template <auto Type> requires (false) struct value_inspector {};

}
