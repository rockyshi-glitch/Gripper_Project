#include <Arduino.h>
#include "motor.h"
#include "sensor.h"
#include "control.h"

void setup() {
    Serial.begin(115200);
    motor_init();
    sensor_init();
    control_init();
}

void loop() {
    control_loop();
    delay(10);
}