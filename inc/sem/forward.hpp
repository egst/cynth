#pragma once

#include <type_traits>

namespace cynth::sem {

    // Compound:

    struct ResolvedValue;
    struct LocalValue;
    struct ResolvedTargetValue;

    // Declarations:

    struct CompleteDeclaration;
    struct IncompleteDeclaration;

    template <bool Complete>
    using Declaration = std::conditional_t<
        Complete,
        CompleteDeclaration,
        IncompleteDeclaration
    >;

    struct TypeDeclaration;

    struct CompleteRangeDeclaration;
    struct IncompleteRangeDeclaration;

    template <bool Complete>
    using RangeDeclaration = std::conditional_t<
        Complete,
        CompleteRangeDeclaration,
        IncompleteRangeDeclaration
    >;

    // Targets:

    namespace target {

        struct DirectTarget;
        struct SubscriptTarget;

    }

    struct Target;

    // Values:

    namespace value {

        struct Bool;
        struct Int;
        struct Float;
        struct String;

        struct InValue;
        struct OutValue;
        struct ConstValue;
        struct ArrayValue;
        struct BufferValue;
        struct FunctionValue;

        struct In;
        struct Out;
        struct Const;
        struct Array;
        struct Buffer;
        struct Function;

        struct Unknown;

    }

    struct CompleteValue;
    struct IncompleteValue;

    template <bool Complete>
    using Value = std::conditional_t<
        Complete,
        CompleteValue,
        IncompleteValue
    >;

    // Types:

    namespace type {

        struct Bool;
        struct Int;
        struct Float;
        struct String;

        struct In;
        struct Out;
        struct Const;
        struct Array;
        struct Buffer;
        struct Function;

        struct IncompleteIn;
        struct IncompleteOut;
        struct IncompleteConst;
        struct IncompleteArray;
        struct IncompleteBuffer;
        struct IncompleteFunction;

        struct Unknown;

    }

    struct CompleteType;
    struct IncompleteType;

    template <bool Complete>
    using Type = std::conditional_t<
        Complete,
        CompleteType,
        IncompleteType
    >;

}
