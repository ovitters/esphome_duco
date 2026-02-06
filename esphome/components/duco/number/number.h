#pragma once

#include "esphome/core/log.h"
#include "esphome/core/component.h"
#include "esphome/components/number/number.h"
#include "../duco.h"

namespace esphome {
namespace duco {

class DucoComfortTemperature : public DucoDevice, public PollingComponent, public number::Number {
 public:
  void setup() override;
  void update() override;

  float get_setup_priority() const override;

  void receive_response(const DucoMessage &message) override;

  void control(float number) override;

  void set_address(uint8_t address);

 protected:
  uint8_t address_;
};

class DucoPassiveCoolingTemperature : public DucoDevice, public PollingComponent, public number::Number {
 public:
  void setup() override;
  void update() override;

  float get_setup_priority() const override;

  void receive_response(const DucoMessage &message) override;

  void control(float number) override;

  void set_address(uint8_t address);

 protected:
  uint8_t address_;
};

class DucoNightboostMax : public DucoDevice, public PollingComponent, public number::Number {
 public:
  void setup() override {
    this->traits.set_min_value(10.0f);
    this->traits.set_max_value(100.0f);
    this->traits.set_step(5.0f);
  }
  void update() override;

  float get_setup_priority() const override;

  void receive_response(const DucoMessage &message) override;

  void control(float number) override;

  void set_address(uint8_t address);

 protected:
  uint8_t address_;
};

class DucoBoxVentilationMin : public DucoDevice, public PollingComponent, public number::Number {
 public:
  void setup() override {
    this->traits.set_min_value(10.0f);
    this->traits.set_max_value(100.0f);
    this->traits.set_step(5.0f);
  }
  void update() override;

  float get_setup_priority() const override;

  void receive_response(const DucoMessage &message) override;

  void control(float number) override;

  void set_address(uint8_t address);

 protected:
  uint8_t address_;
};

class DucoBoxVentilationMax : public DucoDevice, public PollingComponent, public number::Number {
 public:
  void setup() override {
    this->traits.set_min_value(10.0f);
    this->traits.set_max_value(100.0f);
    this->traits.set_step(5.0f);
  }
  void update() override;

  float get_setup_priority() const override;

  void receive_response(const DucoMessage &message) override;

  void control(float number) override;

  void set_address(uint8_t address);

 protected:
  uint8_t address_;
};



}  // namespace duco
}  // namespace esphome
