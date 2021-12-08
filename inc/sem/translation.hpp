#pragma once

#include "esl/string.hpp"
#include "esl/ranges.hpp"
#include "esl/containers.hpp"

#include <string>

// TODO: Come up with a better name. (And rename the file acordingly.)
// Note: This was actually a config file before all of the other configuration items
// were narrowed down to esl-specific stuff only.
namespace cynth {

    namespace str {

        // Strings used to construct names:
        constexpr char const * global   = "cth";
        constexpr char const * tuple    = "tup";
        constexpr char const * value    = "val";
        constexpr char const * variable = "var";
        constexpr char const * boolean  = "bool";
        constexpr char const * integral = "int";
        constexpr char const * floating = "float";
        constexpr char const * string   = "str";
        constexpr char const * array    = "arr";
        constexpr char const * buffer   = "buff";
        constexpr char const * elem     = "e";
        constexpr char const * constant = "const";

    }

    namespace def {

        // Strings refering to names of implementation helpers:
        constexpr char const * arrayCopy   = "arr_copy";
        constexpr char const * arrayCopyTo = "arr_copy_to";
        constexpr char const * arrayMember = "value";

    }

    namespace c {

        /** `{stmt};` */
        inline std::string statement (std::string const & stmt) {
            return stmt + ";";
        }

        /** `cynth_{name}` */
        inline std::string global (std::string const & name) {
            return std::string{str::global} + "_" + name;
        }

        /** `*{val}` */
        inline std::string dereference (std::string const & val) {
            return "*" + val;
        }

        /** `&{val}` */
        inline std::string addressof (std::string const & val) {
            return "&" + val;
        }

        /** `{type} const` */
        inline std::string constness (std::string const & type) {
            return type + " const";
        }

        /** `{type} volatile` */
        inline std::string volatility (std::string const & type) {
            return type + " volatile";
        }

        /** `{type} *` */
        inline std::string pointer (std::string const & type) {
            return type + " *";
        }

        /** `{type} {name}` */
        inline std::string declaration (std::string const & type, std::string const & name) {
            return type + " " + name;
        }

        /** `{type} {name} = {val}` */
        inline std::string definition (std::string const & type, std::string const & name, std::string const & val) {
            return type + " " + name + " = " + val;
        }

        /** `{dst} = {src}` */
        inline std::string assignment (std::string const & src, std::string const & dst) {
            return dst + " = " + src;
        }

        /** `*{dst} = {src}` */
        inline std::string valueAssignment (std::string const & src, std::string const & dst) {
            return c::assignment(c::dereference(dst), src);
        }

        /** `{f}({arg1}, {arg2}, ...)` */
        template <typename... Ts>
        std::string call (std::string f, Ts const &... args) {
            return f + "(" + esl::join(", ", args...) + ")";
        }

        /** `{tplArg1}${tplArg2}$...` */
        template <typename... Ts>
        std::string templateArguments (Ts const &... args) {
            return esl::join("$", args...);
        }

        /** `cth_{type}` */
        inline std::string typeName (std::string const & type) {
            return c::global(type);
        }

        /** `{type}_const` */
        inline std::string constType (std::string const & type) {
            return type + "_" + str::constant;
        }

        /** `cth_tup${type1}${type2}$...` */
        template <typename... Ts>
        std::string tupleType (Ts const &... types) {
            return c::global(std::string{str::tuple} + c::templateArguments(types...));
        }

        /** `cth_arr${type1}${type2}$...` */
        template <typename... Ts>
        std::string arrayType (std::string const & size, Ts const &... types) {
            return c::global(c::templateArguments(str::array, size, types...));
        }

        /** Statically allocated value - `cth_val_{id}` */
        inline std::string valueName (std::string const & id) {
            return std::string{str::value} + "_" + id;
        }

        /** Local variable - `cth_val_{id}` */
        inline std::string variableName (std::string const & id) {
            return std::string{str::variable} + "_" + id;
        }

        /** Array wrapper raw data - `{val}.value` */
        inline std::string arrayValue (std::string const & type) {
            return type + "." + def::arrayMember;
        }

        /** `arr_copy({src})` */
        inline std::string arrayCopy (std::string const & src) {
            return c::call(def::arrayCopy, src);
        }

        /** `arr_copy_to({src})` */
        inline std::string arrayCopyTo (std::string const & src, std::string const & dst) {
            return c::call(def::arrayCopy, src, dst);
        }

    }

}
