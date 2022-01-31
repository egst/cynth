#pragma once

#include <cmath>
#include <string>
#include <utility>

#include "esl/concepts.hpp"
#include "esl/functional.hpp"

#include "interface/types.hpp"
#include "sem/compound.hpp"
#include "sem/numeric_types.hpp"
#include "sem/translation.hpp"

namespace cynth::sem {

    // The integer division is floored. The modulo represents the corresponding remainder.
    // To be consitent, the float to int conversion is also floored.
    // Integer division by zero is undefined behaviour.
    // Floating-point division by zero behaviour is implementation defined in both the C and the C++ standards,
    // and thus will depend on the C and C++ compiler used.

    // Logical and and or operations are currently not short-circuiting at compile-time to simplify implementation.
    // Compile-time evaluation/execution never produces side-effects, so it shouldn't be a problem.
    // At run-time they are always shord-circuiting.

    namespace comptime {

        namespace implementation {

            inline Integral floor (Floating a) {
                return static_cast<Integral>(std::floor(a));
            }

            inline Integral idiv (Integral a, Integral b) {
                return (a - 2 * (a < 0) + 2 * (b < 0)) / b;
            }

            inline Integral imod (Integral a, Integral b) {
                return ((a % b) + b) % b;
            }

            /*
            inline Floating fmod (Floating a, Floating b) {
                return std::fmod((std::fmod(a, b) + b), b);
            }
            */
            constexpr auto fmod =
                [] (esl::same_but_cvref<Floating> auto a, esl::same_but_cvref<Floating> auto b) -> Floating {
                    return std::fmod((std::fmod(a, b) + b), b);
                };

            inline Floating fpow (Floating a, Floating b) {
                return std::pow(a, b);
            }

            // I'll keep these non-branching implementations for now. Benchmarks suggest that there is only a slight
            // improvement over equivalent branching algorithms, the performance might depend on the target platform.
            // TODO: Check if there is a way to leverage the target architechture's division and modulo implementations.
            // Is it common for processors to implement a flooring division?
            // I won't bother with this if most current processors do a truncating division natively.

        }

        template <typename T>
        concept numeric = esl::same_but_cvref<T, Integral> || esl::same_but_cvref<T, Floating>;

        template <typename T>
        concept simple =
            esl::same_but_cvref<T, Integral> || esl::same_but_cvref<T, Floating> || esl::same_but_cvref<T, bool>;

        constexpr auto plus  = [] (numeric auto a) { return +a; };
        constexpr auto minus = [] (numeric auto a) { return -a; };
        constexpr auto add   = [] <numeric T> (T a, T b) { return a + b; };
        constexpr auto sub   = [] <numeric T> (T a, T b) { return a - b; };
        constexpr auto mul   = [] <numeric T> (T a, T b) { return a * b; };
        constexpr auto div   = esl::overload(implementation::idiv, [] (Floating a, Floating b) { return a / b; });
        constexpr auto mod   = esl::overload(implementation::imod, implementation::fmod);
        constexpr auto pow   = implementation::fpow; // Integer exponentiation not supported yet.
        constexpr auto lt    = [] <simple T> (T a, T b) { return a < b; };
        constexpr auto gt    = [] <simple T> (T a, T b) { return a > b; };
        constexpr auto le    = [] <simple T> (T a, T b) { return a <= b; };
        constexpr auto ge    = [] <simple T> (T a, T b) { return a >= b; };
        constexpr auto eq    = [] <simple T> (T a, T b) { return a == b; };
        constexpr auto ne    = [] <simple T> (T a, T b) { return a != b; };
        constexpr auto lnot  = [] (bool a) { return !a; };
        constexpr auto land  = [] (bool a, bool b) { return a && b; };
        constexpr auto lor   = [] (bool a, bool b) { return a || b; };
        /*
        constexpr auto inc   = [] (numeric auto a) { return ++a; };
        constexpr auto dec   = [] (numeric auto a) { return --a; };
        constexpr auto bnot  = [] (Integral a) { return ~a; };
        constexpr auto band  = [] (Integral a, Integral b) { return a & b; };
        constexpr auto bor   = [] (Integral a, Integral b) { return a | b; };
        constexpr auto bxor  = [] (Integral a, Integral b) { return a ^ b; };
        */

