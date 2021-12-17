#pragma once

#include <type_traits>

namespace cynth::sem {

    // Compound:

    struct TypedExpression;
    struct TypedName;
    struct TypedTargetExpression;
    struct ReturnedType;
    struct Returned;
    struct Variable;
    struct ResolvedValue;
    struct ResolvedTarget;
    struct Capture;
    struct ResolvedCapture;
    struct CapturedContext;
    struct ResolvedCapturedContext;

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

#if 0 // TODO: targets probably won't be needed anymore
    // Targets:

    namespace target {

        struct DirectTarget;
        struct SubscriptTarget;

    }

    struct Target;
#endif

    // Values:

    struct ArrayAllocation;

    namespace value {

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
