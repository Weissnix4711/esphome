import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.const import CONF_ID, \
    CONF_BOILER_FLAME_STATUS, CONF_ICON, ICON_FIRE
from .. import opentherm_ns

DEPENDENCIES = ['opentherm']
CODEOWNERS = ['@Weissnix4711']

OpenthermBinarySensor = opentherm_ns.class_('OpenthermBinarySensor', binary_sensor.BinarySensor)

CONFIG_SCHEMA = binary_sensor.BINARY_SENSOR_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(OpenthermBinarySensor),
    cv.Optional(CONF_BOILER_FLAME_STATUS): binary_sensor.BINARY_SENSOR_SCHEMA.extend({
        cv.Optional(CONF_ICON, default=ICON_FIRE): cv.icon
    })
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    # todo
