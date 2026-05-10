# ESP32 Gripper Control Firmware

This is a PlatformIO project for controlling a gripper using ESP32 microcontroller.

## Features

- **Motor Module**: Controls stepper motor for gripper movement
- **Sensor Module**: Reads force from HX711 load cell and limit switches
- **Control Module**: Manages gripper operations with PID force control interface
- **Serial Command Module**: Parses non-blocking serial commands for manual control and diagnostics

## Hardware Requirements

- ESP32 development board
- Stepper motor with driver (e.g., A4988)
- HX711 load cell amplifier
- Limit switches for open/close positions

## Pin Configuration

- Motor: STEP=18, DIR=19, EN=21
- HX711: DT=4, SCK=5
- Limit Switches: Open=12, Close=13

## Building and Uploading

1. Install PlatformIO
2. Open project in VS Code with PlatformIO extension
3. Build: `pio run`
4. Upload: `pio run --target upload`

## Usage

The main loop handles non-blocking serial commands, motor control, and sensor reading.

## Serial Commands

Send commands over the serial monitor at 115200 baud. Commands are line-based and should end with a newline.

- `OPEN`: move the gripper in the open direction
- `CLOSE`: move the gripper in the close direction
- `STOP`: stop motion and exit force-control mode
- `STATUS`: print motor position, force sensor value, limit switch states, speed, target force, and force-control mode
- `TARE`: tare the HX711 force sensor
- `FORCE <newtons>`: set the target gripping force and enter force-control mode
- `SPEED <steps_per_second>`: set the gripper motion speed

## PID Force Control

PID parameters are predefined in `control.h`. The `FORCE <newtons>` command updates the force target and leaves the control loop ready for PID expansion.
