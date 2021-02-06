#pragma once

#include "esphome/core/component.h"
#include "esphome/core/esphal.h"

namespace esphome {
namespace opentherm{

enum OpenthermMessageType : uint8_t {
  READ_DATA = 0b000,
  READ_ACK = 0b100,
  WRITE_DATA = 0b001,
  WRITE_ACK = 0b101,
  INVALID_DATA = 0b010,
  DATA_INVALID = 0b110,
  UNKNOWN_DATAID = 0b111
};

enum OpenthermMessageID : uint8_t {
  STATUS = 0,
  CH_SETPOINT = 1,
  MASTER_CONFIG = 2,
  SLAVE_CONFIG = 3,
  COMMAND_CODE = 4,
  FAULT_FLAGS = 5,
  REMOTE = 6,
  CH2_SETPOINT = 8,
  CH_SEtPOINT_OVERRIDE = 9,
  ROOM_SETPOINT = 16,
  MODULATION_LEVEL = 17,
  DHW_FLOW_RATE = 19,
  DAY_TIME = 20,
  DATE = 21,
  YEAR = 22,
  ROOM_SETPOINT_CH2 = 23,
  ROOM_TEMP = 24,
  FEED_TEMP = 25,
  DHW_TEMP = 26,
  OUTSIDE_TEMP = 27,
  RETURN_WATER_TEMP = 28,
  FEED_TEMP_CH2 = 31,
  DHW2_TEMP = 32,
  DHW_SETPOINT = 56
  // todo add remaining ids
};

struct OpenthermMessage {
  uint8_t type;
  uint8_t id;
  uint8_t high_byte;
  uint8_t low_byte;
};

struct OpenthermRegisteredBinarySensor {
  // todo
};

struct OpenthermRegisteredClimate {
  // todo
};

struct OpenthermRegisteredSensor {
  OpenthermMessage message;
  std::function<void(OpenthermMessage)> function;
};

class OpenthermComponent : public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;

  void set_in_pin(GPIOPin *in_pin) { in_pin_ = in_pin; }
  void set_out_pin(GPIOPin *out_pin) { out_pin_ = out_pin; }

  void register_sensor(byte id, const std::function<void(OpenthermMessage)> &func);

 protected:
  GPIOPin *in_pin_{nullptr};
  GPIOPin *out_pin_{nullptr};

  std::vector<OpenthermRegisteredBinarySensor> binary_sensors_;
  std::vector<OpenthermRegisteredClimate> climates_;
  std::vector<OpenthermRegisteredSensor> sensors_;
};

} // namespace opentherm
} // namespace esphome
