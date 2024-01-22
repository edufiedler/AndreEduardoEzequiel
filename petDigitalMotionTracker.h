#include <MPU9250_WE.h>
#include <Wire.h>

#define MPU9250_ADDR 0x68

void initMPU9250();
void statusMPU9250();
extern MPU9250_WE myMPU9250;