from esphome import pins
import esphome.codegen as cg
from esphome.components import spi
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID, 
    CONF_CS_PIN,
)

DEPENDENCIES = ["spi"]
AUTO_LOAD = ["spi"]
MULTI_CONF = True
CODEOWNERS = ["@jakubkub"]
CONF_MAX_RESISTANCE = "max_resistance"

tpl0501_ns = cg.esphome_ns.namespace("tpl0501")
TPL0501 = tpl0501_ns.class_("TPL0501", cg.Component, spi.SPIDevice)


CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(TPL0501),
    cv.Required(CONF_CS_PIN): pins.gpio_output_pin_schema,
    cv.Optional(CONF_MAX_RESISTANCE, default=100): cv.positive_float,
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    cs = await cg.gpio_pin_expression(config[CONF_CS_PIN])
    cg.add(var.set_cs_pin(cs))
    cg.add(var.set_max_resistance_value(config[CONF_MAX_RESISTANCE]))