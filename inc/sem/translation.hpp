#pragma once

#include <concepts>
#include <optional>
#include <string>

#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/ranges.hpp"
#include "esl/string.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/zip.hpp"

#include "sem/numeric_types.hpp"

// TMP
#include "debug.hpp"

// TODO: Decide where to use std::size_t and where to use sem::Integral
// TODO: Cleanup: Many of the function in c:: are not needed anymore.
// TODO: Either put this in the `sem::` namespace, or move it out of the `sem/` directory.

namespace cynth {

    namespace str {

        // Strings used to construct names:
        /***
        var_<id>
        closurevar_<id>
        itervar_<id>
        val_<id>
        inval_<id>
        <struct>.m_<id>
        <struct>.internal_member
        <tuple>.e<n>
        ***/
        constexpr char const * argument        = "arg";
        constexpr char const * array           = "arr";
        constexpr char const * boolean         = "bool";
        constexpr char const * buffer          = "buff";
        constexpr char const * constant        = "const";
        constexpr char const * closure         = "closure";
        constexpr char const * element         = "e";
        constexpr char const * floating        = "float";
        constexpr char const * function        = "fun";
        constexpr char const * global          = "cth";
        constexpr char const * input           = "in";
        constexpr char const * integral        = "int";
        constexpr char const * iterator        = "iter";
        constexpr char const * member          = "m";
        constexpr char const * output          = "out";
        constexpr char const * string          = "str";
        constexpr char const * structure       = "struct";
        constexpr char const * tuple           = "tup";
        constexpr char const * value           = "val";
        constexpr char const * variable        = "var";
        constexpr char const * variant         = "v";
        constexpr char const * pointer         = "ptr";
        constexpr char const * constantPointer = "constptr";

        // Seaprator in template names:
        //constexpr char const * separator = "__";
        constexpr char const * separator = "$"; // GNU C (GCC) allows dollars, but other compilers might not.

        // Whitespace:
        //constexpr char const * indent = "\t";
        constexpr char const * indent  = "    ";
        constexpr char const * newLine = "\n";

        // GNU extensions and their alternate keywords:
        //constexpr char const * gnuTypeof = "typeof";
        constexpr char const * gnuTypeof    = "__typeof__";
        constexpr char const * gnuAuto      = "__auto_type";
        constexpr char const * gnuLabel     = "__label__";
        constexpr char const * gnuAttribute = "__attribute__";

    }

    namespace def {

        // Strings refering to names of internal implementation declarations:

        // Conversions:
        /***
        convert$<from>$<to>(<value>)
        ***/
        constexpr char const * convert = "convert";

#if 0
        // Arrays:
        // I'm not sure yet, how I'll implement and use this.
        constexpr char const * arrayCopy    = "arr_copy";
        constexpr char const * arrayCopyTo  = "arr_copy_to";
#endif

        // Built-in operations:
        /***
        op$<type>(<value>, ...)
        ***/
        constexpr char const * neg = "neg";
        constexpr char const * add = "add";
        constexpr char const * sub = "sub";
        constexpr char const * mul = "mul";
        constexpr char const * div = "div";
        constexpr char const * mod = "mod";

        // Buffers:
        /***
        <buff>.data
        <buff>.offset
        ***/
        constexpr char const * dataMember   = "data";
        constexpr char const * offsetMember = "offset";

        // Function closures:
        constexpr char const * closureDataMember = "data";
        constexpr char const * branchMember      = "branch";

        // Returning:
        /***
        __label__ ret;
        struct result {} result;
        ret: result;
        ***/
        constexpr char const * returnLabel    = "ret";
        constexpr char const * returnVariable = "result";
        constexpr char const * returnType     = "result";

        // Iteration:
        /***
        struct {
            int pos;
            ...
        } iter = {0, ...}
        # or:
        int iter = 0
        ***/
        constexpr char const * position  = "pos";
        constexpr char const * iteration = "iter";
        // TODO: Make sure that `struct {...} iter` and `int iter` do not collide with themselves (when nested) or each other.

        constexpr char const * empty = "empty";

        // Note: str::floating and str::integral are only used to construct names,
        // while these are actual C type names.
        constexpr char const * boolean  = "bool"; // Requires <stdbool.h>.
        constexpr char const * integral = "int";
        constexpr char const * floating = "float";

