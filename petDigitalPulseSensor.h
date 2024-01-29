#include <PulseSensorPlayground.h>

// PULSE_BLINK e PULSE_FADE são os LEDS que irão revezar de acordo com a batida do coração
const int PULSE_BLINK[2] = {32, 23};
const int PULSE_FADE[2] = {32, 23};

// PULSE_INPUT_PIN irá receber o sinal do sensor de pulso
#define PULSE_INPUT_PIN 36
// PULSE_OUTPUT_PIN irá alimentar corrente para o sensor de pulso e possibilita ligar e desligar o sensor usando digitalWrite HIGH e LOW
#define PULSE_OUTPUT_PIN 16
#define MAX_SIGNAL_SAMPLE 200
#define MAX_BPM_SAMPLE 8

void initPulseSensor();
int statusPulseSensor();