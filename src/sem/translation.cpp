#include "sem/translation.hpp"

// TODO: Explicit includes

namespace cynth::c {

    std::string indentation (int n) {
        return esl::repeat(str::indent, n);
    }

    std::string indented (std::string stmt, int n) {
        // TODO: The empty check should happen in esl::indent.
        return stmt.empty() ? "" : esl::indent(c::indentation(n), c::newLine(), stmt);
    }

    std::string expression (std::string const & expr) {
        constexpr bool neatParentheses = true; // TODO: Put this in some global config.
        if constexpr (neatParentheses)
            return esl::parenthesized(expr);
        else
            return "(" + expr + ")";
    }

    std::string statement (std::string const & stmt) {
        return stmt + ";";
    }

    std::string brackets (std::string const & expr) {
        return "[" + expr + "]";
    }

    std::string declaration (std::string const & type, std::string const & name) {
        return type + " " + name;
    }

    std::string definition (std::string const & type, std::string const & name, std::string const & val) {
        return type + " " + name + " = " + val;
    }

    std::string global (std::string const & name) {
        return std::string{} + str::global + "_" + name;
    }

    std::string valueName (std::string const & id) {
        return std::string{} + str::value + "_" + id;
    }

    std::string outputValueName (std::string const & id) {
        return c::global(std::string{} + str::output + str::value + "_" + id);
    }

    std::string inputValueName (std::string const & id) {
        return c::global(std::string{} + str::input + str::value + "_" + id);
    }

    std::string bufferValueName (std::string const & id) {
        return c::global(std::string{} + str::buffer + str::value + "_" + id);
    }

    std::string inputBufferValueName (std::string const & id) {
        return c::global(std::string{} + str::input + str::buffer + str::value + "_" + id);
    }

    std::string outputBufferValueName (std::string const & id) {
        return c::global(std::string{} + str::output + str::buffer + str::value + "_" + id);
    }

    std::string variableName (std::string const & id) {
        return std::string{} + str::variable + "_" + id;
    }

    std::string tupleVariableName (std::string const & id) {
        return std::string{} + str::tuple + str::variable + "_" + id;
    }

    std::string memberName (std::string const & id) {
        return std::string{} + str::member + "_" + id;
    }

    std::string tupleElementName (std::size_t number) {
        return std::string{} + str::element + std::to_string(number);
    }

    std::string returnElementName (std::size_t number) {
        return std::string{} + str::element + std::to_string(number);
    }

    std::string closureVariableName (std::string const & id) {
        return std::string{} + str::closure + str::variable + "_" + id;
    }

    std::string closureType (std::string const & id) {
        return c::global(std::string{} + str::closure + "_" + id);
    }

    std::string functionName (std::string const & id) {
        return c::global(std::string{} + str::function + "_" + id);
    }

    std::string dereference (std::string const & val) {
        return "*" + val;
    }

    std::string addressof (std::string const & val) {
        return "&" + val;
    }

    std::string arraySubscript (std::string const & array, std::string const & index) {
        return array + "[" + index + "]";
    }

    std::string cast (std::string const & val, std::string const & type) {
        return "(" + type + ") " + val;
    }

    std::string increment (std::string const & val) {
        return "++" + val;
    }

    std::string advance (std::string const & target, std::string const & diff) {
        return target + " += " + diff;
    }

    std::string ternary (std::string const & cond, std::string const & pos, std::string const & neg) {
        return cond + " ? " + pos + " : " + neg;
    }

    std::string structure (std::string const & name) {
        return std::string{} + "struct " + name;
    }

    std::string constness (std::string const & type) {
        return type + " const";
    }

    std::string volatility (std::string const & type) {
        return type + " volatile";
    }

    std::string pointer (std::string const & type) {
        return type + " *";
    }

    std::string infer (std::string const & value) {
        return std::string{} + str::gnuTypeof + "(" + value + ")";
    }

    std::string inferSize (std::string const & value) {
        return std::string{} + "sizeof" + "(" + value + ")";
    }

    std::string autoType () {
        return str::gnuAuto;
    }

    std::string booleanType () {
        //return c::global(str::boolean);
        return def::boolean;
    }

    std::string integralType () {
        //return c::global(str::integral);
        return def::integral;
    }

    std::string floatingType () {
        //return c::global(str::floating);
        return def::floating;
    }

    std::string assignment (std::string const & src, std::string const & dst) {
        return dst + " = " + src;
    }

    std::string valueAssignment (std::string const & src, std::string const & dst) {
        return c::assignment(src, c::dereference(dst));
    }

    std::string designatedInitialization (std::string const & src, std::string const & dst) {
        return "." + dst + " = " + src;
    }

