#include "catch.hpp"

SECTION("test 01"){
    CHECK(1 == 2);
    REQUIRE(1 == 1);
}

SECTION("test 02"){
    CHECK(1 == 2);
    REQUIRE(1 == 1);
}