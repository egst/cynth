#include "syn/nodes/expressions.hpp"

#include <utility>

#include "esl/component.hpp"

namespace esl {

    using cynth::syn::node::Add;
    using cynth::syn::node::And;
    using cynth::syn::node::Application;
    using cynth::syn::node::Array;
    using cynth::syn::node::Block;
    using cynth::syn::node::Bool;
    using cynth::syn::node::Conversion;
    using cynth::syn::node::Div;
    using cynth::syn::node::Eq;
    using cynth::syn::node::ExprFor;
    using cynth::syn::node::ExprIf;
    using cynth::syn::node::Float;
    using cynth::syn::node::Function;
    using cynth::syn::node::Ge;
    using cynth::syn::node::Gt;
    using cynth::syn::node::Int;
    using cynth::syn::node::Le;
    using cynth::syn::node::Lt;
    using cynth::syn::node::Minus;
    using cynth::syn::node::Mod;
    using cynth::syn::node::Mul;
    using cynth::syn::node::Name;
    using cynth::syn::node::Ne;
    using cynth::syn::node::Not;
    using cynth::syn::node::Or;
    using cynth::syn::node::Plus;
    using cynth::syn::node::Pow;
    using cynth::syn::node::String;
    using cynth::syn::node::Sub;
    using cynth::syn::node::Subscript;
    using cynth::syn::node::Tuple;

    template <>
    void component_deleter<Add>::operator () (Add * ptr) const {
        delete ptr;
    }

    template <>
    Add * component_allocator<Add>::operator () (Add const & other) const {
        return new Add{other};
    }

    template <>
    Add * component_allocator<Add>::operator () (Add && other) const {
        return new Add{std::move(other)};
    }

    template <>
    void component_deleter<And>::operator () (And * ptr) const {
        delete ptr;
    }

    template <>
    And * component_allocator<And>::operator () (And const & other) const {
        return new And{other};
    }

    template <>
    And * component_allocator<And>::operator () (And && other) const {
        return new And{std::move(other)};
    }

    template <>
    void component_deleter<Application>::operator () (Application * ptr) const {
        delete ptr;
    }

    template <>
    Application * component_allocator<Application>::operator () (Application const & other) const {
        return new Application{other};
    }

    template <>
    Application * component_allocator<Application>::operator () (Application && other) const {
        return new Application{std::move(other)};
    }

    template <>
    void component_deleter<Array>::operator () (Array * ptr) const {
        delete ptr;
    }

    template <>
    Array * component_allocator<Array>::operator () (Array const & other) const {
        return new Array{other};
    }

    template <>
    Array * component_allocator<Array>::operator () (Array && other) const {
        return new Array{std::move(other)};
    }

    template <>
    void component_deleter<Block>::operator () (Block * ptr) const {
        delete ptr;
    }

    template <>
    Block * component_allocator<Block>::operator () (Block const & other) const {
        return new Block{other};
    }

    template <>
    Block * component_allocator<Block>::operator () (Block && other) const {
        return new Block{std::move(other)};
    }

    template <>
    void component_deleter<Bool>::operator () (Bool * ptr) const {
        delete ptr;
    }

    template <>
    Bool * component_allocator<Bool>::operator () (Bool const & other) const {
        return new Bool{other};
    }

    template <>
    Bool * component_allocator<Bool>::operator () (Bool && other) const {
        return new Bool{std::move(other)};
    }

    template <>
    void component_deleter<Conversion>::operator () (Conversion * ptr) const {
        delete ptr;
    }

    template <>
    Conversion * component_allocator<Conversion>::operator () (Conversion const & other) const {
        return new Conversion{other};
    }

    template <>
    Conversion * component_allocator<Conversion>::operator () (Conversion && other) const {
        return new Conversion{std::move(other)};
    }

    template <>
    void component_deleter<Div>::operator () (Div * ptr) const {
        delete ptr;
    }

    template <>
    Div * component_allocator<Div>::operator () (Div const & other) const {
        return new Div{other};
    }

    template <>
    Div * component_allocator<Div>::operator () (Div && other) const {
        return new Div{std::move(other)};
    }

