#include "motor.h"

AccelStepper stepper(AccelStepper::DRIVER, MOTOR_STEP_PIN, MOTOR_DIR_PIN);

void motor_init() {
    pinMode(MOTOR_EN_PIN, OUTPUT);
    digitalWrite(MOTOR_EN_PIN, LOW); // 使能电机
    stepper.setMaxSpeed(1000);
    stepper.setAcceleration(500);
}

void motor_set_speed(long speed) {
    stepper.setSpeed(speed);
}

void motor_move_to(long position) {
    stepper.moveTo(position);
}

void motor_run() {
    stepper.run();
}