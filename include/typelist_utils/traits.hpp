#pragma once

#include <tuple>
#include <type_traits>

namespace tl::traits
{
template <typename>
struct is_tuple : std::false_type
{};
template <typename... Ts>
struct is_tuple<std::tuple<Ts...>> : std::true_type
{};

template <typename T>
constexpr auto is_tuple_v = is_tuple<T>::value;

}  // namespace tl::traits

namespace tl::concepts
{
template <typename T, typename U>
concept same_as = std::is_same_v<T, U>;

template <typename T>
concept tuple = tl::traits::is_tuple_v<T>;

template <template <typename, typename> typename P, typename T, typename U>
concept binary_value_predicate = requires
{
    {
        P<T, U>::value
        } -> same_as<const bool&>;
};

template <template <typename> typename P, typename T>
concept unary_value_predicate = requires
{
    {
        P<T>::value
        } -> same_as<const bool&>;
};

template <template <typename, typename> typename P, typename T, typename U>
concept binary_type_predicate = requires
{
    typename P<T, U>;
};

template <template <typename> typename P, typename T>
concept unary_type_predicate = requires
{
    typename P<T>::type;
};

}  // namespace tl::concepts
