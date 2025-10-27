#include "main_prog.hpp"
#include "Timing.hpp"
#include "atmodem.hpp"
#include "can2.0.hpp"
#include "can_messages.h"
#include "i2c.hpp"
#include "logger.hpp"
#include "main.hpp"
#include "modu_card.hpp"
#include "random_number_generator.hpp"
#include "sha256.hpp"
#include "simple_task.hpp"
#include "uart.hpp"
#include "usbd_cdc_if.h"

////////////////////////////////////////////////////////////////////////////////
//
//         DO NOT CHANGE THIS FILE UNLESS YOU KNOW WHAT YOU ARE DOING!!!
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// BOARD SETTINGS
std::shared_ptr<moducard::ModuCardBoard> modu_card_board;

////////////////////////////////////////////////////////////////////////////////
// HARDWARE INTERFACES
std::shared_ptr<se::I2cBase> i2c = nullptr;
std::shared_ptr<se::UartBase> uart = nullptr;
std::shared_ptr<se::CanBase> can1 = nullptr;
std::shared_ptr<se::CanBase> can2 = nullptr;

////////////////////////////////////////////////////////////////////////////////
/// INTERFACES_PINS

se::GpioPin pin_uart_rx(*GPIOC, GPIO_PIN_11);
se::GpioPin pin_uart_tx(*GPIOC, GPIO_PIN_10);

se::GpioPin pin_uart_adr_0(*GPIOA, GPIO_PIN_6);
se::GpioPin pin_uart_adr_1(*GPIOA, GPIO_PIN_7);
se::GpioPin pin_uart_adr_2(*GPIOA, GPIO_PIN_5);

se::GpioPin pin_spi_miso(*GPIOB, GPIO_PIN_4);
se::GpioPin pin_spi_mosi(*GPIOC, GPIO_PIN_13);
se::GpioPin pin_spi_ck(*GPIOB, GPIO_PIN_3);

se::GpioPin pin_spi_adr_0(*GPIOC, GPIO_PIN_6);
se::GpioPin pin_spi_adr_1(*GPIOC, GPIO_PIN_7);
se::GpioPin pin_spi_adr_2(*GPIOC, GPIO_PIN_8);

se::GpioPin pin_i2c_sda(*GPIOB, GPIO_PIN_11);
se::GpioPin pin_i2c_scl(*GPIOB, GPIO_PIN_10);

se::GpioPin pin_i2c_adr_0(*GPIOA, GPIO_PIN_15);
se::GpioPin pin_i2c_adr_1(*GPIOB, GPIO_PIN_5);
se::GpioPin pin_i2c_adr_2(*GPIOC, GPIO_PIN_9);

////////////////////////////////////////////////////////////////////////////////
/// ALTMODE PINS

se::GpioPin pin_gate_h1(*GATE_H1_GPIO_Port, GATE_H1_Pin);
se::GpioPin pin_gate_h2(*GATE_H2_GPIO_Port, GATE_H2_Pin);
se::GpioPin pin_gate_h3(*GATE_H3_GPIO_Port, GATE_H3_Pin);
se::GpioPin pin_gate_l1(*GATE_L1_GPIO_Port, GATE_L1_Pin);
se::GpioPin pin_gate_l2(*GATE_L2_GPIO_Port, GATE_L2_Pin);
se::GpioPin pin_gate_l3(*GATE_L3_GPIO_Port, GATE_L3_Pin);
se::GpioPin pin_gpio_fault(*GPIO_FAULT_GPIO_Port, GPIO_FAULT_Pin);
se::GpioPin pin_current1_adc(*ADC_CURRENT_1_GPIO_Port, ADC_CURRENT_1_Pin);
se::GpioPin pin_current2_adc(*ADC_CURRENT_2_GPIO_Port, ADC_CURRENT_2_Pin);
se::GpioPin pin_current3_adc(*ADC_CURRENT_3_GPIO_Port, ADC_CURRENT_3_Pin);
se::GpioPin pin_adc_1(*ADC_1_GPIO_Port, ADC_1_Pin);
se::GpioPin pin_voltage1_adc(*VOLTAGE_1_GPIO_Port, VOLTAGE_1_Pin);
se::GpioPin pin_voltage2_adc(*VOLTAGE_2_GPIO_Port, VOLTAGE_2_Pin);
se::GpioPin pin_voltage3_adc(*VOLTAGE_3_GPIO_Port, VOLTAGE_3_Pin);
se::GpioPin pin_temp_adc(*ADC_TEMP_GPIO_Port, ADC_TEMP_Pin);
se::GpioPin pin_temp_motor_adc(*ADC_TEMPMOTOR_GPIO_Port, ADC_TEMPMOTOR_Pin);

