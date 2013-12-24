#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Let's make an example which shows the difference between pass-by-reference and pass-by-value.
void pass_by_value(int number)
{
	printf("This is the value of the number from the argument: %d\n", number);
	number += 10;
	printf("10 was added to number and now number is \"%d\"\n", number);
}

void pass_by_reference(int *addr)
{
	printf("This is the value of number, which is pointed at by addr: %d\n", *addr);
	*addr += 10;
	printf("This is the value of number, which is pointed at by addr, after 10 was added to it: %d\n", *addr);
}

int main(int argc, char *argv[])
{
	int num = 10;
	int other_num = 10;
	int *ad = &other_num;

	printf("Pass-by-value vs. pass-by-reference\n");

	printf("First pass-by-value will be demonstrated\n");
	printf("The value of num before the function call is %d\n", num);
	pass_by_value(num);
	printf("The value of num after the function call is %d\n", num);

	printf("Next pass-by-reference\n");
	printf("The value pointed at by ad before the function call is %d\n", *ad);
	pass_by_reference(ad);
	printf("The value pointed at by ad after the function call is %d\n", *ad);
	
	return 0;
}
