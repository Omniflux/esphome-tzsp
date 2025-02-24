import esphome.codegen as cg
import esphome.config_validation as cv

CODEOWNERS = ["@Omniflux"]

CONF_TZSP = "tzsp"
CONF_TZSP_IP = "ip"
CONF_TZSP_PORT = "port"
CONF_TZSP_PROTOCOL = "protocol"

tzsp_sender_ns = cg.esphome_ns.namespace("tzsp")
TZSPSender = tzsp_sender_ns.class_("TZSPSender")

TZSP_SENDER_SCHEMA = cv.Schema(
    {
        cv.Optional(CONF_TZSP): cv.Schema(
            {
                cv.Required(CONF_TZSP_IP): cv.ipaddress,
                cv.Optional(CONF_TZSP_PORT, default=0x9090): cv.port,
                cv.Optional(CONF_TZSP_PROTOCOL, default=0): cv.int_range(0, 65535),
            }
        )
    }
)

async def register_tzsp_sender(var, config):
    if CONF_TZSP in config:
        cg.add(var.set_tzsp_ip(str(config[CONF_TZSP][CONF_TZSP_IP])))
        cg.add(var.set_tzsp_port(config[CONF_TZSP][CONF_TZSP_PORT]))
        cg.add(var.set_tzsp_protocol(config[CONF_TZSP][CONF_TZSP_PROTOCOL]))