#include "motor.h"

AccelStepper stepper(AccelStepper::DRIVER, MOTOR_STEP_PIN, MOTOR_DIR_PIN);

void motor_init() {
    pinMode(MOTOR_EN_PIN, OUTPUT);
    motor_enable();
    stepper.setMaxSpeed(1000);
    stepper.setAcceleration(500);
}

void motor_enable() {
    digitalWrite(MOTOR_EN_PIN, LOW); // A4988/DRV8825/TMC STEP/DIR drivers are typically enabled LOW.
}

void motor_disable() {
    digitalWrite(MOTOR_EN_PIN, HIGH); // Disable motor output to reduce heat when holding torque is not needed.
}

void motor_set_speed(long speed) {
    stepper.setSpeed(speed);
}

void motor_move_to(long position) {
    stepper.moveTo(position);
}

long motor_get_position() {
    return stepper.currentPosition();
}

void motor_stop() {
    stepper.stop();
}

void motor_run() {
    stepper.run();
}
