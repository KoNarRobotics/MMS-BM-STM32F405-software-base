#pragma once
#include "encoder_magnetic.hpp"
#include "i2c.hpp"
#include "main.hpp"
#include "main_prog.hpp"
#include "status.hpp"
#include "stmepic.hpp"
#include "uart.hpp"

#include "MT6701.hpp"
#include "uart.hpp"

#include "can_mc_driver.hpp"
#include "mc_firmware/can_base.hpp"
#include "mc_firmware/mc_common.hpp"

uint32_t get_unique_id() {
  uint32_t t1 = HAL_GetUIDw0();
  uint32_t t2 = HAL_GetUIDw1();
  uint32_t t3 = HAL_GetUIDw2();
  return (t1 ^ t2 ^ t3) & 0x1FFFFF; // Return only the lower 21 bits
}

se::SimpleTask task_module_control_loop;

///////////////////////////////////////////////////////////////////////////////
/// PLACE FOR YOUR CUSTOM MODULES INITIALIZATION AND DEFINITIONS

// REPLACE THIS WITH YOUR MODULE include FILE and appropriate type definitions
//
// notice that the only thing that you will require to change in the module
// names in 3 places.
//
// the 'motor_hat' part to your module name
//

#include "motor_hat.hpp"

using ModuleType = mcan::McSlaveDriver<mcan::motor_hat::McCanSlaveInterface_t,
                                       mcan::motor_hat::Hardware_t>;

extern std::shared_ptr<ModuleType> module;

// Don;t forget to implement the write callbacks for your module in the
// module.cpp file
// example callback look like this for the set_motor_position variable in the
// motor_hat module

// void
// mcan::motor_hat::McCanSlaveInterface_t::callback_write_set_motor_position(
// commands::SetMotorPosition &variable) {}

// example for the pid gain p variable in the motor_hat module
// void mcan::motor_hat::McCanSlaveInterface_t::callback_write_pid_gain_p(
//     configs::PidGainP &variable) {}
