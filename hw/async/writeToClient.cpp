#include "writeToClient.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int writeToClient(int infd, char *answer)
{
  size_t s = write(infd, answer, strlen(answer));
  if (s == -1)
  {
    perror("write");
    abort();
    return -1;
  }
  return 0;
}
