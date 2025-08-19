#pragma once

enum Vital {
    VitalTemperature,
    VitalPulse,
    VitalSpo2,
    VitalCount
};

enum Language {
    LANG_ENGLISH,
    LANG_GERMAN,
    LANG_COUNT
};

typedef struct {
    enum Vital status;
    const char* alertMessages[LANG_COUNT];
} VitalInfo;

int vitalsOk(float temperature, float pulseRate, float spo2);

