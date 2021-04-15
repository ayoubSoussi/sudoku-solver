#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/utils.hpp"


TEST_CASE( "toVar function computed", "[tovar]" ) {
    REQUIRE(toVar(0, 0, 0) == 0);
    REQUIRE(toVar(0, 2, 2) == 20);
    REQUIRE(toVar(2, 0, 2) == 164);
    REQUIRE(toVar(2, 2, 0) == 180);
}
