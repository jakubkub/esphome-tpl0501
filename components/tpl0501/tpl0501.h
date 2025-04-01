#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace tpl0501 {

class TPL0501 : public Component {
 public:

  TPL0501() = default;
  void setup() override;
  void dump_config() override;
  void set_cs_pin(GPIOPin *cs_pin);
  void set_max_resistance_value(float max_resistance_value) { max_resistance_value_ = max_resistance_value; }
  void set_wiper(uint8_t value);
  float get_wiper() const;
  void update_wiper_from_resistance(float resistance);

 protected:
    GPIOPin *cs_pin_{nullptr};
    float current_wiper_value_ = 0;
    float max_resistance_value_;

};

}  
}  