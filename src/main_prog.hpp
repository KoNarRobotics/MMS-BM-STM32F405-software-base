#pragma once
#include "can.hpp"
#include "can2.0.hpp"
#include "gpio.hpp"
#include "i2c.hpp"
#include "main.hpp"
#include "stmepic.hpp"
#include "uart.hpp"
#include "version.hpp"

// USB Device includes
#include "modu_card.hpp"

namespace se = stmepic;

////////////////////////////////////////////////////////////////////////////////
//
//         DO NOT CHANGE THIS FILE UNLESS YOU KNOW WHAT YOU ARE DOING!!!
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// BOARD SETTINGS
extern std::shared_ptr<moducard::ModuCardBoard> modu_card_board;
extern uint32_t CAN_MODULE_BASE_ADDRESS;
////////////////////////////////////////////////////////////////////////////////
// HARDWARE INTERFACES
extern std::shared_ptr<se::I2cBase> i2c;
extern std::shared_ptr<se::UartBase> uart;
extern std::shared_ptr<se::CanBase> can1;
extern std::shared_ptr<se::CanBase> can2;

////////////////////////////////////////////////////////////////////////////////
/// INTERFACES_PINS

extern se::GpioPin pin_uart_rx;
extern se::GpioPin pin_uart_tx;
extern se::GpioPin pin_uart_adr_0;
extern se::GpioPin pin_uart_adr_1;
extern se::GpioPin pin_uart_adr_2;
extern se::GpioPin pin_spi_miso;
extern se::GpioPin pin_spi_mosi;
extern se::GpioPin pin_spi_ck;
extern se::GpioPin pin_spi_adr_0;
extern se::GpioPin pin_spi_adr_1;
extern se::GpioPin pin_spi_adr_2;
extern se::GpioPin pin_i2c_sda;
extern se::GpioPin pin_i2c_scl;
extern se::GpioPin pin_i2c_adr_0;
extern se::GpioPin pin_i2c_adr_1;
extern se::GpioPin pin_i2c_adr_2;

////////////////////////////////////////////////////////////////////////////////
/// ALTMODE PINS

extern se::GpioPin pin_a1_gate_h1;
extern se::GpioPin pin_a2_gate_h2;
extern se::GpioPin pin_a3_gate_h3;
extern se::GpioPin pin_a4_gate_l1;
extern se::GpioPin pin_a5_gate_l2;
extern se::GpioPin pin_a6_gate_l3;
extern se::GpioPin pin_a7_gpio_fault;
extern se::GpioPin pin_a8_current1_adc;
extern se::GpioPin pin_a9_current2_adc;
extern se::GpioPin pin_a10_current3_adc;
extern se::GpioPin pin_a11_adc_1;
extern se::GpioPin pin_a12_voltage1_adc;
extern se::GpioPin pin_a13_voltage2_adc;
extern se::GpioPin pin_a14_voltage3_adc;
extern se::GpioPin pin_a15_temp_adc;
extern se::GpioPin pin_a16_temp_motor_adc;

///////////////////////////////////////////////////////////////////////////////
/// ADDITIONAL PINS

extern se::GpioPin gpio_user_led_1;
extern se::GpioPin gpio_user_led_2;

///////////////////////////////////////////////////////////////////////////////
/// MAIN FUNCTIONS
void config_usb_device();
void main_prog();
se::Status init_board();
