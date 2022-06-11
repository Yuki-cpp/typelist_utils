#include <tuple>

#include <catch.hpp>
#include <typelist_utils/tl.hpp>

using a = std::integral_constant<int, 0>;
using b = std::integral_constant<int, 1>;
using c = std::integral_constant<int, 2>;
using d = std::integral_constant<int, 3>;
using e = std::integral_constant<int, 4>;

template <typename T, typename U>
struct is_lesser_than
{
    constexpr static auto value = T::value < U::value;
};

template <typename T, typename U>
struct is_greater_than
{
    constexpr static auto value = T::value > U::value;
};

TEST_CASE("tl::sort works", "[tl::sort]")
{
    SECTION("Test utilities")
    {
        SECTION("Check sorting predicates")
        {
            REQUIRE(is_lesser_than<a, a>::value == false);
            REQUIRE(is_lesser_than<a, b>::value == true);
            REQUIRE(is_lesser_than<b, a>::value == false);

            REQUIRE(is_greater_than<a, a>::value == false);
            REQUIRE(is_greater_than<a, b>::value == false);
            REQUIRE(is_greater_than<b, a>::value == true);
        }

        SECTION("Check that splitting function works")
        {
            using t = std::tuple<a, b, c, d>;
            using l = tl::sort_impl::split_half_l_t<t>;
            using r = tl::sort_impl::split_half_r_t<t>;

            REQUIRE(std::is_same_v<l, std::tuple<a, b>>);
            REQUIRE(std::is_same_v<r, std::tuple<c, d>>);

            using t2 = std::tuple<a, b, c, d, e>;
            using l2 = tl::sort_impl::split_half_l_t<t2>;
            using r2 = tl::sort_impl::split_half_r_t<t2>;

            REQUIRE(std::is_same_v<l2, std::tuple<a, b>>);
            REQUIRE(std::is_same_v<r2, std::tuple<c, d, e>>);
        }
    }

    SECTION("Empty tuples")
    {
        using empty = std::tuple<>;

        using sorted_lesser = tl::sort_t<empty, is_lesser_than>;
        using sorted_greater = tl::sort_t<empty, is_greater_than>;

        REQUIRE(std::is_same_v<empty, sorted_lesser>);
        REQUIRE(std::is_same_v<empty, sorted_greater>);
    }

    SECTION("Sorted in Ascending order")
    {
        using t = std::tuple<a, b, c, d>;

        using ascending = std::tuple<a, b, c, d>;
        using descending = std::tuple<d, c, b, a>;

        using sorted_greater = tl::sort_t<t, is_greater_than>;
        using sorted_lesser = tl::sort_t<t, is_lesser_than>;

        REQUIRE(std::is_same_v<sorted_greater, descending>);
        REQUIRE(std::is_same_v<sorted_lesser, ascending>);
    }

    SECTION("Sorted in Descending order")
    {
        using t = std::tuple<d, c, b, a>;

        using ascending = std::tuple<a, b, c, d>;
        using descending = std::tuple<d, c, b, a>;

        using sorted_greater = tl::sort_t<t, is_greater_than>;
        using sorted_lesser = tl::sort_t<t, is_lesser_than>;

        REQUIRE(std::is_same_v<sorted_greater, descending>);
        REQUIRE(std::is_same_v<sorted_lesser, ascending>);
    }

    SECTION("Mixed")
    {
        using t = std::tuple<d, a, b, e, c, a>;

        using ascending = std::tuple<a, a, b, c, d, e>;
        using descending = std::tuple<e, d, c, b, a, a>;

        using sorted_greater = tl::sort_t<t, is_greater_than>;
        using sorted_lesser = tl::sort_t<t, is_lesser_than>;

        REQUIRE(std::is_same_v<sorted_greater, descending>);
        REQUIRE(std::is_same_v<sorted_lesser, ascending>);
    }
}