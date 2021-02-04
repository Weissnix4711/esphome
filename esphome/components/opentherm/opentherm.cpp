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
  while (OPENTHERM::isIdle()) {
    // todo binary sensors
    for (OpenthermRegisteredSensor sensor : this->sensors_) {
      OPENTHERM::send(out_pin_->get_pin(), sensor.message);
      // todo wait for to be sent, get message, call sensor.function
    }
    // todo climate devices.
    // Need ch and dhw set and is,
    // ch + dhw mode from master status LB
    // and flame status (climate action HEAT/IDLE)
  }
}

void OpenthermComponent::register_sensor(byte id, const std::function<void(OpenthermData)> &func) {
  auto sensor = OpenthermRegisteredSensor {
    .message = OpenthermData {
      .type = OT_MSGTYPE_READ_DATA,
      .id = id,
      .valueHB = 0,
      .valueLB = 0
    },
    .function = func
  };

  this->sensors_.push_back(sensor);
}

} // namespace opentherm
} // namespace esphome
