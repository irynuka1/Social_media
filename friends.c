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
	printf("Added connection %s - %s\n", get_user_name(ind1),
		   get_user_name(ind2));
}

void remove_friend(int ***matrix, char *name)
{
	name = strtok(NULL, "\n ");
	int ind1 = get_user_id(name);
	name = strtok(NULL, "\n ");
	int ind2 = get_user_id(name);
	(*matrix)[ind1][ind2] = 0;
	(*matrix)[ind2][ind1] = 0;
	printf("Removed connection %s - %s\n", get_user_name(ind1),
		   get_user_name(ind2));
}

void suggestions(int ***matrix, char *name)
{
	name = strtok(NULL, "\n ");
	int ind = get_user_id(name);
	int *suggestions = (int *)calloc(MAX_PEOPLE, sizeof(int));
	int suggestions_len = 0;

	for (int i = 0; i < MAX_PEOPLE; i++) {
		if ((*matrix)[ind][i] == 1) {
			for (int j = 0; j < MAX_PEOPLE; j++) {
				if ((*matrix)[i][j] == 1 && (*matrix)[ind][j] == 0 &&
					j != ind) {
					int found = 0;
					for (int k = 0; k < suggestions_len; k++) {
						if (suggestions[k] == j) {
							found = 1;
							break;
						}
					}
					if (!found) {
						suggestions[suggestions_len++] = j;
					}
				}
			}
		}
	}

	if (suggestions_len == 0) {
		printf("There are no suggestions for %s\n", get_user_name(ind));
	} else {
		printf("Suggestions for %s:\n", get_user_name(ind));
		for (int i = 0; i < suggestions_len; i++)
			printf("%s\n", get_user_name(suggestions[i]));
	}

	free(suggestions);
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
	else if (!strcmp(cmd, "suggestions"))
		suggestions(matrix, cmd);

	free(commands);
}
