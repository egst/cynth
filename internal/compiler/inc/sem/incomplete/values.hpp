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

#include "config.hpp"
#include "context/forward.hpp"
#include "interface/forward.hpp"
#include "sem/types.hpp"
#include "syn/categories/expression.hpp"

// Circular dependencies:
#include "sem/forward.hpp"

namespace cynth::sem {

    namespace value {

        struct Bool {
            bool value = false;

            interface::DisplayResult          display        ()                const;
            interface::ValueTranslationResult translateValue (context::Main &) const;

            constexpr static type::Bool valueType = {};

            interface::GetResult<bool> get () const;
        };

        struct Int {
            Integral value = 0;

            interface::DisplayResult          display        ()                const;
            interface::ValueTranslationResult translateValue (context::Main &) const;

            constexpr static type::Int valueType = {};

            interface::GetResult<Integral> get () const;
        };

        struct Float {
            Floating value = 0;

            interface::DisplayResult          display        ()                const;
            interface::ValueTranslationResult translateValue (context::Main &) const;

            constexpr static type::Float valueType = {};

            interface::GetResult<Floating> get () const;
        };

        struct String {
            std::string value;

            interface::DisplayResult          display        ()                const;
            interface::ValueTranslationResult translateValue (context::Main &) const;

            constexpr static type::String valueType = {};

            interface::GetResult<std::string> get () const;
        };

        struct In {
            std::string allocation; // run-time allocation variable name

            interface::DisplayResult          display        ()                const;
            interface::ValueTranslationResult translateValue (context::Main &) const;

            type::In valueType;
        };

        struct Out {
            std::string allocation; // run-time allocation variable name

            interface::DisplayResult          display        ()                const;
            interface::ValueTranslationResult translateValue (context::Main &) const;

            type::Out valueType;
        };

    }

    // Note: The whole incapsulation here ensures that the three properties are always of the same type.
    struct ArithmeticSequence {
        // Sequence definition can be extracted from any literal of the form [<from> to <to> by <by>].
        // For other cases, the array values can still be inspected one by one to try and fit them into a sequence,
        // however, this only happens up to this limit. Otherwise it could be slowing down compilation.
        //constexpr static std::size_t limit = 1000;
        // Update: Nope, this doesn't make much sense. If a comp-time array value isn't recognized as a sequence
        // and is used in a for loop range declaration, it must be declared as a run-time variable,
        // which would go through the sequence elements one by one anyway.

        // TODO: Implement for value::Int and value::Float
        // Update: I don't think this will be possible to do with floats.
        // I can't really compare the differences between elements reliably.
        // Or maybe I could extract it from range elements?
        ArithmeticSequence (Integral const & from, Integral const & to, Integral const & by);
        //ArithmeticSequence (Floating const & from, Floating const & to, Floating const & by);

        CompleteType type () const;
        Integral     size () const;

        inline CompleteValue const & from () const { return *definition.from; }
        inline CompleteValue const & to   () const { return *definition.to;   }
        inline CompleteValue const & by   () const { return *definition.by;   }

    protected:
        struct {
            esl::component<CompleteValue> from;
            esl::component<CompleteValue> to;
            esl::component<CompleteValue> by;
        } definition;
    };

    /** For compile-time allocated arrays. */
    struct ArrayAllocation {
        using Vector = esl::component_vector<CompleteValue>;

        Vector value;

        inline ArrayAllocation () {}
        inline ArrayAllocation (Vector const & value): value{value} {}

        // Comp-time arrays in for ranges containing arithmetic sequnces will be optimized into
        // `for (int i = <from>; i < <to>; i += <by>)` instead of actual run-time array allocation.
        std::optional<ArithmeticSequence> sequence;

        // A comp-time allocation can be explicitly allocated in the resulting C code on demand.
        // This happens when access by a run-time index is needed.
        std::optional<std::string> variable;

        /**
         *  Allocates a corresponding run-time value (while keeping the comp-time value)
         *  if none has already been allocated and returns name of the alloation variable (this->variable).
         */
        //esl::result<std::string> allocate (context::Main &);
        std::string allocate (context::Main &);

        CompleteType type () const;

