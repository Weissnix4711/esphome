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

void ICACHE_RAM_ATTR OpenthermComponent::send_interrupt() {
  bool bit_value;
  if (this->send_bit_ >= 68) {
    this->send_bit_ = 0;
    timer1_disable();
    this->out_pin_->digital_write(true);
  } else {
    bit_value = this->send_frame_.test(this->send_bit_);
    this->out_pin_->digital_write(bit_value);
    this->send_bit_++;
  }
}

void OpenthermComponent::setup() {
  this->in_pin_->setup();
  this->out_pin_->setup();
  this->out_pin_->digital_write(true);
  this->begin_timestamp_ = millis();

#ifdef ARDUINO_ARCH_ESP8266
  timer1_attachInterrupt(send_interrupt);
#endif
#ifdef ARDUINO_ARCH_ESP32
  // todo idk
#endif
}

void OpenthermComponent::loop() {
  if (!activated_) {
    uint32_t current_timestamp_ = millis();
    if (current_timestamp_ - begin_timestamp_ > 1000) {
      this->activated_ = true;
      ESP_LOGD(TAG, "Opentherm ready.");
    }
    return;
  }

  // todo loop through registered components, generate next frame
  // and start timer
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

// todo register climates and binary sensors

} // namespace opentherm
} // namespace esphome
