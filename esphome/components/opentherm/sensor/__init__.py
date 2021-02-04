import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID, \
    CONF_BOILER_FEED_TEMPERATURE, CONF_BOILER_RETURN_WATER_TEMPERATURE, CONF_BOILER_MODULATION, \
    UNIT_CELSIUS, UNIT_PERCENT, ICON_THERMOMETER, ICON_PERCENT
from .. import opentherm_ns, CONF_OPENTHERM_ID, OpenthermComponent

DEPENDENCIES = ['opentherm']
CODEOWNERS = ['@Weissnix4711']

OpenthermSensor = opentherm_ns.class_('OpenthermSensor', cg.Component)

boiler_temperature_schema = sensor.sensor_schema(UNIT_CELSIUS, ICON_THERMOMETER, 2)
boiler_modulation_schema = sensor.sensor_schema(UNIT_PERCENT, ICON_PERCENT, 0)

CONFIG_SCHEMA = cv.Schema.extend({
    cv.GenerateID(): cv.declare_id(OpenthermSensor),
    cv.Required(CONF_OPENTHERM_ID): cv.use_id(OpenthermComponent),
    cv.Optional(CONF_BOILER_FEED_TEMPERATURE): boiler_temperature_schema,
    cv.Optional(CONF_BOILER_RETURN_WATER_TEMPERATURE): boiler_temperature_schema,
    cv.Optional(CONF_BOILER_MODULATION): boiler_modulation_schema
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)

    paren = yield cg.get_variable(config[CONF_OPENTHERM_ID])
    cg.add(var.set_opentherm_parent(paren))

    if CONF_BOILER_FEED_TEMPERATURE in config:
        conf = config[CONF_BOILER_FEED_TEMPERATURE]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_feed_temperature(sens))
    
    if CONF_BOILER_RETURN_WATER_TEMPERATURE in config:
        conf = config[CONF_BOILER_RETURN_WATER_TEMPERATURE]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_return_water_temperature(sens))

    if CONF_BOILER_MODULATION in config:
        conf = config[CONF_BOILER_MODULATION]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_modulation(sens))
