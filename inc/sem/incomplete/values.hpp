#pragma once

#include <string>
#include <variant>
#include <vector>
#include <optional>

#include "esl/category.hpp"
#include "esl/component.hpp"
#include "esl/result.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/type_manip.hpp"
#include "esl/view.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"
#include "sem/numeric_types.hpp"
#include "sem/types.hpp"
#include "syn/categories/expression.hpp"

// Circular dependencies:
#include "sem/forward.hpp"
// TODO: sem/compound
// TODO:
// * values should be fully dependent on types.
// * types should only need incomplete values
// * compound should need both types and values, while nither types nor values should need compound
// * what about declarations?

// Note: No macros escape this file.
#define GET(Type) \
    interface::GetResult<Type> get () const
#define CONVERT(Type) \
    interface::ConversionResult<Type> convertValue (context::Main &, Type const &) const
#define CONVERT_SIMPLE(Type) \
    interface::ConversionResult<Type> convertValue (Type const &) const
#define STATIC_VALUE_TYPE(Type, init) \
    constexpr static Type valueType = init
#define DIRECT_VALUE_TYPE(Type) \
    Type valueType
#define VALUE_TYPE \
    interface::ValueTypeResult valueType () const
#define VALUE_INTERFACE \
    interface::DisplayResult display () const; \
    interface::ValueTranslationResult translateValue (context::Main &) const

namespace cynth::sem {

    namespace value {

        struct Bool {
            std::optional<bool> value;

            VALUE_INTERFACE;

            STATIC_VALUE_TYPE(type::Bool, {});

            GET(bool);

            CONVERT_SIMPLE(type::Bool);
            CONVERT_SIMPLE(type::Int);
            CONVERT_SIMPLE(type::Float);

            constexpr static CompleteValue make (bool); //return sem::value::Bool{.value = value};
        };

        struct Int {
            std::optional<Integral> value;

            VALUE_INTERFACE;

            STATIC_VALUE_TYPE(type::Int, {});

            GET(Integral);

            CONVERT_SIMPLE(type::Bool);
            CONVERT_SIMPLE(type::Int);
            CONVERT_SIMPLE(type::Float);

            constexpr static CompleteValue make (Integral); //return sem::value::Int{.value = value};
        };

        struct Float {
            std::optional<Floating> value;

            VALUE_INTERFACE;

            STATIC_VALUE_TYPE(type::Float, {});

            GET(Floating);

            CONVERT_SIMPLE(type::Bool);
            CONVERT_SIMPLE(type::Int);
            CONVERT_SIMPLE(type::Float);

            constexpr static CompleteValue make (Floating); //return sem::value::Float{.value = value};
        };

        struct String {
            std::optional<std::string> value;

            VALUE_INTERFACE;

            STATIC_VALUE_TYPE(type::String, {});

            GET(std::string);

            constexpr static CompleteValue make (std::string); //return sem::value::Sting{.value = value};
        };

        struct In {
            std::optional<std::string> allocation; // run-time allocation variable name

            VALUE_INTERFACE;

            DIRECT_VALUE_TYPE(type::In);

            CONVERT(type::Bool);
            CONVERT(type::Int);
            CONVERT(type::Float);
            CONVERT(type::In);
            CONVERT(type::Buffer);
        };

        struct Out {
            std::optional<std::string> allocation; // run-time allocation variable name

            VALUE_INTERFACE;

            DIRECT_VALUE_TYPE(type::Out);

            CONVERT(type::Out);
        };

    }

    /** For compile-time allocated arrays. */
    struct ArrayAllocation {
        using Vector = esl::component_vector<CompleteValue>;

        Vector value;

        // A comp-time allocation can be explicitly allocated in the resulting C code on demand.
        // This happens when access by a run-time index is needed.
        std::optional<std::string> variable;

        /**
         *  Allocates a corresponding run-time value (while keeping the comp-time value)
         *  if none has already been allocated and returns name of the alloation variable (this->variable).
         *  TODO: Do I really need esl::result here?
         */
        esl::result<std::string> allocate (context::Main &);
    };

    namespace value {

