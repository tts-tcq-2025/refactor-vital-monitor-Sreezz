#include <gtest/gtest.h>
#include "./monitor.h"

TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
  ASSERT_FALSE(vitalsOk(99, 102, 70));
  ASSERT_TRUE(vitalsOk(98.1, 70, 98));

  ASSERT_FALSE(vitalsOk(103, 70, 95));  // Temperature > 102
  ASSERT_FALSE(vitalsOk(94.9, 70, 95));  // Temperature < 95
  ASSERT_FALSE(vitalsOk(98.6, 101, 95));  // Pulse > 100
  ASSERT_FALSE(vitalsOk(98.6, 59, 95));  // Pulse < 60
  ASSERT_FALSE(vitalsOk(98.6, 70, 89.9));  // Spo2 < 90
  ASSERT_FALSE(vitalsOk(103, 101, 89));  // All vitals not ok
}


TEST(GetAlertMessageTest, ReturnsCorrectMessageInGerman) {
    currentLanguage = LANG_GERMAN;

    EXPECT_STREQ(getAlertMessage(VitalTemperature), "Temperatur ist kritisch!\n");
    EXPECT_STREQ(getAlertMessage(VitalPulse), "Puls ist außerhalb des Bereichs!\n");
    EXPECT_STREQ(getAlertMessage(VitalSpo2), "Sauerstoffsättigung außerhalb des Bereichs!\n");
}

TEST(GetAlertMessageTest, ReturnsCorrectMessageInEnglish) {
    currentLanguage = LANG_ENGLISH;

    EXPECT_STREQ(getAlertMessage(VitalTemperature), "Temperature is critical!\n");
    EXPECT_STREQ(getAlertMessage(VitalPulse), "Pulse Rate is out of range!\n");
    EXPECT_STREQ(getAlertMessage(VitalSpo2), "Oxygen Saturation out of range!\n");
}


