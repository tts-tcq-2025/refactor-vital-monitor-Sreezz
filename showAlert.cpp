#include "./showAlert.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <cstdio>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

void showAlert(const char* message) {
    printf("Message: %s", message);
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}
