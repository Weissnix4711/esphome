#include "opentherm_binary_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace opentherm {

static const char *TAG = "opentherm.binary_sensor";

void OpenthermBinarySensor::setup() {
  // todo register binary sensor
}

void OpenthermBinarySensor::dump_config() {
  ESP_LOGCONFIG(TAG, "Opentherm Binary Sensor:");
  LOG_BINARY_SENSOR("  ", "Flame", this->flame_);
}

} // namespace opentherm
} // namespace esphome

