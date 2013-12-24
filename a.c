#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define MAX_DATA 100


char *itoa(int input)
{
	char out_string[MAX_DATA];
	char *digits = "0123456789";
	int i;
	for (i = 0; input > 0; i++){
		int j;
		for (j = 0; j < strlen(digits); j++){
			if (input%10 == j){
				out_string[i] = digits[j];
				break;
			}
		}
		input /= 10;
	}

	return out_string;
}

int reverse_string(char **in_string, char **out_string)
{
	*out_string = calloc(1, MAX_DATA);
	int i;
	for (i = 0; string[i] != '\0'; i++){
	}
	int j;
	for (j = 0; j < i; j++){
		out_string[j] = string[i - j];
	}
}

int main(int argc, char *argv[])
{
	int a = 25;
	char *a_string = &reverse_string(itoa(a));
	printf("This is the int a: %d\nAnd this is the char * a: %s\n", a, a_string);

	return 0;
}
