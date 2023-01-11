#include <stdio.h>
#include <stdlib.h>
#include "display.h"

#define INIT_BUFFER_SIZE 10

typedef enum softwareId {
  DISPLAY = 2,
  ADD = 3,
  MODIFY = 4,
} softwareId;

bool readClientName(char **ptr) {
  freeIfNotNull(*ptr);
  size_t size = 0;
  int r;

  printf("Please enter a name: ");
  r = getline(ptr, &size, stdin);

  return (r != -1);
}

void invokeSoftware(softwareId id, char *clientName, vector **depositCache, vector **creditCache) {
  switch (id) {
    case DISPLAY:
      loadAndDisplay(clientName, depositCache, creditCache);
      break;
    default:
      break;
  }
}

void cleanUp(char *str, vector *cacheA, vector *cacheB) {
  freeIfNotNull(str);

  cleanCache(cacheA);
  freeIfNotNull(cacheA);

  cleanCache(cacheB);
  freeIfNotNull(cacheB);
}

int main() {
  int option = 0;
  size_t bufferSize = 0;
  char *buffer;
  char *clientName = NULL;
  vector *depositCache = vectorInit();
  vector *creditCache = vectorInit();

  while (option != 5) {
    printf(
        "What we want to do today? Type number corrsponding to the option.\n \
            (1) Specify the client for whom operations will be performed.\n \
            (2) Deposit and credit display software.\n \
            (3) Software for adding deposits and loans.\n \
            (4) Software for modifying the content of deposits and loans.\n \
            (5) Quit.\n");

    int r = getline(&buffer, &bufferSize, stdin);
    option = atoi(buffer);
    freeIfNotNull(buffer);
    bufferSize = 0;

    if (option == 1) {
      readClientName(&clientName);
    } else if (option > 1 && option < 5) {
      invokeSoftware(option, clientName, &depositCache, &creditCache);
    } else if (option == 5) {
      cleanUp(clientName, creditCache, depositCache);
      printf("Have a nice day!\n");
    } else {
      printf("Invalid input!\n");
    }
  }

  return 0;
}
