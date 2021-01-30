#pragma once

#include "esphome/core/component.h"
#include "esphome/core/esphal.h"

#include <opentherm.h>

namespace esphome {
namespace opentherm{

class OpenthermComponent : public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;

  void set_in_pin(GPIOPin *in_pin) { in_pin_ = in_pin; }
  void set_out_pin(GPIOPin *out_pin) { out_pin_ = out_pin; }

 protected:
  GPIOPin *in_pin_{nullptr};
  GPIOPin *out_pin_{nullptr};
};

} // namespace opentherm
} // namespace esphome
