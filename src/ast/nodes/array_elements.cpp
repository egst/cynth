#include "ast/nodes/array_elements.hpp"

#include "esl/component.hpp"

namespace esl {

    using cynth::ast::node::RangeTo;
    using cynth::ast::node::RangeToBy;
    using cynth::ast::node::Spread;

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

    display_result ast::node::RangeTo::display () const {
        return cynth::display(from) + " to " + cynth::display(to);
    }

    ast::array_elem_eval_result ast::node::RangeTo::eval_array_elem (sem::context &) const {
        return ast::make_array_elem_eval_result(result_error{"Range array elements are not supported yet."});
    }

    display_result ast::node::RangeToBy::display () const {
        return cynth::display(from) + " to " + cynth::display(to) + " by " + cynth::display(by);
    }

    ast::array_elem_eval_result ast::node::RangeToBy::eval_array_elem (sem::context &) const {
        return ast::make_array_elem_eval_result(result_error{"Range array elements are not supported yet."});
    }

    display_result ast::node::Spread::display () const {
        return "..." + cynth::display(container);
    }

    ast::array_elem_eval_result ast::node::Spread::eval_array_elem (sem::context &) const {
        return ast::make_array_elem_eval_result(result_error{"Range array elements are not supported yet."});
    }

}
#endif
