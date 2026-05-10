#include <Arduino.h>
#include "motor.h"
#include "sensor.h"
#include "control.h"
#include "commands.h"

void setup() {
    Serial.begin(115200);
    motor_init();
    sensor_init();
    control_init();
    commands_init();
}

void loop() {
    commands_process();
    control_loop();
    delay(10);
}