        constexpr char const * integralSuffix = "";  // alternatively: l, ll
        constexpr char const * floatingSuffix = "f"; // alternatively: l, empty

        constexpr char const * nativeFloatingModulo = "fmodf";  // Alternatively: fmod,  fmodl
        constexpr char const * nativeFloor          = "floorf"; // Alternatively: floor, floorl
        constexpr char const * nativeExponentiation = "powf";   // Alternatively: pow,   powl
        constexpr char const * integralDivision     = "idiv";
        constexpr char const * integralModulo       = "imod";
        constexpr char const * floatingModulo       = "fmod";
        constexpr char const * floor                = "floor";

    }

    namespace c {

        //// Whitespace ////

        /***
        \t...\t
        ***/
        std::string indentation (int n = 1);

        /***
        \t...\t<stmt>
        ***/
        std::string indented (std::string stmt, int n = 1);

        inline std::string newLine () {
            return str::newLine;
        }

        //// Misc. ////

        inline std::string inclusion (std::string const & header) {
            return "#include " + header;
        }

        inline std::string inlineComment (std::string const & content) {
            return "// " + content;
        }

        inline std::string inlined (std::string const & decl) {
            return "inline " + decl;
        }

        /***
        <arg1>, <arg2>, ...
        ***/
        template <typename... Ts>
        std::string inlineJoin (std::string const & sep, Ts const &... args) {
            return esl::join(sep + " " , args...);
        }

        /***
        <arg1>,
        <arg2>,
        ...
        ***/
        template <typename... Ts>
        std::string join (std::string const & sep, Ts const &... args) {
            return esl::join(sep + c::newLine(), args...);
        }

        /***
        # An indented comma-separated list (with line breaks)
            <arg1>,
            <arg2>,
            ...
        ***/
        /* Use c::indented(c::join(...)) instead
        template <typename... Ts>
        std::string indentedJoin (std::string const & sep, Ts const &... args) {
            auto indent = c::indentation();
            auto joined = esl::join(sep + c::newLine() + indent, args...);
            return joined.empty() ? "" : indent + joined;
        }
        */

        /***
        <arg1>, <arg2>, ..., <argN>,
        ***/
        template <typename... Ts>
        std::string inlineTerminatedJoin (std::string const & sep, Ts const &... args) {
            auto joined = esl::join(sep + " " , args...);
            return joined.empty() ? "" : joined + sep;
        }

        /***
        <arg1>,
        <arg2>,
        ...
        <argN>,
        ***/
        template <typename... Ts>
        std::string terminatedJoin (std::string const & sep, Ts const &... args) {
            auto joined = esl::join(sep + c::newLine(), args...);
            return joined.empty() ? "" : joined + sep;
        }

        /***
        # An indented comma-separated list (with line breaks)
            <arg1>,
            <arg2>,
            ...
            <argN>,
        ***/
        /* Use c::indented(c::terminatedJoin(...)) instead
        template <typename... Ts>
        std::string indentedTerminatedJoin (std::string const & sep, Ts const &... args) {
            auto indent = c::indentation();
            auto joined = esl::join(sep + c::newLine() + indent, args...);
            return joined.empty() ? "" : indent + joined + sep;
        }
        */

        /**
         *  Most expressions are explicitly parenthesized to avoid precedence issues.
         *  By default, this doesn't introduce unnecessary parentheses.
         *  The expression is scanned for matching parentheses on both ends.
         *  However, this might be a slight translation time slowdown
         *  so set `neatParentheses` to false in the config if readable C code is not a concern.
         */
        /***
        (<expr>)
        ***/
        std::string expression (std::string const & expr);

        /***
        <stmt>;
        ***/
        std::string statement (std::string const & stmt);

        /***
        [<expr>]
        ***/
        std::string brackets (std::string const & expr);

        //// Declarations & definitions ////

        /***
        <type> <name>
        ***/
        std::string declaration (std::string const & type, std::string const & name);

        /***
        <type> <name> = <val>
        ***/
        std::string definition (std::string const & type, std::string const & name, std::string const & val);

        //// Naming ////

        /**
         *  For now, I'll jsut use the unique id numbers in decimal
         *  but I might switch do hex or some other more compact representation later.
         *  TODO: Update code everyghere to use this function instead of std::to_string.
         */
        template <std::integral T>
        inline std::string id (T number) {
            return std::to_string(number);
        }

        /***
        cth_<name>
        ***/
        std::string global (std::string const & name);

