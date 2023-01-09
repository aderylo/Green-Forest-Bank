#include <stdio.h>
#include <stdlib.h>
#include "accounts.h"
#include "utils/vector.h"

#ifndef DISPLAY_UTILS
#define DISPLAY_UTILS

#define CREDIT_PATH "credits"
#define DEPOSITS_PATH "deposits"

bool loadAndDisplay(char *name, vector **depositsCache, vector **creditCache) {

}

void load(char *name, vector **cache, char *basePath){
    
}


void display(vector *accounts) {
  if (vectorSize(accounts) == 0)
    printf("No data available!\n");

  for (size_t i = 0; i < vectorSize(accounts); i++) {
    fprintAccount(stderr, (account *)vectorGet(accounts, i));
  }
}


#endif /* ACCOUNTS_UTILS */
