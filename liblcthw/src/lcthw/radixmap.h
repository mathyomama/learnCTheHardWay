#ifndef _radixmap_h
#define _radixmap_h
#include <stdint.h>

typedef union RMElement {
	uint64_t raw;
	struct {
		uint32_t key;
		uint32_t value;
	} data;
} RMElement;

/*
 * max = the size of memory allocated to contents
 * end = the last index in contents
 * counter = unsigned int of 4 bytes which keeps track of 
 * contents = data
 * temp = temporary data
 */
typedef struct RadixMap {
	size_t max;
	size_t end;
	uint32_t counter;
	RMElement *contents;
	RMElement *temp;
} RadixMap;

RadixMap *RadixMap_create(size_t max);

void RadixMap_destroy(RadixMap *map);

void RadixMap_sort(RadixMap *map);

RMElement *RadixMap_find(RadixMap *map, uint32_t key);

int RadixMap_add(RadixMap *map, uint32_t key, uint32_t value);

int RadixMap_delete(RadixMap *map, RMElement *el);

#endif
