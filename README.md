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

```yaml

external_components:
  - source: github://Omniflux/esphome-tzsp

example_component:
  tzsp:
    ip: 192.168.1.10
    port: 37008
    protocol: 255

```