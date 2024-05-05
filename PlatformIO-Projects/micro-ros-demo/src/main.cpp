#include <Arduino.h>
#include <micro_ros_platformio.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <helper.hpp>
#include <config.hpp>

#if !defined(MICRO_ROS_TRANSPORT_ARDUINO_SERIAL)
#error This code is only avaliable for Arduino framework with serial transport.
#endif

rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;

/**
 * @brief runs once at the start of execution, sets up ROS Client Library and nodes
 */
void setup() {
    // Configure serial transport
    Serial.begin(115200);
    set_microros_serial_transports(Serial);
    delay(2000);

    // initialize rcl, create init_options
    allocator = rcl_get_default_allocator();
    RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

    // Initialize node
    init_all_nodes(support);

    // Initialize executor
    RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));

    // Attach node ot executor
    attach_all_to_executor(executor);
}

/**
 * @brief runs every tick, spins the executor
 */
void loop() {
    delay(100);
    RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
}