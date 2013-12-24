#ifndef list_algos_h
#define list_algos_h
#include <lcthw/list.h>


// This creates a function pointer which will compare node values
typedef int (*List_compare)(const void *a, const void *b);


// Declaring the bubble sort which accepts parameters List and List_compare; returns exiting code
int List_bubble_sort(List *list, List_compare cmp);

// Declaring the merge sort which accepts parameters List and List_compare; returns exiting code
List *List_merge_sort(List *list, List_compare cmp);


#endif
