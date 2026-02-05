#include "version.h"
#include "../duco.h"
#include <vector>


namespace esphome {
namespace duco {

static const char *const TAG = "duco sensor";

void DucoVersion::set_address(uint8_t address) { ESP_LOGD(TAG, "Version: SetAddress %i",address); this->address_ = address; }

void DucoVersion::setup() {}

void DucoVersion::update() {
  DucoMessage message;
  message.function = 0x10;
  message.data = {0x01, address_, 0x00, 0x00, 0x04};
  this->parent_->send(message, this);
}

float DucoVersion::get_setup_priority() const {
  // After DUCO
  return setup_priority::BUS - 2.0f;
}

void DucoVersion::receive_response(const DucoMessage &message) {
  if (message.function == 0x12) {
    // Serial response received, parse it
    uint16_t versionmajor = (message.data[3] << 8) + message.data[2];
    uint8_t versionsub = message.data[4];
    uint8_t versionminor = message.data[5];
    uint8_t versionpatch = message.data[6];
    std::string version;
    // sprintf data to string
    char buf[8];
    sprintf(buf, "%hu.%i.%i.%i", versionmajor, versionsub, versionminor, versionpatch);
    version += buf;

    if (this->parent_->isValidString(version)) {
      ESP_LOGD(TAG, "Node %i Version: %s",address_ ,version.c_str());

      publish_state(version);
    } else {
      ESP_LOGD(TAG, "INVALID DATA Node %i Version: %s",address_ ,version.c_str());
    }

    // do not wait for new messages with the same ID
    this->parent_->stop_waiting(message.id);
  }
}

}  // namespace duco
}  // namespace esphome