        std::optional<ArithmeticSequence> sequentialize ();

        /**
         *  Allocated array values with only const-valued array references to them can be optimized in some cases.
         *  By default, all newly created array values (usually with an array literal)
         *  are marked as "constant" (const-valued) to allow optimizations.
         *  When assigning to a non-const variable or passing as a non-const argument
         *  (or maybe even explicitly converting to a non-const value?) call this function to relax this constness.
         *  Note that this might not correspond with the .constval property of type::Array.
         *  Actual constness of types can only be added, not removed. So all array values start as non-const types
         *  with this hidden "constant" property that might be relaxed when first assigned or passed.
         */
        void relax ();

        esl::view<ArrayAllocation::Vector::iterator> trimmedValue (Integral);

    protected:
        bool constant = true;
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

            interface::DisplayResult          display        ()                const;
            interface::ValueTranslationResult translateValue (context::Main &) const;

            type::Array valueType;
        };

        // TODO: Do I need to store the generator here?
        struct Buffer {
            std::string allocation;

            interface::DisplayResult          display        ()                const;
            interface::ValueTranslationResult translateValue (context::Main &) const;

            type::Buffer valueType;
        };

    }

    struct FunctionDefinition {
        struct Parameter {
            std::string name;
            Integral    arity;
        };
        struct Implementation {
            esl::tiny_vector<Parameter>               parameters; // Parameter names and size of the corresponding tuples
            esl::component<syn::category::Expression> body;       // Unevaluated body expression
            esl::component<Closure>                   closure;    // Comp-time captured values and run-time typed names
        };
        using Result = esl::component_vector<FunctionDefinition *>;
        using Switch = esl::component_vector<value::Function>;
        using Variant = std::variant<
            Implementation, // A "leaf" function with a direct implementation.
            Switch          // A "switch" function only delegating to other functions based on a runtime value.
        >;

        Variant                    implementation;
        type::Function             type;
        std::optional<std::string> closureType; // Run-time closure variable type. No value => No run-time closure.
        std::optional<std::string> name;        // Run-time function name.         No value => Not defined yet.
        Result                     returnedFunctions = {}; // In case of returning functions.
    };

    namespace value {

        // TODO: Which members really need to be in a component?
        // TODO: Will optional strings also cause the still unfixed segfault problem?

        struct Function {
            // I'm really starting to hate C++...
            // All this boiler plate code just because of a referential member?
            inline Function (
                FunctionDefinition & definition,
                std::optional<std::string> closureVariable = std::nullopt
            ):  definition{definition},
                closureVariable{std::move(closureVariable)} {}

            inline Function (Function const & other):
                definition{other.definition},
                closureVariable{other.closureVariable} {}

            inline Function (Function && other):
                definition{other.definition},
                closureVariable{std::move(other.closureVariable)} {}

            inline Function & operator = (Function const & other) {
                definition      = other.definition;
                closureVariable = other.closureVariable;
                return *this;
            }

            inline Function & operator = (Function && other) {
                definition      = other.definition;
                closureVariable = std::move(other.closureVariable);
                return *this;
            }

            // TODO: This seems to introduce some issues with const values.
            FunctionDefinition &       definition;
            std::optional<std::string> closureVariable; // Run-time closure variable.

            // Note: A function value may be linked to a local variable containing its runtime closure data.
            // This makes it a "partially run-time" vlaue, that is passed around in a semantic structure,
            // but might also need some run-time definitions in the C code to be complete.
            // Some array values are also "partially run-time" with their allocation variables.
            // The fact that the runtime part of the function is a local variable means that it might
            // require more careful manipulation, because the variable must be transfrered (copied)
            // along with the function value (when returning, or maybe when assigning to another function variable),
            // unlike the allocation variables of arrays, that have a wider (function) scope.

            inline bool runtimeClosure () const {
                //return closureVariable || definition.closureType;
                //return closureVariable.has_value();
                return definition.closureType.has_value();
            }

            interface::DisplayResult display () const;

            // Temporary solution for returning functions from functions:
            interface::ValueTranslationResult translateValue (context::Main &) const;

            type::Function & valueType = definition.type;
            // TODO: Make sure this still satisfies the has::valueType concept.
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
