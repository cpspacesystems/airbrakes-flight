// This file is written a little weird because it is a config file, but
// if you follow the format, add a #ifdef for each of your build configurations,
// and put your functions in the right place, then it should all work!
#pragma once

// default imports
#include <micro_ros_platformio.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>

// Import all your c++ files here
#include <handlers/daylight_sensor.hpp>
#include <handlers/light_switch.hpp>
#include <handlers/imu.hpp>
#include <handlers/gps.hpp>
#include <handlers/altimeter.hpp>
#include <handlers/imuextra.hpp>

// Choose your node names here
#if defined(ROLE_SENSOR)
    #define ROLE_NODE_NAME "micro_ros_sensor"
#elif defined(ROLE_EFFECTOR)
    #define ROLE_NODE_NAME "micro_ros_effector"
#endif


// Put the handler counts for all your nodes here
const size_t HANDLER_COUNT = (
    #ifdef ROLE_SENSOR
    // daylight_sensor::HANDLER_COUNT + 
    // imu::HANDLER_COUNT +
    // gps::HANDLER_COUNT + 
    altimeter::HANDLER_COUNT +
    imuextra::HANDLER_COUNT +
    #endif
    #ifdef ROLE_EFFECTOR
    // light_switch::HANDLER_COUNT + 
    #endif
0);

/**
 * @brief Put the initializers for all your nodes here
 * 
 * @param support support struct to be passed to initializers
 */
void init_all_handlers(rclc_support_t &support, rcl_node_t &node) {
    #ifdef ROLE_SENSOR  // put all sensor initializers here
        // daylight_sensor::init_handlers(support, node);
        // imu::init_handlers(support, node);
        // gps::init_handlers(support, node);
        altimeter::init_handlers(support, node);
        imuextra::init_handlers(support, node);
    #endif
    #ifdef ROLE_EFFECTOR  // put all sensor initializers here
        // light_switch::init_handlers(support, node);
    #endif
}

/**
 * @brief Put the executor attachers for all your nodes here
 * 
 * @param executor executor struct to be passed to executors
 */
void attach_all_to_executor(rclc_executor_t &executor) {
    #ifdef ROLE_SENSOR  // put all sensor attachers here
        // daylight_sensor::attach_to_executor(executor);
        // imu::attach_to_executor(executor);
        // gps::attach_to_executor(executor);
        altimeter::attach_to_executor(executor);
        imuextra::attach_to_executor(executor);
    #endif
    #ifdef ROLE_EFFECTOR  // putt all effector attachers here
        // light_switch::attach_to_executor(executor);
    #endif
}