#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <cstdio>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

Language currentLanguage = LANG_GERMAN;  // Default language

// Mapping table - Language order should be same as enum Language order
const VitalInfo vitalInfoTable[VitalCount] = {
    {VitalTemperature, {
        "Temperature is critical!\n",
        "Temperatur ist kritisch!\n"
    }},
    {VitalPulse, {
        "Pulse Rate is out of range!\n",
        "Puls ist außerhalb des Bereichs!\n"
    }},
    {VitalSpo2, {
        "Oxygen Saturation out of range!\n",
        "Sauerstoffsättigung außerhalb des Bereichs!\n"
    }}
};

typedef bool (*VitalCheckFunction)(float);

bool isTemperatureCritical(float temperature) {
    return (temperature > 102 || temperature < 95);
}

bool isPulseOutOfRange(float pulseRate) {
    return (pulseRate < 60 || pulseRate > 100);
}

bool isSpo2Low(float spo2) {
    return (spo2 < 90);
}

// Function pointer array
VitalCheckFunction vitalChecks[] = {
    isTemperatureCritical,
    isPulseOutOfRange,
    isSpo2Low
};

const char* getAlertMessage(int CurrVital) {
    return vitalInfoTable[CurrVital].alertMessages[currentLanguage];
}

void showAlert(const char* message) {
    printf("Message: %s", message);
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
    float values[] = {temperature, pulseRate, spo2};
    bool allOk = true;

    for (int i = VitalTemperature; i < VitalCount; i++) {
        if (vitalChecks[i](values[i])) {
            const char* message = getAlertMessage(i);
            showAlert(message);
            allOk = false;
        }
    }
    return allOk ? 1 : 0;
}
