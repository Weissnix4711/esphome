#include "opentherm.h"
#include "esphome/core/log.h"

namespace esphome {
namespace opentherm {

static const char *TAG = "opentherm";

OpenthermData message;

void OpenthermComponent::setup() {
  this->in_pin_->setup();
  this->out_pin_->setup();
}

} // namespace opentherm
} // namespace esphome
