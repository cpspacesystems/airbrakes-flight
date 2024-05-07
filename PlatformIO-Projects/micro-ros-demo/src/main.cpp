// Main file to configure RCL Executor and run a configured node with attached handlers

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

/**
 * @brief runs once at the start of execution, sets up ROS Client Library and nodes
 */
void setup() {
    rclc_support_t support;
    rcl_allocator_t allocator;
    rcl_node_t node;

    // Configure serial transport
    Serial.begin(115200);
    set_microros_serial_transports(Serial);
    delay(2000);

    // initialize rcl, create init_options
    allocator = rcl_get_default_allocator();
    RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

    // Initialize node
    RCCHECK(rclc_node_init_default(&node, NODE_NAME, "", &support));
    init_all_handlers(support, node);

    // Initialize executor
    RCCHECK(rclc_executor_init(&executor, &support.context, HANDLER_COUNT, &allocator));

    // Attach node ot executor
    attach_all_to_executor(executor);
}

/**
 * @brief runs every tick, spins the executor
 */
void loop() {
    const size_t delta_t = 100;
    delay(delta_t);
    RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(delta_t)));
}