        /***
        # Statically allocated value
        val_<id> (no global prefix)
        ***/
        std::string valueName (std::string const & id);

        /***
        # Statically allocated output value
        cth_outval_<id>
        ***/
        std::string outputValueName (std::string const & id);

        /***
        # Statically allocated input value
        cth_inval_<id>
        ***/
        std::string inputValueName (std::string const & id);

        /***
        # Statically allocated buffer value
        cth_buffval_<id>
        ***/
        std::string bufferValueName (std::string const & id);

        /***
        # Statically allocated input buffer value
        cth_inbuffval_<id>
        ***/
        std::string inputBufferValueName (std::string const & id);

        /***
        # Statically allocated output buffer value
        cth_outbuffval_<id>
        ***/
        std::string outputBufferValueName (std::string const & id);

        /***
        # Local variable
        var_<id>
        ***/
        std::string variableName (std::string const & id);

        /***
        # Local tuple variable - returning from blocks.
        tupvar_<id>
        ***/
        std::string tupleVariableName (std::string const & id);

        // TODO: Might be not needed.
        /***
        # Struct member name
        m_<id>
        ***/
        std::string memberName (std::string const & id);

        /***
        # Tuple struct member name
        e<number>
        ***/
        std::string tupleElementName (std::size_t number);

        /***
        # Result struct member name
        e<number>
        ***/
        std::string returnElementName (std::size_t number);

        /***
        # Local variable holding a function's closure
        closurevar_<id>
        ***/
        std::string closureVariableName (std::string const & id);

        /***
        closure
        ***/
        inline std::string closureArgumentName () {
            return str::closure;
        }

        /***
        # Function closure type
        cth_closure_<id>
        ***/
        std::string closureType (std::string const & id);

        /***
        cth_fun_<id>
        ***/
        std::string functionName (std::string const & id);

        //// Built-in operations ////

        /***
        *<val>
        ***/
        std::string dereference (std::string const & val);

        /***
        &<val>
        ***/
        std::string addressof (std::string const & val);

        /***
        <array>[<index>]
        ***/
        std::string arraySubscript (std::string const & array, std::string const & index);

        /***
        <f>(
            <arg1>,
            <arg2>,
            ...
        )
        ***/
        template <typename... Ts>
        std::string call (std::string f, Ts const &... args) {
            auto joined  = c::indented(c::join(",", args...));
            auto newLine = c::newLine();
            return f + "(" + (joined.empty() ? "" : newLine + joined + newLine) + ")";
        }

        /***
        <f>(<arg1>, <arg2>, ...)
        ***/
        template <typename... Ts>
        std::string inlineCall (std::string f, Ts const &... args) {
            return f + "(" + c::inlineJoin(",", args...) + ")";
        }

        /***
        (<type>) <val>
        ***/
        std::string cast (std::string const & val, std::string const & type);

        /***
        ++<val>
        ***/
        std::string increment (std::string const & val);

        /***
        <target> += <diff>
        ***/
        std::string advance (std::string const & target, std::string const & diff);

        /***
        <cond> ? <pos> : <neg>
        ***/
        std::string ternary (std::string const & cond, std::string const & pos, std::string const & neg);

        /***
        -<a>
        ***/
        inline std::string negate (std::string const & a) {
            return "-" + a;
        }

        /***
        <a> + <b>
        ***/
        inline std::string add (std::string const & a, std::string const & b) {
            return a + " + " + b;
        }

        /***
        <a> - <b>
        ***/
        inline std::string sub (std::string const & a, std::string const & b) {
            return a + " - " + b;
        }

        /***
        <a> * <b>
        ***/
        inline std::string mul (std::string const & a, std::string const & b) {
            return a + " * " + b;
        }

        /***
        <a> * <b>
        ***/
        inline std::string div (std::string const & a, std::string const & b) {
            return a + " / " + b;
        }

        /***
        <a> % <b>
        ***/
        inline std::string mod (std::string const & a, std::string const & b) {
            return a + " % " + b;
        }

        /***
        <a> < <b>
        ***/
        inline std::string lt (std::string const & a, std::string const & b) {
            return a + " < " + b;
        }

        /***
        <a> > <b>
        ***/
        inline std::string gt (std::string const & a, std::string const & b) {
            return a + " > " + b;
        }

