#pragma once

#include <optional>
#include <string>
#include <tuple>
#include <unordered_map>

#include "esl/result.hpp"
#include "esl/tiny_vector.hpp"

#include "sem/compound.hpp"
#include "sem/declarations.hpp"
#include "sem/types.hpp"
#include "sem/values.hpp"

namespace cynth::context {

    struct Cynth {
        using Value       = sem::LocalValue;
        //using ValueVector = esl::tiny_vector<Value>;
        using ValueVector = std::vector<Value>; // TODO: Some problems with tiny_vector in unordered_map.
        using Type        = sem::CompleteType;
        using TypeVector  = esl::tiny_vector<Type>;

        std::unordered_map<std::string, ValueVector> values;
        std::unordered_map<std::string, TypeVector>  types;

        Cynth * parent;

        Cynth ();

        Cynth (Cynth const &) = default;
        Cynth (Cynth &&)      = default;

        esl::result<Value      *> defineValue (std::string, Value const &);
        esl::result<TypeVector *> defineType  (std::string, Type  const &);

        // TODO?
        esl::result<void> defineValue (
            esl::tiny_vector<sem::CompleteDeclaration> const &,
            esl::tiny_vector<sem::CompleteValue> const &
        );
        esl::result<void> declare (
            esl::tiny_vector<sem::CompleteDeclaration> const &
        );

        Value      * findValueInside (std::string const &);
        TypeVector * findTypeInside  (std::string const &);
        Value      * findValue       (std::string const &);
        TypeVector * findType        (std::string const &);

        template <typename Value>
        void initStorage ();

        // TODO: Is this needed anywhere else? If not, just write it out directly.
        template <typename T>
        using RefvalContainer = std::forward_list<T>;

        template <typename Value>
        RefvalContainer<Value> & storedValues ();

        template <typename Value>
        esl::reference_result<Value> storeValue (Value const &);

        static Cynth makeChild ();

    protected:
        std::tuple<
            std::optional<RefvalContainer<sem::value::InValue>>,
            std::optional<RefvalContainer<sem::value::OutValue>>,
            std::optional<RefvalContainer<sem::value::ArrayValue>>,
            std::optional<RefvalContainer<sem::value::BufferValue>>,
            std::optional<RefvalContainer<sem::value::FunctionValue>>
        > referential;
    };

}