        // TODO: Figure out a way to work with arrays containing tuples.
        struct Array {
            // TODO: Reference (reference_wrapper) instead of a pointer.
            // For now, let's assume a non-empty vector as an invariant.
            using Allocation = std::variant<
                ArrayAllocation *, // compile-time allocation structure
                std::string        // run-time allocation variable name
            >;

            Allocation allocation;

            VALUE_INTERFACE;

            DIRECT_VALUE_TYPE(type::Array);

            //GET(std::vector<esl::tiny_vector<CompleteValue>>);

            CONVERT(type::Array);

            /* TODO?
            static esl::result<CompleteValue> make (
                value::ArrayValue *,
                esl::component_vector<CompleteType> &&,
                Integral
            );
            */

            esl::view<ArrayAllocation::Vector::iterator> trimmed_value () const;
        };

        // TODO: Do I need to store the generator here?
        struct Buffer {
            esl::component<std::string> allocation;

            VALUE_INTERFACE;

            DIRECT_VALUE_TYPE(type::Buffer);

            CONVERT(type::Buffer);

            //constexpr static esl::result<CompleteValue> make (value::BufferValue *, Integral);
        };

    }

    struct FunctionDefinition {
        struct Implementation {
            std::vector<std::pair<std::string, Integral>> parameters; // Parameter names and size of the corresponding tuples
            esl::component<syn::category::Expression>     body;       // Unevaluated body expression
            esl::component<sem::ResolvedCapturedContext>  context;    // Comp-time captured values and run-time typed names
        };
        using Switch = esl::component_vector<value::Function>;
        using Variant = std::variant<
            Implementation, // A "leaf" function with a direct implementation.
            Switch          // A "switch" function only delegating to other functions.
        >;

        Variant                    implementation;
        type::Function             type;
        std::optional<std::string> contextType; // Run-time context variable type. No value => No run-time context.
        std::string                name; // Run-time function name
    };

    namespace value {

        // TODO: Which members really need to be in a component?
        // TODO: Will optional strings also cause the still unfixed segfault problem?

        struct Function {
            FunctionDefinition &       definition;
            std::optional<std::string> contextVariable; // Run-time context variable.

            // Note: A function value may be linked to a local variable containing its runtime context data.
            // This makes it a "partially run-time" vlaue, that is passed around in a semantic structure,
            // but might also need some run-time definitions in the C code to be complete.
            // Some array values are also "partially run-time" with their allocation variables.
            // The fact that the runtime part of the function is a local variable means that it might
            // require more careful manipulation, because the variable must be transfrered (copied)
            // along with the function value (when returning, or maybe when assigning to another function variable),
            // unlike the allocation variables of arrays, that have a wider (function) scope.

            // TODO: Define in cpp.
            inline bool contextual () const {
                return definition.contextType.has_value();
            }

            VALUE_INTERFACE;

            //VALUE_TYPE;
            //DIRECT_VALUE_TYPE(type::Function);
            type::Function & valueType = definition.type;
            // TODO: I hope this will still satitfy the directTypeName concept.

            //GET(Function);

            CONVERT(type::Function);
            CONVERT(type::Buffer);

            Function copy (std::optional<std::string> contextVariable) const;
        };

        struct Unknown {
            esl::optional_component<IncompleteDeclaration> decl;
        };

    }

    namespace detail::values {

        using Simple = std::variant<
            value::Bool,
            value::Int,
            value::Float
        >;

        using Complete = esl::extend<
            Simple,
            value::In,
            value::Out,
            value::Array,
            value::Buffer,
            value::Function
        >;

        using Incomplete = esl::extend<
            Complete,
            value::Unknown
        >;

    }

    struct CompleteValue: esl::category<CompleteValue, detail::values::Complete> {
        using Base = esl::category<CompleteValue, detail::values::Complete>;
        using Base::Base;
    };

    struct IncompleteValue: esl::category<IncompleteValue, detail::values::Incomplete> {
        using Base = esl::category<IncompleteValue, detail::values::Incomplete>;
        using Base::Base;
    };

}

#undef GET
#undef CONVERT
#undef STATIC_VALUE_TYPE
#undef DIRECT_VALUE_TYPE
#undef VALUE_TYPE
#undef VALUE_INTERFACE
