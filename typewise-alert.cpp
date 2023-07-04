#include "typewise-alert.h"
#include <stdio.h>
#include<map>
using namespace std;

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  map<CoolingType,pair<int,int>> coolingTypeLimits;
  coolingTypeLimits[PASSIVE_COOLING] = {0, 35};
  coolingTypeLimits[HI_ACTIVE_COOLING] = {0, 45};
  coolingTypeLimits[MED_ACTIVE_COOLING] = {0, 40};
  
  pair<int, int> limits = coolingTypeLimits.at(coolingType);
  return inferBreach(temperatureInC, limits.first, limits.second);
}

BreachType checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
  return breachType;
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  if(breachType == TOO_LOW) {
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
  }
  else if(breachType == TOO_HIGH) {
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
  }
}
