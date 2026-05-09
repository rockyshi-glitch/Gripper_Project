#include <Arduino.h>

#define STEPPER_PIN_1 21
#define STEPPER_PIN_2 22
#define STEPPER_PIN_3 19
#define STEPPER_PIN_4 18

const int stepDelay = 2; // ms between steps
const int stepsPerRevolution = 4096; // 28BYJ-48 common value

int stepIndex = 0;

const int stepSequence[8][4] = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

void setStepperPins(int a, int b, int c, int d) {
  digitalWrite(STEPPER_PIN_1, a);
  digitalWrite(STEPPER_PIN_2, b);
  digitalWrite(STEPPER_PIN_3, c);
  digitalWrite(STEPPER_PIN_4, d);
}

void stepMotor(int step) {
  stepIndex = (stepIndex + step + 8) % 8;
  setStepperPins(
    stepSequence[stepIndex][0],
    stepSequence[stepIndex][1],
    stepSequence[stepIndex][2],
    stepSequence[stepIndex][3]
  );
}

void stepSteps(int steps, int direction) {
  for (int i = 0; i < abs(steps); i++) {
    stepMotor(direction);
    delay(stepDelay);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);
  setStepperPins(0, 0, 0, 0);

  Serial.println("ESP32 Stepper Motor Control Startup");
}

void loop() {
  Serial.println("Rotate clockwise one revolution...");
  stepSteps(stepsPerRevolution, 1);
  delay(1000);

  Serial.println("Rotate counterclockwise one revolution...");
  stepSteps(stepsPerRevolution, -1);
  delay(1000);
}
