#include <typelist_utils/tl.hpp>

int main()
{
    using t = std::tuple<int, bool>;
    tl::swap_elements_t<t, 0, 1> x(true, 42);
}
