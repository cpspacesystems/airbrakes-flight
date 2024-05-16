#pragma once

#include <micro_ros_platformio.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>

#include <support/constants.hpp>

// Import all your c++ files here
#include <nodes/light_switch.hpp>

// Put the handler counts for all your nodes here
const size_t HANDLER_COUNT = 
    light_switch::HANDLER_COUNT;

/**
 * @brief Put the initializers for all your nodes here
 * 
 * @param support support struct to be passed to initializers
 */
void init_all_handlers(rclc_support_t &support, rcl_node_t &node) {
    light_switch::init_handlers(support, node);
}

/**
 * @brief Put the executor attachers for all your nodes here
 * 
 * @param executor executor struct to be passed to executors
 */
void attach_all_to_executor(rclc_executor_t &executor) {
    light_switch::attach_to_executor(executor);
}