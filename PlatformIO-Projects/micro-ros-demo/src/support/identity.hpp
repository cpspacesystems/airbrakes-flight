#pragma once

#include <Arduino.h>

/**
 * Default device ID is 0.
*/
#ifndef DEVICE_ID
#define DEVICE_ID 0
#endif

/**
 * Teensy A
*/
#if DEVICE_ID == 1
    #define ROLE_EFFECTOR
    #define ID_Serial Serial1
    #define ID_PIN_LED LED_BUILTIN
#endif

/**
 * Teensy B
*/
#if DEVICE_ID == 2
    #define ROLE_SENSOR
    #define ID_Serial Serial2
    #define ID_PIN_LED LED_BUILTIN
#endif

/**
 * Pico A
*/
#if DEVICE_ID == 3
    #define ROLE_EFFECTOR
    #define ID_Serial Serial1
    #define ID_PIN_LED 22

    // UART Serial2(8, 9, NC, NC);
#endif

/**
 * Pico B
*/
#if DEVICE_ID == 4
    #define ROLE_SENSOR
    #define ID_Serial Serial
    #define ID_PIN_LED 22

    // UART Serial2(8, 9, NC, NC);
#endif