        /***
        <a> <= <b>
        ***/
        inline std::string le (std::string const & a, std::string const & b) {
            return a + " <= " + b;
        }

        /***
        <a> >= <b>
        ***/
        inline std::string ge (std::string const & a, std::string const & b) {
            return a + " >= " + b;
        }

        /***
        <a> == <b>
        ***/
        inline std::string eq (std::string const & a, std::string const & b) {
            return a + " == " + b;
        }

        /***
        <a> != <b>
        ***/
        inline std::string ne (std::string const & a, std::string const & b) {
            return a + " != " + b;
        }

        /***
        !<a>
        ***/
        inline std::string lnot (std::string const & a) {
            return "!" + a;
        }

        /***
        <a> && <b>
        ***/
        inline std::string land (std::string const & a, std::string const & b) {
            return a + " && " + b;
        }

        /***
        <a> || <b>
        ***/
        inline std::string lor (std::string const & a, std::string const & b) {
            return a + " || " + b;
        }

        /***
        return <val>
        ***/
        inline std::string functionReturn (std::string const & val) {
            return "return " + val;
        }

        //// Built-in types ////

        /***
        struct <name>
        ***/
        std::string structure (std::string const & name);

        namespace detail::translation {

            template <typename... Ts>
            inline std::string compoundDefinition (
                std::string                const &    kind,
                std::optional<std::string> const &    name,
                Ts                         const &... items
            ) {
                auto head     = std::string{} + kind + " " + (name ? *name + " " : "") + "{";
                auto newLine  = c::newLine();
                auto contents = c::indented(c::terminatedJoin(";", items...));
                return head + (!contents.empty() ? newLine + contents + newLine : "") + "}";
                // When empty: `<kind> <name> {}`
            }

            template <esl::sized_range T>
            inline std::string prefixedCompoundDefinition (
                std::string                const & kind, // "struct" or "union"
                std::string                const & prefix,
                std::optional<std::string> const & name,
                T                                  items
            ) {
                for (auto const & [i, item]: esl::enumerate(items))
                    item += std::string{} + " " + prefix + std::to_string(i);

                auto head     = std::string{} + kind + " " + (name ? *name + " " : "") + "{";
                auto newLine  = c::newLine();
                auto contents = c::indented(c::terminatedJoin(";", items));
                return head + (!contents.empty() ? newLine + contents + newLine : "") + "}";
                // When empty: `<kind> <name> {}`
            }

        }

        /***
        struct <name> {
            <decl1>;
            <decl2>;
            ...
        }
        ***/
        template <typename... Ts>
        inline std::string structureDefinition (std::string const & name, Ts const &... decls) {
            return detail::translation::compoundDefinition("struct", std::make_optional(name), decls...);
        }

        /***
        struct {
            <decl1>;
            <decl2>;
            ...
        }
        ***/
        template <typename... Ts>
        inline std::string anonymousStructureDefinition (Ts const &... decls) {
            return detail::translation::compoundDefinition("struct", std::nullopt, decls...);
        }

        /***
        struct <name> {
            <type1> e0;
            <type2> e1;
            ...
        }
        ***/
        template <esl::sized_range T>
        inline std::string tupleStructureDefinition (std::string const & name, T const & types = esl::nullrange<>{}) {
            return detail::translation::prefixedCompoundDefinition("struct", str::tuple, std::make_optional(name), types);
        }

        /***
        struct {
            <type1> e0;
            <type2> e1;
            ...
        }
        ***/
        template <esl::sized_range T>
        inline std::string anonymousTupleStructureDefinition (T const & types = esl::nullrange<>{}) {
            return detail::translation::prefixedCompoundDefinition("struct", str::tuple, std::nullopt, types);
        }

        /***
        union <name> {
            <decl1>;
            <decl2>;
            ...
        }
        ***/
        template <typename... Ts>
        inline std::string unionDefinition (std::string const & name, Ts const &... decls) {
            return detail::translation::compoundDefinition("union", std::make_optional(name), decls...);
        }

        /***
        union {
            <decl1>;
            <decl2>;
            ...
        }
        ***/
        template <typename... Ts>
        inline std::string anonymousUnionDefinition (Ts const &... decls) {
            return detail::translation::compoundDefinition("union", std::nullopt, decls...);
        }

