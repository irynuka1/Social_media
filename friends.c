#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "friends.h"
#include "users.h"

void add_remove_friend(int ***matrix, char *names, int op_type)
{
	// Get the id of the users
	names = strtok(NULL, "\n ");
	int id1 = get_user_id(names);
	names = strtok(NULL, "\n ");
	int id2 = get_user_id(names);

	// Add or remove the connection between the users
	(*matrix)[id1][id2] = op_type;
	(*matrix)[id2][id1] = op_type;

	if (op_type == 1)
		printf("Added connection %s - %s\n", get_user_name(id1),
			   get_user_name(id2));
	else
		printf("Removed connection %s - %s\n", get_user_name(id1),
			   get_user_name(id2));
}

void suggestions(int ***matrix, char *name)
{
	name = strtok(NULL, "\n ");
	int id = get_user_id(name), check = 0;
	int *suggestions = calloc(MAX_PEOPLE, sizeof(int));
	DIE(!suggestions, "Calloc failed!");
	int *visited = calloc(MAX_PEOPLE, sizeof(int));
	DIE(!visited, "Calloc failed!");

	// Mark the current user as visited
	visited[id] = 1;
	// Mark the friends of the current user as visited
	for (int i = 0; i < MAX_PEOPLE; i++)
		if ((*matrix)[id][i] == 1)
			visited[i] = 1;

	// Find the friends of the friends
	for (int i = 0; i < MAX_PEOPLE; i++)
		if ((*matrix)[id][i] == 1)
			for (int j = 0; j < MAX_PEOPLE; j++)
				if ((*matrix)[i][j] && !(*matrix)[id][j] && j != id) {
					suggestions[j] = 1;
					check = 1;
				}

	// Print the suggestions if there are any
	if (check == 0) {
		printf("There are no suggestions for %s\n", name);
	} else {
		printf("Suggestions for %s:\n", name);
		for (int i = 0; i < MAX_PEOPLE; i++)
			if (suggestions[i])
				printf("%s\n", get_user_name(i));
	}

	free(suggestions);
	free(visited);
}

void distance(int ***matrix, char *names)
{
	// Get the id of the users
	names = strtok(NULL, "\n ");
	int id1 = get_user_id(names);
	names = strtok(NULL, "\n ");
	int id2 = get_user_id(names);

	int *visited = calloc(MAX_PEOPLE, sizeof(int));
	DIE(!visited, "Calloc failed!");
	int *queue = malloc(MAX_PEOPLE * sizeof(int));
	DIE(!queue, "Malloc failed!");
	int *dist = malloc(MAX_PEOPLE * sizeof(int));
	DIE(!dist, "Malloc failed!");
	int front = 0, rear = 0;
	// Initialize the visited array
	for (int i = 0; i < MAX_PEOPLE; i++)
		dist[i] = -1;

	// Add the first user to the queue
	queue[rear++] = id1;
	visited[id1] = 1;
	dist[id1] = 0;

	// BFS
	while (front < rear) {
		int current = queue[front++];
		for (int i = 0; i < MAX_PEOPLE; i++)
			if ((*matrix)[current][i] && !visited[i]) {
				visited[i] = 1;
				dist[i] = dist[current] + 1;
				queue[rear++] = i;
			}
	}

	// Print the distance between the users if there is a path
	if (dist[id2] == -1)
		printf("There is no way to get from %s to %s\n", get_user_name(id1),
			   get_user_name(id2));
	else
		printf("The distance between %s - %s is %d\n", get_user_name(id1),
			   get_user_name(id2), dist[id2]);

	free(visited);
	free(queue);
	free(dist);
}

void common(int ***matrix, char *names)
{
	// Get the id of the users
	names = strtok(NULL, "\n ");
	int id1 = get_user_id(names);
	names = strtok(NULL, "\n ");
	int id2 = get_user_id(names);

	int no_friends = 0;
	int *common = malloc(MAX_PEOPLE * sizeof(int));
	DIE(!common, "Malloc failed!");

	// Find the common friends
	for (int i = 0; i < MAX_PEOPLE; i++)
		if ((*matrix)[id1][i] == 1 && (*matrix)[id2][i] == 1)
			common[no_friends++] = i;

	// Print the common friends if there are any
	if (no_friends == 0) {
		printf("No common friends for %s and %s\n", get_user_name(id1),
			   get_user_name(id2));
	} else {
		printf("The common friends between %s and %s are:\n",
			   get_user_name(id1), get_user_name(id2));

		for (int i = 0; i < no_friends; i++)
			printf("%s\n", get_user_name(common[i]));
	}

	free(common);
}

void friends(int ***matrix, char *name)
{
	// Get the id of the user
	name = strtok(NULL, "\n ");
	int ind = get_user_id(name);

	int no_friends = 0;

	// Find the number of friends
	for (int i = 0; i < MAX_PEOPLE; i++)
		if ((*matrix)[ind][i] == 1)
			no_friends++;

	printf("%s has %d friends\n", get_user_name(ind), no_friends);
}

void popular(int ***matrix, char *name)
{
	// Get the id of the user
	name = strtok(NULL, "\n ");
	int id = get_user_id(name);

	int most_popular = id;
	int popular_friends = 0;

	// Find number of friends of the user
	for (int i = 0; i < MAX_PEOPLE; i++)
		if ((*matrix)[id][i] == 1)
			popular_friends++;

	// Find the user with the most friends
	for (int i = 0; i < MAX_PEOPLE; i++) {
		if ((*matrix)[id][i] == 1) {
			int no_friends = 0;

			for (int j = 0; j < MAX_PEOPLE; j++)
				if ((*matrix)[i][j] == 1)
					no_friends++;

			if (no_friends > popular_friends) {
				popular_friends = no_friends;
				most_popular = i;
			}
		}
	}

	// Print the most popular user
	if (most_popular == id)
		printf("%s is the most popular\n", get_user_name(id));
	else
		printf("%s is the most popular friend of %s\n",
			   get_user_name(most_popular), get_user_name(id));
}

void handle_input_friends(char *input, int ***matrix)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;
	if (!strcmp(cmd, "add"))
		add_remove_friend(matrix, cmd, 1);
	else if (!strcmp(cmd, "remove"))
		add_remove_friend(matrix, cmd, 0);
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

