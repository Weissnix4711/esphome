import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.const import CONF_IN_PIN, CONF_OUT_PIN, CONF_ID

CODEOWNERS = ['@Weissnix4711']

ESP_PLATFORMS = ['ESP8266']

opentherm_ns = cg.esphome_ns.namespace('opentherm')
OpenthermComponent = opentherm_ns.class_('OpenthermComponent', cg.Component)

CONF_OPENTHERM_ID = 'opentherm_id'
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(OpenthermComponent),
    cv.Required(CONF_IN_PIN): pins.gpio_input_pullup_pin_schema,
    cv.Required(CONF_OUT_PIN): pins.gpio_output_pin_schema
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)

    in_pin = yield cg.gpio_pin_expression(config[CONF_IN_PIN])
    out_pin = yield cg.gpio_pin_expression(config[CONF_OUT_PIN])
    cg.add(var.set_in_pin(in_pin))
    cg.add(var.set_out_pin(out_pin))

    # https://platformio.org/lib/show/4348/Opentherm
    cg.add_library('4348', '1.2')