        constexpr auto btoi = [] (bool     a) -> Integral { return a; };
        constexpr auto itob = [] (Integral a) -> bool     { return a; };
        constexpr auto itof = [] (Integral a) -> Floating { return a; };
        constexpr auto ftoi = [] (Floating a) -> Integral { return implementation::floor(a); };
        constexpr auto btof = [] (bool     a) -> Floating { return a; };
        constexpr auto ftob = [] (Floating a) -> bool     { return implementation::floor(a); };

    }

    namespace runtime {

        namespace definition {

            /***
            int cth_imod (int a, int b) {
                return ((a % b) + b) % b;
            }
            ***/
            inline std::string imod () {
                constexpr auto first  = "a";
                constexpr auto second = "b";
                return
                    /*c::inlined*/(c::inlineFunctionBegin(
                        c::integralType(),
                        c::global(def::integralModulo),
                        c::declaration(c::integralType(), first),
                        c::declaration(c::integralType(), second)
                    )) + c::newLine() +
                    c::functionBody(c::functionReturn(
                        c::mod(c::expression(c::add(c::expression(c::mod(first, second)), second)), second)
                    )) + c::newLine() +
                    c::end();
            }

            /***
            int cth_idiv (int a, int b) {
                return (a - 2 * (a < 0) + 2 * (b < 0)) / b;
            }
            ***/
            inline std::string idiv () {
                constexpr auto first  = "a";
                constexpr auto second = "b";
                return
                    /*c::inlined*/(c::inlineFunctionBegin(
                        c::integralType(),
                        c::global(def::integralDivision),
                        c::declaration(c::integralType(), first),
                        c::declaration(c::integralType(), second)
                    )) + c::newLine() +
                    c::functionBody(c::functionReturn(
                        c::div(c::expression(
                            c::add(
                                c::sub(
                                    first,
                                    c::mul(
                                        c::integralLiteral(2),
                                        c::expression(c::lt(first, c::integralLiteral(0)))
                                    )
                                ),
                                c::mul(
                                    c::integralLiteral(2),
                                    c::expression(c::lt(second, c::integralLiteral(0)))
                                )
                            )
                        ), second)
                    )) + c::newLine() +
                    c::end();
            }

            /***
            int cth_floor (float a) {
                return (int) floorf(a); // alternatively: floor, floorl
            }
            ***/
            inline std::string floor () {
                constexpr auto arg = "a";
                return
                    /*c::inlined*/(c::inlineFunctionBegin(
                        c::integralType(),
                        c::global(def::floor),
                        c::declaration(c::floatingType(), arg)
                    )) + c::newLine() +
                    c::functionBody(c::functionReturn(
                        c::cast(c::inlineCall(def::nativeFloor, arg), c::integralType())
                    )) + c::newLine() +
                    c::end();
            }

            /***
            float cth_fmod (float a, float b) {
                return fmodf((fmodf(a, b) + b), b); // alternatively: floor, floorl
            }
            ***/
            inline std::string fmod () {
                constexpr auto first  = "a";
                constexpr auto second = "b";
                return
                    /*c::inlined*/(c::inlineFunctionBegin(
                        c::floatingType(),
                        c::global(def::floatingModulo),
                        c::declaration(c::floatingType(), first),
                        c::declaration(c::floatingType(), second)
                    )) + c::newLine() +
                    c::functionBody(c::functionReturn(
                        c::inlineCall(
                            def::nativeFloatingModulo,
                            c::add(
                                c::inlineCall(def::nativeFloatingModulo, first, second),
                                second
                            ),
                            second
                        )
                    )) + c::newLine() +
                    c::end();
            }

        }

        namespace implementation {

