#include <unity.h>
#include "motor.h"
#include "sensor.h"
#include "control.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_motor_init(void) {
    motor_init();
    TEST_ASSERT_EQUAL(0, stepper.currentPosition());
}

void test_sensor_init(void) {
    sensor_init();
    TEST_ASSERT_TRUE(scale.is_ready());
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_motor_init);
    RUN_TEST(test_sensor_init);
    UNITY_END();
    return 0;
}