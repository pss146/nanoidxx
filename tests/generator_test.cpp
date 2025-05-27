#include <catch2/catch_test_macros.hpp>

#include <nanoid/nanoid.h>

TEST_CASE("Random Int") {
    nanoid::RandomGenerator rg;

    auto n = rg.randomInt32();
    REQUIRE(n != -1);
}

TEST_CASE("Random Int in range") {
    nanoid::RandomGenerator rg;
    const int min = 0;
    const int max = 10;

    auto n = rg.randomInt32(min, max);
    REQUIRE(n >= min);
    REQUIRE(n <= max);
}

TEST_CASE("Random data") {
    nanoid::RandomGenerator rg;
    const int size = 20;
    std::vector<uint8_t> buff(size, '\0');

    REQUIRE_NOTHROW(rg.randomBytes(buff.data(), size));
}