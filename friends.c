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
					if (!found)
						suggestions[suggestions_len++] = j;
				}
			}
		}
	}

	// Sort the suggestions vector
	for (int i = 0; i < suggestions_len - 1; i++)
		for (int j = i + 1; j < suggestions_len; j++)
			if (suggestions[i] > suggestions[j]) {
				int aux = suggestions[i];
				suggestions[i] = suggestions[j];
				suggestions[j] = aux;
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

void distance(int ***matrix, char *name)
{
	name = strtok(NULL, "\n ");
	int ind1 = get_user_id(name);
	name = strtok(NULL, "\n ");
	int ind2 = get_user_id(name);

	int *visited = calloc(MAX_PEOPLE, sizeof(int));
	int *queue = malloc(MAX_PEOPLE * sizeof(int));
	int *dist = malloc(MAX_PEOPLE * sizeof(int));
	int front = 0, rear = 0;
	for (int i = 0; i < MAX_PEOPLE; i++)
		dist[i] = -1;

	queue[rear++] = ind1;
	visited[ind1] = 1;
	dist[ind1] = 0;

	while (front < rear) {
		int current = queue[front++];
		for (int i = 0; i < MAX_PEOPLE; i++)
			if ((*matrix)[current][i] && !visited[i]) {
				visited[i] = 1;
				dist[i] = dist[current] + 1;
				queue[rear++] = i;
			}
	}

	char *name1 = get_user_name(ind1);
	char *name2 = get_user_name(ind2);

	if (dist[ind2] == -1)
		printf("There is no way to get from %s to %s\n", name1, name2);
	else
		printf("The distance between %s - %s is %d\n", name1, name2,
			   dist[ind2]);

	free(visited);
	free(queue);
	free(dist);
}

void common(int ***matrix, char *name)
{
	name = strtok(NULL, "\n ");
	int ind1 = get_user_id(name);
	name = strtok(NULL, "\n ");
	int ind2 = get_user_id(name);

	int number_of_common = 0;
	int *common = (int *)calloc(MAX_PEOPLE, sizeof(int));

	for (int i = 0; i < MAX_PEOPLE; i++)
		if ((*matrix)[ind1][i] == 1 && (*matrix)[ind2][i] == 1)
			common[number_of_common++] = i;
	
	if (number_of_common == 0) {
		printf("No common friends for %s and %s\n",
			   get_user_name(ind1), get_user_name(ind2));
	} else {
		printf("The common friends between %s and %s are:\n",
			   get_user_name(ind1), get_user_name(ind2));
		for (int i = 0; i < number_of_common; i++)
			printf("%s\n", get_user_name(common[i]));
	}

	free(common);
}

void friends(int ***matrix, char *name)
{
	name = strtok(NULL, "\n ");
	int ind = get_user_id(name);
	
	int number_of_friends = 0;

	for (int i = 0; i < MAX_PEOPLE; i++)
		if ((*matrix)[ind][i] == 1)
			number_of_friends++;
	
	printf("%s has %d friends\n", get_user_name(ind), number_of_friends);
}

void popular(int ***matrix, char *name)
{
	name = strtok(NULL, "\n ");
	int ind = get_user_id(name);

	int most_popular = ind;
	int number_of_friends_popular = 0;

	for (int i = 0; i < MAX_PEOPLE; i++)
		if ((*matrix)[ind][i] == 1)
			number_of_friends_popular++;

	for (int i = 0; i < MAX_PEOPLE; i++) {
		if ((*matrix)[ind][i] == 1) {
			int number_of_friends = 0;
			for (int j = 0; j < MAX_PEOPLE; j++)
				if ((*matrix)[i][j] == 1)
					number_of_friends++;
			if (number_of_friends > number_of_friends_popular) {
				number_of_friends_popular = number_of_friends;
				most_popular = i;
			}
		}
	}

	if (most_popular == ind)
		printf("%s is the most popular\n", get_user_name(ind));
	else
		printf("%s is the most popular friend of %s\n",
			   get_user_name(most_popular), get_user_name(ind));
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
	else if (!strcmp(cmd, "distance"))
		distance(matrix, cmd);
	else if (!strcmp(cmd, "common"))
		common(matrix, cmd);
	else if (!strcmp(cmd, "friends"))
		friends(matrix, cmd);
	else if (!strcmp(cmd, "popular"))
		popular(matrix, cmd);

	free(commands);
}
