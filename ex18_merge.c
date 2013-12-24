#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//Our old friend die from ex17.
void die(const char *message)
{
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	exit(1);
}

/* a typedef creates a fake type, in this
 * case for a function point */
typedef int (*compare_cb)(int a, int b);
typedef int *(*algorthm)(int *numbers, int count, compare_cb cmp);

/*
 * A classic bubble sort function that uses the
 * compare_cb to do the sorting.*/
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
	int temp = 0;
	int i = 0;
	int j = 0;
	int *target = malloc(count*sizeof(int));
	if (!target) die("Memory error.");

	memcpy(target, numbers, count*sizeof(int));

	for (i = 0; i < count; i++){
		for (j = 0; j < count -1; j++){
			if (cmp(target[j], target[j + 1]) > 0){
				temp = target[j + 1];
				target[j + 1] = target[j];
				target[j] = temp;
			}
		}
	}

	return target;
}

int *merge_sort(int *numbers, int count, compare_cb cmp)
{
	if (count == 1){
		return numbers;
	}
	int middle = count/2;
	int *new_list_a = merge_sort(numbers, middle, cmp);
	int *new_list_b = merge_sort(&numbers[middle], count - middle, cmp);

	//Time to merge lists
	int *new_numbers = malloc(count*sizeof(int));
	if (!new_numbers) die("Memory error.");
	int a_counter = 0;
	int b_counter = 0;
	int counter = a_counter + b_counter;
	//printf("Starting the merging process\n");
	while (counter < count){
		if (cmp(new_list_a[a_counter], new_list_b[b_counter]) <= 0){
			new_numbers[counter++] = new_list_a[a_counter++];
			if (a_counter == middle){
				int i;
				for (i = 0; i < count - middle - b_counter; i++){
					new_numbers[counter + i] = new_list_b[b_counter + i];
				}
				/*
				printf("The rest of the new_list_b\n");
				for (i = b_counter; i < count - middle; i++){
					printf("%d ", new_list_b[i]);
				}
				printf("\n");
				*/
				break;
			}
		} else {
			new_numbers[counter++] = new_list_b[b_counter++];
			if (b_counter == count - middle){
				int i;
				for (i = 0; i < middle - a_counter; i++){
					new_numbers[counter + i] = new_list_a[a_counter + i];
				}
				/*
				printf("The rest of the new_list_a\n");
				for (i = a_counter; i < middle; i++){
					printf("%d ", new_list_a[i]);
				}
				printf("\n");
				*/
				break;
			}
		}
	}
	/*
	printf("The rearranged list: ");
	int i;
	for (i = 0; i < count; i++){
		printf("%d ", new_numbers[i]);
	}
	printf("\n");
	*/
	return new_numbers;
}

int sorted_order(int a, int b)
{
	return a - b;
}

int reverse_order(int a, int b)
{
	return b - a;
}

int strange_order(int a, int b)
{
	if (a == 0 || b ==0){
		return 0;
	} else {
		return a%b;
	}
}

/*
 * Used to test that we are sorting things correctly
 * by doning the sort and printing it out.
 */
void test_sorting(int *numbers, int count, algorthm alg, compare_cb cmp)
{
	int i = 0;
	int *sorted = alg(numbers, count, cmp);

	if (!sorted) die("Failed to sort as requested.");
	printf("The sorted list: ");
	for (i = 0; i < count; i++){
		printf("%d ", sorted[i]);
	}
	printf("\n");

	free(sorted);

	/*
	unsigned char *data =  (unsigned char *)cmp;

	for (i = 0; i < 50; i++){
		printf("%02x:", data[i]);
	}

	printf("\n");
	*/
}

int main(int argc, char *argv[])
{
	if (argc < 2) die("USAGE: ex18 4 3 1 5 6");

	int count = argc - 1;
	int i = 0;
	char **inputs = argv + 1;

	int *numbers = malloc(count*sizeof(int));
	if (!numbers) die("Memory error.");

	for (i = 0; i < count; i++){
		numbers[i] = atoi(inputs[i]);
	}
	
	test_sorting(numbers, count, merge_sort, sorted_order);
	test_sorting(numbers, count, bubble_sort, sorted_order);
	test_sorting(numbers, count, merge_sort, reverse_order);
	test_sorting(numbers, count, bubble_sort, reverse_order);

	free(numbers);

	return 0;
}
