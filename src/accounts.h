#include <stdio.h>
#include <string.h>
#include "memalloc.h"
#include "utils/file.h"
#include "utils/vector.h"

#ifndef ACCOUNTS_UTILS
#define ACCOUNTS_UTILS

#define SUCCESS 0

typedef struct account {
  char *name;
  int number;
  char *date;
  vector *subAccounts;
} account;

typedef struct subAccount {
  int sum;
  vector *records;
} subAccount;

typedef struct record {
  int interest;
  int duration;
} record;


account *initAccount(char *name, int number, char *date) {
  account *acc = MALLOCATE(account);
  acc->number = number;
  acc->name = MALLOCATE_ARRAY(char, strlen(name));
  strcpy(acc->name, name);
  acc->date = MALLOCATE_ARRAY(char, strlen(date));
  strcpy(acc->date, date);
  acc->subAccounts = vectorInit();

  return acc;
}

subAccount *initSubAccount(int sum) {
  subAccount *subAcc = MALLOCATE(subAccount);
  subAcc->sum = sum;
  subAcc->records = vectorInit();
  return subAcc;
}

void subAccountDestructor(subAccount *subAcc) {
  if (subAcc) {
    for (size_t i = 0; i < vectorSize(subAcc->records); i++) {
      record *r = (record *)vectorGet(subAcc->records, i);
      freeIfNotNull(r);
    }

    free(subAcc);
  }
}

void accountDestructor(account *acc) {
  if (acc) {
    for (size_t i = 0; i < vectorSize(acc->subAccounts); i++) {
      subAccountDestructor((subAccount *)vectorGet(acc->subAccounts, i));
    }
    freeIfNotNull(acc->date);
    freeIfNotNull(acc->name);
    freeIfNotNull(acc);
  }
}

bool accountAddSubAccount(account *acc, subAccount *subAcc) {
  return (vectorPushBack(acc->subAccounts, subAcc) == SUCCESS);
}

bool subAccountAddRecord(subAccount *subAcc, record rec) {
  record *recPtr = MALLOCATE(record);
  *recPtr = rec;
  return (vectorPushBack(subAcc->records, recPtr) == SUCCESS);
}


void fprintAccount(FILE *stream, account *acc) {
  fprintf(stream, "Name: %s\n", acc->name);
  fprintf(stream, "Number: %d\n", acc->number);
  fprintf(stream, "Date: %s\n", acc->date);

  for (size_t i = 0; i < vectorSize(acc->subAccounts); i++) {
    subAccount *subAcc = (subAccount *)vectorGet(acc->subAccounts, i);
    fprintf(stream, "Sum: %d\n", subAcc->sum);

    for (size_t j = 0; j < vectorSize(subAcc->records); j++) {
      record *rec = (record *)vectorGet(subAcc->records, j);
      fprintf(stream, "Procent: %d\n", rec->interest);
      fprintf(stream, "Duration: %d\n", rec->duration);
    }
  }
}


void saveToFile(account *acc, char *filepath) {
  FILE *fptr;
  if ((fptr = fopen(filepath, "w")) == NULL) {
    fprintf(stderr, "Error opening file\n");
    exit(ERROR_CODE);
  }

  fprintAccount(fptr, acc);

  fclose(fptr);
}

account *readFromFile(char *filepath) {
  FILE *fptr;
  char *buffer = MALLOCATE_ARRAY(char, 20);
  size_t bufferSize = 20;
  char *firstToken, *secondToken;
  char *name = NULL, *date = NULL;
  int number, interest, duration, sum;
  account *account;

  if ((fptr = fopen(filepath, "r")) == NULL) {
    fprintf(stderr, "Error opening file\n");
    exit(ERROR_CODE);
  }

  for (size_t i = 0; i < 3; i++) {
    readLine(&buffer, &bufferSize);
    char *firstToken = strtok(buffer, " \n");
    char *secondToken = strtok(NULL, " \n");

    if (i == 0 && strcmp(firstToken, "Name:") == 0)
      name = secondToken;
    else if (i == 1 && strcmp(firstToken, "Number:") == 0)
      number = atoi(secondToken);
    else if (i == 3 && strcmp(firstToken, "Date:") == 0)
      date = secondToken;
    else {
      fprintf(stderr, "Error parsing\n");
      exit(ERROR_CODE);
    }
  }

  account = initAccount(name, number, date);


  while (readLine(&buffer, &bufferSize)) {
    readLine(&buffer, &bufferSize);
    char *firstToken = strtok(buffer, " \n");
    char *secondToken = strtok(NULL, " \n");

    if (strcmp(firstToken, "Sum:")) {
      sum = atoi(secondToken);
      subAccount *subAccount = initSubAccount(sum);
      int i = 1;

      while (readLine(&buffer, &bufferSize)) {
        char *firstToken = strtok(buffer, " \n");
        char *secondToken = strtok(NULL, " \n");
        if (i % 2 == 1 && strcmp(firstToken, "Procent:"))
          interest = atoi(secondToken);
        else if (i % 2 == 1 && strcmp(firstToken, "Duration:")) {
          duration = atoi(secondToken);
        } else {
          fprintf(stderr, "Error parsing\n");
          exit(ERROR_CODE);
        }

        if (i % 2 == 0) {
          record r = (record){.interest = interest, .duration = duration};
          subAccountAddRecord(subAccount, r);
        }

        i++;
      }

      accountAddSubAccount(account, subAccount);

    } else {
      fprintf(stderr, "Error parsing\n");
      exit(ERROR_CODE);
    }
  }

  fclose(fptr);

  return account;
}

#endif /* ACCOUNTS_UTILS */