///////////////////////////////////////////////////////////////////////////////
/// ADDITIONAL PINS

se::GpioPin gpio_user_led_1(*GPIO_LED_1_GPIO_Port, GPIO_LED_1_Pin);
se::GpioPin gpio_user_led_2(*GPIO_LED_2_GPIO_Port, GPIO_LED_2_Pin);

////////////////////////////////////////////////////////////////////////////////
// REST OF THE CODE

extern "C" {
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM6) {
    se::Ticker::get_instance().irq_update_ticker();
    HAL_IncTick();
  }

  if (htim->Instance == TIM7) {
    HAL_IncTick();
  }
}
}

void main_prog() {
  // START ALL INTERRUPTS
  HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
  HAL_TIM_Base_Start_IT(&htim6);

  // INIT USB CO< port
  // MX_USB_PCD_Init();
  // MX_USB_Device_Init();

  // INIT LOGGER
  std::string version = std::to_string(VERSION_MAJOR) + "." +
                        std::to_string(VERSION_MINOR) + "." +
                        std::to_string(VERSION_BUILD);
  se::Logger::get_instance().init(se::LOG_LEVEL::LOG_LEVEL_DEBUG, true, nullptr,
                                  false, version);

  // stmepic::algorithm::SHA256::get_instance().init(hhash);
  // stmepic::algorithm::RandomNumberGenerator::get_instance().init(hrng);

  // INIT UART HANDLERS
  // STMEPIC_ASSING_TO_OR_HRESET(uart5,
  //                             se::UART::Make(huart5, se::HardwareType::DMA));
  // STMEPIC_NONE_OR_HRESET(uart5->hardware_start());

  ////////////////////////////////////////////////////////////////////////////////
  // INIT CAN HANDLER

  // YOU CAN MODIFY THE FILTERS HERE if needed
  CAN_FilterTypeDef can_filter1;
  can_filter1.FilterBank = 1;
  can_filter1.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  can_filter1.FilterActivation = CAN_FILTER_ENABLE;
  can_filter1.FilterMode = CAN_FILTERMODE_IDMASK;
  can_filter1.FilterScale = CAN_FILTERSCALE_16BIT;
  can_filter1.FilterIdHigh = 0;
  can_filter1.FilterIdLow = 0;
  can_filter1.FilterMaskIdHigh = 0;
  can_filter1.FilterMaskIdLow = 0;
  can_filter1.SlaveStartFilterBank = 0;
  STMEPIC_ASSING_TO_OR_HRESET(
      can1, se::CAN::Make(hcan1, can_filter1, nullptr, nullptr));

  CAN_FilterTypeDef can_filter2;
  can_filter2.FilterBank = 2;
  can_filter2.FilterFIFOAssignment = CAN_FILTER_FIFO1;
  can_filter2.FilterActivation = CAN_FILTER_ENABLE;
  can_filter2.FilterMode = CAN_FILTERMODE_IDMASK;
  can_filter2.FilterScale = CAN_FILTERSCALE_16BIT;
  can_filter2.FilterIdHigh = 0;
  can_filter2.FilterIdLow = 0;
  can_filter2.FilterMaskIdHigh = 0;
  can_filter2.FilterMaskIdLow = 0;
  can_filter2.SlaveStartFilterBank = 0;

  STMEPIC_ASSING_TO_OR_HRESET(
      can2, se::CAN::Make(hcan2, can_filter2, nullptr, nullptr));

  STMEPIC_NONE_OR_HRESET(can1->hardware_start());
  STMEPIC_NONE_OR_HRESET(can2->hardware_start());

  STMEPIC_ASSING_TO_OR_HRESET(
      modu_card_board,
      moducard::ModuCardBoard::Make(CAN_MODULE_BASE_ADDRESS, gpio_user_led_1,
                                    can1, can2, init_board));
  STMEPIC_NONE_OR_HRESET(modu_card_board->device_start());
}