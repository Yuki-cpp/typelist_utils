#define CATCH_CONFIG_MAIN

#include <iostream>
#include <tuple>

#include <catch2/catch.hpp>
#include <typelist_utils/tl.hpp>

TEST_CASE("tl::start_with works", "[tl::start_with]")
{
    SECTION("Checking empty tuples")
    {
        using empty = std::tuple<>;

        REQUIRE(tl::start_with_v<empty, int> == false);
    }

    SECTION("Checking non empty tuples")
    {
        using t = std::tuple<bool, float, long>;

        REQUIRE(tl::start_with_v<t, bool> == true);
        REQUIRE(tl::start_with_v<t, int> == false);
        REQUIRE(tl::start_with_v<t, float> == false);
        REQUIRE(tl::start_with_v<t, long> == false);
    }
}

TEST_CASE("tl::count works", "[tl::count]")
{
    SECTION("Checking empty tuples")
    {
        using empty = std::tuple<>;

        REQUIRE(tl::count_v<empty, int> == 0);
    }

    SECTION("Checking non empty tuples")
    {
        using t = std::tuple<bool, float, float, int>;

        REQUIRE(tl::count_v<t, bool> == 1);
        REQUIRE(tl::count_v<t, float> == 2);
        REQUIRE(tl::count_v<t, int> == 1);
        REQUIRE(tl::count_v<t, char> == 0);
    }
}

TEST_CASE("tl::contains works", "[tl::contains]")
{
    SECTION("Checking empty tuples")
    {
        using empty = std::tuple<>;

        REQUIRE(tl::contains_v<empty, int> == false);
    }

    SECTION("Checking non empty tuples")
    {
        using t = std::tuple<bool, float, float, int>;

        REQUIRE(tl::contains_v<t, bool> == true);
        REQUIRE(tl::contains_v<t, float> == true);
        REQUIRE(tl::contains_v<t, int> == true);
        REQUIRE(tl::contains_v<t, char> == false);
    }
}

TEST_CASE("tl::concat works", "[tl::concat]")
{
    SECTION("Concatenating non empty tuples")
    {
        using t1 = std::tuple<int>;
        using t2 = std::tuple<double>;
        using t3 = std::tuple<double, char>;

        REQUIRE(std::is_same_v<tl::concat_t<t1, t2>, std::tuple<int, double>>);
        REQUIRE(std::is_same_v<tl::concat_t<t2, t3>, std::tuple<double, double, char>>);
    }

    SECTION("Concatenating empty tuples")
    {
        using empty = std::tuple<>;
        using t1 = std::tuple<double>;
        using t2 = std::tuple<double, char>;

        REQUIRE(std::is_same_v<tl::concat_t<empty, empty>, empty>);

        REQUIRE(std::is_same_v<tl::concat_t<empty, t1>, t1>);
        REQUIRE(std::is_same_v<tl::concat_t<t1, empty>, t1>);

        REQUIRE(std::is_same_v<tl::concat_t<empty, t2>, t2>);
        REQUIRE(std::is_same_v<tl::concat_t<t2, empty>, t2>);
    }
}