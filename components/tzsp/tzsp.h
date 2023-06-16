#pragma once

#include <cstddef>
#include <memory>
#include <vector>

#include <esphome/components/network/ip_address.h>
#include <esphome/components/socket/socket.h>

namespace esphome {
namespace tzsp {

constexpr u_int16_t TZSP_PORT = 0x9090;
constexpr u_int8_t TZSP_HEADER_LENGTH = 5;

class TZSPSender {
  public:
    TZSPSender() = default;

    void set_tzsp_ip(const network::IPAddress ip) { this->sockaddr_in_.sin_addr.s_addr = ip; }
    void set_tzsp_port(uint16_t port) { this->sockaddr_in_.sin_port = htons(port); }
    void set_tzsp_protocol(uint16_t protocol) { this->tzsp_protocol_ = htons(protocol); }

    template<class T>
    void tzsp_send(const T& container) {
      if (this->sockaddr_in_.sin_addr.s_addr != ESPHOME_INADDR_ANY)
      {
        if (this->socket_ == nullptr)
          this->socket_ = socket::socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);

        if (this->socket_ != nullptr) {
          std::vector<uint8_t> buffer { 1, 1, static_cast<uint8_t>(this->tzsp_protocol_), static_cast<uint8_t>(this->tzsp_protocol_ >> 8), 1 };
          buffer.insert(buffer.end(), std::begin(container), std::end(container));
          this->socket_->sendto(buffer.data(), buffer.size(), 0, reinterpret_cast<sockaddr*>(&this->sockaddr_in_), sizeof(this->sockaddr_in_));
        }
      }
    }

  protected:
    uint16_t tzsp_protocol_{};
    std::unique_ptr<socket::Socket> socket_;
    struct sockaddr_in sockaddr_in_ { sizeof(struct sockaddr_in), AF_INET, htons(TZSP_PORT), { ESPHOME_INADDR_ANY }, 0 };
    static_assert(offsetof(sockaddr_in, sin_family) != 0, "sin_size removed from sockaddr_in - fix initializer");
};

}
}