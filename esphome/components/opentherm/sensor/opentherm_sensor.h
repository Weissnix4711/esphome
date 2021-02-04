#pragma once

#include "esphome/core/component.h"
#include "esphome/components/opentherm/opentherm.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace opentherm {

class OpenthermSensor : public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;

  void set_opentherm_parent(OpenthermComponent *parent) { this->parent_ = parent; }

  void set_feed_temperature(sensor::Sensor *feed) { this->feed_ = feed; }
  void set_return_water_temperature(sensor::Sensor *return_water) { this->return_water_ = return_water; }
  void set_modulation(sensor::Sensor *modulation) { this->modulation_ = modulation; }

 protected:
  OpenthermComponent *parent_;

  sensor::Sensor *feed_;
  sensor::Sensor *return_water_;
  sensor::Sensor *modulation_;
};

} // namespace opentherm
} // namespace esphome
