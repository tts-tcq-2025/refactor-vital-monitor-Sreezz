#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;


enum VitalStatus 
{
    OK,
    TemperatureCritical,
    PulseOutOfRange,
    Spo2Low
};


bool isTemperatureCritical(float temperature) 
{
    return (temperature > 102 || temperature < 95);
}

bool isPulseOutOfRange(float pulseRate) 
{
    return (pulseRate < 60 || pulseRate > 100);
}

bool isSpo2Low(float spo2) 
{
    return (spo2 < 90);
}

enum VitalStatus evaluateVitals(float temperature, float pulseRate, float spo2) 
{
    if (isTemperatureCritical(temperature)) 
    {
        return TemperatureCritical;
    }
    if (isPulseOutOfRange(pulseRate)) 
    {
        return PulseOutOfRange;
    }
    if (isSpo2Low(spo2)) 
    {
        return Spo2Low;
    }
    return OK;
}

void showAlert(enum VitalStatus status) 
{
      switch (status) 
    {
        case TemperatureCritical:
            cout << "Temperature is critical!\n";
            break;
        case PulseOutOfRange:
            cout << "Pulse Rate is out of range!\n";
            break;
        case Spo2Low:
            cout << "Oxygen Saturation out of range!\n";
            break;
        default:
            //
            break;
    }
    for (int i = 0; i < 6; i++) 
    {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}


int vitalsOk(float temperature, float pulseRate, float spo2) 
{
    enum VitalStatus status = evaluateVitals(temperature, pulseRate, spo2);
    showAlert(status);

    if(status == OK)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  
}

