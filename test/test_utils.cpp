#include <tuple>

#include <catch.hpp>
#include <typelist_utils/tl.hpp>

TEST_CASE("tl::start_with works", "[tl::start_with]")
{
    SECTION("Empty tuples")
    {
        using empty = std::tuple<>;

        REQUIRE(tl::start_with_v<empty, int> == false);
    }

    SECTION("Non empty tuples")
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
    SECTION("Empty tuples")
    {
        using empty = std::tuple<>;

        REQUIRE(tl::count_v<empty, int> == 0);
    }

    SECTION("Non empty tuples")
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
    SECTION("Empty tuples")
    {
        using empty = std::tuple<>;

        REQUIRE(tl::contains_v<empty, int> == false);
    }

    SECTION("Non empty tuples")
    {
        using t = std::tuple<bool, float, float, int>;

        REQUIRE(tl::contains_v<t, bool> == true);
        REQUIRE(tl::contains_v<t, float> == true);
        REQUIRE(tl::contains_v<t, int> == true);
        REQUIRE(tl::contains_v<t, char> == false);
    }
}

TEST_CASE("tl::contains_all works", "[tl::contains_all]")
{
    SECTION("Empty tuples")
    {
        using empty = std::tuple<>;

        REQUIRE(tl::contains_all_v<empty> == true);
        REQUIRE(tl::contains_all_v<empty, int> == false);
    }

    SECTION("Non empty tuples")
    {
        using t = std::tuple<bool, float, float, int>;

        REQUIRE(tl::contains_all_v<t, bool, float, int> == true);
        REQUIRE(tl::contains_all_v<t, bool, double, int> == false);
        REQUIRE(tl::contains_all_v<t, double, double, double> == false);
        REQUIRE(tl::contains_all_v<t> == true);
    }
}

TEST_CASE("tl::concat works", "[tl::concat]")
{
    SECTION("Empty tuples")
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

    SECTION("Non empty tuples")
    {
        using t1 = std::tuple<int>;
        using t2 = std::tuple<double>;
        using t3 = std::tuple<double, char>;

        REQUIRE(std::is_same_v<tl::concat_t<t1, t2>, std::tuple<int, double>>);
        REQUIRE(std::is_same_v<tl::concat_t<t2, t3>, std::tuple<double, double, char>>);
    }
}

TEST_CASE("tl::split works", "[tl::split]")
{
    SECTION("Empty tuple")
    {
        using empty = std::tuple<>;

        REQUIRE(std::is_same_v<tl::split_l_t<empty, 0>, empty>);
        REQUIRE(std::is_same_v<tl::split_r_t<empty, 0>, empty>);
    }

    SECTION("Unit tuple")
    {
        using empty = std::tuple<>;
        using unit = std::tuple<int>;

        REQUIRE(std::is_same_v<tl::split_l_t<unit, 0>, empty>);
        REQUIRE(std::is_same_v<tl::split_r_t<unit, 0>, unit>);

        REQUIRE(std::is_same_v<tl::split_l_t<unit, 1>, unit>);
        REQUIRE(std::is_same_v<tl::split_r_t<unit, 1>, empty>);
    }

    SECTION("Bigger tuples")
    {
        using empty = std::tuple<>;
        using odd = std::tuple<double, int, long>;

        REQUIRE(std::is_same_v<tl::split_l_t<odd, 0>, empty>);
        REQUIRE(std::is_same_v<tl::split_l_t<odd, 1>, std::tuple<double>>);
        REQUIRE(std::is_same_v<tl::split_l_t<odd, 2>, std::tuple<double, int>>);
        REQUIRE(std::is_same_v<tl::split_l_t<odd, 3>, odd>);

        REQUIRE(std::is_same_v<tl::split_r_t<odd, 0>, odd>);
        REQUIRE(std::is_same_v<tl::split_r_t<odd, 1>, std::tuple<int, long>>);
        REQUIRE(std::is_same_v<tl::split_r_t<odd, 2>, std::tuple<long>>);
        REQUIRE(std::is_same_v<tl::split_r_t<odd, 3>, empty>);

        using even = std::tuple<double, char, int, bool>;

        REQUIRE(std::is_same_v<tl::split_l_t<even, 0>, empty>);
        REQUIRE(std::is_same_v<tl::split_l_t<even, 1>, std::tuple<double>>);
        REQUIRE(std::is_same_v<tl::split_l_t<even, 2>, std::tuple<double, char>>);
        REQUIRE(std::is_same_v<tl::split_l_t<even, 3>, std::tuple<double, char, int>>);
        REQUIRE(std::is_same_v<tl::split_l_t<even, 4>, even>);

        REQUIRE(std::is_same_v<tl::split_r_t<even, 0>, even>);
        REQUIRE(std::is_same_v<tl::split_r_t<even, 1>, std::tuple<char, int, bool>>);
        REQUIRE(std::is_same_v<tl::split_r_t<even, 2>, std::tuple<int, bool>>);
        REQUIRE(std::is_same_v<tl::split_r_t<even, 3>, std::tuple<bool>>);
        REQUIRE(std::is_same_v<tl::split_r_t<even, 4>, empty>);
    }
}

TEST_CASE("tl::for_each works", "[tl::for_each]")
{
    SECTION("Empty tuples")
    {
        using empty = std::tuple<>;
        REQUIRE(std::is_same_v<tl::for_each_t<empty, std::make_unsigned>, empty>);
    }

    SECTION("Non empty tuples")
    {
        using t = std::tuple<int, short, long>;
        using t2 = std::tuple<unsigned int, unsigned short, unsigned long>;
        REQUIRE(std::is_same_v<tl::for_each_t<t, std::make_unsigned>, t2>);
    }
}

TEST_CASE("tl::swap_elements works", "[tl::swap_elements]")
{
    SECTION("Short tuples")
    {
        using t = std::tuple<int, short>;
        using swapped = std::tuple<short, int>;

        REQUIRE(std::is_same_v<tl::swap_elements_t<t, 0, 1>, swapped>);
    }

    SECTION("Bigger tuples")
    {
        using t = std::tuple<int, short, long>;
        using swap_0_1 = std::tuple<short, int, long>;
        using swap_0_2 = std::tuple<long, short, int>;
        using swap_1_2 = std::tuple<int, long, short>;

        REQUIRE(std::is_same_v<tl::swap_elements_t<t, 0, 1>, swap_0_1>);
        REQUIRE(std::is_same_v<tl::swap_elements_t<t, 0, 2>, swap_0_2>);
        REQUIRE(std::is_same_v<tl::swap_elements_t<t, 1, 2>, swap_1_2>);
    }
}