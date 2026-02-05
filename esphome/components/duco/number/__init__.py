import esphome.codegen as cg
from esphome.components import number
import esphome.config_validation as cv
from esphome.const import CONF_ID, DEVICE_CLASS_TEMPERATURE, UNIT_CELSIUS, CONF_ADDRESS

from .. import CONF_DUCO_ID, DUCO_COMPONENT_SCHEMA

DEPENDENCIES = ["duco"]
CODEOWNERS = ["@kokx"]

UNIT_DAYS = "days"

CONF_FILTER_REMAINING = "filter_remaining"
CONF_COMFORT_TEMPERATURE = "comfort_temperature"

duco_ns = cg.esphome_ns.namespace("duco")
DucoComfortTemperature = duco_ns.class_(
    "DucoComfortTemperature", cg.PollingComponent, number.Number
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.Optional(CONF_COMFORT_TEMPERATURE): cv.ensure_list(
            number.number_schema(
                DucoComfortTemperature,
                unit_of_measurement=UNIT_CELSIUS,
                device_class=DEVICE_CLASS_TEMPERATURE,
            )
            .extend(
                {
                    cv.GenerateID(): cv.declare_id(DucoComfortTemperature),
                    cv.Optional(CONF_ADDRESS): cv.int_range(0, 255),
                }
            )
            .extend(cv.COMPONENT_SCHEMA)
            .extend(cv.polling_component_schema("60s"))
            .extend(DUCO_COMPONENT_SCHEMA)
        )
    }
).extend(DUCO_COMPONENT_SCHEMA)


async def to_code(config):
    parent = await cg.get_variable(config[CONF_DUCO_ID])

    if CONF_COMFORT_TEMPERATURE in config:
        for comf_temperature_config in config[CONF_COMFORT_TEMPERATURE]:
            var = cg.new_Pvariable(comf_temperature_config[CONF_ID])
            await cg.register_component(var, comf_temperature_config)
            await number.register_number(var, comf_temperature_config, min_value=10.0, max_value=25.5, step=0.1)
            cg.add(var.set_parent(parent))
            if CONF_ADDRESS in comf_temperature_config:
                cg.add(var.set_address(comf_temperature_config[CONF_ADDRESS]))
            else:
                cg.add(var.set_address(12))
