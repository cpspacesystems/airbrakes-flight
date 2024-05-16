#pragma once

#include <support/identity.hpp>

#ifdef ROLE_EFFECTOR
    #define ROLE_NODE_NAME "micro_ros_effector"

    // Nodes to run
    #define LIGHT_SWITCH

    // Role-based constants required by any nodes listed above
    #define LIGHT_SWITCH_SUB_ON_TOPIC_NAME "daytime"
    #define LIGHT_SWITCH_SUB_OFF_TOPIC_NAME "daytime"
    #define LIGHT_SWITCH_LED_PIN ID_PIN_LED
#endif

#ifdef ROLE_SENSOR
    #define ROLE_NODE_NAME "micro_ros_sensor"

    // Nodes to run
    #define DAYLIGHT_SENSOR

    // Role-based constants required by any nodes listed above
    #define DAYLIGHT_SENSOR_TOPIC_NAME "daytime"
#endif


/**
 * Likely there is no need to use this class. Any literals should be defined
 * above using the #define preprocessor directive.
*/
// class Constants {
// public:
//     #ifdef ROLE_EFFECTOR
//     #endif
//     #ifdef ROLE_SENSOR
//     #endif
// };