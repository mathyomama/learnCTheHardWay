#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct Person {
	char *name;
	int age;
	int height;
	int weight;
};

struct Person Person_create(char *name, int age, int height, int weight)
{
	struct Person who;

	who.name = strdup(name);
	who.age = age;
	who.height = height;
	who.weight = weight;

	return who;
}

/*void Person_destroy(struct Person who)
{
	//assert(who != NULL);

	free(who.name);
	free(&who);
}*/

void Person_print(struct Person who)
{
	printf("Name: %s\n", who.name);
	printf("\tAge: %d\n", who.age);
	printf("\tHeight: %d\n", who.height);
	printf("\tWeight: %d\n", who.weight);
}

int main(int argc, char *argv[])
{
	struct Person jasper = Person_create("Jasper Johnson", 42, 70, 140);
	printf("%s is at memory location %p:\n", jasper.name, &jasper);
	Person_print(jasper);
	
//	Person_destroy(jasper);

	return 0;
}
