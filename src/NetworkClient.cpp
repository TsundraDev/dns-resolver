#include "NetworkClient.hpp"

#include <cstdio>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

NetworkClient::NetworkClient(IPv4 server, uint16_t port, TransportLayerProtocol protocol) :
  m_server(server),
  m_port(port),
  m_protocol(protocol),
  m_socket(-1) {}

bool NetworkClient::connectServer() {
  // Create socket
  switch (m_protocol) {
    case TransportLayerProtocol::TCP: m_socket = socket(AF_INET, SOCK_STREAM, 0); break;
    case TransportLayerProtocol::UDP: m_socket = socket(AF_INET, SOCK_DGRAM, 0); break;
  }
  if (m_socket < 0) {
    fprintf(stderr, "NetworkClient::connect - Error creating socket\n");
    return false;
  }

  // Connect to server
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(m_server.ip());
  server_addr.sin_family = htonl(m_port);

  int status = connect(m_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (status < 0) {
    fprintf(stderr, "NetworkClient::connect - Error connecting to server\n");
    return false;
  }

  return true;
}

void NetworkClient::disconnectServer() {
  close(m_socket);
}

void NetworkClient::sendServer(uint8_t* data, uint64_t size) {
  send(m_socket, data, size, 0);
}

uint64_t NetworkClient::recvServer(uint8_t* buffer, uint64_t buffer_size) {
  return recv(m_socket, buffer, buffer_size, 0);
}
