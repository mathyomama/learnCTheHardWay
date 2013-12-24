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
		int i;
		for (i = 0; i < count - 1; i++) {
			metric = cmp(a->value, b->value);
			if (metric > 0) {
				tmp_value = a->value;
				a->value = b->value;
				b->value = tmp_value;
				swaps++;
			}
			a = a->next;
			b = b->next;
		}
		count--;
		List_print(list);
		printf("%d\n", swaps);
	} while (swaps);

	return 0;
}


List *List_merge_sort(List *list, List_compare cmp)
{
	// obviously if the list has one node, then it is sorted
	if (list->count <= 1) {
		return 0;
	}

	// Divide the list first, this isn't efficient because of the very nature of the linked list
	int half_count = list->count/2;
	ListNode *node = list->first;
	int i;
	for (i = 0; i < half_count; i++) {
		node = node->next;
	}
	List *listA = NULL;
	listA->first = list->first;
	listA->last = node;
	listA->count = half_count;
	List *listB = NULL;
	listB->first = node->next;
	listB->last = list->last;
	listB->count = list->count - half_count;
	
	// Do the recursion now (other algorithms have the recursion at the end)
	listA = List_merge_sort(listA, cmp);
	listB = List_merge_sort(listB, cmp);

	// At this point listA and listB are sorted and so they can be merged
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
			nodeB->prev =node;
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
	}

	return list;
}
