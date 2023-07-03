#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(40, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
}

TEST_CASE("infer the breach according to limits for PASSIVE_COOLING") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 30) == NORMAL); //0,35
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 40) == TOO_HIGH); //0,35
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -1) == TOO_LOW); //0,35
}
TEST_CASE("infer the breach according to limits HI_ACTIVE_COOLING") {
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 40) == NORMAL); //0,45
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 46) == TOO_HIGH); //0,45
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -1) == TOO_LOW); //0,45
}
TEST_CASE("infer the breach according to limits MED_ACTIVE_COOLING") {
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 35) == NORMAL); //0,40
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 45) == TOO_HIGH); //0,40
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1) == TOO_LOW); //0,40
}
