#ifndef SENSOR_H
#define SENSOR_H

#include <HX711.h>

// HX711引脚定义
#define HX711_DT_PIN 4
#define HX711_SCK_PIN 5

// 限位开关引脚定义
#define LIMIT_SWITCH_OPEN_PIN 12
#define LIMIT_SWITCH_CLOSE_PIN 13

extern HX711 scale;

void sensor_init();
float sensor_get_force();
bool sensor_is_open_limit();
bool sensor_is_close_limit();

#endif