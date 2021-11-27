#pragma once

#include "util/general.hpp"
#include "basic_config.hpp"

#include <concepts>

namespace Cynth {

    /*
    struct GenericError {
        String message;

        GenericError ():               message{""} {}
        GenericError (char const * m): message{m}  {}
        GenericError (String       m):  message{m}  {}
        GenericError (GenericError const &) = default;
        GenericError (GenericError &&)      = default;
    };
    */

    struct ResultError {
        String message;

        ResultError ():               message{""} {}
        //ResultError (char const * m): message{m}  {}
        ResultError (String       m): message{m}  {}
        ResultError (ResultError const &) = default;
        ResultError (ResultError &&)      = default;
    };
    // TODO: Instead of simple string error messages, introduce a typed system of errors with specific values.

    namespace Detail::Result {

        template <typename Derived, typename T = ResultError>
        struct ResultBase {
            constexpr T const & operator * () const & requires (!Util::same<T, ResultError>) {
                return derived().value();
            }

            constexpr T & operator * () & requires (!Util::same<T, ResultError>) {
                return derived().value();
            }

            constexpr T && operator * () && requires (!Util::same<T, ResultError>) {
                //return derived().value();
                return static_cast<Derived &&>(*std::move(this)).value();
            }

            constexpr T const * operator -> () const requires (!Util::same<T, ResultError>) {
                return derived().get();
            }

            constexpr T * operator -> () requires (!Util::same<T, ResultError>) {
                return derived().get();
            }

            constexpr explicit operator bool () const {
                return derived().hasValue();
            }

            constexpr T valueOr (T const & fallback) const requires (!Util::same<T, ResultError>) {
                return derived().hasValue()
                    ? derived().value()
                    : fallback;
            }

        private:
            constexpr Derived & derived () & {
                return *static_cast<Derived *>(this);
            }

            constexpr Derived const & derived () const & {
                return *static_cast<Derived const *>(this);
            }

            constexpr Derived && derived () && {
                // TODO: This doesn't work for some reason.
                return static_cast<Derived &&>(*std::move(this));
            }
        };

    }

    template <typename T> requires (!Util::same<T, ResultError>)
    struct Result: Detail::Result::ResultBase<Result<T>, T> {
        using Value = T;

        constexpr Result (ResultError const & e): content{e}            {}
        constexpr Result (ResultError &&      e): content{std::move(e)} {}
        constexpr Result (Value       const & v): content{v}            {}
        constexpr Result (Value       &&      v): content{std::move(v)} {}
        constexpr Result (Result      const &) = default;
        constexpr Result (Result      &&)      = default;

        constexpr bool hasValue () const {
            return content.index() == 0;
        }

        constexpr bool hasError () const {
            return !hasValue();
        }

        constexpr Value const * get () const {
            return hasValue() ? &value() : nullptr;
        }

        constexpr Value * get () {
            return hasValue() ? &value() : nullptr;
        }

        constexpr Value const & value () const & {
            return std::get<Value>(content);
        }

        constexpr Value & value () & {
            return std::get<Value>(content);
        }

        constexpr Value && value () && {
            return std::get<Value>(std::move(content));
        }

        constexpr ResultError const & error () const & {
            return std::get<ResultError>(content);
        }

        constexpr ResultError & error () & {
            return std::get<ResultError>(content);
        }

        constexpr ResultError && error () && {
            return std::get<ResultError>(std::move(content));
        }

    //protected:
        std::variant<Value, ResultError> content;
    };

    template <typename T> requires (!Util::same<T, ResultError>)
    struct ReferenceResult: Detail::Result::ResultBase<ReferenceResult<T>, T> {
        using Value = T;

        constexpr ReferenceResult (ResultError     const & e): content{e}            {}
        constexpr ReferenceResult (ResultError     &&      e): content{std::move(e)} {}
        constexpr ReferenceResult (Value           &       v): content{&v}           {}
        constexpr ReferenceResult (ReferenceResult const &) = default;
        constexpr ReferenceResult (ReferenceResult &&)      = default;

        constexpr bool hasValue () const {
            return content.index() == 0;
        }

        constexpr bool hasError () const {
            return !hasValue();
        }

        constexpr Value const * get () const {
            return hasValue() ? std::get<Value *>(content) : nullptr;
        }

        constexpr Value * get () {
            return hasValue() ? std::get<Value *>(content) : nullptr;
        }

        constexpr Value const & value () const & {
            return *std::get<Value *>(content);
        }

        constexpr Value & value () & {
            return *std::get<Value *>(content);
        }

        constexpr Value && value () && {
            return *std::get<Value *>(std::move(content));
        }

        constexpr ResultError const & error () const & {
            return std::get<ResultError>(content);
        }

        constexpr ResultError & error () & {
            return std::get<ResultError>(content);
        }

        constexpr ResultError && error () && {
            return std::get<ResultError>(std::move(content));
        }

    //protected:
        std::variant<Value *, ResultError> content;
    };

    template <>
    struct Result<void>: Detail::Result::ResultBase<Result<void>> {
        using Value = void;

        constexpr Result () {}
        constexpr Result (ResultError const & e): content{e}            {}
        constexpr Result (ResultError &&      e): content{std::move(e)} {}
        constexpr Result (Result      const &) = default;
        constexpr Result (Result      &&)      = default;

        constexpr bool hasValue () const {
            return !content.has_value();
        }

        constexpr bool hasError () const {
            return !hasValue();
        }

        constexpr ResultError const & error () const & {
            return *content;
        }

        constexpr ResultError & error () & {
            return *content;
        }

        constexpr ResultError && error () && {
            return *std::move(content);
        }

    //protected:
        std::optional<ResultError> content;
    };

    template <typename T> requires (!Util::same<T, ResultError>)
    struct OptionalResult: Detail::Result::ResultBase<OptionalResult<T>, T> {
        using Value = T;

        constexpr OptionalResult () {}
        constexpr OptionalResult (ResultError    const & e): content{e}            {}
        constexpr OptionalResult (ResultError    &&      e): content{std::move(e)} {}
        constexpr OptionalResult (Value          const & v): content{v}            {}
        constexpr OptionalResult (Value          &&      v): content{std::move(v)} {}
        constexpr OptionalResult (OptionalResult const &) = default;
        constexpr OptionalResult (OptionalResult &&)      = default;

        constexpr bool hasValue () const {
            return content.has_value() && (content->index() == 0);
        }

        constexpr bool hasError () const {
            return content.has_value() && (content->index() == 1);
        }

        constexpr bool empty () const {
            return !content.has_value();
        }

        constexpr Value const & value () const & {
            return std::get<Value>(*content);
        }

        constexpr Value & value () & {
            return std::get<Value>(*content);
        }

        constexpr Value && value () && {
            return std::get<Value>(*std::move(content));
        }

        constexpr ResultError const & error () const & {
            return std::get<ResultError>(*content);
        }

        constexpr ResultError & error () & {
            return std::get<ResultError>(*content);
        }

        constexpr ResultError && error () && {
            return std::get<ResultError>(*std::move(content));
        }

    //protected:
        std::optional<std::variant<Value, ResultError>> content;
    };

    constexpr auto makeResult = [] <typename T> (T && value) {
        return Result{std::forward<T>(value)};
    };

    constexpr auto makeOptionalResult = [] <typename T> (T && value) {
        return OptionalResult{std::forward<T>(value)};
    };

    constexpr auto resultToOptional = [] <typename T> (T && r) {
        using Value = typename T::Value;
        return r.hasValue()
            ? std::optional<Value>{*r}
            : std::optional<Value>{};
    };

}
