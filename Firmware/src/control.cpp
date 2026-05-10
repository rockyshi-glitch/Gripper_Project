#include "control.h"

PIDParams pid_params = {1.0, 0.0, 0.0}; // 默认PID参数

float target_force = 0.0;
bool force_control_mode = false;

void control_init() {
    // 初始化控制逻辑
}

void control_loop() {
    if (force_control_mode) {
        // PID力控逻辑预留
        float current_force = sensor_get_force();
        float error = target_force - current_force;
        // 计算PID输出
        // motor_set_speed(pid_output);
    }
    motor_run();
}

void control_set_target_force(float force) {
    target_force = force;
    force_control_mode = true;
}

float control_get_target_force() {
    return target_force;
}

bool control_is_force_control_enabled() {
    return force_control_mode;
}

void control_stop() {
    force_control_mode = false;
    motor_stop();
}

void control_open_gripper() {
    if (!sensor_is_open_limit()) {
        force_control_mode = false;
        motor_move_to(motor_get_position() + 100); // 示例移动
    }
}

void control_close_gripper() {
    if (!sensor_is_close_limit()) {
        force_control_mode = false;
        motor_move_to(motor_get_position() - 100); // 示例移动
    }
}
