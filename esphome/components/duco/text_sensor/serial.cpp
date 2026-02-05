#include "serial.h"
#include "../duco.h"
#include <vector>

namespace esphome {
namespace duco {

static const char *const TAG = "duco sensor";

void DucoSerial::set_address(uint8_t address) { ESP_LOGD(TAG, "Serial: SetAddress %i",address); this->address_ = address; }

void DucoSerial::setup() {}

void DucoSerial::update() {
  DucoMessage message;
  message.function = 0x10;
  if (address_ == 0x00) { // hardcoded address for box serial
    message.data = {0x01, 0x01, 0x00, 0x1a, 0x10};
  } else {
    message.data = {0x01, address_, 0x00, 0x08, 0x06};
  }
  this->parent_->send(message, this);
}

float DucoSerial::get_setup_priority() const {
  // After DUCO
  return setup_priority::BUS - 2.0f;
}

void DucoSerial::receive_response(const DucoMessage &message) {
  if (message.function == 0x12) {
    // Serial response received, parse it
    auto null_pos = std::find(message.data.begin() + 2, message.data.end(), 0x00);
    std::string serial(message.data.begin() + 2, null_pos);

    if (this->parent_->isValidString(serial)) {
      ESP_LOGD(TAG, "Node %i Serial: %s",address_ ,serial.c_str());
      publish_state(serial);
    } else {
      ESP_LOGD(TAG, "INVALID DATA Node %i Serial: %s",address_ ,serial.c_str());
    }

    // do not wait for new messages with the same ID
    this->parent_->stop_waiting(message.id);
  }
}

}  // namespace duco
}  // namespace esphome
