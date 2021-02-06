#include "opentherm.h"
#include "esphome/core/log.h"

namespace esphome {
namespace opentherm {

static const char *TAG = "opentherm";
static const int MAXIMUM_REQUEST_DELAY = 800;

void OpenthermComponent::setup() {
  this->in_pin_->setup();
  this->out_pin_->setup();
  this->out_pin_->digital_write(true);
  delay(1000);
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
