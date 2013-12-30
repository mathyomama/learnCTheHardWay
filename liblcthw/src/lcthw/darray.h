#ifndef _DArray_h
#define _DArray_h
#include <stdlib.h>
#include <assert.h>
#include <lcthw/dbg.h>

/*
 * end is the last element in contents; end is the index after the last element (i.e. the length of the array).
 * max is the maximum size of memory allocated in content. This will increase/decrease when expand/contract is called.
 * element_size is the size of each block of data used to store each element
 * expand_rate is how much elements the contents grows and shrinks by during expansion and contraction
 * contents holds the data (double pointer since it's an array)
 */
typedef struct DArray {
	int end;
	int max;
	size_t element_size;
	size_t expand_rate;
	void **contents;
} DArray;

DArray *DArray_create(size_t element_size, size_t initial_max);

void DArray_destroy(DArray *array);

void DArray_clear(DArray *array);

int DArray_expand(DArray *array);

int DArray_contract(DArray *array);

int DArray_push(DArray *array, void *el);

void *DArray_pop(DArray *array);

void DArray_clear_destroy(DArray *array);

#define DArray_last(A) ((A)->contents[(A)->end - 1])
#define DArray_first(A) ((A)->contents[0])
#define DArray_end(A) ((A)->end)
#define DArray_count(A) DArray_end(A)
#define DArray_max(A) ((A)->max)

#define DEFAULT_EXPAND_RATE 300

static inline void DArray_set(DArray *array, int i, void *el)
{
	check(i < array->max, "darray attempt set to past max.");
	if (i > array->end) array->end = i;
	array->contents[i] = el;
error:
	return;
}

static inline void *DArray_get(DArray *array, int i)
{
	check( i < array->max, "darray attempt to get past max.");
	return array->contents[i];
error:
	return NULL;
}

static inline void *DArray_remove(DArray *array, int i)
{
	void *el = array->contents[i];

	array->contents[i] = NULL;

	return el;
}

static inline void *DArray_new(DArray *array)
{
	check(array->element_size > 0, "Can't use DArray_new on 0 size array.");

	return calloc(1, array->element_size);

error:
	return NULL;
}

#define DArray_free(E) free((E))

#endif
