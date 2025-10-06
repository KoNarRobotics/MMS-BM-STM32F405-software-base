#pragma once
#include "can.hpp"
#include "main.hpp"
#include "stmepic.hpp"
#include "version.hpp"

// USB Device includes
#include "modu_card.hpp"

namespace se = stmepic;

extern std::shared_ptr<moducard::ModuCardBoard> modu_card_board;

void config_usb_device();

void main_prog();
