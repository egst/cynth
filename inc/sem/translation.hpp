#pragma once

#include <string>

#include "esl/containers.hpp"
#include "esl/ranges.hpp"
#include "esl/string.hpp"

// TODO: Either put this in the `sem::` namespace, or move it out of the `sem/` directory.
namespace cynth {

    namespace str {

        // Strings used to construct names:
        constexpr char const * array    = "arr";
        constexpr char const * boolean  = "bool";
        constexpr char const * buffer   = "buff";
        constexpr char const * constant = "const";
        constexpr char const * context  = "ctx";
        constexpr char const * elem     = "e";
        constexpr char const * floating = "float";
        constexpr char const * global   = "cth";
        constexpr char const * input    = "in";
        constexpr char const * integral = "int";
        constexpr char const * member   = "m";
        constexpr char const * output   = "out";
        constexpr char const * string   = "str";
        constexpr char const * tuple    = "tup";
        constexpr char const * value    = "val";
        constexpr char const * variable = "var";

        // Indentation:
        constexpr char const * indent = "    ";
        //constexpr char const * indent = "\t";

        // GNU extensions and their alternate keywords:
        constexpr char const * gnuTypeof = "typeof";
        //constexpr char const * gnuTypeof = "__typeof__";

    }

    namespace def {

        // Strings refering to names of internal implementation declarations:

        // Conversions:
        constexpr char const * convert      = "convert";

        // Arrays:
        constexpr char const * arrayCopy    = "arr_copy";
        constexpr char const * arrayCopyTo  = "arr_copy_to";

        // Builtin operations:
        constexpr char const * neg          = "neg";
        constexpr char const * add          = "add";
        constexpr char const * sub          = "sub";
        constexpr char const * mul          = "mul";
        constexpr char const * div          = "div";
        constexpr char const * mod          = "mod";

        // Buffers:
        constexpr char const * dataMember   = "data";
        constexpr char const * offsetMember = "offset";

    }

    namespace c {

        /**
         *  `(<expr>)`
         *  Most expressions are explicitly parenthesized to avoid precedence issues.
         *  By default, this doesn't introduce unnecessary parentheses.
         *  The expression is scanned for matching parentheses on both ends.
         *  However, this might be a slight translation time slowdown
         *  so set `neatParentheses` to false in the config if readable C code is not a concern.
         */
        inline std::string expression (std::string const & expr) {
            constexpr bool neatParentheses = true; // TODO: Put this in some global config.
            if constexpr (neatParentheses)
                return esl::parenthesized(expr);
            else
                return std::string{} + "(" + expr + ")";
        }

        /** `<stmt>;` */
        inline std::string statement (std::string const & stmt) {
            return stmt + ";";
        }

        /** `cynth_<name>` */
        inline std::string global (std::string const & name) {
            return std::string{} + str::global + "_" + name;
        }

        /** `*<val>` */
        inline std::string dereference (std::string const & val) {
            return "*" + val;
        }

        /** `&<val>` */
        inline std::string addressof (std::string const & val) {
            return "&" + val;
        }

        /** `<type> const` */
        inline std::string constness (std::string const & type) {
            return type + " const";
        }

        /** `<type> volatile` */
        inline std::string volatility (std::string const & type) {
            return type + " volatile";
        }

        /** `<type> *` */
        inline std::string pointer (std::string const & type) {
            return type + " *";
        }

        /** `struct <name>` */
        inline std::string structure (std::string const & name) {
            return std::string{} + "structure " + name;
        }

        /** `{\n\t<stmt1>;\n\t<stmt2>;\n\t...;\n\t<stmtN>;\n}` */
        template <typename... Ts>
        inline std::string block (Ts const &... stmts) {
            return std::string{} +
                "{\n" + str::indent + esl::join(std::string{} + ";\n" + str::indent, stmts...) + ";\n}";
        }

        /** A GNU statement expression extension - `({\n\t<stmt1>;\n\t<stmt2>;\n\t...;\n\t<stmtN>;\n})` */
        template <typename... Ts>
        inline std::string blockExpression (Ts const &... stmts) {
            return std::string{} +
                "({\n" + str::indent + esl::join(std::string{} + ";\n" + str::indent, stmts...) + ";\n})";
        }

        /** A GNU typeof extension - `typeof(<value>)` */
        inline std::string infer (std::string const & value) {
            return std::string{} + str::gnuTypeof + "(" + value + ")";
        }

        /** `<type> <name>` */
        inline std::string declaration (std::string const & type, std::string const & name) {
            return type + " " + name;
        }

        /** `<type> <name> = <val>` */
        inline std::string definition (std::string const & type, std::string const & name, std::string const & val) {
            return type + " " + name + " = " + val;
        }

        /** `<dst> = <src>` */
        inline std::string assignment (std::string const & src, std::string const & dst) {
            return dst + " = " + src;
        }

        /** `*<dst> = <src>` */
        inline std::string valueAssignment (std::string const & src, std::string const & dst) {
            return c::assignment(c::dereference(dst), src);
        }

        /** `.<dst> = <src>` */
        inline std::string desigatedInitialization (std::string const & src, std::string const & dst) {
            return "." + dst + " = " + src;
        }

        /** Brace initialization - `{<arg1>, <arg2>, ...}` */
        template <typename... Ts>
        std::string init (Ts const &... args) {
            return "{" + esl::join(", ", args...) + "}";
        }

