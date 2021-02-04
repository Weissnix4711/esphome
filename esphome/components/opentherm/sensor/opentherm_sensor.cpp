#include "opentherm_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace opentherm {

static const char *TAG = "opentherm.sensor";

void OpenthermSensor::setup() {
  // todo register sensors
}

void OpenthermSensor::dump_config() {
  ESP_LOGCONFIG(TAG, "Opentherm Binary Sensor:");
  LOG_SENSOR("  ", "Flame", this->feed_);
  LOG_SENSOR("  ", "Return Water", this->return_water_);
  LOG_SENSOR("  ", "Modulation", modulation_);
}

} // namespace opentherm
} // namespace esphome

