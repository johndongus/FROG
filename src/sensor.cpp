#include "sensor.h"
#include "Arduino.h"

Sensor::Sensor(int pin) : pin(pin) {
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
}

PressureSensor::PressureSensor(int pin) : Sensor(pin) {}

float PressureSensor::readValue() {
    uint32_t raw = analogRead(pin);
    uint32_t voltage = esp_adc_cal_raw_to_voltage(raw, &adc_chars);
    float adjustedVoltage = voltage + 20;
    return (adjustedVoltage - 500) / (4500 - 500) * 100.0;
}
