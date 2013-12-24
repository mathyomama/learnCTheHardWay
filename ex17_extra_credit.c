#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>

/*
#define MAX_DATA 512
#define MAX_ROWS 100
*/

struct Address {
	int id;
	int set;
	char *name;
	char *email;
};

struct Database {
	int max_data;
	int max_rows;
	struct Address *rows;
};

struct Connection {
	FILE *file;
	struct Database *db;
};

void Database_close(struct Connection *conn);

void die(const char *message, struct Connection *conn)
{
	if (errno) {
		perror(message);
	} else {
		printf("Error: %s\n", message);
	}

	Database_close(conn);

	exit(1);
}

void Address_print(struct Address *addr)
{
	printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
	int rc = fread(&conn->db->max_data, sizeof(int), 1, conn->file);
	if (rc != 1) die("Failed to load max_data.", conn);
	rc = fread(&conn->db->max_rows, sizeof(int), 1, conn->file);
	if (rc != 1) die("Failed to load max_rows.", conn);
	int i;
	for (i = 0; i <= conn->db->max_rows; i++){
		rc = fread(&conn->db->rows[i], sizeof(struct Address), 1, conn->file);
		if (rc != 1) die("Failed to load database.", conn);
	}
	/*
	rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	if (rc != 1) die("Failed to load database.", conn);
	*/
}

struct Connection *Database_open(const char *filename, char mode)
{
	struct Connection *conn = malloc(sizeof(struct Connection));
	if (!conn) die("Memory error: conn.", conn);

	conn->db = malloc(sizeof(struct Database));
	if (!conn->db) die("Memory error: db.", conn);

	if (mode == 'c'){
		conn->file = fopen(filename, "w");
	} else {
		conn->file = fopen(filename, "r+");

		if (conn->file){
			Database_load(conn);
		}
	}

	if (!conn->file) die("Failed to open the file.", conn);

	return conn;
}

void Database_close(struct Connection *conn)
{
	if (conn){
		if (conn->file) fclose(conn->file);
		if (conn->db) free(conn->db);
		free(conn);
	}
}

void Database_write(struct Connection *conn)
{
	rewind(conn->file);

	int rc = fwrite(&conn->db->max_data, sizeof(int), 1, conn->file);
	if (rc != 1) die("Failed to write max_data.", conn);
	rc = fwrite(&conn->db->max_rows, sizeof(int), 1, conn->file);
	if (rc != 1) die("Failed to write max_rows.", conn);
	int i;
	for (i = 0; i <= conn->db->max_rows; i++){
		rc = fwrite(&conn->db->rows[i], sizeof(struct Address), 1, conn->file);
		if (rc != 1) die("Failed to write database", conn);
	}
	/*
	rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	if (rc != 1) die("Failed to write database.", conn);
	*/

	rc = fflush(conn->file);
	if (rc == -1) die("Cannot flush database.", conn);
}

void Database_create(struct Connection *conn, int max_data, int max_rows)
{
	int i = 0;
	conn->db->max_data = max_data;
	conn->db->max_rows = max_rows;
	conn->db->rows = malloc(max_rows);
	if (!conn->db->rows) die("Memory error: rows.", conn);

	for (i = 0; i < max_rows; i++){
		//make a prototype to initialize it
		struct Address addr = {.id = i, .set = 0};
		addr.name = malloc(max_data);
		if (!addr.name) die("Memory error: addr.name.", conn);
		addr.email = malloc(max_data);
		if (!addr.email) die("Memory error: addr.email.", conn);
		// then just assign it
		conn->db->rows[i] = addr;
	}
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
	struct Address *addr = &conn->db->rows[id];
	int max_data = conn->db->max_data;
	if (addr->set) die("Already set, delete it first", conn);

	addr->set = 1;
	// Warning: bug, read the "How to Break It" and fix this
	char *res = strncpy(addr->name, name, max_data);
	if (max_data > 0){
		addr->name[max_data - 1] = '\0';
	}
	// demonstrate the strncpy bug
	if (!res) die("Name copy failed", conn);

	res = strncpy(addr->email, email, max_data);
	if (max_data > 0){
		addr->email[max_data - 1] = '\0';
	}
	if (!res) die("Email copy failed", conn);
}

void Database_get(struct Connection *conn, int id)
{
	struct Address *addr = &conn->db->rows[id];

	if (addr->set){
		Address_print(addr);
	} else {
		die("ID is not set", conn);
	}
}

void Database_delete(struct Connection *conn, int id)
{
	struct Address addr = {.id = id, .set = 0};
	conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
	int i = 0;
	struct Database *db = conn->db;
	int max_rows = conn->db->max_rows;

	for (i = 0; i < max_rows; i++){
		struct Address *cur = &db->rows[i];

		if (cur->set){
			Address_print(cur);
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc < 3){// die("USAGE: ex17 <dbfile> <action> [action params]");
		if (errno){
			perror("USAGE: ex17 <dbfile> <action> [action params]");
		} else {
			printf("Error: USAGE: ex17 <dbfile> <action> [action params]\n");
		}
		exit(1);
	}

	char *filename = argv[1];
	char action = argv[2][0];
	struct Connection *conn = Database_open(filename, action);
	int id = 0;

	if (argc > 3 && action != 'c'){
	       id = atoi(argv[3]);
	       if (id >= conn->db->max_rows) die("There aren't that many records.", conn);
	}

	switch (action){
		case 'c':
			Database_create(conn, atoi(argv[3]), atoi(argv[4]));
			Database_write(conn);
			break;

		case 'g':
			if (argc != 4) die("Need an id to get", conn);

			Database_get(conn, id);
			break;

		case 's':
			if (argc != 6) die("Need id, name, email to set", conn);

			Database_set(conn, id, argv[4], argv[5]);
			Database_write(conn);
			break;

		case 'd':
			if (argc != 4) die("Need id to delete", conn);

			Database_delete(conn, id);
			Database_write(conn);
			break;

		case 'l':
			Database_list(conn);
			break;

		default:
			die("Invalid action, only c=create, g=get, s=set, d=del, l=list", conn);
	}

	Database_close(conn);
	
	return 0;
}
