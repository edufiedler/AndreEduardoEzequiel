#include <OneWire.h>
#include <DallasTemperature.h>

const int oneWireBus = GPIO_NUM_33; // de GPIO_NUM_34 até GPIO_NUM_39 apenas Input

void initTempSensors();
void statusTempSensors();