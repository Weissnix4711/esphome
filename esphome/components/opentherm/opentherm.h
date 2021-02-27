#pragma once

#include "esphome/core/component.h"
#include "esphome/core/esphal.h"

#include <opentherm.h>

namespace esphome {
namespace opentherm{

enum OpenthermCurrentType {
  BINARY_SENSOR,
  CLIMATE,
  SENSOR
};

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

  // todo register_binary_senor
  // todo register_climate
  void register_sensor(byte id, const std::function<void(OpenthermData)> &func);

 protected:
  GPIOPin *in_pin_{nullptr};
  GPIOPin *out_pin_{nullptr};

  OpenthermCurrentType current_type_;
  OpenthermData current_response_;

  std::vector<OpenthermRegisteredBinarySensor> binary_sensors_;
  std::vector<OpenthermRegisteredBinarySensor>::iterator binary_sensor_it_ = this->binary_sensors_.begin();
  std::vector<OpenthermRegisteredClimate> climates_;
  std::vector<OpenthermRegisteredClimate>::iterator climate_it_ = this->climates_.begin();
  std::vector<OpenthermRegisteredSensor> sensors_;
  std::vector<OpenthermRegisteredSensor>::iterator sensor_it_ = this->sensors_.begin();

  void send_binary_sensor_(OpenthermRegisteredBinarySensor &binary_sensor);
  void send_climate_(OpenthermRegisteredClimate &climate);
  void send_sensor_(OpenthermRegisteredSensor &sensor);

  uint32_t last_request_timestamp_ = 0;
};

} // namespace opentherm
} // namespace esphome