            /***
            cth_floor(<a>)
            ***/
            inline std::string floor (std::string const & a) {
                return c::inlineCall(c::global(def::floor), a);
            }

            /***
            cth_idiv(<a>, <b>)
            ***/
            inline std::string idiv (std::string const & a, std::string const & b) {
                return c::inlineCall(c::global(def::integralDivision), a, b);
            }

            /***
            cth_imod(<a>, <b>)
            ***/
            inline std::string imod (std::string const & a, std::string const & b) {
                return c::inlineCall(c::global(def::integralModulo), a, b);
            }

            /***
            cth_fmod(<a>, <b>)
            ***/
            inline std::string fmod (std::string const & a, std::string const & b) {
                return c::inlineCall(c::global(def::floatingModulo), a, b);
            }

            /***
            powf(<a>, <b>)
            ***/
            inline std::string fpow (std::string const & a, std::string const & b) {
                return c::inlineCall(def::nativeExponentiation, a, b);
            }

            /** Identity. */
            inline std::string id (std::string const & a) { return a; }

        }

        namespace detail {

            template <typename T>
            constexpr auto typeParam (auto const & f) {
                return [&] <typename... Ts> (T const &, Ts &&... args) {
                    return f(std::forward<Ts>(args)...);
                };
            }

            constexpr auto numericTypeParam (auto const & f) {
                return [&] <typename... Ts> (interface::numericType auto const &, Ts &&... args) {
                    return f(std::forward<Ts>(args)...);
                };
            }

            constexpr auto simpleTypeParam (auto const & f) {
                return [&] <typename... Ts> (interface::simpleType auto const &, Ts &&... args) {
                    return f(std::forward<Ts>(args)...);
                };
            }

        }

        constexpr auto plus  = detail::numericTypeParam(implementation::id);
        constexpr auto minus = detail::numericTypeParam(c::negate);
        constexpr auto add   = detail::numericTypeParam(c::add);
        constexpr auto sub   = detail::numericTypeParam(c::sub);
        constexpr auto mul   = detail::numericTypeParam(c::mul);
        constexpr auto div   = esl::overload(detail::typeParam<type::Int>(implementation::idiv), detail::typeParam<type::Float>(c::div));
        constexpr auto mod   = esl::overload(detail::typeParam<type::Int>(implementation::imod), detail::typeParam<type::Float>(implementation::fmod));
        constexpr auto pow   = detail::typeParam<type::Float>(implementation::fpow);
        constexpr auto lt    = detail::simpleTypeParam(c::lt);
        constexpr auto gt    = detail::simpleTypeParam(c::gt);
        constexpr auto le    = detail::simpleTypeParam(c::le);
        constexpr auto ge    = detail::simpleTypeParam(c::ge);
        constexpr auto eq    = detail::simpleTypeParam(c::eq);
        constexpr auto ne    = detail::simpleTypeParam(c::ne);
        constexpr auto lnot  = detail::typeParam<type::Bool>(c::lnot);
        constexpr auto land  = detail::typeParam<type::Bool>(c::land);
        constexpr auto lor   = detail::typeParam<type::Bool>(c::lor);

        /***
        (int) <val>
        ***/
        inline std::string btoi (std::string const & a) {
            return c::cast(a, c::integralType());
        }

        /***
        (bool) <val>
        ***/
        inline std::string itob (std::string const & a) {
            return c::cast(a, c::booleanType());
        }

        /***
        (float) <val>
        ***/
        inline std::string itof (std::string const & a) {
            return c::cast(a, c::floatingType());
        }

        /***
        cth_floor(<val>)
        ***/
        inline std::string ftoi (std::string const & a) {
            return implementation::floor(a);
        }

        /***
        (float) <val>
        ***/
        inline std::string btof (std::string const & a) {
            return c::cast(a, c::floatingType());
        }

        /***
        (bool) cth_floor(<val>)
        ***/
        inline std::string ftob (std::string const & a) {
            return c::cast(implementation::floor(a), c::booleanType());
        }

    }

}
