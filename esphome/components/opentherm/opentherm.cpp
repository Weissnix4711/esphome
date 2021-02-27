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
  this->last_request_timestamp_ = millis();
}

void OpenthermComponent::loop() {
  // Make sure communication isn't already in progress.
  if ((millis() - this->last_request_timestamp_) < 1000) {
    return;
  } else if (!OPENTHERM::isIdle) {
    ESP_LOGW(TAG, "Opentherm is not idle!");
    return;
  }

  // Timeout / message received.
  if (OPENTHERM::isError()) {
    ESP_LOGW(TAG, "Timeout.");
    return;
  } else if (OPENTHERM::getMessage(this->current_response_)) {
    // todo
    return;
  }

  // If we need to communicate again, no timeout occured
  // or message was received,
  // send the next request.
  switch (this->current_type_)
  {
  case OpenthermCurrentType::BINARY_SENSOR:
    // todo
    break;

  case OpenthermCurrentType::CLIMATE:
    // todo
    break;

  case OpenthermCurrentType::SENSOR:
    this->send_sensor_(*(this->sensor_it_));
    // todo check if that was the last element in vector
    // todo advance iterator.
    break;
  }
}

void OpenthermComponent::send_binary_sensor_(OpenthermRegisteredBinarySensor &binary_sensor) {
  // todo
}

void OpenthermComponent::send_climate_(OpenthermRegisteredClimate &climate) {
  // todo
}

void OpenthermComponent::send_sensor_(OpenthermRegisteredSensor &sensor) {
  OPENTHERM::send(out_pin_->get_pin(), sensor.message);
  while (!OPENTHERM::isSent()) { }
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