        /***
        union <name> {
            <type1> v0;
            <type2> v1;
            ...
        }
        ***/
        template <esl::sized_range T>
        inline std::string variantUnionDefinition (std::string const & name, T const & types) {
            return detail::translation::prefixedCompoundDefinition("union", str::variant, std::make_optional(name), types);
        }

        /***
        union {
            <type1> v0;
            <type2> v1;
            ...
        }
        ***/
        template <esl::sized_range T>
        inline std::string anonymousVariantUnionDefinition (T const & types = esl::nullrange<>{}) {
            return detail::translation::prefixedCompoundDefinition("union", str::variant, std::nullopt, types);
        }

        /***
        <type> const
        ***/
        std::string constness (std::string const & type);

        /***
        <type> volatile
        ***/
        std::string volatility (std::string const & type);

        /***
        <type> *
        ***/
        std::string pointer (std::string const & type);

        /***
        # GNU typeof extension
        typeof(<value>)
        ***/
        std::string infer (std::string const & value);

        /***
        # GNU typeof extension
        sizeof(<value>)
        ***/
        std::string inferSize (std::string const & value);

        /***
        # GNU auto type extension
        __auto_type
        ***/
        std::string autoType ();

        //// Simple types ////

        /***
        bool
        ***/
        std::string booleanType ();

        /***
        int
        ***/
        std::string integralType ();

        /***
        float
        ***/
        std::string floatingType ();

        //// Compound statements ////

        /***
        {
            <stmt1>;
            <stmt2>;
            ...
            <stmtN>;
        }
        ***/
        template <typename... Ts>
        std::string block (Ts const &... stmts) {
            auto newLine = c::newLine();
            return "{" + newLine + c::terminatedJoin(";", stmts...) + newLine + "}";
        }

        /***
        # GNU statement expression extension
        ({
            <stmt1>;
            <stmt2>;
            ...;
            <stmtN>;
        })
        ***/
        template <typename... Ts>
        std::string blockExpression (Ts const &... stmts) {
            auto newLine = c::newLine();
            return "({" + newLine + c::terminatedJoin(";", stmts...) + newLine + "})";
        }

        //// Assignments ////

        /***
        <dst> = <src>
        ***/
        std::string assignment (std::string const & src, std::string const & dst);

        /***
        *<dst> = <src>
        ***/
        std::string valueAssignment (std::string const & src, std::string const & dst);

        //// Initialization ////

        /***
        .<dst> = <src>
        ***/
        std::string designatedInitialization (std::string const & src, std::string const & dst);

        /***
        # Brace initialization (with line breaks)
        {
            <arg1>,
            <arg2>,
            ...
        }
        ***/
        template <typename... Ts>
        std::string init (Ts const &... args) {
            auto indent  = c::indentation();
            auto newLine = c::newLine();
            auto contents = c::indented(c::join(",", args...));
            return "{" + (!contents.empty() ? newLine + contents + newLine : "") + "}";
        }

        /***
        # Brace initialization (with no line breaks)
        {<arg1>, <arg2>, ...}
        ***/
        template <typename... Ts>
        std::string inlineInit (Ts const &... args) {
            return "{" + c::inlineJoin("," , args...) + "}";
        }

        /***
        {0}
        ***/
        inline std::string zeroInitialization () {
            return "{0}";
        }

        /***
        .data = <expr>
        ***/
        std::string dataInitialization (std::string const & expr);

        /***
        .data.v<number> = <expr>
        ***/
        std::string closureDataInitialization (std::size_t number, std::string const & expr);

        /***
        .branch = <number>
        ***/
        std::string branchInitialization (std::size_t const & number);

        /***
        # Assignment of individual array values after it has been declared.
        # Useful for "initialization" of function-allocated arrays from values created later on in the function.
        <array>[1] = <value1>;
        <array>[2] = <value2>;
        ...
        ***/
        template <esl::range T>
        std::string arrayIndividualInitialization (std::string const & array, T const & values) {
            std::vector<std::string> result;
            result.reserve(values.size());
            for (auto const & [i, value]: esl::enumerate(values)) {
                auto assgn = c::statement(c::assignment(value, c::arraySubscript(array, std::to_string(i))));
                result.push_back(assgn);
            }
            return c::join("", result);
        }

        /***
        # memcpy to an array after it has been declared.
        # Useful for "initialization" of function-allocated arrays from another array created later on in the function.
        #memcpy(<array>, <from>, <size> * sizeof(<type>));
        memcpy(<array>, <from>, sizeof(<array>));
        ***/
        std::string arrayBulkInitialization (
            std::string const & array, std::string const & from
            //sem::Integral size, std::string const & type
        );

