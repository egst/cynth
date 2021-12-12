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
        template <typename T>
        using RefvalContainer = std::forward_list<T>;

        std::unordered_map<std::string, esl::tiny_vector<sem::LocalValue>> values;
        //std::unordered_map<std::string, std::vector<sem::LocalValue>> values;
        std::unordered_map<std::string, esl::tiny_vector<sem::CompleteValue>>  types;

        Cynth * parent;

        Cynth ();

        Cynth (Cynth const &) = default;
        Cynth (Cynth &&)      = default;

        esl::result<sem::LocalValue                     *> defineValue (std::string, sem::ResolvedValue const &);
        esl::result<esl::tiny_vector<sem::CompleteType> *> defineType  (std::string, sem::CompleteType  const &);

        // TODO?
        esl::result<void> defineValue (
            esl::tiny_vector<sem::CompleteDeclaration> const &,
            esl::tiny_vector<sem::CompleteValue> const &
        );
        esl::result<void> declare (
            esl::tiny_vector<sem::CompleteDeclaration> const &
        );

        sem::LocalValue                     * findValueInside (std::string const &);
        esl::tiny_vector<sem::CompleteType> * findTypeInside  (std::string const &);
        sem::LocalValue                     * findValue       (std::string const &);
        esl::tiny_vector<sem::CompleteType> * findType        (std::string const &);

        template <typename Value>
        void initStorage ();

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
