#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(40, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
}

TEST_CASE("infer the breach according to limits for PASSIVE_COOLING") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 30) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 40) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -1) == TOO_LOW);
}
TEST_CASE("infer the breach according to limits for HI_ACTIVE_COOLING") {
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 40) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 46) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -1) == TOO_LOW);
}
TEST_CASE("infer the breach according to limits for MED_ACTIVE_COOLING") {
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 35) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 45) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1) == TOO_LOW);
}

TEST_CASE("infer the breach according to limits of PASSIVE_COOLING and send alert") {
  AlertTarget alertController = TO_CONTROLLER;
  AlertTarget alertEmail = TO_EMAIL;
  BatteryCharacter batteryChar;
  
  batteryChar.coolingType = PASSIVE_COOLING;
  REQUIRE(checkAndAlert(alertController,batteryChar, 30) == NORMAL);
  REQUIRE(checkAndAlert(alertEmail,batteryChar, 30) == NORMAL);
  REQUIRE(checkAndAlert(alertController,batteryChar, 40) == TOO_HIGH);
  REQUIRE(checkAndAlert(alertEmail,batteryChar, 40) == TOO_HIGH);
  REQUIRE(checkAndAlert(alertController,batteryChar, -1) == TOO_LOW);
  REQUIRE(checkAndAlert(alertEmail,batteryChar, -1) == TOO_LOW);
}

TEST_CASE("infer the breach according to limits of HI_ACTIVE_COOLING and send alert") {
  AlertTarget alertController = TO_CONTROLLER;
  AlertTarget alertEmail = TO_EMAIL;
  BatteryCharacter batteryChar;

  batteryChar.coolingType = HI_ACTIVE_COOLING;
  REQUIRE(checkAndAlert(alertController,batteryChar, 40) == NORMAL);
  REQUIRE(checkAndAlert(alertEmail,batteryChar, 40) == NORMAL);
  REQUIRE(checkAndAlert(alertController,batteryChar, 46) == TOO_HIGH);
  REQUIRE(checkAndAlert(alertEmail,batteryChar, 46) == TOO_HIGH);
  REQUIRE(checkAndAlert(alertController,batteryChar, -1) == TOO_LOW);
  REQUIRE(checkAndAlert(alertEmail,batteryChar, -1) == TOO_LOW);
}

TEST_CASE("infer the breach according to limits of MED_ACTIVE_COOLING and send alert") {
  AlertTarget alertController = TO_CONTROLLER;
  AlertTarget alertEmail = TO_EMAIL;
  BatteryCharacter batteryChar;

  batteryChar.coolingType = MED_ACTIVE_COOLING;
  REQUIRE(checkAndAlert(alertController,batteryChar, 35) == NORMAL);
  REQUIRE(checkAndAlert(alertEmail,batteryChar, 35) == NORMAL);
  REQUIRE(checkAndAlert(alertController,batteryChar, 45) == TOO_HIGH);
  REQUIRE(checkAndAlert(alertEmail,batteryChar, 45) == TOO_HIGH);
  REQUIRE(checkAndAlert(alertController,batteryChar, -1) == TOO_LOW);
  REQUIRE(checkAndAlert(alertEmail,batteryChar, -1) == TOO_LOW);
}
