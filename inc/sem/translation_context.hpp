#pragma once

#include <cstddef>
#include <string>

#include "esl/result.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/component.hpp"

#include "sem/context.hpp"
#include "sem/forward.hpp"

namespace cynth::sem {

    struct GlobalContext {
        std::size_t nextId ();

    protected:
        std::vector<std::string> internalTypes;
        std::vector<std::string> internalFunctions;
        std::vector<std::string> userFunctions;
        std::vector<std::string> staticData; // static lifetime allocations

        std::size_t id = 0;
    };

    // TODO: find a better name for this
    struct TranslationContext {

        TranslationContext (GlobalContext & ctx): globalCtx{ctx} {}

        esl::result<TypedValue> convert (
            CompleteType const &,
            TypedValue   const &
        );

        esl::result<esl::tiny_vector<TypedValue>> convert (
            esl::tiny_vector<CompleteType> const &,
            esl::tiny_vector<TypedValue>   const &
        );

        esl::result<void> define (
            CompleteDeclaration const &,
            esl::tiny_vector<TypedValue> const &
        );

        esl::result<void> define (
            esl::tiny_vector<CompleteDeclaration> const &,
            esl::tiny_vector<TypedValue>          const &
        );

        esl::result<void> define (
            std::string const &,
            esl::tiny_vector<CompleteType> const &,
            esl::tiny_vector<TypedValue>   const &
        );

        esl::result<void> declare (
            std::string const &,
            esl::tiny_vector<CompleteType> const &
        );

        esl::result<void> assign (
            std::string const &,
            esl::tiny_vector<TypedValue> const &
        );

    //protected:
        esl::result<void> declareValue (
            std::string const &,
            esl::tiny_vector<CompleteType> const &
        );

        esl::result<void> initValue (
            std::string const &,
            esl::component_vector<TypedValue> const & // TODO: or maybe tiny_component_vector?
        );

        esl::result<void> beginFunction ();
        esl::result<void> endFunction   ();
        esl::result<void> beginScope    ();
        esl::result<void> endScope      ();

        // TODO: Don't forget that these must completely ignore empty strings.
        esl::result<void> insertStatement          (std::string);
        esl::result<void> insertFunctionAllocation (std::string);
        esl::result<void> insertStaticAllocation   (std::string);
        esl::result<void> insertInternalFunction   (std::string);
        esl::result<void> insertInternalType       (std::string);

        std::size_t nextId ();

        Context compCtx;

    protected:
        GlobalContext & globalCtx;

        struct {
            std::vector<std::string> functionData; // function scope lifetime allocations
            std::vector<std::string> statements;   // including stuff like: `if (...) {`, `for (...) {`, `{`, `}`
        } local;
    };

}
