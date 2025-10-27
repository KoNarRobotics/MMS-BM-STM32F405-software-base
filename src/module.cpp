
#include "module.hpp"
#include "i2c.hpp"
#include "main.hpp"
#include "main_prog.hpp"
#include "status.hpp"
#include "stmepic.hpp"

se::Status init_board() {
  STMEPIC_ASSING_TO_OR_RETURN(
      i2c,
      se::I2C::Make(hi2c2, pin_i2c_sda, pin_i2c_scl, se::HardwareType::DMA));

  STMEPIC_ASSING_TO_OR_RETURN(uart,
                              se::UART::Make(huart4, se::HardwareType::DMA));

  ////////////////////////////////////////////////////////////////////////////
  /// PLACE FOR YOUR CUSTOM MODULES INITIALIZATION

  return se::Status::OK();
}
