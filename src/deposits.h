#include <stdio.h>
#include <string.h>
#include "memalloc.h"
#include "utils/vector.h"

#ifndef ACCOUNTS_UTILS
#define ACCOUNTS_UTILS

#define SUCCESS 0

typedef struct account {
  char *name;
  int number;
  char *date;
  vector *subAccounts;
};

typedef struct subAccount {
  int sum;
  vector *records;
};

typedef struct record {
  int interest;
  int duration;
};


account *initAccount(int number, char *name) {
  account *acc = MALLOCATE(account);
  acc->number = number;
  acc->name = MALLOCATE_ARRAY(char, strlen(name));
  strcpy(acc->name, name);
  return acc;
}

// record *initRecord(int sum, int percent, int duration) {
//   record *rec = MALLOCATE(record);
//   rec->sum = sum;
//   rec->percent = percent;
//   rec->duration = duration;
//   return rec;
// }

// bool addRecord(account *acc, record rec) {
//   record *recPtr = MALLOCATE(record);
//   *recPtr = rec;
//   return (vectorPushBack(acc->records, recPtr) == SUCCESS);
// }

bool saveToFile(account *acc, char *filepath) {
  FILE *fptr;
  if ((fptr = fopen(filepath, "w")) == NULL) {
    fprintf(stderr, "Error opening file\n");
    exit(ERROR_CODE);
  }

  fprintf(fptr, "Name: %s\n", acc->name);
  fprintf(fptr, "Number: %d\n", acc->number);
  fprintf(fptr, "Date: %s\n", acc->date);

  for (size_t i = 0; i < vectorSize(acc->subAccounts); i++) {
    subAccount *subAcc = (subAccount *)vectorGet(acc->subAccounts, i);
    fprintf(fptr, "Sum: %d\n", subAcc->sum);

    for (size_t j = 0; j < vectorSize(subAcc->records); j++) {
      record *rec = (record *)vectorGet(subAcc->records, j);
      fprintf(fptr, "Procent: %d\n", rec->interest);
      fprintf(fptr, "Duration: %d\n", rec->duration);
    }
  }


  fclose(fptr);
}

#endif /* ACCOUNTS_UTILS */
