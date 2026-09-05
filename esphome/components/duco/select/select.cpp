#include "select.h"
#include "../duco.h"
#include <vector>

namespace esphome {
namespace duco {

static const char *const TAG = "duco select";

const std::string DucoSelect::MODE_AUTO = "AUTO";
const std::string DucoSelect::MODE_MAN1 = "MAN1";
const std::string DucoSelect::MODE_MAN2 = "MAN2";
const std::string DucoSelect::MODE_MAN3 = "MAN3";
const std::string DucoSelect::MODE_EMPT = "EMPT";
const std::string DucoSelect::MODE_CNT1 = "CNT1";
const std::string DucoSelect::MODE_CNT2 = "CNT2";
const std::string DucoSelect::MODE_CNT3 = "CNT3";
const std::string DucoSelect::MODE_MAN1X2 = "MAN1x2";
const std::string DucoSelect::MODE_MAN2X2 = "MAN2x2";
const std::string DucoSelect::MODE_MAN3X2 = "MAN3x2";
const std::string DucoSelect::MODE_MAN1X3 = "MAN1x3";
const std::string DucoSelect::MODE_MAN2X3 = "MAN2x3";
const std::string DucoSelect::MODE_MAN3X3 = "MAN3x3";

const std::string DucoBypassControl::BYPASS_AUTO = "AUTO";
const std::string DucoBypassControl::BYPASS_OPEN = "OPEN";
const std::string DucoBypassControl::BYPASS_CLOSED = "CLOSED";

const std::string DucoBypassAdaptiveControl::BYPASS_ADAPTIVE_ON = "ON";
const std::string DucoBypassAdaptiveControl::BYPASS_ADAPTIVE_OFF = "OFF";

const std::string DucoHeaterMode::HEATER_ON  = "ON";
const std::string DucoHeaterMode::HEATER_OFF  = "OFF";

const std::string DucoPassiveCooling::PASSIVE_COOLING_ON = "ON";
const std::string DucoPassiveCooling::PASSIVE_COOLING_OFF = "ON";

const uint8_t DucoSelect::MODE_CODE_AUTO = 0x00;
const uint8_t DucoSelect::MODE_CODE_MAN1 = 0x04;
const uint8_t DucoSelect::MODE_CODE_MAN2 = 0x05;
const uint8_t DucoSelect::MODE_CODE_MAN3 = 0x06;
const uint8_t DucoSelect::MODE_CODE_EMPT = 0x07;
const uint8_t DucoSelect::MODE_CODE_CNT1 = 0x08;
const uint8_t DucoSelect::MODE_CODE_CNT2 = 0x09;
const uint8_t DucoSelect::MODE_CODE_CNT3 = 0x0a;
const uint8_t DucoSelect::MODE_CODE_MAN1X2 = 0x84;
const uint8_t DucoSelect::MODE_CODE_MAN2X2 = 0x85;
const uint8_t DucoSelect::MODE_CODE_MAN3X2 = 0x86;
const uint8_t DucoSelect::MODE_CODE_MAN1X3 = 0xc4;
const uint8_t DucoSelect::MODE_CODE_MAN2X3 = 0xc5;
const uint8_t DucoSelect::MODE_CODE_MAN3X3 = 0xc6;

const uint8_t DucoBypassControl::BYPASS_CODE_AUTO = 0x00;
const uint8_t DucoBypassControl::BYPASS_CODE_OPEN = 0x02;
const uint8_t DucoBypassControl::BYPASS_CODE_CLOSED = 0x01;

const uint8_t DucoBypassAdaptiveControl::BYPASS_ADAPTIVE_CODE_ON = 0x01;
const uint8_t DucoBypassAdaptiveControl::BYPASS_ADAPTIVE_CODE_OFF = 0x00;

const uint8_t DucoHeaterMode::HEATER_CODE_ON = 0x01;
const uint8_t DucoHeaterMode::HEATER_CODE_OFF = 0x00;

const uint8_t DucoPassiveCooling::PASSIVE_COOLING_CODE_ON = 0x00;
const uint8_t DucoPassiveCooling::PASSIVE_COOLING_CODE_OFF = 0x01;


std::string code_to_string(uint8_t mode) {
  switch (mode) {
    case 0x00:  // Both BYPASS_CODE_AUTO and MODE_CODE_AUTO are 0x00
      return DucoSelect::MODE_AUTO;
    case DucoSelect::MODE_CODE_MAN1:
      return DucoSelect::MODE_MAN1;
    case DucoSelect::MODE_CODE_MAN2:
      return DucoSelect::MODE_MAN2;
    case DucoSelect::MODE_CODE_MAN3:
      return DucoSelect::MODE_MAN3;
    case DucoSelect::MODE_CODE_EMPT:
      return DucoSelect::MODE_EMPT;
    case DucoSelect::MODE_CODE_CNT1:
      return DucoSelect::MODE_CNT1;
    case DucoSelect::MODE_CODE_CNT2:
      return DucoSelect::MODE_CNT2;
    case DucoSelect::MODE_CODE_CNT3:
      return DucoSelect::MODE_CNT3;
    case DucoSelect::MODE_CODE_MAN1X2:
      return DucoSelect::MODE_MAN1X2;
    case DucoSelect::MODE_CODE_MAN2X2:
      return DucoSelect::MODE_MAN2X2;
    case DucoSelect::MODE_CODE_MAN3X2:
      return DucoSelect::MODE_MAN3X2;
    case DucoSelect::MODE_CODE_MAN1X3:
      return DucoSelect::MODE_MAN1X3;
    case DucoSelect::MODE_CODE_MAN2X3:
      return DucoSelect::MODE_MAN2X3;
    case DucoSelect::MODE_CODE_MAN3X3:
      return DucoSelect::MODE_MAN3X3;
    default:
      return DucoSelect::MODE_AUTO;
  }
  return DucoSelect::MODE_AUTO;
}

uint8_t string_to_code(const std::string &mode) {
  if (mode == DucoSelect::MODE_MAN1) {
    return DucoSelect::MODE_CODE_MAN1;
  }
  if (mode == DucoSelect::MODE_MAN2) {
    return DucoSelect::MODE_CODE_MAN2;
  }
  if (mode == DucoSelect::MODE_MAN3) {
    return DucoSelect::MODE_CODE_MAN3;
  }
  if (mode == DucoSelect::MODE_EMPT) {
    return DucoSelect::MODE_CODE_EMPT;
  }
  if (mode == DucoSelect::MODE_CNT1) {
    return DucoSelect::MODE_CODE_CNT1;
  }
  if (mode == DucoSelect::MODE_CNT2) {
    return DucoSelect::MODE_CODE_CNT2;
  }
  if (mode == DucoSelect::MODE_CNT3) {
    return DucoSelect::MODE_CODE_CNT3;
  }
  if (mode == DucoSelect::MODE_MAN1X2) {
    return DucoSelect::MODE_CODE_MAN1X2;
  }
  if (mode == DucoSelect::MODE_MAN2X2) {
    return DucoSelect::MODE_CODE_MAN2X2;
  }
  if (mode == DucoSelect::MODE_MAN3X2) {
    return DucoSelect::MODE_CODE_MAN3X2;
  }
  if (mode == DucoSelect::MODE_MAN1X3) {
    return DucoSelect::MODE_CODE_MAN1X3;
  }
  if (mode == DucoSelect::MODE_MAN2X3) {
    return DucoSelect::MODE_CODE_MAN2X3;
  }
  if (mode == DucoSelect::MODE_MAN3X3) {
    return DucoSelect::MODE_CODE_MAN3X3;
  }
  if (mode == DucoSelect::MODE_AUTO) {
    return DucoSelect::MODE_CODE_AUTO;
  }
  return DucoSelect::MODE_CODE_AUTO;
}

std::string code_to_string_bypass(uint8_t mode) {
  switch (mode) {
    case DucoBypassControl::BYPASS_CODE_AUTO:  // Both BYPASS_CODE_AUTO and MODE_CODE_AUTO are 0x00
      return DucoBypassControl::BYPASS_AUTO;
    case DucoBypassControl::BYPASS_CODE_OPEN:
      return DucoBypassControl::BYPASS_OPEN;
    case DucoBypassControl::BYPASS_CODE_CLOSED:
      return DucoBypassControl::BYPASS_CLOSED;
    default:
      return DucoBypassControl::BYPASS_AUTO;
  }
  return DucoBypassControl::BYPASS_AUTO;
}

uint8_t string_to_code_bypass(const std::string &mode) {
  if (mode == DucoBypassControl::BYPASS_AUTO) {
    return DucoBypassControl::BYPASS_CODE_AUTO;
  }
  if (mode == DucoBypassControl::BYPASS_OPEN) {
    return DucoBypassControl::BYPASS_CODE_OPEN;
  }
  if (mode == DucoBypassControl::BYPASS_CLOSED) {
    return DucoBypassControl::BYPASS_CODE_CLOSED;
  }
  return DucoBypassControl::BYPASS_CODE_AUTO;
}

std::string code_to_string_bypass_adaptive(uint8_t mode) {
  switch (mode) {
    case DucoBypassAdaptiveControl::BYPASS_ADAPTIVE_CODE_ON:
      return DucoBypassAdaptiveControl::BYPASS_ADAPTIVE_ON;
    case DucoBypassAdaptiveControl::BYPASS_ADAPTIVE_CODE_OFF:
      return DucoBypassAdaptiveControl::BYPASS_ADAPTIVE_OFF;
    default:
      return DucoBypassAdaptiveControl::BYPASS_ADAPTIVE_ON;
  }
  return DucoBypassAdaptiveControl::BYPASS_ADAPTIVE_OFF;
}

uint8_t string_to_code_bypass_adaptive(const std::string &mode) {
  if (mode == DucoBypassAdaptiveControl::BYPASS_ADAPTIVE_ON) {
    return DucoBypassAdaptiveControl::BYPASS_ADAPTIVE_CODE_ON;
  }
  if (mode == DucoBypassAdaptiveControl::BYPASS_ADAPTIVE_OFF) {
    return DucoBypassAdaptiveControl::BYPASS_ADAPTIVE_CODE_OFF;
  }
  return DucoBypassAdaptiveControl::BYPASS_ADAPTIVE_CODE_ON;
}

std::string code_to_string_heater(uint8_t mode) {
  switch (mode) {
    case DucoHeaterMode::HEATER_CODE_ON:
      return DucoHeaterMode::HEATER_ON;
    case DucoHeaterMode::HEATER_CODE_OFF:
      return DucoHeaterMode::HEATER_OFF;
    default:
      return DucoHeaterMode::HEATER_OFF;
  }
  return DucoHeaterMode::HEATER_OFF;
}

uint8_t string_to_code_heater(const std::string &mode) {
  if (mode == DucoHeaterMode::HEATER_ON) {
    return DucoBypassAdaptiveControl::BYPASS_ADAPTIVE_CODE_ON;
  }
  if (mode == DucoHeaterMode::HEATER_OFF) {
    return DucoHeaterMode::HEATER_CODE_OFF;
  }
  return DucoHeaterMode::HEATER_CODE_OFF;
}


std::string code_to_string_passive_cooling(uint8_t mode) {
  switch (mode) {
    case DucoPassiveCooling::PASSIVE_COOLING_CODE_ON:
      return DucoPassiveCooling::PASSIVE_COOLING_ON;
    case DucoPassiveCooling::PASSIVE_COOLING_CODE_OFF:
      return DucoPassiveCooling::PASSIVE_COOLING_OFF;
    default:
      return DucoPassiveCooling::PASSIVE_COOLING_OFF;
  }
  return DucoPassiveCooling::PASSIVE_COOLING_OFF;
}

uint8_t string_to_code_passive_cooling(const std::string &mode) {
  if (mode == DucoPassiveCooling::PASSIVE_COOLING_ON) {
    return DucoPassiveCooling::PASSIVE_COOLING_CODE_ON;
  }
  if (mode == DucoPassiveCooling::PASSIVE_COOLING_OFF) {
    return DucoPassiveCooling::PASSIVE_COOLING_CODE_OFF;
  }
  return DucoPassiveCooling::PASSIVE_COOLING_CODE_OFF;
}


void DucoSelect::set_address(uint8_t address) { ESP_LOGD(TAG, "DucoSelect: SetAddress %i",address); this->address_ = address; }

void DucoSelect::setup() {
  ESP_LOGD(TAG, "DucoSelect: setup!");
}

void DucoSelect::update() {
  DucoMessage message;
  message.function = 0x0c;
  message.data = {0x02, address_};
  this->parent_->send(message, this);
}

float DucoSelect::get_setup_priority() const {
  // After DUCO
  return setup_priority::BUS - 2.0f;
}

void DucoSelect::receive_response(const DucoMessage &message) {
  if (message.function == 0x0e && message.data[0] != 0x01) {
    // mode response received, parse it
    auto mode = code_to_string(message.data[0]);

    publish_state(mode);

    ESP_LOGD(TAG, "DucoSelect::Current mode: %s", mode.c_str());

    // do not wait for new messages with the same ID
    this->parent_->stop_waiting(message.id);
  }
  if (message.function == 0x0e && message.data[0] == 0x01) {
    this->parent_->stop_waiting(message.id);
  }
}

void DucoSelect::control(const std::string &value) {
  DucoMessage message;
  message.function = 0x0c;
  message.data = {0x04, address_, string_to_code(value)};
  this->parent_->send(message, this);
}

void DucoBypassControl::set_address(uint8_t address) { ESP_LOGD(TAG, "DucoBypassControl: SetAddress %i",address); this->address_ = address; }

void DucoBypassControl::setup() {
  ESP_LOGD(TAG, "DucoBypassControl: setup!");
}

void DucoBypassControl::update() {
  DucoMessage message;
  message.function = 0x24;
  message.data = {0x00, 0x10, 0x0a};
  this->parent_->send(message, this);
}

float DucoBypassControl::get_setup_priority() const {
  // After DUCO
  return setup_priority::BUS - 2.0f;
}

void DucoBypassControl::receive_response(const DucoMessage &message) {
  if (message.function == 0x26 && message.data[0] == 0x01 && message.data[1] == 0x10 && message.data[2] == 0x0a) {
    // mode response received, parse it
    auto mode = code_to_string_bypass(message.data[3]);

    publish_state(mode);

    ESP_LOGD(TAG, "DucoBypassControl: Current mode: %s", mode.c_str());

    // do not wait for new messages with the same ID
    this->parent_->stop_waiting(message.id);
  }
  if (message.function == 0x26 && message.data[0] == 0x01) {
    this->parent_->stop_waiting(message.id);
  }
}

void DucoBypassControl::control(const std::string &value) {
  if (!this->parent_->is_advanced_features_enabled()) {
    ESP_LOGW(TAG, "DucoBypassAdaptiveControl: Advanced features disabled, control rejected!");
    // Publish the current state again to revert the GUI change
    this->publish_state(StringRef(this->current_option()));
    return;
  }
  DucoMessage message;
  message.function = 0x24;
  message.data = {address_, 0x10, 0x0a, string_to_code_bypass(value), 0x00, 0x00, 0x00};
  this->parent_->send(message, this);
}

void DucoBypassAdaptiveControl::set_address(uint8_t address) { ESP_LOGD(TAG, "DucoBypassAdaptiveControl: SetAddress %i",address); this->address_ = address; }

void DucoBypassAdaptiveControl::setup() {
  ESP_LOGD(TAG, "DucoBypassAdaptiveControl: setup!");
}

void DucoBypassAdaptiveControl::update() {
  DucoMessage message;
  message.function = 0x24;
  message.data = {0x00, 0x11, 0x0a};
  this->parent_->send(message, this);
}

float DucoBypassAdaptiveControl::get_setup_priority() const {
  // After DUCO
  return setup_priority::BUS - 2.0f;
}


void DucoBypassAdaptiveControl::receive_response(const DucoMessage &message) {
  if (message.function == 0x26 && message.data[0] == 0x01 && message.data[1] == 0x11 && message.data[2] == 0x0a) {
    // mode response received, parse it
    auto mode = code_to_string_bypass_adaptive(message.data[3]);

    publish_state(mode);

    ESP_LOGD(TAG, "DucoBypassAdaptiveControl: Current mode: %s", mode.c_str());

    // do not wait for new messages with the same ID
    this->parent_->stop_waiting(message.id);
  }
  if (message.function == 0x26 && message.data[0] == 0x01) {
    this->parent_->stop_waiting(message.id);
  }
}

void DucoBypassAdaptiveControl::control(const std::string &value) {
  if (!this->parent_->is_advanced_features_enabled()) {
    ESP_LOGW(TAG, "DucoBypassAdaptiveControl: Advanced features disabled, control rejected!");
    // Publish the current state again to revert the GUI change
    this->publish_state(StringRef(this->current_option()));
    return;
  }
  DucoMessage message;
  message.function = 0x24;
  message.data = {address_,0x11, 0x0a, string_to_code_bypass_adaptive(value), 0x00, 0x00, 0x00};
  this->parent_->send(message, this);
}

void DucoHeaterMode::set_address(uint8_t address) { ESP_LOGD(TAG, "DucoBypassAdaptiveControl: SetAddress %i",address); this->address_ = address; }

void DucoHeaterMode::setup() {}

void DucoHeaterMode::update() {
  DucoMessage message;
  message.function = 0x24;
  message.data = {0x00, 0x20, 0x0a};
  this->parent_->send(message, this);
}

float DucoHeaterMode::get_setup_priority() const {
  // After DUCO
  return setup_priority::BUS - 2.0f;
}


void DucoHeaterMode::receive_response(const DucoMessage &message) {
  if (message.function == 0x26 && message.data[0] == 0x01 && message.data[1] == 0x20 && message.data[2] == 0x0a) {
    // mode response received, parse it
    auto mode = code_to_string_bypass_adaptive(message.data[3]);

    publish_state(mode);

    ESP_LOGD(TAG, "DucoHeaterMode: Current mode: %s", mode.c_str());

    // do not wait for new messages with the same ID
    this->parent_->stop_waiting(message.id);
  }
  if (message.function == 0x26 && message.data[0] == 0x01) {
    this->parent_->stop_waiting(message.id);
  }
}

void DucoHeaterMode::control(const std::string &value) {
  if (!this->parent_->is_advanced_features_enabled()) {
    ESP_LOGW(TAG, "DucoHeaterMode: Advanced features disabled, control rejected!");
    // Publish the current state again to revert the GUI change
    this->publish_state(StringRef(this->current_option()));
    return;
  }
  DucoMessage message;
  message.function = 0x24;
  message.data = {address_,0x20, 0x0a, string_to_code_bypass_adaptive(value), 0x00, 0x00, 0x00};
  this->parent_->send(message, this);
}

void DucoPassiveCooling::set_address(uint8_t address) { ESP_LOGD(TAG, "PassiveCooling: SetAddress %i",address); this->address_ = address; }

void DucoPassiveCooling::setup() {}

void DucoPassiveCooling::update() {
  DucoMessage message;
  message.function = 0x24;
  message.data = {0x00, 0x01, 0x03};
  this->parent_->send(message, this);
}

float DucoPassiveCooling::get_setup_priority() const {
  // After DUCO
  return setup_priority::BUS - 2.0f;
}


void DucoPassiveCooling::receive_response(const DucoMessage &message) {
  if (message.function == 0x26 && message.data[0] == 0x01 && message.data[1] == 0x01 && message.data[2] == 0x03) {
    // mode response received, parse it
    auto mode = code_to_string_bypass_adaptive(message.data[3]);

    publish_state(mode);

    ESP_LOGD(TAG, "DucoPassiveCooling: Current mode: %s", mode.c_str());

    // do not wait for new messages with the same ID
    this->parent_->stop_waiting(message.id);
  }
  if (message.function == 0x26 && message.data[0] == 0x01) {
    this->parent_->stop_waiting(message.id);
  }
}

void DucoPassiveCooling::control(const std::string &value) {
  if (!this->parent_->is_advanced_features_enabled()) {
    ESP_LOGW(TAG, "DucoPassiveCooling: Advanced features disabled, control rejected!");
    // Publish the current state again to revert the GUI change
    this->publish_state(StringRef(this->current_option()));
    return;
  }
  DucoMessage message;
  message.function = 0x24;
  message.data = {address_,0x01, 0x03, string_to_code_bypass_adaptive(value), 0x00, 0x00, 0x00};
  this->parent_->send(message, this);
}


}  // namespace duco
}  // namespace esphome