        /***
        # memcpy to an array with the given size
        # Useful for "assignment" to arrays or contiguous subarrays.
        memcpy(<array>, <from>, <size> * sizeof(<type>));
        ***/
        std::string arrayBulkCopy (
            std::string const & array, std::string const & from,
            sem::Integral size, std::string const & type
        );

        //// Structural access ////

        /***
        <structure>.<member>
        ***/
        std::string memberAccess (std::string const & structure, std::string const & member);

        /***
        <structure>.e<number>
        ***/
        std::string tupleElement (std::string const & structure, std::size_t number);

        /***
        # Union "variant"/"alternative"
        <structure>.v<number>
        ***/
        std::string unionVariant (std::string const & structure, std::size_t number);

        /***
        # Buffer wrapper raw data
        <structure>.data
        ***/
        std::string bufferData (std::string const & structure);

        /***
        # Buffer wrapper offset
        <structure>.offset
        ***/
        std::string bufferOffset (std::string const & structure);

        /***
        iter.pos
        ***/
        std::string iterationPosition ();

        /***
        iter
        ***/
        std::string simpleIterationPosition ();

        /***
        # Result struct member access
        result.e<number>
        ***/
        std::string returnElement (std::size_t number);

        /***
        <structure>.data
        ***/
        std::string closureData (std::string const & structure, std::size_t variant);

        /***
        <structure>.branch
        ***/
        std::string closureBranch (std::string const & structure);

        //// Templates ////

        /***
        <tplArg1>$<tplArg2>$...
        ***/
        template <typename... Ts>
        std::string templateArguments (Ts const &... args) {
            return esl::join("$", args...);
        }

        template <typename... Ts>
        std::string tupleTypeName (Ts const &... types) {
            return c::global(c::templateArguments(str::tuple, types...));
        }

        /***
        struct cth_tup$<type1>$<type2>$...
        ***/
        template <typename... Ts>
        std::string tupleType (Ts const &... types) {
            return c::structure(c::tupleTypeName(types...));
        }

        /***
        cth_arr$<size>$<type>
        # alternatively:
        typeof(<type> [<size>])
        ***/
        std::string arrayType (std::size_t size, std::string const & type);

        /***
        struct cth_buff$<size>
        ***/
        std::string bufferType (sem::Integral size);

        //// Types ////

        /***
        struct cth_empty
        ***/
        std::string emptyType ();

        /***
        struct cth_empty {};
        ***/
        std::string emptyTypeDefinition ();

        /***
        float const * const
        ***/
        std::string bufferPointer ();

        /***
        <type>
        ***/
        std::string inputType (std::string const & type);

        /***
        <type> const *
        ***/
        std::string inputPointerType (std::string const & type);

        /***
        <type>
        ***/
        std::string outputType (std::string const & type);

        /***
        <type> *
        ***/
        std::string outputPointerType (std::string const & type);

        //// Compound head (begin) & end ////

        /***
        # GNU statement expression extension
        ({
        ***/
        inline std::string blockExpressionBegin () {
            return "({";
        }

        /***
        # Extracting a returned value from an expression block.
        __auto_type <var> = ({
        ***/
        std::string blockExpressionBegin (std::string const & var);

        /***
        # GNU statement expression extension
        })
        ***/
        inline std::string blockExpressionEnd () {
            return "})";
        }

        /***
        {
        ***/
        inline std::string blockBegin () {
            return "{";
        }

        /***
        }
        ***/
        inline std::string end () {
            return "}";
        }

        /***
        {
        ***/
        inline std::string blockbegin () {
            return "{";
        }

        /***
        if (<cond>) {
        ***/
        std::string ifBegin (std::string const & cond);

        /***
        else {
        ***/
        inline std::string elseBegin () {
            return "else {";
        }

        /***
        } else {
        ***/
        inline std::string cuddledElse () {
            return "} else {";
        }

        /***
        swith (<val>) {
        ***/
        std::string switchBegin (std::string const & val);

