#pragma once

#include <string>

namespace cynth::ast::token {

    namespace base {

        template <typename content_type>
        struct token {
            content_type content;
            token (content_type const & content): content{content} {}
        };
        /*template <>
        struct token<std::string> {
            std::string content;
            token (std::string content): content{std::move(content)} {}
            token (char const * content): content{content} {}
            token (char * content): content{content} {}
        };*/
        template <>
        struct token<void> {};

    }

    using name_token = base::token<std::string>;
    struct Name: name_token {
        using name_token::name_token;
    };

    using type_name_token = base::token<std::string>;
    struct TypeName: type_name_token {
        using type_name_token::type_name_token;
    };

    using integer_token = base::token<std::string>;
    struct Integer: integer_token {
        using integer_token::integer_token;
    };

    using decimal_token = base::token<std::string>;
    struct Decimal: decimal_token {
        using decimal_token::decimal_token;

    };

    using string_token = base::token<std::string>;
    struct String: string_token {
        using string_token::string_token;
    };

    struct Return:   base::token<void> {};
    struct If:       base::token<void> {};
    struct Else:     base::token<void> {};
    struct When:     base::token<void> {};
    struct While:    base::token<void> {};
    struct For:      base::token<void> {};
    struct In:       base::token<void> {};
    struct To:       base::token<void> {};
    struct By:       base::token<void> {};
    struct Type:     base::token<void> {};
    struct Buffer:   base::token<void> {};

    struct OParen:   base::token<void> {};
    struct CParen:   base::token<void> {};
    struct OBrack:   base::token<void> {};
    struct CBrack:   base::token<void> {};
    struct OBrace:   base::token<void> {};
    struct CBrace:   base::token<void> {};
    struct Add:      base::token<void> {};
    struct Sub:      base::token<void> {};
    struct Mult:     base::token<void> {};
    struct Div:      base::token<void> {};
    struct Mod:      base::token<void> {};
    struct Pow:      base::token<void> {};
    struct Asgn:     base::token<void> {};
    struct AddAsgn:  base::token<void> {};
    struct SubAsgn:  base::token<void> {};
    struct MultAsgn: base::token<void> {};
    struct DivAsgn:  base::token<void> {};
    struct ModAsgn:  base::token<void> {};
    struct PowAsgn:  base::token<void> {};
    struct Eq:       base::token<void> {};
    struct Ne:       base::token<void> {};
    struct Ge:       base::token<void> {};
    struct Le:       base::token<void> {};
    struct Gt:       base::token<void> {};
    struct Lt:       base::token<void> {};
    struct Comma:    base::token<void> {};
    struct Colon:    base::token<void> {};
    struct Sep:      base::token<void> {};
    struct Auto:     base::token<void> {};

    struct NONE:     base::token<void> {}; // YY_NULL

}
