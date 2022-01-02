#pragma once

#include <forward_list>
#include <tuple>

#include "context/forward.hpp"

namespace cynth::context {

    template <typename... Values>
    struct Storage {
        friend Main;

        template <typename T>
        using RefvalContainer = std::forward_list<T>;

        template <typename Value>
        RefvalContainer<Value> & storedValues () {
            return std::get<RefvalContainer<Value>>(referential);
        }

        template <typename Value>
        Value & storeValue (Value const & value) {
            auto & stored = storedValues<Value>();
            stored.push_front(value);
            return stored.front();
        }

    protected:
        std::tuple<RefvalContainer<Values>...> referential;
    };

}