        /***
        case <num>: <`default:`>?
            <stmt1>
            <stmt2>
            ...
            <`break;`>?
        ***/
        template <typename... Ts>
        std::string switchCase (std::size_t num, bool defolt, bool brek, Ts const &... stmts) {
            auto newLine = c::newLine();
            auto indent  = c::indentation();
            auto label   = std::string{} + "case " + std::to_string(num) + ":" + (defolt ? " default:" : "");
            return label + newLine + c::indented(c::join("", stmts...)) + newLine + (brek ? indent + "break;" : "");
        }

        /***
        while (<cond>) {
        ***/
        std::string whileBegin (std::string const & cond);

        /***
        for (<init>; <cond>; <iter>) {
        ***/
        std::string inlineForBegin (std::string const & init, std::string const & cond, std::string const & iter);

        /***
        for (
            <init>;
            <cond>;
            <iter>
        ) {
        ***/
        std::string forBegin (std::string const & init, std::string const & cond, std::string const & iter);

        /***
        <out> <name> (<param1>, <param2>, ...) {
        ***/
        template <typename... Ts>
        std::string inlineFunctionBegin (
            std::string const & out, std::string const & name, Ts const &... params
        ) {
            return out + " " + name + " (" + c::inlineJoin(",", params...) + ") {";
        }

        /***
        <out> <name> (
            <param1>,
            <param2>,
            ...
        ) {
        ***/
        template <typename... Ts>
        std::string functionBegin (
            std::string const & out, std::string const & name, Ts const &... params
        ) {
            auto newLine = c::newLine();
            auto joined  = c::join(",", params...);
            return out + " " + name + " (" + 
                (joined.empty() ? "" : newLine + c::indented(joined) + newLine) + ") {";
        }

        /***
        <type1> arg1,
        <type2> arg2,
        ...
        ***/
        template <esl::sized_range T>
        std::string functionParameters (T types) {
            for (auto const & [i, type]: esl::enumerate(types))
                type += std::string{} + " " + str::argument + std::to_string(i);
            return c::join(",", types);
        }

        /***
        arg1,
        arg2,
        ...
        ***/
        template <esl::sized_range T>
        std::string functionArguments (T types) {
            for (auto const & [i, type]: esl::enumerate(types))
                type = str::argument + std::to_string(i);
            return c::join(",", types);
        }

        /***
            <stmt1>;
            <stmt2>;
            ...
            <stmtN>;
        ***/
        template <typename... Ts>
        std::string functionBody (
            Ts const &... params
        ) {
            return c::indented(c::terminatedJoin(";", params...));
        }

        //// Looping ////

        /***
        struct {
            int pos;
            <decl1>;
            <decl2>;
            ...
        } iter = {0, <init1>, <init2>, ...}
        ***/
        template <esl::range T, esl::range U>
        std::string iterationStructure (T const & decls, U const & inits) {
            auto posDecl = c::declaration(c::integralType(), def::position);
            auto type    = c::anonymousStructureDefinition(posDecl, decls);
            auto init    = c::inlineInit(inits);
            return c::definition(type, def::iteration, init);
        }

        /***
        int iter = 0
        ***/
        std::string iterationVariable ();

        //// Labels ////

        /***
        goto <label>
        ***/
        std::string jump (std::string label);

        /***
        <label>:
        ***/
        std::string label (std::string label);

        /***
        # GNU extension - local labels
        __label__ <name>
        ***/
        std::string labelDeclaration (std::string const & name);

        //// Returning ////

        // TODO: Might not be needed.
        /***
        __label__ ret;
        struct result {
            <type1> e0;
            <type2> e1;
            ...
        } result;
        ***/
        template <esl::sized_range T> requires (std::convertible_to<esl::range_value_type<T>, std::string>)
        std::string returnInit (T const & types, bool function = false) {
            esl::tiny_vector<std::string> decls;
            decls.reserve(decls.size());
            for (auto const & [i, type]: esl::enumerate(types))
                decls.push_back(std::string{type} + " " + c::tupleElementName(i));
            return
                (function ? "" : c::statement(c::labelDeclaration(def::returnLabel)) + c::newLine()) +
                c::statement(c::declaration(c::structureDefinition(def::returnType, decls), def::returnVariable));
        }

        /***
        __label__ ret;
        struct result {
            <type1> e0;
            <type2> e5; # Some elements can be skipped.
            ...
        } result;
        ***/
        template <esl::sized_range T> requires (std::convertible_to<esl::range_value_type<T>, std::string>)
        std::string returnInitFromDeclarations (T const & decls, bool function = false) {
            return
                (function ? "" : c::statement(c::labelDeclaration(def::returnLabel)) + c::newLine()) +
                c::statement(c::declaration(c::structureDefinition(def::returnType, decls), def::returnVariable));
        }

