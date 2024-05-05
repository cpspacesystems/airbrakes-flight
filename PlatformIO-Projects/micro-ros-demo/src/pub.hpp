#pragma once

#include <Arduino.h>
#include <micro_ros_platformio.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/int32.h>

#include <helper.hpp>


namespace pub
{

rcl_publisher_t publisher;
std_msgs__msg__Int32 msg;
rcl_timer_t timer;


/** Funciton Prototypes */
void timer_callback(rcl_timer_t *, int64_t);

/**
 * @brief Sets up all the data necessary for a node to run
 * 
 * @param support ros client library support structure
 */
void init_node(rclc_support_t &support) {
    // create node
    rcl_node_t node;
    RCCHECK(rclc_node_init_default(&node, "micro_ros_platformio_node", "", &support));

    // create publisher
    RCCHECK(rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "counter_topic"));

    // create timer to trigger publisher
    const unsigned int timer_timeout = 1000;
    RCCHECK(rclc_timer_init_default(
        &timer,
        &support,
        RCL_MS_TO_NS(timer_timeout),
        timer_callback));

    // Configure local information
    pinMode(LED_BUILTIN, OUTPUT);
    msg.data = 0;
}

/**
 * @brief Attaches our node to the executor through a timer so it will run
 * 
 * @param executor ros executor structure with executor info
 */
void attach_to_executor(rclc_executor_t &executor) {
    RCCHECK(rclc_executor_add_timer(&executor, &timer));
}

/**
 * @brief Called at a set interval, publishes a message every tick
 * 
 * @param timer ros2 timer object
 * @param last_call_time the last time this function was called
 */
void timer_callback(rcl_timer_t *timer, int64_t last_call_time) {
    RCLC_UNUSED(last_call_time);
    if (timer != NULL) {
        RCSOFTCHECK(rcl_publish(&publisher, &msg, NULL));
        // change LED state to show publishing
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        msg.data++;
    }
}
}