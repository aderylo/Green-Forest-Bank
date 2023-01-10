#include <stdio.h>
#include <stdlib.h>
#include "display.h"

typedef enum softwareId {
  DISPLAY = 2,
  ADD = 3,
  MODIFY = 4,
} softwareId;

void readClientName(char *ptr) {
  // lol
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

int main() {
  int option = 0;
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

    scanf("%d", &option);

    if (option == 1) {
      readClientName(clientName);
    } else if (option > 1 && option < 5) {
      if (clientName)
        invokeSoftware(option, clientName, &depositCache, &creditCache);
      else
        printf("First you must specify client name, use option (1)\n");
    } else if (option == 5) {
      // clear memory
      printf("Have a nice day!\n");
    }
  }

  return 0;
}
