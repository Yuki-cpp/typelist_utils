#pragma once

#include <tuple>
#include <type_traits>

#include "traits.hpp"
#include "utils.hpp"

namespace tl
{

namespace sort_impl
{
template <tl::concepts::tuple T>
using split_half_l_t = split_l_t<T, std::tuple_size_v<T> / 2>;

template <tl::concepts::tuple T>
using split_half_r_t = split_r_t<T, std::tuple_size_v<T> / 2>;

template <tl::concepts::tuple A,
          tl::concepts::tuple B,
          template <typename, typename>
          typename Predicate>
struct merge;

template <tl::concepts::tuple B, template <typename, typename> typename Predicate>
struct merge<std::tuple<>, B, Predicate>
{
    using type = B;
};

template <typename A, typename... As, template <typename, typename> typename Predicate>
struct merge<std::tuple<A, As...>, std::tuple<>, Predicate>
{
    using type = std::tuple<A, As...>;
};

template <typename A,
          typename... As,
          typename B,
          typename... Bs,
          template <typename, typename>
          typename Predicate>
    requires tl::concepts::binary_value_predicate<Predicate, A, B>
struct merge<std::tuple<A, As...>, std::tuple<B, Bs...>, Predicate>
{
    using list_a = std::tuple<A, As...>;
    using list_b = std::tuple<B, Bs...>;
    using type = std::conditional_t<
        Predicate<A, B>::value,
        tl::concat_t<std::tuple<A>, typename merge<std::tuple<As...>, list_b, Predicate>::type>,
        tl::concat_t<std::tuple<B>, typename merge<list_a, std::tuple<Bs...>, Predicate>::type>>;
};

template <tl::concepts::tuple A,
          tl::concepts::tuple B,
          template <typename, typename>
          typename Predicate>
using merge_t = typename merge<A, B, Predicate>::type;

}  // namespace sort_impl

template <tl::concepts::tuple T, template <typename, typename> typename Predicate>
struct sort;

template <template <typename, typename> typename Predicate>
struct sort<std::tuple<>, Predicate>
{
    using type = std::tuple<>;
};

template <typename T, template <typename, typename> typename Predicate>
struct sort<std::tuple<T>, Predicate>
{
    using type = std::tuple<T>;
};

// Inductive step
template <typename T, typename... Ts, template <typename, typename> typename Predicate>
struct sort<std::tuple<T, Ts...>, Predicate>
{
    using input_t = std::tuple<T, Ts...>;
    using left_sort_t = typename sort<tl::sort_impl::split_half_l_t<input_t>, Predicate>::type;
    using right_sort_t = typename sort<tl::sort_impl::split_half_r_t<input_t>, Predicate>::type;

    using type = tl::sort_impl::merge_t<left_sort_t, right_sort_t, Predicate>;
};

template <tl::concepts::tuple T, template <typename, typename> typename Predicate>
using sort_t = typename sort<T, Predicate>::type;

}  // namespace tl
