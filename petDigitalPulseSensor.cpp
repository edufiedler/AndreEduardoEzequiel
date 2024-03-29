#include "petDigitalPulseSensor.h"

PulseSensorPlayground pulseSensor;

void initPulseSensor()
{
    pulseSensor.begin();
    pulseSensor.analogInput(PULSE_INPUT_PIN);
    pulseSensor.setSerial(Serial);
}

String statusPulseSensor()
{
    String log;
    log = "BPM: ";
    log += getBPMPulseSensor();
    log += "\n";
    return log;
}

String statusPulseSensor(int bpm)
{
    String log;
    log = "BPM: ";
    log += bpm;
    log += "\n";
    return log;
}

int getBPMPulseSensor()
{
    int ledIndex = 0;
    int Signal[MAX_SIGNAL_SAMPLE];
    int signalIndex = 0;
    int signalArraySize = 0;
    int avgSignal = 0;
    int bpmSample[MAX_BPM_SAMPLE];
    int bpmIndex = 0;
    int finalBPM = 0;

    while (!finalBPM)
    {
        Signal[signalIndex] = analogRead(PULSE_INPUT_PIN);
        signalArraySize = (signalIndex > signalArraySize) ? signalIndex : signalArraySize;

        for (int i = 0; i < MAX_SIGNAL_SAMPLE; i++)
        {
            avgSignal += Signal[i];
        }

        avgSignal /= (signalArraySize + 1);
        pulseSensor.setThreshold(avgSignal * 1.1);

        signalIndex = (++signalIndex) % MAX_SIGNAL_SAMPLE;

        if (pulseSensor.sawStartOfBeat())
        {
            ledIndex = (ledIndex + 1) % 2;
            pulseSensor.blinkOnPulse(PULSE_BLINK[ledIndex]);
            pulseSensor.fadeOnPulse(PULSE_FADE[ledIndex]);
            Serial.println(pulseSensor.getBeatsPerMinute());

            bpmSample[bpmIndex] = pulseSensor.getBeatsPerMinute();
            bpmIndex = (++bpmIndex) % MAX_BPM_SAMPLE;
        }

        for (int i = 0; i < MAX_BPM_SAMPLE; i++)
        {
            if (bpmSample[i] >= bpmSample[(i + 1) % MAX_BPM_SAMPLE] + 2 || bpmSample[i] <= bpmSample[(i + 1) % MAX_BPM_SAMPLE] - 2 || bpmSample[i] <= 30)
            {
                finalBPM = 0;
                break;
            }
            else
            {
                finalBPM += bpmSample[i];
            }
            finalBPM /= MAX_BPM_SAMPLE;
        }

        delay(100);
    }
    return finalBPM;
}