#include "petDigitalTempSensors.h"

OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

// Number of temperature devices found
int numberOfDevices;

// We'll use this variable to store a found device address
DeviceAddress tempDeviceAddress;

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if (deviceAddress[i] < 16)
            Serial.print("0");
        Serial.print(deviceAddress[i], HEX);
    }
    Serial.println();
}

void initTempSensors()
{
    sensors.begin();
    // Grab a count of devices on the wire
    numberOfDevices = sensors.getDeviceCount();

    // locate devices on the bus
    Serial.print("Locating devices...");
    Serial.print("Found ");
    Serial.print(numberOfDevices, DEC);
    Serial.println(" devices.");

    // Loop through each device, print out address
    for (int i = 0; i < numberOfDevices; i++)
    {
        // Search the wire for address
        if (sensors.getAddress(tempDeviceAddress, i))
        {
            Serial.print("Found device ");
            Serial.print(i, DEC);
            Serial.print(" with address: ");
            printAddress(tempDeviceAddress);
            Serial.println();
        }
        else
        {
            Serial.print("Found ghost device at ");
            Serial.print(i, DEC);
            Serial.print(" but could not detect address. Check power and cabling");
        }
    }
}

String statusTempSensors()
{
    String log;
    sensors.requestTemperatures(); // Send the command to get temperatures

    // Loop through each device, print out temperature data
    for (int i = 0; i < numberOfDevices; i++)
    {
        // Search the wire for address
        if (sensors.getAddress(tempDeviceAddress, i))
        {
            float tempC = sensors.getTempC(tempDeviceAddress);
            
            // Output the device ID
            Serial.printf("Temperature for device %d:", i);
            Serial.printf("Temp C: %f\n", tempC);
            printAddress(tempDeviceAddress);
            Serial.println();
            log = "Temperature for device " + i;
            log += ": ";
            log += tempC;
            log += "\n";
        }
    }
    return log;
}