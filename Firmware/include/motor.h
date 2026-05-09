#ifndef MOTOR_H
#define MOTOR_H

#include <AccelStepper.h>

// 步进电机引脚定义
#define MOTOR_STEP_PIN 18
#define MOTOR_DIR_PIN 19
#define MOTOR_EN_PIN 21

extern AccelStepper stepper;

void motor_init();
void motor_set_speed(long speed);
void motor_move_to(long position);
void motor_run();

#endif