    template <>
    void component_deleter<Eq>::operator () (Eq * ptr) const {
        delete ptr;
    }

    template <>
    Eq * component_allocator<Eq>::operator () (Eq const & other) const {
        return new Eq{other};
    }

    template <>
    Eq * component_allocator<Eq>::operator () (Eq && other) const {
        return new Eq{std::move(other)};
    }

    template <>
    void component_deleter<ExprFor>::operator () (ExprFor * ptr) const {
        delete ptr;
    }

    template <>
    ExprFor * component_allocator<ExprFor>::operator () (ExprFor const & other) const {
        return new ExprFor{other};
    }

    template <>
    ExprFor * component_allocator<ExprFor>::operator () (ExprFor && other) const {
        return new ExprFor{std::move(other)};
    }

    template <>
    void component_deleter<ExprIf>::operator () (ExprIf * ptr) const {
        delete ptr;
    }

    template <>
    ExprIf * component_allocator<ExprIf>::operator () (ExprIf const & other) const {
        return new ExprIf{other};
    }

    template <>
    ExprIf * component_allocator<ExprIf>::operator () (ExprIf && other) const {
        return new ExprIf{std::move(other)};
    }

    template <>
    void component_deleter<Float>::operator () (Float * ptr) const {
        delete ptr;
    }

    template <>
    Float * component_allocator<Float>::operator () (Float const & other) const {
        return new Float{other};
    }

    template <>
    Float * component_allocator<Float>::operator () (Float && other) const {
        return new Float{std::move(other)};
    }

    template <>
    void component_deleter<Function>::operator () (Function * ptr) const {
        delete ptr;
    }

    template <>
    Function * component_allocator<Function>::operator () (Function const & other) const {
        return new Function{other};
    }

    template <>
    Function * component_allocator<Function>::operator () (Function && other) const {
        return new Function{std::move(other)};
    }

    template <>
    void component_deleter<Ge>::operator () (Ge * ptr) const {
        delete ptr;
    }

    template <>
    Ge * component_allocator<Ge>::operator () (Ge const & other) const {
        return new Ge{other};
    }

    template <>
    Ge * component_allocator<Ge>::operator () (Ge && other) const {
        return new Ge{std::move(other)};
    }

    template <>
    void component_deleter<Gt>::operator () (Gt * ptr) const {
        delete ptr;
    }

    template <>
    Gt * component_allocator<Gt>::operator () (Gt const & other) const {
        return new Gt{other};
    }

    template <>
    Gt * component_allocator<Gt>::operator () (Gt && other) const {
        return new Gt{std::move(other)};
    }

    template <>
    void component_deleter<Int>::operator () (Int * ptr) const {
        delete ptr;
    }

    template <>
    Int * component_allocator<Int>::operator () (Int const & other) const {
        return new Int{other};
    }

    template <>
    Int * component_allocator<Int>::operator () (Int && other) const {
        return new Int{std::move(other)};
    }

    template <>
    void component_deleter<Le>::operator () (Le * ptr) const {
        delete ptr;
    }

    template <>
    Le * component_allocator<Le>::operator () (Le const & other) const {
        return new Le{other};
    }

    template <>
    Le * component_allocator<Le>::operator () (Le && other) const {
        return new Le{std::move(other)};
    }

    template <>
    void component_deleter<Lt>::operator () (Lt * ptr) const {
        delete ptr;
    }

    template <>
    Lt * component_allocator<Lt>::operator () (Lt const & other) const {
        return new Lt{other};
    }

    template <>
    Lt * component_allocator<Lt>::operator () (Lt && other) const {
        return new Lt{std::move(other)};
    }

    template <>
    void component_deleter<Minus>::operator () (Minus * ptr) const {
        delete ptr;
    }

    template <>
    Minus * component_allocator<Minus>::operator () (Minus const & other) const {
        return new Minus{other};
    }

    template <>
    Minus * component_allocator<Minus>::operator () (Minus && other) const {
        return new Minus{std::move(other)};
    }

    template <>
    void component_deleter<Mod>::operator () (Mod * ptr) const {
        delete ptr;
    }