    std::string dataInitialization (std::string const & expr) {
        return c::designatedInitialization(expr, def::dataMember);
    }

    std::string closureDataInitialization (std::size_t number, std::string const & expr) {
        return c::designatedInitialization(
            expr, std::string{} + def::dataMember + "." + str::variant + std::to_string(number)
        );
    }

    std::string branchInitialization (std::size_t const & number) {
        return c::designatedInitialization(std::to_string(number), def::branchMember);
    }

    std::string arrayBulkInitialization (
        std::string const & array, std::string const & from
        //sem::Integral size, std::string const & type
    ) {
        //auto sizeArg = c::mul(std::to_string(size), c::inferSize(type));
        auto sizeArg = c::inferSize(array);
        // This only works when <array> is an array, not a pointer, which is OK
        // for "initialization" of allocated array values, but it not OK for a general-case array copy.
        return c::call("memcpy", array, from, sizeArg);
    }

    std::string arrayBulkCopy (
        std::string const & array, std::string const & from,
        sem::Integral size, std::string const & type
    ) {
        auto sizeArg = c::mul(std::to_string(size), c::inferSize(type));
        return c::call("memcpy", array, from, sizeArg);
    }

    std::string memberAccess (std::string const & structure, std::string const & member) {
        return structure + "." + member;
    }

    std::string tupleElement (std::string const & structure, std::size_t number) {
        return c::memberAccess(structure, c::tupleElementName(number));
    }

    std::string unionVariant (std::string const & structure, std::size_t number) {
        return c::memberAccess(structure, str::variant + std::to_string(number));
    }

    std::string bufferData (std::string const & structure) {
        return structure + "." + def::dataMember;
    }

    std::string bufferOffset (std::string const & structure) {
        return structure + "." + def::dataMember;
    }

    std::string iterationPosition () {
        return std::string{} + def::iteration + "." + def::position;
    }

    std::string simpleIterationPosition () {
        return def::iteration;
    }

    std::string returnElement (std::size_t number) {
        return c::memberAccess(def::returnVariable, c::returnElementName(number));
    }

    std::string closureData (std::string const & structure, std::size_t variant) {
        return structure + "." + def::closureDataMember + "." + str::variant + std::to_string(variant);
    }

    std::string closureBranch (std::string const & structure) {
        return structure + "." + def::branchMember;
    }

    // TODO: Remove this.
    std::string arrayTypeName (std::size_t size, std::string const & type) {
        return c::global(c::templateArguments(std::string{} + str::array, std::to_string(size), type));
    }

    std::string arrayType (std::size_t size, std::string const & type) {
        return c::global(c::templateArguments(std::string{} + str::array, std::to_string(size), type));
        //return std::string{} + str::gnuTypeof + "(" + type + " " + "[" + size + "])";
    }

    std::string bufferType (sem::Integral size) {
        return c::structure(c::global(c::templateArguments(std::string{} + str::buffer, std::to_string(size))));
    }

    std::string emptyType () {
        return c::structure(c::global(def::empty));
    }

    std::string emptyTypeDefinition () {
        return c::structureDefinition(c::global(def::empty));
    }

    std::string bufferPointer () {
        return c::constness(c::pointer(c::constness(c::floatingType())));
    }

    std::string inputType (std::string const & type) {
        return type;
    }

    std::string inputPointerType (std::string const & type) {
        return c::pointer(c::constness(c::inputType(type)));
    }

    std::string outputType (std::string const & type) {
        return type;
    }

    std::string outputPointerType (std::string const & type) {
        return c::pointer(c::outputType(type));
    }

    std::string blockExpressionBegin (std::string const & var) {
        return c::definition(c::autoType(), var, c::blockExpressionBegin());
    }

    std::string ifBegin (std::string const & cond) {
        return std::string{} + "if (" + cond + ") {";
    }

    std::string switchBegin (std::string const & val) {
        return std::string{} + "switch (" + val + ") {";
    }

    std::string whileBegin (std::string const & cond) {
        return "while (" + cond + ") {";
    }

    std::string inlineForBegin (std::string const & init, std::string const & cond, std::string const & iter) {
        return "for (" + c::join(";", init, cond, iter) + ") {";
    }

    std::string forBegin (std::string const & init, std::string const & cond, std::string const & iter) {
        auto newLine = c::newLine();
        return "for (" + newLine + c::indented(c::join(";", init, cond, iter)) + newLine + ") {";
    }

    std::string iterationVariable () {
        return c::definition(c::integralType(), def::iteration, "0");
    }

    std::string jump (std::string label) {
        return std::string{} + "goto " + label;
    }

    std::string label (std::string label) {
        return label + ":";
    }

