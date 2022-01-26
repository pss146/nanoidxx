#include <catch2/catch.hpp>
#include <iostream>

#include "nanoid/nanoid.h"

TEST_CASE("Random IDs") {
    nanoid::NanoId gen;

    auto id1 = gen.generate();
    REQUIRE(id1.size() == 21);

    auto id2 = gen.generate();
    REQUIRE(id1.compare(id2) != 0);
}

TEST_CASE("Invalid params") {
    nanoid::NanoId gen;

    REQUIRE_THROWS_AS(gen.generate(0), std::invalid_argument);
    REQUIRE_THROWS_AS(gen.generate(std::string()), std::invalid_argument);
    REQUIRE_THROWS_AS(gen.generate(std::string(300, '_')), std::invalid_argument);
}

TEST_CASE("Valid generation") {
    nanoid::NanoId gen;

    std::string alphabet = "12345ABCD";
    auto id1 = gen.generate(alphabet, 16);
    REQUIRE(id1.size() == 16);

    for (auto ch: id1) {
        REQUIRE(alphabet.find(ch) != std::string::npos);
    }
}

TEST_CASE("Multiple IDs generation") {
    nanoid::NanoId id;

    for (auto i = 0; i < 20; i++) {
        std::cout << "Generated Id: " << id.generate(8) << std::endl;
    }
}