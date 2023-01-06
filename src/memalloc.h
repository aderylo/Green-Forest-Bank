
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>

#ifndef __STY_COMMON_MEMALLOC_H__
#define __STY_COMMON_MEMALLOC_H__

#define ERROR_CODE 1

#define CHECK(f)         \
  do {               \
    if ((f) != true) \
      return false;   \
  } while (0)

#define max(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define RET_NULL_IF_NULL(ptr) \
if (ptr == NULL) return NULL;

#define RET_FALSE_IF_NULL(ptr) \
if (ptr == NULL) return false;
/**
* @def freeIfNotNull(STRUCT)
*
* Macro freeing pointer if it's not NULL;
*
* @param[in] ptr : pointer to be freed
*/
#define freeIfNotNull(ptr) \
if(ptr != NULL) {          \
free(ptr);                 \
ptr = NULL;                \
}

/**
* @def MALLOCATE(STRUCT)
*
* Macro giving value of pointer to the allocated structure @p STRUCT
*
* NOTICE: Assertion checking is done for allocation errors.
*
* @param[in] STRUCT : Type to be allocated
*/
#define MALLOCATE(STRUCT) \
( (STRUCT*) AllocateMemoryBlock(sizeof(STRUCT)) )

/**
* @def MALLOCATE_ARRAY(STRUCT, LEN)
*
* Macro giving value of pointer to the allocated array of size @p LEN
* of structures @p STRUCT
*
* NOTICE: Assertion checking is done for allocation errors.
*
* @param[in] STRUCT : Type to be allocated
* @param[in] LEN    : Length of array to be allocated
*/
#define MALLOCATE_ARRAY(STRUCT, LEN) \
( (STRUCT*) AllocateMemoryBlockArray((LEN), sizeof(STRUCT)) )

/**
* @def MREALLOCATE(STRUCT, PTR)
*
* Macro giving value of pointer to the reallocated structure @p STRUCT
*
* NOTICE: Assertion checking is done for allocation errors.
*
* @param[in] STRUCT : Type to be allocated
* @param[in] PTR    : Pointer to currently allocated structure
*/
#define MREALLOCATE(STRUCT, PTR) \
( (STRUCT*) ReallocateMemoryBlock((PTR), sizeof(STRUCT)) )

/**
* @def MREALLOCATE_ARRAY(STRUCT, LEN, PTR)
*
* Macro giving value of pointer to the reallocated array of size @p LEN
* of structures @p STRUCT
*
* NOTICE: Assertion checking is done for allocation errors.
*
* @param[in] STRUCT : Type to be allocated
* @param[in] LEN    : Length of new array
* @param[in] PTR    : Pointer to currently allocated structure array
*/
#define MREALLOCATE_ARRAY(STRUCT, LEN, PTR) \
( (STRUCT*) ReallocateMemoryBlockArray((STRUCT*)(PTR), (LEN), sizeof(STRUCT)) )

/**
* @def MALLOCATE_BLOCKS(SIZE, LEN)
*
* Macro giving value of pointer to the allocated array of size @p LEN
* of blocks of size @p SIZE bytes
*
* NOTICE: Assertion checking is done for allocation errors.
*
* @param[in] BLOCK_SIZE : Length of single block in bytes
* @param[in] LEN        : Length of array to be allocated
*/
#define MALLOCATE_BLOCKS(BLOCK_SIZE, LEN) \
( (void*) AllocateMemoryBlockArray((LEN), (BLOCK_SIZE)) )

/** As defined, function handles any memory allocation issues
 * by finishing program with status 1 and relevant error message.
 */
static inline void CheckForMemoryAllocationError(void *ptr) {
    if (ptr == NULL || errno == ENOMEM) {
        fprintf(stderr, "ERROR 0\n");
        exit(ERROR_CODE);
    }
}

/**
* Function allocating @p size bytes.
*
* NOTICE: Assertion checking is done for allocation errors.
*
* @param[in] size : size_t
* @return void* to allocated memory block
*/
static inline void *AllocateMemoryBlock(size_t size) {
    assert(size > 0);

    void *data = malloc(size);
    CheckForMemoryAllocationError(data);

    return data;
}

/**
* Function reallocating @p size bytes.
*
* NOTICE: Assertion checking is done for allocation errors.
*
* @param[in] p    : reused void* pointer
* @param[in] size : size_t
* @return void* to allocated memory block
*/
static inline void *ReallocateMemoryBlock(void *p, size_t size) {
    if (p == NULL) return AllocateMemoryBlock(size);
    assert(size > 0);

    void *data = realloc(p, size);

    return data;
}

/**
* Function allocating @p count block each of size @p size bytes.
*
* NOTICE: Assertion checking is done for allocation errors.
*
* @param[in] count : size_t
* @param[in] size  : size_t
* @return void* to allocated memory array
*/
static inline void *AllocateMemoryBlockArray(size_t count, size_t size) {
    assert(count > 0);
    assert(size > 0);

    void *data = calloc(count, size);
    CheckForMemoryAllocationError(data);

    return data;
}

/**
* Function reallocating @p count block each of size @p size bytes.
*
* NOTICE: Assertion checking is done for allocation errors.
*
* @param[in] p     : reused void* pointer
* @param[in] count : size_t
* @param[in] size  : size_t
* @return void* to allocated memory array
*/
static inline void *ReallocateMemoryBlockArray(void *p, size_t count, size_t size) {
    if (p == NULL) return AllocateMemoryBlockArray(count, size);
    assert(count > 0);
    assert(size > 0);

    void *data = realloc(p, count * size);
    CheckForMemoryAllocationError(data);

    return data;
}

#endif /* __STY_COMMON_MEMALLOC_H__ */