#pragma once

#include <optional>
#include <variant>
#include <string_view>
#include <concepts>
#include <string>

namespace cynth {

    /*
    struct generic_error {
        std::string message;

        generic_error ():               message{""} {}
        generic_error (char const * m): message{m}  {}
        generic_error (std::string m):  message{m}  {}
        generic_error (generic_error const &) = default;
        generic_error (generic_error &&)      = default;
    };
    */

    struct result_error {
        //std::string_view message;
        std::string message;

        result_error ():               message{""} {}
        //result_error (char const * m): message{m}  {}
        result_error (std::string  m): message{m}  {}
        result_error (result_error const &) = default;
        result_error (result_error &&)      = default;
    };
    // TODO: Instead of simple string error messages, introduce a typed system of errors with specific values.

    namespace detail {

        template <typename Derived, typename T = result_error>
        struct result_base {
            constexpr T const & operator * () const & requires (!std::same_as<T, result_error>) {
                return derived().value();
            }

            constexpr T & operator * () & requires (!std::same_as<T, result_error>) {
                return derived().value();
            }

            constexpr T && operator * () && requires (!std::same_as<T, result_error>) {
                //return derived().value();
                return static_cast<Derived &&>(*std::move(this)).value();
            }

            constexpr T const * operator -> () const requires (!std::same_as<T, result_error>) {
                return derived().get();
            }

            constexpr T * operator -> () requires (!std::same_as<T, result_error>) {
                return derived().get();
            }

            constexpr explicit operator bool () const {
                return derived().has_value();
            }

            constexpr T value_or (T const & fallback) const requires (!std::same_as<T, result_error>) {
                return derived().has_value()
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

    template <typename T> requires (!std::same_as<T, result_error>)
    struct result: detail::result_base<result<T>, T> {
        using value_type = T;

        constexpr result (result_error const & e): content{e}            {}
        constexpr result (result_error &&      e): content{std::move(e)} {}
        constexpr result (value_type   const & v): content{v}            {}
        constexpr result (value_type   &&      v): content{std::move(v)} {}
        constexpr result (result       const &) = default;
        constexpr result (result       &&)      = default;

        constexpr bool has_value () const {
            return content.index() == 0;
        }

        constexpr bool has_error () const {
            return !has_value();
        }

        constexpr value_type const * get () const {
            return has_value() ? &value() : nullptr;
        }

        constexpr value_type * get () {
            return has_value() ? &value() : nullptr;
        }

        constexpr value_type const & value () const & {
            return std::get<value_type>(content);
        }

        constexpr value_type & value () & {
            return std::get<value_type>(content);
        }

        constexpr value_type && value () && {
            return std::get<value_type>(std::move(content));
        }

        constexpr result_error const & error () const & {
            return std::get<result_error>(content);
        }

        constexpr result_error & error () & {
            return std::get<result_error>(content);
        }

        constexpr result_error && error () && {
            return std::get<result_error>(std::move(content));
        }

    //protected:
        std::variant<value_type, result_error> content;
    };

    template <typename T> requires (!std::same_as<T, result_error>)
    struct reference_result: detail::result_base<reference_result<T>, T> {
        using value_type = T;

        constexpr reference_result (result_error     const & e): content{e}            {}
        constexpr reference_result (result_error     &&      e): content{std::move(e)} {}
        constexpr reference_result (value_type       &       v): content{&v}           {}
        constexpr reference_result (reference_result const &) = default;
        constexpr reference_result (reference_result &&)      = default;

        constexpr bool has_value () const {
            return content.index() == 0;
        }

        constexpr bool has_error () const {
            return !has_value();
        }

        constexpr value_type const * get () const {
            return has_value() ? std::get<value_type *>(content) : nullptr;
        }

        constexpr value_type * get () {
            return has_value() ? std::get<value_type *>(content) : nullptr;
        }

        constexpr value_type const & value () const & {
            return *std::get<value_type *>(content);
        }

        constexpr value_type & value () & {
            return *std::get<value_type *>(content);
        }

        constexpr value_type && value () && {
            return *std::get<value_type *>(std::move(content));
        }

        constexpr result_error const & error () const & {
            return std::get<result_error>(content);
        }

        constexpr result_error & error () & {
            return std::get<result_error>(content);
        }

        constexpr result_error && error () && {
            return std::get<result_error>(std::move(content));
        }

    //protected:
        std::variant<value_type *, result_error> content;
    };

    template <>
    struct result<void>: detail::result_base<result<void>> {
        using value_type = void;

        constexpr result () {}
        constexpr result (result_error const & e): content{e}            {}
        constexpr result (result_error &&      e): content{std::move(e)} {}
        constexpr result (result       const &) = default;
        constexpr result (result       &&)      = default;

        constexpr bool has_value () const {
            return !content.has_value();
        }

        constexpr bool has_error () const {
            return !has_value();
        }

        constexpr result_error const & error () const & {
            return *content;
        }

        constexpr result_error & error () & {
            return *content;
        }

        constexpr result_error && error () && {
            return *std::move(content);
        }

    //protected:
        std::optional<result_error> content;
    };

    template <typename T> requires (!std::same_as<T, result_error>)
    struct optional_result: detail::result_base<optional_result<T>, T> {
        using value_type = T;

        constexpr optional_result () {}
        constexpr optional_result (result_error    const & e): content{e}            {}
        constexpr optional_result (result_error    &&      e): content{std::move(e)} {}
        constexpr optional_result (value_type      const & v): content{v}            {}
        constexpr optional_result (value_type      &&      v): content{std::move(v)} {}
        constexpr optional_result (optional_result const &) = default;
        constexpr optional_result (optional_result &&)      = default;

        constexpr bool has_value () const {
            return content.has_value() && (content->index() == 0);
        }

        constexpr bool has_error () const {
            return content.has_value() && (content->index() == 1);
        }

        constexpr bool empty () const {
            return !content.has_value();
        }

        constexpr value_type const & value () const & {
            return std::get<value_type>(*content);
        }

        constexpr value_type & value () & {
            return std::get<value_type>(*content);
        }

        constexpr value_type && value () && {
            return std::get<value_type>(*std::move(content));
        }

        constexpr result_error const & error () const & {
            return std::get<result_error>(*content);
        }

        constexpr result_error & error () & {
            return std::get<result_error>(*content);
        }

        constexpr result_error && error () && {
            return std::get<result_error>(*std::move(content));
        }

    //protected:
        std::optional<std::variant<value_type, result_error>> content;
    };

    constexpr auto make_result = [] <typename T> (T && value) {
        return result{std::forward<T>(value)};
    };

    constexpr auto make_optional_result = [] <typename T> (T && value) {
        return optional_result{std::forward<T>(value)};
    };

    constexpr auto result_to_optional = [] <typename T> (T && r) {
        using value_type = typename T::value_type;
        return r.has_value()
            ? std::optional<value_type>{*r}
            : std::optional<value_type>{};
    };

}
