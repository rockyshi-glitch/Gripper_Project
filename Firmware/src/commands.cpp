#include "commands.h"

#include <Arduino.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "control.h"
#include "motor.h"
#include "sensor.h"

namespace {
const size_t COMMAND_BUFFER_SIZE = 64;
char command_buffer[COMMAND_BUFFER_SIZE];
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

void print_status() {
    Serial.print("STATUS force=");
    Serial.print(sensor_get_force(), 2);
    Serial.print(" target=");
    Serial.print(control_get_target_force(), 2);
    Serial.print(" position=");
    Serial.print(motor_get_position());
    Serial.print(" open_limit=");
    Serial.print(sensor_is_open_limit() ? 1 : 0);
    Serial.print(" close_limit=");
    Serial.print(sensor_is_close_limit() ? 1 : 0);
    Serial.print(" force_mode=");
    Serial.println(control_is_force_control_enabled() ? 1 : 0);
}

void handle_force_command(const char *argument) {
    if (argument == nullptr || *argument == '\0') {
        Serial.println("ERR FORCE requires a target value in newtons");
        return;
    }

    char *end = nullptr;
    float force = strtof(argument, &end);
    while (end != nullptr && *end != '\0' && isspace(static_cast<unsigned char>(*end))) {
        end++;
    }

    if (end == argument || (end != nullptr && *end != '\0')) {
        Serial.println("ERR invalid FORCE value");
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

void handle_command(char *command) {
    trim_command(command);
    if (command[0] == '\0') {
        return;
    }

    char parsed_command[COMMAND_BUFFER_SIZE];
    strncpy(parsed_command, command, COMMAND_BUFFER_SIZE - 1);
    parsed_command[COMMAND_BUFFER_SIZE - 1] = '\0';
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
        const char *argument = command + 5;
        while (*argument != '\0' && isspace(static_cast<unsigned char>(*argument))) {
            argument++;
        }
        handle_force_command(argument);
    } else {
        Serial.println("ERR unknown command");
    }
}
}

void commands_init() {
    command_length = 0;
    command_buffer[0] = '\0';
    Serial.println("Gripper serial command interface ready");
}

void commands_process() {
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

        if (command_length < COMMAND_BUFFER_SIZE - 1) {
            command_buffer[command_length] = input;
            command_length++;
        } else {
            command_length = 0;
            command_buffer[0] = '\0';
            Serial.println("ERR command too long");
        }
    }
}
