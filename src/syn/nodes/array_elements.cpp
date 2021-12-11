#include "syn/nodes/array_elements.hpp"

#include "esl/component.hpp"

namespace esl {

    using cynth::syn::node::RangeTo;
    using cynth::syn::node::RangeToBy;
    using cynth::syn::node::Spread;

    template <>
    void component_deleter<RangeTo>::operator () (RangeTo * ptr) const {
        delete ptr;
    }

    template <>
    RangeTo * component_allocator<RangeTo>::operator () (RangeTo const & other) const {
        return new RangeTo{other};
    }

    template <>
    RangeTo * component_allocator<RangeTo>::operator () (RangeTo && other) const {
        return new RangeTo{std::move(other)};
    }

    template <>
    void component_deleter<RangeToBy>::operator () (RangeToBy * ptr) const {
        delete ptr;
    }

    template <>
    RangeToBy * component_allocator<RangeToBy>::operator () (RangeToBy const & other) const {
        return new RangeToBy{other};
    }

    template <>
    RangeToBy * component_allocator<RangeToBy>::operator () (RangeToBy && other) const {
        return new RangeToBy{std::move(other)};
    }

    template <>
    void component_deleter<Spread>::operator () (Spread * ptr) const {
        delete ptr;
    }

    template <>
    Spread * component_allocator<Spread>::operator () (Spread const & other) const {
        return new Spread{other};
    }

    template <>
    Spread * component_allocator<Spread>::operator () (Spread && other) const {
        return new Spread{std::move(other)};
    }

}

// TODO
#if 0
namespace cynth {

    display_result syn::node::RangeTo::display () const {
        return cynth::display(from) + " to " + cynth::display(to);
    }

    syn::array_elem_eval_result syn::node::RangeTo::eval_array_elem (sem::context &) const {
        return syn::make_array_elem_eval_result(result_error{"Range array elements are not supported yet."});
    }

    display_result syn::node::RangeToBy::display () const {
        return cynth::display(from) + " to " + cynth::display(to) + " by " + cynth::display(by);
    }

    syn::array_elem_eval_result syn::node::RangeToBy::eval_array_elem (sem::context &) const {
        return syn::make_array_elem_eval_result(result_error{"Range array elements are not supported yet."});
    }

    display_result syn::node::Spread::display () const {
        return "..." + cynth::display(container);
    }

    syn::array_elem_eval_result syn::node::Spread::eval_array_elem (sem::context &) const {
        return syn::make_array_elem_eval_result(result_error{"Range array elements are not supported yet."});
    }

}
#endif
