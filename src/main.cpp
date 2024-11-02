#include <cstdint>
#include <unistd.h>
#include <sys/socket.h>

#include <NetworkClient.hpp>

int main() {

  NetworkClient client = NetworkClient(IPv4(198, 41, 0, 4),
                                       53,
                                       TransportLayerProtocol::UDP);

  client.connectServer();
  client.disconnectServer();
  return 0;
}
