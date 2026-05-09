# Project Overview

This repository contains the development of a force-controlled adaptive electric gripper for collaborative robot end-effectors.

# Project Goals

- Build a functional prototype
- Implement force control
- Support soft gripping
- Use low-cost manufacturable components
- Generate portfolio-quality engineering outputs

# Hardware Platform

- ESP32
- Stepper motor
- HX711 force sensor
- Limit switches

# Software Stack

- PlatformIO
- Modular C++
- PID control
- Serial communication

# Project Structure

01_Requirements/
02_Research/
03_Mechanical/
04_Electronics/
05_Control/
06_Testing/
07_Documents/
08_Portfolio/

# Engineering Targets

- Grip force: 5–40N
- Stroke: 30–50mm
- Repeatability <1mm

# Coding Rules

- Separate motor, sensor and control logic
- Use modular C++ files
- Add comments for all PID parameters
- Keep functions reusable

# Important

Do not overwrite CAD exports.
Do not rename folders automatically.
Always preserve BOM and test data.