#include <catch2/catch.hpp>
#include <iostream>

#include "nanoid/nanoid.h"

TEST_CASE("Test test :)") {
    nanoid::NanoId id;

    for (auto i = 0; i < 10; i++) {
        std::cout << "Generated Id: " << id.generate(8) << std::endl;
    }

    REQUIRE(true);
}