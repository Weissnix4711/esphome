import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate
from esphome.const import CONF_ID, \
    CONF_BOILER_CH_SETPOINT, CONF_BOILER_DHW_SETPOINT, \
    CONF_ICON, ICON_RADIATOR, ICON_WATER_PUMP
from .. import opentherm_ns, CONF_OPENTHERM_ID, OpenthermComponent

DEPENDENCIES = ['opentherm']
CODEOWNERS = ['@Weissnix4711']

OpenthermClimate = opentherm_ns.class_('OpenthermClimate', climate.Climate)

CONFIG_SCHEMA = cv.Schema.extend({
    cv.GenerateID(): cv.declare_id(OpenthermClimate),
    cv.Required(CONF_OPENTHERM_ID): cv.use_id(OpenthermComponent),
    cv.Optional(CONF_BOILER_CH_SETPOINT): climate.CLIMATE_SCHEMA.extend({
        cv.Optional(CONF_ICON, default=ICON_RADIATOR): cv.icon
    }),
    cv.Optional(CONF_BOILER_DHW_SETPOINT): climate.CLIMATE_SCHEMA.extend({
        cv.Optional(CONF_ICON, default=ICON_WATER_PUMP): cv.icon
    })
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield climate.register_climate(var, config)

    paren = yield cg.get_variable(config[CONF_OPENTHERM_ID])
    cg.add(var.set_opentherm_parent(paren)

    #todo
