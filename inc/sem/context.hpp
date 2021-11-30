#pragma once

#include "esl/result.hpp"
#include "esl/tiny_vector.hpp"

#include <tuple>
#include <string>
#include <optional>
#include <unordered_map>

#include "sem/types.hpp"
#include "sem/values.hpp"
#include "sem/context_types.hpp"

namespace cynth::sem {

    struct Context {
        std::unordered_map<std::string, TypedValueVector> values;
        std::unordered_map<std::string, TypeVector>       types;

        Context * parent;

        Context ();

        Context (Context const &) = default;
        Context (Context &&)      = default;

        esl::result<void> defineValue (std::string, TypedValue       const &);
        esl::result<void> defineValue (std::string, TypedValueVector const &);
        esl::result<void> defineType  (std::string, CompleteType     const &);
        esl::result<void> defineType  (std::string, TypeVector       const &);

        // TODO?
        esl::result<void> defineValue (esl::tiny_vector<CompleteDeclaration> const &, esl::tiny_vector<CompleteValue> const &);
        esl::result<void> declare     (esl::tiny_vector<CompleteDeclaration> const &);

        TypedValue * findValueInside (std::string const &);
        TypeVector * findTypeInside  (std::string const &);
        TypedValue * findValue       (std::string const &);
        TypeVector * findType        (std::string const &);

        template <typename Value>
        void initStorage ();

        template <typename Value>
        RefvalContainer<Value> & storedValues ();

        template <typename Value>
        esl::reference_result<Value> storeValue (Value const &);

        static Context makeChild ();

    protected:
        std::tuple<
            std::optional<RefvalContainer<value::InValue>>,
            std::optional<RefvalContainer<value::OutValue>>,
            std::optional<RefvalContainer<value::ArrayValue>>,
            std::optional<RefvalContainer<value::BufferValue>>,
            std::optional<RefvalContainer<value::FunctionValue>>
        > referential;
    };

}
