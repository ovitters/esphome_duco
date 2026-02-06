import esphome.codegen as cg
from esphome.components import select
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_ADDRESS
from .. import CONF_DUCO_ID, DUCO_COMPONENT_SCHEMA

DEPENDENCIES = ["duco"]
CODEOWNERS = ["@kokx"]

CONF_MODE = "mode"
CONF_BYPASS = "bypass"
CONF_BYPASS_ADAPTIVE = "adaptive_bypass"
CONF_HEATER="heater"

DUCO_MODE_OPTIONS = [
    "AUTO",
    "MAN1",
    "MAN2",
    "MAN3",
    "EMPT",
    "CNT1",
    "CNT2",
    "CNT3",
    "MAN1x2",
    "MAN2x2",
    "MAN3x2",
    "MAN1x3",
    "MAN2x3",
    "MAN3x3",
]

BYPASS_OPTIONS = [
    "AUTO",
    "OPEN",
    "CLOSED",
]

BYPASS_ADAPTIVE_OPTIONS = [
    "ON",
    "OFF",
]

HEATER_OPTIONS = [
    "ON",
    "OFF",
]



duco_ns = cg.esphome_ns.namespace("duco")
DucoSelect = duco_ns.class_("DucoSelect", cg.PollingComponent, select.Select)
DucoBypassControl = duco_ns.class_("DucoBypassControl", cg.PollingComponent, select.Select)
DucoBypassAdaptiveControl = duco_ns.class_("DucoBypassAdaptiveControl", cg.PollingComponent, select.Select)
DucoHeaterMode = duco_ns.class_("DucoHeaterMode", cg.PollingComponent, select.Select)


CONFIG_SCHEMA = cv.Schema(
    {
        cv.Optional(CONF_MODE): cv.ensure_list(
            select.select_schema(DucoSelect)
            .extend(
                {
                    cv.GenerateID(): cv.declare_id(DucoSelect),
                    cv.Optional(CONF_ADDRESS, default=1): cv.int_range(0, 68),
                }
            )
            .extend(cv.COMPONENT_SCHEMA)
            .extend(cv.polling_component_schema("3s"))
            .extend(DUCO_COMPONENT_SCHEMA)
        ),
        cv.Optional(CONF_BYPASS): cv.ensure_list(
            select.select_schema(DucoBypassControl)
            .extend(
                {
                    cv.GenerateID(): cv.declare_id(DucoBypassControl),
                    cv.Optional(CONF_ADDRESS, default=1): cv.int_range(0, 68),
                }
            )
            .extend(cv.COMPONENT_SCHEMA)
            .extend(cv.polling_component_schema("3s"))
            .extend(DUCO_COMPONENT_SCHEMA)
        ),
        cv.Optional(CONF_BYPASS_ADAPTIVE): cv.ensure_list(
            select.select_schema(DucoBypassAdaptiveControl)
            .extend(
                {
                    cv.GenerateID(): cv.declare_id(DucoBypassAdaptiveControl),
                    cv.Optional(CONF_ADDRESS, default=1): cv.int_range(0, 68),
                }
            )
            .extend(cv.COMPONENT_SCHEMA)
            .extend(cv.polling_component_schema("3s"))
            .extend(DUCO_COMPONENT_SCHEMA)
        ),
        cv.Optional(CONF_HEATER): cv.ensure_list(
            select.select_schema(DucoHeaterMode)
            .extend(
                {
                    cv.GenerateID(): cv.declare_id(DucoHeaterMode),
                    cv.Optional(CONF_ADDRESS, default=1): cv.int_range(0, 68),
                }
            )
            .extend(cv.COMPONENT_SCHEMA)
            .extend(cv.polling_component_schema("3s"))
            .extend(DUCO_COMPONENT_SCHEMA)
        )


    }
).extend(DUCO_COMPONENT_SCHEMA)

async def to_code(config):
    parent = await cg.get_variable(config[CONF_DUCO_ID])

    if CONF_MODE in config:
        for select_config in config[CONF_MODE]:
            var = cg.new_Pvariable(select_config[CONF_ID])
            await cg.register_component(var, select_config)
            await select.register_select(var, select_config, options=DUCO_MODE_OPTIONS)
            cg.add(var.set_parent(parent))
            cg.add(var.set_address(select_config[CONF_ADDRESS]))

    if CONF_BYPASS in config:
        for select_config in config[CONF_BYPASS]:
            var = cg.new_Pvariable(select_config[CONF_ID])
            await cg.register_component(var, select_config)
            await select.register_select(var, select_config, options=BYPASS_OPTIONS)
            cg.add(var.set_parent(parent))
            cg.add(var.set_address(select_config[CONF_ADDRESS]))

    if CONF_BYPASS_ADAPTIVE in config:
        for select_config in config[CONF_BYPASS_ADAPTIVE]:
            var = cg.new_Pvariable(select_config[CONF_ID])
            await cg.register_component(var, select_config)
            await select.register_select(var, select_config, options=BYPASS_ADAPTIVE_OPTIONS)
            cg.add(var.set_parent(parent))
            cg.add(var.set_address(select_config[CONF_ADDRESS]))

    if CONF_HEATER in config:
        for select_config in config[CONF_HEATER]:
            var = cg.new_Pvariable(select_config[CONF_ID])
            await cg.register_component(var, select_config)
            await select.register_select(var, select_config, options=HEATER_OPTIONS)
            cg.add(var.set_parent(parent))
            cg.add(var.set_address(select_config[CONF_ADDRESS]))
