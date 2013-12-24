#include <stdio.h>

int main(int argc, char *argv[])
{
	// go through each string in argv
	char *states[4];
	int i = 0;
	/*while(i < 4)
	{
		states[i] = argv[i];
		i++;
	}
	*/
	*states = argv;

	int j = 0;
	while(j < 4)
	{
		printf("state %d: %s\n", j, states[j]);
		j++;
	}

	return 0;
}
