import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.const import CONF_ID, \
    CONF_BOILER_FLAME_STATUS, CONF_ICON, ICON_FIRE
from .. import opentherm_ns, CONF_OPENTHERM_ID, OpenthermComponent

DEPENDENCIES = ['opentherm']
CODEOWNERS = ['@Weissnix4711']

OpenthermBinarySensor = opentherm_ns.class_('OpenthermBinarySensor', cg.Component)

CONFIG_SCHEMA = cv.Schema.extend({
    cv.GenerateID(): cv.declare_id(OpenthermBinarySensor),
    cv.Required(CONF_OPENTHERM_ID): cv.use_id(OpenthermComponent),
    cv.Optional(CONF_BOILER_FLAME_STATUS): binary_sensor.BINARY_SENSOR_SCHEMA.extend({
        cv.Optional(CONF_ICON, default=ICON_FIRE): cv.icon
    })
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)

    paren = yield cg.get_variable(config[CONF_OPENTHERM_ID])
    cg.add(var.set_opentherm_parent(paren))

    if CONF_BOILER_FLAME_STATUS in config:
        conf = config[CONF_BOILER_FLAME_STATUS]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_flame_status(sens))