    std::string labelDeclaration (std::string const & name) {
        return std::string{} + str::gnuLabel + " " + name;
    }

    std::string blockExpressionReturn () {
        return c::statement(c::label(def::returnLabel) + " " + def::returnVariable);
    }

    std::string mainReturn () {
        // TODO...
        return c::label(def::returnLabel);
    }

    std::string returnJump () {
        return c::statement(c::jump(def::returnLabel));
    }

    std::string returnValue (std::size_t number, std::string const & value) {
        auto target  = c::returnElement(number);
        return c::statement(c::assignment(value, target));
    }

    std::string returnFunction (
        std::size_t number,
        std::size_t branch,
        std::optional<std::string> const & value
    ) {
        auto branchString = std::to_string(branch);
        auto branchTarget = c::memberAccess(c::returnElement(number), def::branchMember);
        if (value) {
            auto dataTarget =
                c::unionVariant(c::memberAccess(c::returnElement(number), def::closureDataMember), branch);
            return
                c::statement(c::assignment(branchString, branchTarget)) + c::newLine() +
                c::statement(c::assignment(*value, dataTarget));
        }
        return c::statement(c::assignment(branchString, branchTarget));
    }

    std::string functionResultInit (std::string type) {
        return c::statement(c::declaration(type, def::returnVariable));
    }

    std::string functionResultReturn () {
        return c::statement(c::functionReturn(def::returnVariable));
    }

    std::string attribute (std::string const & attr) {
        return std::string{} + str::gnuAttribute + "((" + attr + "))";
    }

    std::string unused () {
        return c::attribute("unused");
    }

    std::string used () {
        return c::attribute("used");
    }

    std::string hot () {
        return c::attribute("hot");
    }

    std::string cold () {
        return c::attribute("cold");
    }

    std::string pure () {
        return c::attribute("pure");
    }

    std::string booleanLiteral (bool val) {
        //return c::cast(val ? "1" : "0", c::booleanType());
        return val ? "true" : "false";
    }

    std::string integralLiteral (sem::Integral val) {
        return std::to_string(val) + def::integralSuffix;
    }

    std::string floatingLiteral (sem::Floating val) {
        return std::to_string(val) + def::floatingSuffix;
    }

    std::string closureLiteral (
        std::string                const & type,
        std::size_t                const & branch,
        std::optional<std::string> const & expr
    ) {
        return c::structureLiteral(
            c::structure(type),
            c::branchInitialization(branch),
            c::closureDataInitialization(branch, expr.value_or(c::emptyValue()))
        );
    }

    std::string emptyValue () {
        return "(" + c::structure(c::global(def::empty)) + ") {}";
    }

}

namespace cynth::tpl {

    std::string TypeSpecifier::merged () const {
        return
            (constant  ? std::string{} + str::constant        + delim : "") +
            (constptr  ? std::string{} + str::constantPointer + delim : "") +
            (pointer   ? std::string{} + str::pointer         + delim : "") +
            (structure ? std::string{} + str::structure       + delim : "") +
            type;
    }

    std::string TypeSpecifier::full () const {
        return
            (structure  ? std::string{} + "struct "  : "") +
            type +
            (constant   ? std::string{} + " const"   : "") +
            (pointer    ? std::string{} + " *"       : "") +
            (constptr   ? std::string{} + " * const" : "");
    }

    std::string Array::name () const {
        return c::arrayType(size, elemType.merged());
    }

    std::string Array::definition () const {
        return c::statement(
            "typedef " + elemType.full() + " " + name() +
            " [" + std::to_string(size) + "]"
        );
    }

    std::string Buffer::name () const {
        return c::bufferType(size);
    }

    std::string Buffer::definition () const {
        return c::statement(c::structureDefinition(
            name(),
            c::declaration(c::arrayType(size, c::floatingType()), def::dataMember),
            c::declaration(c::integralType(), def::offsetMember)
        ));
    }

    namespace {

        std::string tupleName (Tuple const & tup) {
            return c::tupleTypeName(
                esl::lift<esl::target::vector>(mergeTypeSpecifier)(tup.types)
            );
        }

    }

    std::string Tuple::name () const {
        return c::tupleType(
            esl::lift<esl::target::vector>(mergeTypeSpecifier)(types)
        );
    }

    std::string Tuple::definition () const {
        std::vector<std::string> decls;
        decls.reserve(types.size());
        for (auto const & [i, s]: esl::enumerate(types))
            decls.push_back(c::declaration(s.full(), c::tupleElementName(i)));
        //auto name = name();
        auto name = tupleName(*this);
        return c::statement(c::structureDefinition(name, decls));
    }

}
