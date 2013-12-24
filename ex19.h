#ifndef _ex19_h
#define _ex19_h

#include "object.h"
#define BUFFER_SIZE 20

/*
 * Creating the Hero "class"
 * The hero has a certain amount of hit points/health and the will do damage based on his attack_power
 * 'Attack' and 'init' functions are modified
 */
struct Hero {
	Object proto;
	char name[BUFFER_SIZE];
	int hit_points;
	int attack_power;
};

typedef struct Hero Hero;

int Hero_attack(void *self, int damage);
int Hero_init(void *self, char *name);

/*
 * Creating the Monster "class"
 * There is an 'attack' and 'init' function which will modify the base functions in 'proto'
 */
struct Monster {
	Object proto;
	int hit_points;
	int attack_power;
};

typedef struct Monster Monster;

int Monster_attack(void *self, int damage);
int Monster_init(void *self);

/*
 * Creating the Room "class" which holds the monster and the hero in it.
 * Each room also has the rooms adjacent to it. If there isn't a room adjacent to it then that is NULL.
 * The Room class modifies the 'move', 'attack', and 'init' functions from the object.c file
 */
struct Room {
	Object proto;
	
	Monster *bad_guy;
	Hero *good_guy;

	struct Room *north;
	struct Room *south;
	struct Room *east;
	struct Room *west;
};

typedef struct Room Room;

void *Room_move(void *self, Direction direction);
int Room_attack(void *self, int damage);
int Room_init(void *self);

/*
 * Creating the Map "class" which holds a few rooms; start is where the hero starts and location is where the hero is, currently.
 * The functions modify the base 'move', 'attack', and 'init' functions from the object.c file
 */
struct Map {
	Object proto;
	Room *start;
	Room *location;
};

typedef struct Map Map;
void *Map_move(void *self, Direction direction);
int Map_attack(void *self, int damage);
int Map_init(void *sefl);

#endif
