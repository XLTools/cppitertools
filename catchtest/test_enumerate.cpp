#include <enumerate.hpp>

#include <vector>
#include <string>
#include <iterator>
#include <utility>
#include <sstream>

namespace Catch {
template <typename A, typename B>
std::string toString( const std::pair<A, B>& p) {
    std::ostringstream oss;
    oss << '{' << p.first << ", " << p.second << '}';
    return oss.str();
}
}

#include "catch.hpp"

using Vec = std::vector<std::pair<std::size_t, char>>;
using iter::enumerate;

TEST_CASE("Basic Function", "[enumerate]") {
    std::string str = "abc";
    auto e = enumerate(str);
    Vec v(std::begin(e), std::end(e));
    Vec vc{{0, 'a'}, {1, 'b'}, {2, 'c'}};

    REQUIRE( v == vc );
}

TEST_CASE("Empty", "[enumerate]") {
    std::string emp{};
    auto e = enumerate(emp);
    Vec v(std::begin(e), std::end(e));

    REQUIRE( v.empty() );
}

TEST_CASE("Modifications through enumerate affect container", "[enumerate]") {
    std::vector<int> v{1, 2, 3, 4};
    std::vector<int> vc(v.size(), -1);
    for (auto&& p : enumerate(v)){
        p.second = -1;
    }

    REQUIRE( v == vc );
}

TEST_CASE("Static array works", "[enumerate]") {
    char arr[] = {'w', 'x', 'y'};

    SECTION("Conversion to vector") {
        auto e = enumerate(arr);
        Vec v(std::begin(e), std::end(e));
        Vec vc{{0, 'w'}, {1, 'x'}, {2, 'y'}};
        REQUIRE( v == vc );
    }

    SECTION("Modification through enumerate") {
        for (auto&& p : enumerate(arr)) {
            p.second = 'z';
        }
        std::vector<char> v(std::begin(arr), std::end(arr));
        decltype(v) vc(v.size(), 'z');
        REQUIRE( v == vc );
    }
}

TEST_CASE("initializer_list works", "[enumerate]") {
    auto e = enumerate({'a', 'b', 'c'});
    Vec v(std::begin(e), std::end(e));
    Vec vc{{0, 'a'}, {1, 'b'}, {2, 'c'}};
    REQUIRE( v == vc );
}