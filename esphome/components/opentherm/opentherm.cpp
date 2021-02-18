#include "opentherm.h"
#include "esphome/core/log.h"

namespace esphome {
namespace opentherm {

static const char *TAG = "opentherm";
static const int MAXIMUM_REQUEST_DELAY = 800;

float OpenthermMessage::f88() {
  float value = (int8_t) high_byte;
  return value + (float) low_byte / 256.0;
}

void OpenthermMessage::f88(float value) {
  if (value >= 0) {
    high_byte = (uint8_t) value;
    float fraction = (value - high_byte);
    low_byte = fraction * 256;
  } else {
    high_byte = (uint8_t) (value - 1);
    float fraction = (value - high_byte - 1);
    low_byte = fraction * 256;
  }
}

uint16_t OpenthermMessage::u16() {
  uint16_t value = high_byte;
  return (value << 8) | low_byte;
}

void OpenthermMessage::u16(uint16_t value) {
  low_byte = value & 0xFF;
  high_byte = (value >> 8) & 0xFF;
}

int16_t OpenthermMessage::s16() {
  int16_t value = high_byte;
  return (value << 8) | low_byte;
}

void OpenthermMessage::s16(int16_t value) {
  low_byte = value & 0xFF;
  high_byte = (value >> 8) & 0xFF;
}

void OpenthermComponent::setup() {
  this->in_pin_->setup();
  this->out_pin_->setup();
  this->out_pin_->digital_write(true);
}

void OpenthermComponent::loop() {
  // todo
}

void OpenthermComponent::register_sensor(uint8_t id, const std::function<void(OpenthermMessage)> &func) {
  auto sensor = OpenthermRegisteredSensor {
    .message = OpenthermMessage {
      .type = OpenthermMessageType::READ_DATA,
      .id = id,
      .high_byte = 0,
      .low_byte = 0
    },
    .function = func
  };

  this->sensors_.push_back(sensor);
}

} // namespace opentherm
} // namespace esphome
