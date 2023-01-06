#include <stdio.h>
#include <string.h>
#include "memalloc.h"
#include "utils/vector.h"

#ifndef ACCOUNTS_UTILS
#define ACCOUNTS_UTILS

#define SUCCESS 0

typedef struct account {
  char *name;
  int idNumber;
  vector *records;
};

typedef struct record {
  int sum;
  int percent;
  int duration;
};


account *initAccount(int idNumber, char *name) {
  account *acc = MALLOCATE(account);
  acc->idNumber = idNumber;
  acc->name = MALLOCATE_ARRAY(char, strlen(name));
  strcpy(acc->name, name);
  return acc;
}

record *initRecord(int sum, int percent, int duration) {
  record *rec = MALLOCATE(record);
  rec->sum = sum;
  rec->percent = percent;
  rec->duration = duration;
  return rec;
}

bool addRecord(account *acc, record rec) {
  record *recPtr = MALLOCATE(record);
  *recPtr = rec;
  return (vectorPushBack(acc->records, recPtr) == SUCCESS);
}

bool saveToFile(account *acc, char *filepath) {
  FILE *fptr;
  if ((fptr = fopen(filepath, "w")) == NULL) {
    fprintf(stderr, "Error opening file\n");
    exit(ERROR_CODE);
  }

  fprintf(fptr, "Name: %s\n", acc->name);
  fprintf(fptr, "Id: %d", acc->idNumber);
  for (size_t i = 0; i < vectorSize(acc->records); i++) {
    record *rec = (record *)vectorGet(acc->records, i);

    fprintf(fptr, "Sum: %d", rec->sum);
    fprintf(fptr, "Percent: %d", rec->percent);
    fprintf(fptr, "Duration: %d", rec->duration);
  }


  fclose(fptr);
}

#endif /* ACCOUNTS_UTILS */
