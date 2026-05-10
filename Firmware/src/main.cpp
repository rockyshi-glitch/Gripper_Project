#include <Arduino.h>
#include "motor.h"
#include "sensor.h"
#include "control.h"
#include "serial_command.h"

void setup() {
    Serial.begin(115200);
    motor_init();
    sensor_init();
    control_init();
    serial_command_init();
}

void loop() {
    serial_command_process();
    control_loop();
    delay(10);
}
