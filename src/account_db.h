#include <stdio.h>
#include <stdlib.h>
#include "accounts.h"

#ifndef ACCOUNT_DB
#define ACCOUNT_DB

#define CREDIT_PATH "credits"
#define DEPOSITS_PATH "deposits"
#define INIT_BUFFER_SIZE 20
#define MAX_FILE_PATH_LEN 60

void generateFilepath(int id, char *basePath, char **filepath) {
  freeIfNotNull(*filepath);
  *filepath = MALLOCATE_ARRAY(char, MAX_FILE_PATH_LEN);
  sprintf(*filepath, "%s/%d.account", basePath, id);
}

bool readIntegerArg(int *arg, int lowerBound, int upperBound) {
  size_t bufferSize = 0;
  char *buffer;

  int r, opt;
  if (r = getline(&buffer, &bufferSize, stdin) == EOF) {
    freeIfNotNull(buffer);
    return false;
  }
  *arg = atoi(buffer);
  if (!(*arg >= lowerBound && *arg <= upperBound))
    fprintf(stderr, "Invalid argument!\n");

  return (*arg >= lowerBound && *arg <= upperBound);
}

bool readDate(char **date) {
  size_t bufferSize = 0;
  char *buffer;
  int r;

  if (r = getline(&buffer, &bufferSize, stdin) == EOF) {
    freeIfNotNull(buffer);
    return false;
  }

  freeIfNotNull(*date);
  *date = buffer;

  return true;
}

bool addAccount(char *name, int *counter) {
  size_t bufferSize = 0;
  char *buffer, *date, *filepath;
  int r, option, sum, percent, duration;
  // get the first five fields from context

  printf(
      "New account will be a credit or a deposit?\n \
    (1) credit\n \
    (2) deposit \n");
  if (readIntegerArg(&option, 1, 2) == false)
    return false;


  printf("Specify sum: \n");
  if (readIntegerArg(&sum, 0, __INT_MAX__) == false)
    return false;

  printf("Specify date: \n");
  if (readDate(&date) == false)
    return false;

  printf("Specify percent: \n");
  if (readIntegerArg(&percent, 0, __INT_MAX__) == false)
    return false;

  printf("Specify duration: \n");
  if (readIntegerArg(&duration, 0, __INT_MAX__) == false)
    return false;


  // now we can init account
  account *acc = initAccount(name, ++(*counter), date);
  subAccount *subAcc = initSubAccount(sum);
  record rec = (record){.interest = percent, .duration = duration};
  subAccountAddRecord(subAcc, rec);
  accountAddSubAccount(acc, subAcc);
  if (option == 1)
    generateFilepath(*counter, CREDIT_PATH, &filepath);
  if (option == 2)
    generateFilepath(*counter, DEPOSITS_PATH, &filepath);

  saveToFile(acc, filepath);


  return true;
}


#endif /* ACCOUNT_DB */