        /***
        ret: result;
        ***/
        std::string blockExpressionReturn ();

        /***
        ret:
        ***/
        std::string mainReturn ();

        /***
        goto ret;
        ***/
        std::string returnJump ();

        /***
        result.e<number> = <value>;
        ***/
        std::string returnValue (std::size_t number, std::string const & value);

        /***
        result.e<number>.branch = <branch>;
        result.e<number>.data.v<branch> = <expr>; # optionally
        ***/
        std::string returnFunction (
            std::size_t number,
            std::size_t branch,
            std::optional<std::string> const & value
        );

        /***
        <type> result;
        ***/
        std::string functionResultInit (std::string type);

        /***
        return result;
        ***/
        std::string functionResultReturn ();

        //// Attributes ////

        /***
        # GNU extension
        __attribute__((<attr>))
        ***/
        std::string attribute (std::string const & attr);

        /** Avoids warnings about unused declarations with -Wall. */
        std::string unused ();

        /** Could be useful for some IO declarations. */
        std::string used ();

        /** A hot branch or a function. */
        std::string hot ();

        /** A cold branch or a function. */
        std::string cold ();

        /** A pure function. */
        std::string pure ();

        //// Literals ////

        /***
        # Boolean literal
        # Requires <stdbool.h>
        true/false
        ***/
        std::string booleanLiteral (bool val);

        /***
        # Integer literal
        <val>
        ***/
        std::string integralLiteral (sem::Integral val);

        /***
        # Float literal
        <val>f
        ***/
        std::string floatingLiteral (sem::Floating val);

        // TODO: Note that it is also possible to construct arrays with a compound literal:
        // (int [4]) {1, 2, 3, 4}
        // This could be useful when passing around newly initialized arrays.
        /***
        # GNU compound literals extension
        (<structure>) {
            <init1>,
            <init2>,
            ...
        }
        ***/
        template <typename... Ts>
        std::string structureLiteral (std::string const & structure, Ts const &... inits) {
            return c::cast(c::init(inits...), structure);
        }

        /***
        (struct <type>) {
            .branch = <branch>,
            .data.v<branch> = <expr> # optionally
        }
        ***/
        std::string closureLiteral (
            std::string                const & type,
            std::size_t                const & branch,
            std::optional<std::string> const & expr
        );

        /***
        (struct cth_empty) {}
        ***/
        std::string emptyValue ();

        //// Unsorted (TODO) ////

#if 0
        /***
        arr_copy(<src>)
        ***/
        inline std::string arrayCopy (std::string const & src) {
            return c::call(def::arrayCopy, src);
        }

        /***
        arr_copy_to(<src>)
        ***/
        inline std::string arrayCopyTo (std::string const & src, std::string const & dst) {
            return c::call(def::arrayCopy, src, dst);
        }
#endif

        // TODO: All functions should follow this parameter order:
        // name, type, value (e.g. declare(name, type), define(name, type, value))
        // except when there is a "source" and "destination", then it should be:
        // source, destination
        // (e.g. cast(value, type))

    }

    namespace tpl {

        /** E.g. `const_struct_cth_foo_bar` -> `struct cth_foo_bar const` */
        struct TypeSpecifier {
            constexpr static char const * delim = "_";

            std::string type;
            bool constant  = false;
            bool structure = false;
            bool pointer   = false;
            bool constptr  = false;
            // Do not mix pointer and constptr.
            // TODO: Instead, make pointer a three-state value {none, pointer, constptr}

            // TODO: Should I omit the `cth` prefix in the merged form?
            // It would make the merged type names shorter,
            // but keeping the prefix will be simpler to implement and will be more flexible.
            std::string merged () const;
            std::string full   () const;
        };

        inline std::string mergeTypeSpecifier (TypeSpecifier spec) {
            return spec.merged();
        }

        struct Array {
            TypeSpecifier elemType;
            sem::Integral size;

            std::string name       () const;
            std::string definition () const;
        };

        struct Buffer {
            sem::Integral size;

            std::string name       () const;
            std::string definition () const;
        };

        struct Tuple {
            esl::tiny_vector<TypeSpecifier> types;

            std::string name       () const;
            std::string definition () const;
        };

    }

}
