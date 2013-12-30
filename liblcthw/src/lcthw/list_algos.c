#include <lcthw/dbg.h>
#include <lcthw/list_algos.h>
#include <lcthw/list.h>


int List_bubble_sort(List *list, List_compare cmp)
{
	// Return a good exit status if the list has one or fewer nodes meaning the list is already sorted
	if (list->count <= 1){
		return 0;
	}

	ListNode *a = list->first, *b = list->first->next;
	void *tmp_value;
	int swaps = 0;
	int count = list->count;
	int metric;
	do {
		swaps = 0;
		a = list->first;
		b = a->next;
		int i;
		for (i = 0; i < count - 1; i++) {
			//printf("A value: %s\n", a->value);
			//printf("B value: %s\n", b->value);
			metric = cmp(a->value, b->value);
			if (metric > 0) {
				tmp_value = a->value;
				a->value = b->value;
				b->value = tmp_value;
				swaps++;
			}
			a = a->next;
			b = b->next;
			//fflush(stdout);
		}
		count--;
		//List_print(list);
		//printf("%d\n", swaps);
	} while (swaps);

	return 0;
}


List *List_merge_sort(List *list, List_compare cmp)
{
	fflush(stdout);
	// obviously if the list has one node, then it is sorted
	if (List_count(list) <= 1) {
		return list;
	}

	// Divide the list first, this isn't efficient because of the very nature of the linked list
	int half_count = list->count/2;
	/*
	ListNode *node = list->first;
	int i;
	for (i = 0; i < half_count - 1; i++) {
		node = node->next;
	}
	List *listA = List_create();
	listA->first = list->first;
	listA->last = node;
	listA->count = half_count;
	List *listB = List_create();
	listB->first = node->next;
	listB->last = list->last;
	listB->count = list->count - half_count;
	listA->last->next = NULL;
	*/

	List *listA = List_create();
	List *listB = List_create();
	int count = 0;
	LIST_FOREACH(list, first, next, cur) {
		if (count < half_count) {
			List_push(listA, cur->value);
		} else {
			List_push(listB, cur->value);
		}
		count++;
	}
	
	// Do the recursion now (other algorithms have the recursion at the end)
	List *listA_sorted = List_merge_sort(listA, cmp);
	List *listB_sorted = List_merge_sort(listB, cmp);

	if (listA_sorted != listA) List_destroy(listA);
	if (listB_sorted != listB) List_destroy(listB);

	// At this point listA and listB are sorted and so they can be merged
	/*
	ListNode *nodeA = listA->first;
	ListNode *nodeB = listB->first;
	int metric = cmp(nodeA->value, nodeB->value);
	if (metric <= 0) {
		list->first = nodeA;
		nodeA = nodeA->next;
	} else {
		list->first = nodeB;
		nodeB = nodeB->next;
	}
	node = list->first;
	while (nodeA != NULL && nodeB != NULL) {
		metric = cmp(nodeA->value, nodeB->value);
		if (metric <= 0) {
			node->next = nodeA;
			nodeA->prev = node;
			node = nodeA;
			nodeA = nodeA->next;
		} else {
			node->next = nodeB;
			nodeB->prev = node;
			node = nodeB;
			nodeB = nodeB->next;
		}
	}
	if (nodeA == NULL) {
		node->next = nodeB;
		list->last = listB->last;
	} else if (nodeB == NULL) {
		node->next = nodeA;
		list->last = listA->last;
	}*/

	List *result = List_create();
	void *val = NULL;
	while (List_count(listA_sorted) > 0 || List_count(listB_sorted) > 0) {
		if (List_count(listA_sorted) > 0 && List_count(listB_sorted) > 0) {
			if (cmp(List_first(listA_sorted), List_first(listB_sorted)) > 0) {
				val = List_shift(listB_sorted);
			} else {
				val = List_shift(listA_sorted);
			}
			List_push(result, val);
		} else if (List_count(listA_sorted) > 0) {
			val = List_shift(listA_sorted);
			List_push(result, val);
		} else if (List_count(listB_sorted) > 0) {
			val = List_shift(listB_sorted);
			List_push(result, val);
		}
	}

	List_destroy(listA_sorted);
	List_destroy(listB_sorted);


	return result;
}
