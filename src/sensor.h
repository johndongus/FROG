#pragma once
#include <esp_adc_cal.h>

class Sensor {
protected:
    int pin;
    esp_adc_cal_characteristics_t adc_chars;

public:
    Sensor(int pin);
    virtual float readValue() = 0;
};

class PressureSensor : public Sensor {
public:
    PressureSensor(int pin);
    float readValue() override;
};
