#ifndef CONTROL_H
#define CONTROL_H

#include "motor.h"
#include "sensor.h"

// PID参数预留
struct PIDParams {
    float Kp;
    float Ki;
    float Kd;
};

extern PIDParams pid_params;

void control_init();
void control_loop();
void control_set_target_force(float force);
void control_open_gripper();
void control_close_gripper();

#endif