#pragma once

#include<map>
using namespace std;

map<CoolingType,pair<int,int>> coolingTypeLimits;
coolingTypeLimits.insert(PASSIVE_COOLING,pair<int, int>(0,35));
coolingTypeLimits.insert(HI_ACTIVE_COOLING,pair<int, int>(0,45));
coolingTypeLimits.insert(MED_ACTIVE_COOLING,pair<int, int>(0,40));

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

void checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
