#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <cstdio>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

enum Vital {
    VitalTemperature,
    VitalPulse,
    VitalSpo2,
    VitalCount
};

typedef struct {
    enum Vital status;
    const char* alertMessage;
} VitalInfo;

// Mapping table
const VitalInfo vitalInfoTable[VitalCount] = {
    {VitalTemperature, "Temperature is critical!\n"},
    {VitalPulse, "Pulse Rate is out of range!\n"},
    {VitalSpo2, "Oxygen Saturation out of range!\n"}
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

void showAlert(int CurrVital) {
    printf("Message: %s", vitalInfoTable[CurrVital].alertMessage);
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
        allOk &= !vitalChecks[i](values[i]) || (showAlert(i), false);
    }
    return allOk ? 1 : 0;
}
