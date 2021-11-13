#pragma once

#include "result.hpp"
#include "component.hpp"
#include "sem/context.hpp"
#include "sem/types.hpp"
// TODO: All explicit includes.

#include <string>
#include <cstddef>

namespace cynth::sem {

    // TODO: find a better name for this
    struct translation_context {

        result<typed_value> convert (
            type::complete const &,
            typed_value    const &
        );

        result<tuple_vector<typed_value>> convert (
            tuple_vector<type::complete> const &,
            tuple_vector<typed_value>    const &
        );

        result<void> define (
            complete_decl             const &,
            tuple_vector<typed_value> const &
        );

        result<void> define (
            tuple_vector<complete_decl> const &,
            tuple_vector<typed_value>   const &
        );

        result<void> define (
            std::string                  const &,
            tuple_vector<type::complete> const &,
            tuple_vector<typed_value>    const &
        );

        result<void> declare (
            std::string                  const &,
            tuple_vector<type::complete> const &
        );

        result<void> assign (
            std::string               const &,
            tuple_vector<typed_value> const &
        );

        std::size_t next_id ();

    protected:
        result<void> declare_value (
            std::string                  const &,
            tuple_vector<type::complete> const &
        );

        result<void> init_value (
            std::string                   const &,
            component_vector<typed_value> const &
        );

        // TODO...
        result<void> begin_function   ();
        result<void> end_function     ();
        result<void> begin_scope      ();
        result<void> end_scope        ();
        result<void> insert_statement ();

        // Global & main:
        //tuple_vector<?> declarations;    // may contaion initializations
        //tuple_vector<?> definitions;     // function definitions
        //tuple_vector<?> initializations;
        //tuple_vector<?> statements;      // statements, `if (...) {`, `for (...) {`, `{`, `}`

        // Local (current function):
        struct {
            //tuple_vector<?> declarations;
            //tuple_vector<?> initializations;
            //tuple_vector<?> statements;      // statements, `if (...) {`, `for (...) {`, `{`, `}`
        } function_context;

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
        context compconst_context;

    };

}
