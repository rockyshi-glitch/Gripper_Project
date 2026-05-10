#include "serial_command.h"

#include <Arduino.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "control.h"
#include "motor.h"
#include "sensor.h"

namespace {
const size_t SERIAL_COMMAND_BUFFER_SIZE = 64;
char command_buffer[SERIAL_COMMAND_BUFFER_SIZE];
size_t command_length = 0;

void trim_command(char *command) {
    char *start = command;
    while (*start != '\0' && isspace(static_cast<unsigned char>(*start))) {
        start++;
    }

    if (start != command) {
        memmove(command, start, strlen(start) + 1);
    }

    size_t length = strlen(command);
    while (length > 0 && isspace(static_cast<unsigned char>(command[length - 1]))) {
        command[length - 1] = '\0';
        length--;
    }
}

void uppercase_command(char *command) {
    for (size_t i = 0; command[i] != '\0'; i++) {
        command[i] = static_cast<char>(toupper(static_cast<unsigned char>(command[i])));
    }
}

bool parse_float_argument(const char *argument, float *value) {
    if (argument == nullptr || *argument == '\0') {
        return false;
    }

    char *end = nullptr;
    float parsed_value = strtof(argument, &end);
    while (end != nullptr && *end != '\0' && isspace(static_cast<unsigned char>(*end))) {
        end++;
    }

    if (end == argument || (end != nullptr && *end != '\0')) {
        return false;
    }

    *value = parsed_value;
    return true;
}

const char *command_argument(const char *command, size_t command_name_length) {
    const char *argument = command + command_name_length;
    while (*argument != '\0' && isspace(static_cast<unsigned char>(*argument))) {
        argument++;
    }
    return argument;
}

void print_status() {
    Serial.print("STATUS position=");
    Serial.print(motor_get_position());
    Serial.print(" force=");
    Serial.print(sensor_get_force(), 2);
    Serial.print(" open_limit=");
    Serial.print(sensor_is_open_limit() ? 1 : 0);
    Serial.print(" close_limit=");
    Serial.print(sensor_is_close_limit() ? 1 : 0);
    Serial.print(" speed=");
    Serial.print(motor_get_speed());
    Serial.print(" target_force=");
    Serial.print(control_get_target_force(), 2);
    Serial.print(" force_mode=");
    Serial.println(control_is_force_control_enabled() ? 1 : 0);
}

void handle_force_command(const char *argument) {
    float force = 0.0f;
    if (!parse_float_argument(argument, &force)) {
        Serial.println("ERR FORCE requires a numeric target value");
        return;
    }

    if (force < 0.0f) {
        Serial.println("ERR FORCE value must be non-negative");
        return;
    }

    control_set_target_force(force);
    Serial.print("OK FORCE ");
    Serial.println(force, 2);
}

void handle_speed_command(const char *argument) {
    float speed = 0.0f;
    if (!parse_float_argument(argument, &speed)) {
        Serial.println("ERR SPEED requires a numeric value");
        return;
    }

    if (speed < 1.0f) {
        Serial.println("ERR SPEED value must be at least 1 step/s");
        return;
    }

    motor_set_speed(static_cast<long>(speed));
    Serial.print("OK SPEED ");
    Serial.println(motor_get_speed());
}

void handle_command(char *command) {
    trim_command(command);
    if (command[0] == '\0') {
        return;
    }

    char parsed_command[SERIAL_COMMAND_BUFFER_SIZE];
    strncpy(parsed_command, command, SERIAL_COMMAND_BUFFER_SIZE - 1);
    parsed_command[SERIAL_COMMAND_BUFFER_SIZE - 1] = '\0';
    uppercase_command(parsed_command);

    if (strcmp(parsed_command, "OPEN") == 0) {
        control_open_gripper();
        Serial.println("OK OPEN");
    } else if (strcmp(parsed_command, "CLOSE") == 0) {
        control_close_gripper();
        Serial.println("OK CLOSE");
    } else if (strcmp(parsed_command, "STOP") == 0) {
        control_stop();
        Serial.println("OK STOP");
    } else if (strcmp(parsed_command, "STATUS") == 0) {
        print_status();
    } else if (strcmp(parsed_command, "TARE") == 0) {
        sensor_tare();
        Serial.println("OK TARE");
    } else if (strncmp(parsed_command, "FORCE", 5) == 0) {
        handle_force_command(command_argument(command, 5));
    } else if (strncmp(parsed_command, "SPEED", 5) == 0) {
        handle_speed_command(command_argument(command, 5));
    } else {
        Serial.println("ERR unknown command");
    }
}
}

void serial_command_init() {
    command_length = 0;
    command_buffer[0] = '\0';
    Serial.println("Gripper serial command interface ready");
}

void serial_command_process() {
    while (Serial.available() > 0) {
        char input = static_cast<char>(Serial.read());

        if (input == '\r') {
            continue;
        }

        if (input == '\n') {
            command_buffer[command_length] = '\0';
            handle_command(command_buffer);
            command_length = 0;
            command_buffer[0] = '\0';
            continue;
        }

        if (command_length < SERIAL_COMMAND_BUFFER_SIZE - 1) {
            command_buffer[command_length] = input;
            command_length++;
        } else {
            command_length = 0;
            command_buffer[0] = '\0';
            Serial.println("ERR command too long");
        }
    }
}
