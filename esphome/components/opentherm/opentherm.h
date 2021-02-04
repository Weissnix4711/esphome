#pragma once

#include "esphome/core/component.h"
#include "esphome/core/esphal.h"

#include <opentherm.h>

namespace esphome {
namespace opentherm{

struct OpenthermRegisteredBinarySensor {
  // todo
};

struct OpenthermRegisteredClimate {
  // todo
};

struct OpenthermRegisteredSensor {
  OpenthermData message;
  std::function<void(OpenthermData)> function;
};

class OpenthermComponent : public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;

  void set_in_pin(GPIOPin *in_pin) { in_pin_ = in_pin; }
  void set_out_pin(GPIOPin *out_pin) { out_pin_ = out_pin; }

  void register_sensor(byte id, const std::function<void(OpenthermData)> &func);

 protected:
  GPIOPin *in_pin_{nullptr};
  GPIOPin *out_pin_{nullptr};

  std::vector<OpenthermRegisteredBinarySensor> binary_sensors_;
  std::vector<OpenthermRegisteredClimate> climates_;
  std::vector<OpenthermRegisteredSensor> sensors_;
};

} // namespace opentherm
} // namespace esphome
