#include "vector.h"
#include <stdlib.h>
#include <string.h>

#define VECTOR_INIT_CAPACITY 6

struct vector {
  void **items;
  size_t capacity;
  size_t total;
};

/*
 * Stwórz pusty wektor.
 */
vector *vectorInit() {
  vector *v = (vector *)malloc(sizeof(vector));
  if (v) {
    v->capacity = VECTOR_INIT_CAPACITY;
    v->total = 0;
    v->items = malloc(sizeof(void *) * v->capacity);
    if (!v->items) {
      free(v);
      return NULL;
    }
  }
  return v;
}

/*
 * Zmień pojemność wektora.
 */
int vectorResize(vector *v, int capacity) {
  int status = UNDEFINE;
  if (v) {
    void **items = realloc(v->items, sizeof(void *) * capacity);
    if (items) {
      v->items = items;
      v->capacity = capacity;
      status = SUCCESS;
    }
  }
  return status;
}

/*
 * Zmień wartość pod dannym indeksem.
 */
int vectorSet(vector *v, size_t index, void *item) {
  int status = UNDEFINE;
  if (v) {
    if (index < v->total) {
      v->items[index] = item;
      status = SUCCESS;
    }
  }
  return status;
}

/*
 * Ile elementów przechowywuje obecnie wektor.
 */
size_t vectorSize(vector *v) {
  return v->total;
}

/*
 * Dodaj na koniec element.
 */
int vectorPushBack(vector *v, void *item) {
  int status = UNDEFINE;
  if (v) {
    if (v->capacity == v->total) {
      status = vectorResize(v, v->capacity * 2);
      if (status != UNDEFINE) {
        v->items[v->total++] = item;
      }
    } else {
      v->items[v->total++] = item;
      status = SUCCESS;
    }
  }
  return status;
}

/*
 * Daj wskaznik na elemnet pod dannym indeksem.
 */
void *vectorGet(vector *v, size_t index) {
  void *readData = NULL;
  if (v) {
    if (index < v->total) {
      readData = v->items[index];
    }
  }
  return readData;
}

/*
 * Usuń element z wektora.
 */
int vectorRemove(vector *v, size_t index) {
  int status = UNDEFINE;
  size_t i = 0;
  if (v) {
    if (index >= v->total)
      return status;
    v->items[index] = NULL;
    for (i = index; (i < v->total - 1); ++i) {
      v->items[i] = v->items[i + 1];
      v->items[i + 1] = NULL;
    }
    v->total--;
    if ((v->total > 0) && ((v->total) == (v->capacity / 4))) {
      vectorResize(v, v->capacity / 2);
    }
    status = SUCCESS;
  }
  return status;
}

/*
 * Zwolnij pamięc po strukturze.
 */
int vectorFree(vector *v) {
  int status = UNDEFINE;
  if (v) {
    free(v->items);
    v->items = NULL;
    free(v);
    status = SUCCESS;
  }
  return status;
}

void **vectorBegin(vector *v) {
  return v->items;
}

int vectorPurge(vector *v, void (*destructor)(void *)) {
  int status = UNDEFINE;
  for (size_t i = 0; i < vectorSize(v); ++i)
    destructor((void *)vectorGet(v, i));

  status = vectorFree(v);
  return status;
}

static char *c_string(char *string) {
  char *c_string = calloc(strlen(string) + 1, sizeof(char));
  strcpy(c_string, string);
  return c_string;
}

vector *strToVec(char *string, char *whitespace) {
  char *copy = calloc(strlen(string) + 1, sizeof(char));
  vector *v = vectorInit();
  char *token;

  strcpy(copy, string);
  token = strtok(copy, whitespace);
  if (token)
    vectorPushBack(v, c_string(token));

  while ((token = strtok(0, whitespace)))
    vectorPushBack(v, c_string(token));

  free(copy);
  copy = NULL;

  return v;
}
