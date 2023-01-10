#ifndef FILE_UTILS
#define FILE_UTILS

#include <malloc.h>
#include <sys/types.h>

#include <sys/stat.h>

#include <stdbool.h>
#include <err.h>
#include <fts.h>
#include <stdio.h>
#include "../memalloc.h"
#include "../utils/vector.h"
#include "string.h"

bool getFilepaths(char *dirPath, vector *filepaths) {
  FTS *ftsp;
  FTSENT *p, *chp;
  int fts_options = FTS_COMFOLLOW | FTS_LOGICAL | FTS_NOCHDIR;
  char *const path[] = {dirPath, NULL};
  if ((ftsp = fts_open(path, fts_options, NULL)) == NULL) {
    warn("fts_open");
    return false;
  }
  /* Initialize ftsp with as many argv[] parts as possible. */
  chp = fts_children(ftsp, 0);
  if (chp == NULL) {
    return true; /* no files to traverse */
  }
  while ((p = fts_read(ftsp)) != NULL) {
    if (p->fts_info == FTS_F) {
      char *filepath = MALLOCATE_ARRAY(char, strlen(filepath));
      strcpy(filepath, p->fts_path);
      vectorPushBack(filepaths, filepath);
    }
  }
  fts_close(ftsp);
  return true;
}


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


#endif  // FILE_UTILS
