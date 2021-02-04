#pragma once

#include "esphome/core/component.h"
#include "esphome/components/opentherm/opentherm.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

namespace esphome {
namespace opentherm {

class OpenthermBinarySensor : public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;

  void set_opentherm_parent(OpenthermComponent *parent) { this->parent_ = parent; }

  void set_flame_status(binary_sensor::BinarySensor *flame) { this->flame_ = flame; }

 protected:
  OpenthermComponent *parent_;

  binary_sensor::BinarySensor *flame_;
};

} // namespace opentherm
} // namespace esphome