    template <>
    Mod * component_allocator<Mod>::operator () (Mod const & other) const {
        return new Mod{other};
    }

    template <>
    Mod * component_allocator<Mod>::operator () (Mod && other) const {
        return new Mod{std::move(other)};
    }

    template <>
    void component_deleter<Mul>::operator () (Mul * ptr) const {
        delete ptr;
    }

    template <>
    Mul * component_allocator<Mul>::operator () (Mul const & other) const {
        return new Mul{other};
    }

    template <>
    Mul * component_allocator<Mul>::operator () (Mul && other) const {
        return new Mul{std::move(other)};
    }

    template <>
    void component_deleter<Name>::operator () (Name * ptr) const {
        delete ptr;
    }

    template <>
    Name * component_allocator<Name>::operator () (Name const & other) const {
        return new Name{other};
    }

    template <>
    Name * component_allocator<Name>::operator () (Name && other) const {
        return new Name{std::move(other)};
    }

    template <>
    void component_deleter<Ne>::operator () (Ne * ptr) const {
        delete ptr;
    }

    template <>
    Ne * component_allocator<Ne>::operator () (Ne const & other) const {
        return new Ne{other};
    }

    template <>
    Ne * component_allocator<Ne>::operator () (Ne && other) const {
        return new Ne{std::move(other)};
    }

    template <>
    void component_deleter<Not>::operator () (Not * ptr) const {
        delete ptr;
    }

    template <>
    Not * component_allocator<Not>::operator () (Not const & other) const {
        return new Not{other};
    }

    template <>
    Not * component_allocator<Not>::operator () (Not && other) const {
        return new Not{std::move(other)};
    }

    template <>
    void component_deleter<Or>::operator () (Or * ptr) const {
        delete ptr;
    }

    template <>
    Or * component_allocator<Or>::operator () (Or const & other) const {
        return new Or{other};
    }

    template <>
    Or * component_allocator<Or>::operator () (Or && other) const {
        return new Or{std::move(other)};
    }

    template <>
    void component_deleter<Plus>::operator () (Plus * ptr) const {
        delete ptr;
    }

    template <>
    Plus * component_allocator<Plus>::operator () (Plus const & other) const {
        return new Plus{other};
    }

    template <>
    Plus * component_allocator<Plus>::operator () (Plus && other) const {
        return new Plus{std::move(other)};
    }

    template <>
    void component_deleter<Pow>::operator () (Pow * ptr) const {
        delete ptr;
    }

    template <>
    Pow * component_allocator<Pow>::operator () (Pow const & other) const {
        return new Pow{other};
    }

    template <>
    Pow * component_allocator<Pow>::operator () (Pow && other) const {
        return new Pow{std::move(other)};
    }

    template <>
    void component_deleter<String>::operator () (String * ptr) const {
        delete ptr;
    }

    template <>
    String * component_allocator<String>::operator () (String const & other) const {
        return new String{other};
    }

    template <>
    String * component_allocator<String>::operator () (String && other) const {
        return new String{std::move(other)};
    }

    template <>
    void component_deleter<Sub>::operator () (Sub * ptr) const {
        delete ptr;
    }

    template <>
    Sub * component_allocator<Sub>::operator () (Sub const & other) const {
        return new Sub{other};
    }

    template <>
    Sub * component_allocator<Sub>::operator () (Sub && other) const {
        return new Sub{std::move(other)};
    }

    template <>
    void component_deleter<Subscript>::operator () (Subscript * ptr) const {
        delete ptr;
    }

    template <>
    Subscript* component_allocator<Subscript>::operator () (Subscript const & other) const {
        return new Subscript{other};
    }

    template <>
    Subscript* component_allocator<Subscript>::operator () (Subscript && other) const {
        return new Subscript{std::move(other)};
    }

    template <>
    void component_deleter<Tuple>::operator () (Tuple * ptr) const {
        delete ptr;
    }

    template <>
    Tuple * component_allocator<Tuple>::operator () (Tuple const & other) const {
        return new Tuple{other};
    }

    template <>
    Tuple * component_allocator<Tuple>::operator () (Tuple && other) const {
        return new Tuple{std::move(other)};
    }

}
