#include <stdio.h>
#include <stdlib.h>
#include "accounts.h"

#ifndef DISPLAY_UTILS
#define DISPLAY_UTILS

#define CREDIT_PATH "credits"
#define DEPOSITS_PATH "deposits"


bool cleanCache(vector *cache) {
  bool okay = true;
  if (vectorSize(cache) > 0) {
    for (size_t i = vectorSize(cache) - 1; i > 0; i--) {
      accountDestructor((account *)vectorGet(cache, i));
      okay &= (SUCCESS == vectorRemove(cache, i));
    }
  }

  return okay;
}

bool load(char *name, char *dirPath, vector **cache) {
  char *filepath;
  vector *filepaths = vectorInit();
  cleanCache(*cache);


  if (!getFilepaths(dirPath, filepaths))
    return false;

  for (size_t i = 0; i < vectorSize(filepaths); i++) {
    filepath = (char *)vectorGet(filepaths, i);
    account *acc = readFromFile(filepath);
    if (strcmp(acc->name, name) == 0)
      vectorPushBack(*cache, acc);
    else
      accountDestructor(acc);
  }

  return true;
}


void display(vector *accounts) {
  if (vectorSize(accounts) == 0)
    printf("No data available!\n");

  for (size_t i = 0; i < vectorSize(accounts); i++) {
    fprintAccount(stdout, (account *)vectorGet(accounts, i));
  }
}

bool loadAndDisplay(char *name, vector **depositsCache, vector **creditCache) {
  bool okay = true;

  if (okay &= load(name, DEPOSITS_PATH, depositsCache) == false)
    fprintf(stderr, "Error loading deposit files!\n");

  if (okay &= load(name, CREDIT_PATH, creditCache) == false)
    fprintf(stderr, "Error loading credit files!\n");

  if (okay) {
    printf("%s deposits:\n", name);
    display(*depositsCache);

    printf("%s credits:\n", name);
    display(*creditCache);
  }

  return okay;
}


#endif /* ACCOUNTS_UTILS */
