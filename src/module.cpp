
#include "module.hpp"
#include "i2c.hpp"
#include "main.hpp"
#include "main_prog.hpp"
#include "status.hpp"
#include "stmepic.hpp"

std::shared_ptr<ModuleType> module;

se::Status module_task(se::SimpleTask &, void *args) {
  (void)args;
  module->control_loop();
  return se::Status::OK();
}

se::Status init_board() {
  STMEPIC_ASSING_TO_OR_RETURN(
      i2c,
      se::I2C::Make(hi2c2, pin_i2c_sda, pin_i2c_scl, se::HardwareType::DMA));

  STMEPIC_ASSING_TO_OR_RETURN(uart,
                              se::UART::Make(huart4, se::HardwareType::DMA));

  auto maybe_module = ModuleType::Make(nullptr, get_unique_id());
  if (!maybe_module.ok()) {
    return se::Status::Invalid(maybe_module.status().to_string().c_str());
  }
  module = maybe_module.valueOrDie();

  task_module_control_loop.task_init(module_task, nullptr, 1, nullptr, 1048,
                                     tskIDLE_PRIORITY + 1, "ModuleControlLoop");
  task_module_control_loop.task_run();

  module->start_driver();

  // To access interface variables.
  // module->get_interface()

  ////////////////////////////////////////////////////////////////////////////
  /// PLACE FOR YOUR CUSTOM MODULES INITIALIZATION

  return se::Status::OK();
}
