#ifndef __DNS_RESOLVER__NETWORKCLIENT_HPP__
#define __DNS_RESOLVER__NETWORKCLIENT_HPP__

#include <cstdint>
#include <cstdio>

class IPv4 {
public:
  uint8_t m_ip[4];

  IPv4(uint8_t ip0, uint8_t ip1, uint8_t ip2, uint8_t ip3) :
    m_ip{ip0, ip1, ip2, ip3} {}

  uint32_t ip() { return *(uint32_t*)m_ip; }
};

enum class TransportLayerProtocol {TCP, UDP};

class NetworkClient {
public:
  IPv4 m_server;
  uint16_t m_port;
  TransportLayerProtocol m_protocol;

  int m_socket;

  NetworkClient(IPv4 server, uint16_t port, TransportLayerProtocol protocol);


  bool connectServer();
  void disconnectServer();

  void sendServer(uint8_t* data, uint64_t size);
  uint64_t recvServer(uint8_t* buffer, uint64_t buffer_size);
};

#endif
