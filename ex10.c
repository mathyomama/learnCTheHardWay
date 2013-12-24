#include <stdio.h>

int main(int argc, char *argv[])
{
	int i = 0;

	//go through each string in argv
	//why am I skipping argv[0]?
	for(i = 1; i < argc; i++)
	{
		printf("arg %d: %s\n", i, argv[i]);
	}

	// let's make our own array of strings
	char *states[] = {
		"California",
		"Oregon",
		"Washington",
		"Texas"
	};
	argv = states;
	int num_states = 4;
	int j;

	for(i = 0, j = 10; i < num_states; i++, j>>=1)
	{
		printf("j = %d, state %d: %s\n", j, i, states[i]);
	}

	for(i = 0; i < num_states; i++)
	{
		printf("fake state %d: %s\n", i, argv[i]);
	}

	return 0;
}
