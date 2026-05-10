#include "sensor.h"

HX711 scale;

void sensor_init() {
    scale.begin(HX711_DT_PIN, HX711_SCK_PIN);
    scale.set_scale(2280.f); // 校准因子，需要根据实际调整
    sensor_tare();

    pinMode(LIMIT_SWITCH_OPEN_PIN, INPUT_PULLUP);
    pinMode(LIMIT_SWITCH_CLOSE_PIN, INPUT_PULLUP);
}

void sensor_tare() {
    scale.tare(); // 去皮，后续需要在无负载状态下调用
}

float sensor_get_force() {
    return scale.get_units(10); // 获取平均值
}

bool sensor_is_open_limit() {
    return digitalRead(LIMIT_SWITCH_OPEN_PIN) == LOW;
}

bool sensor_is_close_limit() {
    return digitalRead(LIMIT_SWITCH_CLOSE_PIN) == LOW;
}
