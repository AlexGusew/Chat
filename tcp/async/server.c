#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  int MasterSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  struct sockaddr_in SockAddr;
  SockAddr.sin_family = AF_INET;
  SockAddr.sin_port = htons(1337);
  SockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  bind(MasterSocket, (struct sockaddr *)(&SockAddr), sizeof(SockAddr));

  listen(MasterSocket, SOMAXCONN);

  printf("Waiting 4 a client...\n");
  int ActiveSocket;
  fd_set socketsSet, recievedSet;
  int max = MasterSocket;

  FD_ZERO(&socketsSet);
  FD_ZERO(&recievedSet);
  FD_SET(MasterSocket, &socketsSet);

  while (1)
  {
    recievedSet = socketsSet;

    select(max + 1, &recievedSet, NULL, NULL, NULL);

    for (ActiveSocket = 0; ActiveSocket <= max; ActiveSocket++)
    {
      if (FD_ISSET(ActiveSocket, &recievedSet))
      {
        if (ActiveSocket != MasterSocket)
        {
          char Buffer[100];
          size_t msg_size = recv(ActiveSocket, Buffer, 100, 0);
          Buffer[msg_size] = 0;
          send(ActiveSocket, Buffer, msg_size, 0);

          printf("Client #%d send msg: %s\n", ActiveSocket, Buffer);
        }
        else
        {
          ActiveSocket = accept(MasterSocket, 0, 0);
          FD_SET(ActiveSocket, &socketsSet);
          if (ActiveSocket > max)
            max = ActiveSocket;
          printf("Client #%d connected!\n", ActiveSocket);
        }
      }
    }
  }

  return 0;
}
