#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <thread>
#include <mutex>
#include <atomic>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER "127.0.0.1"
#define PORT 1488
#define BUFF_SIZE 1024

using namespace std;

class UdpData {
public:
  
};

int main() {
  int sock;
  sockaddr_in serverAddr, clientAddr;
  char buffer[BUFF_SIZE]; 
  
  // create socket
  if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("fail create socket");
    exit(EXIT_FAILURE);
  }
  
  // init addr
    memset(&serverAddr, 0, sizeof(serverAddr));
    
  // set addr's params
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  serverAddr.sin_addr.s_addr = inet_addr(SERVER);
  
  if (bind(sock, (const sockaddr*) &serverAddr, sizeof(serverAddr)) < 0) {
    perror("error binding");
    exit(EXIT_FAILURE);
  }
  
  for (;;) {
    socklen_t sz = sizeof(clientAddr);
    
    cout << inet_ntoa(serverAddr.sin_addr) << endl;
    cout << serverAddr.sin_port << endl;
    
    if (int msg = recvfrom(sock, (char*)buffer, BUFF_SIZE, 0, (sockaddr*) &clientAddr, &sz) < 0) {
      perror("Error read data from sender");
      exit(EXIT_FAILURE);
    }
    cout << "lol2" << endl;
    
    if (strlen(buffer) == 0) {
      break;
    }
    
    cout << buffer << endl;
  }
  
  return 0;
}