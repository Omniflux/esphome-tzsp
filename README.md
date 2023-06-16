# TZSP component for ESPHome

Inherit from tzsp::TZSPSender and call tzsp_send(...) to send data. See [esphome-tzspserial](https://github.com/Omniflux/esphome-tzspserial) for an example.

```cpp

#include <array>
#include "esphome.h"

class MyCustomComponent : public Component, public tzsp::TZSPSender {
 public:
  MyCustomComponent() = default;

  void setup() override {
    std::array<char, 8> buffer;
    // ...
    this->tzsp_send(buffer);
  }
};

```

```python

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.components import tzsp

AUTO_LOAD = ["tzsp"]
DEPENDENCIES = ["tzsp"]

mycustomcomponent_ns = cg.esphome_ns.namespace("mycustomcomponent")
MyCustomComponent = mycustomcomponent_ns.class_("MyCustomComponent", cg.Component)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(MyCustomComponent)
    }
).extend(cv.COMPONENT_SCHEMA).extend(tzsp.TZSP_SENDER_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await tzsp.register_tzsp_sender(var, config)

```

```yaml

external_components:
  - source: github://Omniflux/esphome-tzsp

example_component:
  tzsp:
    ip: 192.168.1.10
    port: 37008
    protocol: 255

```