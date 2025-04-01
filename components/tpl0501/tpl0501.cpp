#include "tpl0501.h"
#include "esphome/core/log.h"

namespace esphome {
namespace tpl0501 {

static const char *const TAG = "tpl0501";

void TPL0501::setup() {
    if (cs_pin_ != nullptr) {
        ESP_LOGD(TAG, "Setting up TPL0501 Potentiometer on CS pin: %d", this->cs_pin_);
        cs_pin_->setup();
        cs_pin_->digital_write(true);
        }
  }

void TPL0501::dump_config() {
    ESP_LOGCONFIG(TAG, "Setting up TPL0501 Potentiometer");
    LOG_PIN("  CS Pin: ", this->cs_pin_);
  }

void TPL0501::set_cs_pin(GPIOPin *cs_pin) {
    cs_pin_ = cs_pin;
  }

void TPL0501::set_wiper(uint8_t value) {
    if (cs_pin_ != nullptr) {
      cs_pin_->digital_write(false); 
      SPI.transfer(value); 
      cs_pin_->digital_write(true); 
    }
  }

float TPL0501::get_wiper() const {
    return current_wiper_value_;
  }

void TPL0501::update_wiper_from_resistance(float resistance) {
    uint8_t wiper_value = static_cast<uint8_t>((resistance / this->max_resistance_value_) * 255.0);
    set_wiper(wiper_value);
    current_wiper_value_ = wiper_value;
  }

}
}
