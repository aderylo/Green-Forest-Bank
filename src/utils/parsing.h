#ifndef ACCOUNT_PARSING
#define ACCOUNT_PARSING

#include <malloc.h>
#include "../memalloc.h"


bool readLine(char **buffer, size_t *bufferSize) {
  int character;
  unsigned int pos = 0;

  while ((character = fgetc(stdin)) != '\n' && character != EOF) {
    if (pos + 1 >= *bufferSize) {
      *bufferSize *= 2;
      *buffer = MREALLOCATE_ARRAY(char, *bufferSize, *buffer);
    }

    (*buffer)[pos++] = (char)character;
  }

  // The '\n' or eof is removed and replaced with a null termination.
  (*buffer)[pos] = '\0';

  return character != EOF;
}


#endif  // ACCOUNT_PARSING
