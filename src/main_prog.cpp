#include "main_prog.hpp"
#include "Timing.hpp"
#include "atmodem.hpp"
#include "can2.0.hpp"
#include "can_messages.h"
#include "logger.hpp"
#include "main.hpp"
#include "modu_card.hpp"
#include "random_number_generator.hpp"
#include "sha256.hpp"
#include "simple_task.hpp"
#include "uart.hpp"
#include "usbd_cdc_if.h"

////////////////////////////////////////////////////////////////////////////////
// Board settings
std::shared_ptr<moducard::ModuCardBoard> modu_card_board;
static constexpr uint32_t CAN_MODULE_BASE_ADDRESS = 0x300;

////////////////////////////////////////////////////////////////////////////////
// HARDWARE INTERFACES

// base hardware interfaces DON'T TOUCH
// std::shared_ptr<se::UART> uart5 = nullptr;
std::shared_ptr<se::CAN> can1 = nullptr;
std::shared_ptr<se::CAN> can2 = nullptr;

// se::GpioPin gpio_boot_enable(*BOOT_EN_GPIO_Port, BOOT_EN_Pin);
se::GpioPin gpio_user_led_1(*GPIO_LED_1_GPIO_Port, GPIO_LED_1_Pin);
se::GpioPin gpio_user_led_2(*GPIO_LED_2_GPIO_Port, GPIO_LED_2_Pin);
// se::GpioPin gpio_status_led(*STATUS_LED_GPIO_Port, STATUS_LED_Pin);
// se::GpioPin gpio_usr_button(*USR_BUTTON_GPIO_Port, USR_BUTTON_Pin);

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

Status init_board() {
  gpio_user_led_1.write(0);
  // gpio_user_led_2.write(0);

  ///////////////////////////////////////////////////////////////////////////
  // HERE ADD MORE OF YOUR INIT CODE

  ///////////////////////////////////////////////////////////////////////////
  return Status::OK();
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
  // INIT FDCAN HANDLER

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

  STMEPIC_NONE_OR_HRESET(can1->hardware_start());
  STMEPIC_NONE_OR_HRESET(can2->hardware_start());

  STMEPIC_ASSING_TO_OR_HRESET(
      modu_card_board,
      moducard::ModuCardBoard::Make(CAN_MODULE_BASE_ADDRESS, gpio_user_led_1,
                                    can1, can2, init_board));
  STMEPIC_NONE_OR_HRESET(modu_card_board->device_start());
}