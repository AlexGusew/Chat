#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

int main()
{
  int ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  struct sockaddr_in SockAddr;
  SockAddr.sin_family = AF_INET;
  SockAddr.sin_port = htons(1337);
  SockAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  connect(ClientSocket, (struct sockaddr *)&SockAddr, sizeof(SockAddr));

  char *msg = (char*)malloc(sizeof(char) * 100);

  while (msg != "")
  {
    scanf("%s", msg);
    send(ClientSocket, msg, strlen(msg), 0);
    size_t msg_size = recv(ClientSocket, msg, 1024, 0);
    msg[msg_size] = 0;

    printf("%s\n", msg);
  }

  return 0;
}
