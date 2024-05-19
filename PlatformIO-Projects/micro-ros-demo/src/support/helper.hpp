#pragma once

#include <Arduino.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>

#include <support/identity.hpp>  // included so files only need to import helper

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if(temp_rc != RCL_RET_OK){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if(temp_rc != RCL_RET_OK){}}

// Error handle loop
void error_loop() {
  while(1) {
    delay(100);
  }
}