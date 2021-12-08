#pragma once

#include <cstddef>
#include <string>

#include "esl/result.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/component.hpp"

#include "sem/context.hpp"
#include "sem/forward.hpp"

namespace cynth::sem {

    // TODO: find a better name for this
    struct TranslationContext {

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

        std::size_t nextId ();

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

        esl::result<void> insertStatement          (std::string);
        esl::result<void> insertFunctionAllocation (std::string);
        esl::result<void> insertStaticAllocation   (std::string);

    protected:
        // Global:
        std::vector<std::string> staticData; // static lifetime

        // Local (current function or main):
        struct {
            std::vector<std::string> functionData; // function scope lifetime
            std::vector<std::string> statements;   // including stuff like: `if (...) {`, `for (...) {`, `{`, `}`
        } functionContext;

        // Every identifier that could potentially collide with others
        // gets a unique id incorporated into its name.
        // Examples:
        // cth_add_Int$Float_Int$Float - internal function to add (Int, Float) + (Int, Float)
        // cth_Int                     - the (Int) single type
        // cth_Int$Float               - the (Int, Float) pair type
        // cth_t_12_Foo                - user defined type named Foo
        // cth_v_247_bar               - global user defined value named bar
        // cth_f_67_fun                - user defined function named fun
        // cth_c_68_fun                - implicitly defined "captured context" struct fo the fun function
        // cth_s_69_fun                - implicitly defined "switch" function for the fun function
        // cth_l_69                    - implicitly "lambda" function for a user defined anonymous function
        // v_116_x                     - local user defined value named x
        std::size_t id = 0;

    public: // TODO: Decide on visibility. (And other similar structures as well.)
        // Compilation constants:
        Context compconst;

    };

}
