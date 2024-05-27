#pragma once

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <sensor_msgs/msg/nav_sat_fix.h>

#include <support/helper.hpp>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"

#define SEALEVELPRESSURE_HPA (1013.25)
#define ALTIMETER_TOPIC_NAME "altimeter"
#define ALTIMETER_0_WIRE Wire 
#define ALTIMETER_0_ADDR 0x76
#define ALTIMETER_1_WIRE Wire
#define ALTIMETER_1_ADDR 0x77
#define ALTIMETER_UPDATE_MS 50

class Altimeter {
    private: 
    uint8_t id;
    Adafruit_BMP3XX bmp;

    rcl_publisher_t publisher;
    sensor_msgs__msg__NavSatFix altitude_msg;

    public:
    Altimeter(uint8_t id, TwoWire &wire, uint8_t slave_addr) {
        // Initialize altimeter on I2C
        this->bmp.begin_I2C(slave_addr, &wire);
        this->id = id;

        // Set up oversampling and filter initialization
        bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
        bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
        bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
        bmp.setOutputDataRate(BMP3_ODR_50_HZ);
    }

    rcl_ret_t measure() {
        altitude_msg.altitude = bmp.readAltitude(SEALEVELPRESSURE_HPA);

        return rcl_publish(&publisher, &altitude_msg, nullptr);
    }

    void init_handlers(rclc_support_t &support, rcl_node_t &node) {
        // create publisher
        RCCHECK(rclc_publisher_init_default(
            &publisher,
            &node,
            ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, NavSatFix),
            (ALTIMETER_TOPIC_NAME + String(this->id) + "/raw").c_str()));
    }
};

namespace altimeter {
    const size_t HANDLER_COUNT = 1;

    rcl_timer_t timer; 

    Altimeter altimeter0(0, ALTIMETER_0_WIRE, ALTIMETER_0_ADDR);
    Altimeter altimeter1(1, ALTIMETER_1_WIRE, ALTIMETER_1_ADDR);

    void timer_callback(rcl_timer_t *timer, int64_t last_call_time) {
        RCLC_UNUSED(last_call_time);
        if (timer != NULL) {
            altimeter0.measure();
            altimeter1.measure();
        }
    }

    /**
     * @brief Sets up all the data necessary for a node to run
     * 
     * @param support ros client library support structure
     */
    void init_handlers(rclc_support_t &support, rcl_node_t &node) {
        altimeter0.init_handlers(support, node);
        altimeter1.init_handlers(support, node);

        // Create timer
        const unsigned int delta_t = ALTIMETER_UPDATE_MS;
        RCCHECK(rclc_timer_init_default(
            &timer,
            &support,
            RCL_MS_TO_NS(delta_t),
            timer_callback));
    }

    /**
     * @brief Attaches our handlers to the executor, like our timer
     * 
     * @param executor ros executor structure with executor info
     */
    void attach_to_executor(rclc_executor_t &executor) {
        RCCHECK(rclc_executor_add_timer(&executor, &timer));
    }
}
