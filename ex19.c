#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ex19.h"

int Hero_attack(void *self, int damage)
{
	Hero *hero = self;

	printf("The monster attacks %s", hero->name);

	hero->hit_points -= damage;
	printf("The monster hit you for %d hp.\n", damage);

	if (hero->hit_points > 0){
		printf("%s is still alive with %d hp.\n", hero->name, hero->hit_points);
		return 0;
	} else {
		printf("The great hero, %s, has been slain.\n", hero->name);
		printf("Good-bye");
		return 1;
	}
}

int Hero_init(void *self, char *name)
{
	Hero *hero = self;
	hero->hit_points = 20;
	hero->attack_power = 1;

	int tries = 3;
	int count;
	printf("You have three shots at this.\n");
	for (count = 0; count < tries; count++) {
		printf("Please enter the hero's name: ");
		int result = scanf("%s", hero->name);
		if (result == 1){
			printf("To confirm, the hero's name is %s, y or n?", hero->name);
			char ch = getchar();
			getchar();
			if (ch == y) {
				printf("Thank you.\n");
				break;
			} else if (ch == no) {
				continue;
			} else {
				printf("Don't give me that bs. Re-enter the hero's name.");
			}
		} else {
			printf("Wasn't able to get input, try again.");
		}
	}

	if (count == tries) {
		hero->name = "Johnny";
		printf("You couldn't decide in %d tries so now the hero's name is \"%s\".", tries, hero->name);
	}

	return 1;
}

Object HeroProto = {
	.init = Hero_init,
	.attack = Hero_attack
};
	

int Monster_attack(void *self, int damage)
{
	Monster *monster = self;

	printf("You attack %s!\n", monster->_(description));

	monster->hit_points -= damage;

	if (monster->hit_points > 0){
		printf("You hit the monster for %d hp.\n", damage);
		printf("It is still alive with %d hp.\n", monster->hit_points);
		return 0;
	} else {
		printf("It is dead!\n");
		return 1;
	}
}

int Monster_init(void *self)
{
	Monster *monster = self;
	monster->hit_points = 10;
	monster->attack_power = 1;
	return 1;
}

Object MonsterProto = {
	.init = Monster_init,
	.attack = Monster_attack
};

void *Room_move(void *self, Direction direction)
{
	Room *room = self;
	Room *next = NULL;

	if (direction == NORTH &&room->north){
		printf("You go north, into:\n");
		next = room->north;
	} else if (direction == SOUTH && room->south){
		printf("You go south, into:\n");
		next = room->south;
	} else if (direction == EAST && room->east){
		printf("You go east, into:\n");
		next = room->east;
	} else if (direction == WEST && room->west){
		printf("You go west, into:\n");
		next = room->west;
	} else {
		printf("You can't go that direstion.");
		next = NULL;
	}

	if (next) {
		next->_(describe)(next);
	}

	return next;
}


int Room_attack(void *self, int damage)
{
	Room *room = self;
	Hero *hero = room->good_guy;
	Monster *monster = room->bad_guy;

	if (monster){
		monster->_(attack)(monster, damage);
		hero->_(attack)(hero, damage);
		return 1;
	} else {
		printf("You flail in the air at nothing. Idiot.\n");
		return 0;
	}
}


Object RoomProto = {
	.move = Room_move,
	.attack = Room_attack
};

void *Map_move(void *self, Direction direction)
{
	Map *map = self;
	Room *location = map->location;
	Room *next = NULL;

	next = location->_(move)(location, direction);

	if (next){
		map->location = next;
	}
	
	return next;
}

int Map_attack(void *self, int damage)
{
	Map *map = self;
	Room *location = map->location;

	return location->_(attack)(location, damage);
}


int Map_init(void *self)
{
	Map *map = self;

	//make some rooms for a small map
	Room *hall = NEW(Room, "The great hall");
	Room *throne = NEW(Room, "The throne room");
	Room *arena = NEW(Room, "The arena with the minotaur");
	Room *kitchen = NEW(Room, "Kitchen, you have the knife now");

	// put the bad guy in the arena
	arena->bad_guy = NEW(Monster, "The evil minotaur");

	//setup the map rooms
	hall->north = throne;

	throne->west = arena;
	throne->east = kitchen;
	throne->south = hall;

	arena->east = throne;
	kitchen->west = throne;

	// start the map and the character off in the hall
	map->start = hall;
	map->location = hall;
	
	return 1;
}

Object MapProto = {
	.init = Map_init,
	.move = Map_move,
	.attack = Map_attack
};

int process_input(Map *game)
{
	printf("\n> ");

	char ch = getchar();
	getchar(); // eat ENTER

	int damage = rand() % 4;

	switch(ch) {
		case -1:
			printf("Giving up? You suck.\n");
			return 0;
			break;

		case 'n':
			game->_(move)(game, NORTH);
			break;

		case 's':
			game->_(move)(game, SOUTH);
			break;

		case 'e':
			game->_(move)(game, EAST);
			break;

		case 'w':
			game->_(move)(game, WEST);
			break;

		case 'a':
			game->_(attack)(game, damage);
			break;

		case 'l':
			printf("You can go:\n");
			if (game->location->north) printf("NORTH\n");
			if (game->location->south) printf("SOUTH\n");
			if (game->location->east) printf("EAST\n");
			if (game->location->west) printf("WEST\n");
			break;

		default:
			printf("What?: %d\n", ch);
	}

	return 1;
}

int main(int argc, char *argv[])
{
	// simple way to setup the randomness
	srand(time(NULL));

	//make our map to work with
	Map *game = NEW(Map, "The Hall of the Minotaur.");

	printf("You enter the ");
	game->location->_(describe)(game->location);

	while (process_input(game)){
	}

	return 0;
}
