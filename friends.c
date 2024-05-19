#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "friends.h"
#include "users.h"

void add_friend(int ***matrix, char *name)
{
	name = strtok(NULL, "\n ");
	int ind1 = get_user_id(name);
	name = strtok(NULL, "\n ");
	int ind2 = get_user_id(name);
	(*matrix)[ind1][ind2] = 1;
	(*matrix)[ind2][ind1] = 1;
	printf("Added connection %s - %s\n", get_user_name(ind1), get_user_name(ind2));
}

void remove_friend(int ***matrix, char *name)
{
	name = strtok(NULL, "\n ");
	int ind1 = get_user_id(name);
	name = strtok(NULL, "\n ");
	int ind2 = get_user_id(name);
	(*matrix)[ind1][ind2] = 0;
	(*matrix)[ind2][ind1] = 0;
	printf("Removed connection %s - %s\n", get_user_name(ind1), get_user_name(ind2));
}

void handle_input_friends(char *input, int ***matrix)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;
	if (!strcmp(cmd, "add"))
		add_friend(matrix, cmd);
	else if (!strcmp(cmd, "remove"))
		remove_friend(matrix, cmd);
	else if (!strcmp(cmd, "suggestions")) {
	}
	else if (!strcmp(cmd, "distance")) {
	}
	else if (!strcmp(cmd, "common")) {
	}
	else if (!strcmp(cmd, "friends")){
	}
	else if (!strcmp(cmd, "popular")) {
	}
	free(commands);
}