        /** Zero array initialization - `{0}` */
        inline std::string zeroInit () {
            return "{0}";
        }

        /** `<f>(<arg1>, <arg2>, ...)` */
        template <typename... Ts>
        std::string call (std::string f, Ts const &... args) {
            return f + "(" + esl::join(", ", args...) + ")";
        }

        /** `<tplArg1>$<tplArg2>$...` */
        template <typename... Ts>
        std::string templateArguments (Ts const &... args) {
            return esl::join("$", args...);
        }

        /** `<type>_const` */
        inline std::string constType (std::string const & type) {
            return type + "_" + str::constant;
        }

        /** `cth_<type>` */
        inline std::string typeName (std::string const & type) {
            return c::global(type);
        }

        /** `struct cth_tup$<type1>$<type2>$...` */
        template <typename... Ts>
        std::string tupleType (Ts const &... types) {
            return c::structure(c::global(std::string{} + str::tuple + c::templateArguments(types...)));
        }

        /** `struct cth_arr$<size>$<type1>$<type2>$...` */
        /* TODO: This probably won't be needed anymore.
        template <typename... Ts>
        std::string arrayValueType (std::string const & size, Ts const &... types) {
            return c::structure(c::global(c::templateArguments(std::string{} + str::array, size, types...)));
        }
        */

        /** `typeof(<type> [<size>])` */
        inline std::string arrayValueType (std::string const & size, std::string const & type) {
            return std::string{} + str::gnuTypeof + "(" + type + " " + "[" + size + "])";
        }

        /** `struct cth_tup$<type1>$<type2>$... *` */
        template <typename... Ts>
        std::string arrayPointerType (Ts const &... types) {
            return c::pointer(c::tupleType(types...));
        }

        /** `struct cth_tup$<type1>$<type2>$... * const` */
        template <typename... Ts>
        std::string constArrayPointerType (Ts const &... types) {
            return c::constness(c::pointer(c::tupleType(types...)));
        }

        /** `struct cth_buff$<size>` */
        inline std::string bufferValueType (std::string size) {
            return c::structure(c::global(c::templateArguments(std::string{} + str::buffer, size)));
        }

        /** `cth_float const * const` */
        inline std::string bufferPointerType () {
            return c::constness(c::pointer(c::constness(c::typeName(str::floating))));
        }

        /** Statically allocated value - `val_<id>` (no global prefix) */
        inline std::string valueName (std::string const & id) {
            return std::string{} + str::value + "_" + id;
        }

        /** Statically allocated output value - `cth_outval_<id>` */
        inline std::string outputValueName (std::string const & id) {
            return c::global(std::string{} + str::output + str::value + "_" + id);
        }

        /** Statically allocated input value - `cth_inval_<id>` */
        inline std::string inputValueName (std::string const & id) {
            return c::global(std::string{} + str::input + str::value + "_" + id);
        }

        /** Statically allocated buffer value - `cth_buffval_<id>` */
        inline std::string bufferValueName (std::string const & id) {
            return c::global(std::string{} + str::buffer + str::value + "_" + id);
        }

        /** Statically allocated input buffer value - `cth_inbuffval_<id>` */
        inline std::string inputBufferValueName (std::string const & id) {
            return c::global(std::string{} + str::input + str::buffer + str::value + "_" + id);
        }

        /** Statically allocated output buffer value - `cth_outbuffval_<id>` */
        inline std::string outputBufferValueName (std::string const & id) {
            return c::global(std::string{} + str::output + str::buffer + str::value + "_" + id);
        }

        /** Local variable - `var_<id>` */
        inline std::string variableName (std::string const & id) {
            return std::string{} + str::variable + "_" + id;
        }

        /** Struct member - `m_<id>` */
        inline std::string memberName (std::string const & id) {
            return std::string{} + str::member + "_" + id;
        }

        /** Local variable holding a function's context - `ctxvar_<id>` */
        inline std::string contextVariableName (std::string const & id) {
            return std::string{} + str::context + str::variable + "_" + id;
        }

        /** Array wrapper raw data - `<structure>.data` */
        /* TODO: This probably won't be needed anymore.
        inline std::string arrayData (std::string const & structure) {
            return structure + "." + def::dataMember;
        }
        */

        /** Buffer wrapper raw data - `<structure>.data` */
        inline std::string bufferData (std::string const & structure) {
            return structure + "." + def::dataMember;
        }

        /** `<array>[<index>]` */
        inline std::string arraySubscript (std::string const & array, std::string const & index) {
            return array + "[" + index + "]";
        }

        /** `arr_copy(<src>)` */
        inline std::string arrayCopy (std::string const & src) {
            return c::call(def::arrayCopy, src);
        }

        /** `arr_copy_to(<src>)` */
        inline std::string arrayCopyTo (std::string const & src, std::string const & dst) {
            return c::call(def::arrayCopy, src, dst);
        }

        /** `<type> volatile` */
        inline std::string inputValueType (std::string const & type) {
            return c::volatility(type);
        }

        /** `<type> volatile *` */
        inline std::string inputPointerType (std::string const & type) {
            return c::pointer(c::inputValueType(type));
        }

        /** `<type>` */
        inline std::string outputValueType (std::string const & type) {
            return type;
        }

        /** `<type> *` */
        inline std::string outputPointerType (std::string const & type) {
            return c::pointer(c::inputValueType(type));
        }

    }

}
