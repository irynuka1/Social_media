/**
 * The entrypoint of the homework. Every initialization must be done here
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "users.h"
#include "friends.h"
#include "posts.h"
#include "feed.h"

/**
 * Initializez every task based on which task we are running
*/
void init_tasks(void)
{
	#ifdef TASK_1

	#endif

	#ifdef TASK_2

	#endif

	#ifdef TASK_3

	#endif
}

/**
 * Entrypoint of the program, compiled with different defines for each task
*/
int main(void)
{
	init_users();

	init_tasks();
	
	#ifdef TASK_1
	// Initialize the friends matrix
	int **matrix = malloc(MAX_PEOPLE * sizeof(int *));
	for (int i = 0; i < MAX_PEOPLE; i++)
		matrix[i] = calloc(MAX_PEOPLE, sizeof(int));
	#endif

	#ifdef TASK_2
	// Initialize the social media
	posts_and_reposts_t *social_m = calloc(1, sizeof(posts_and_reposts_t));
	social_m->pos_and_repos = calloc(1, sizeof(g_tree_t *));
	social_m->pos_count = 1;
	social_m->pos_and_repos[0] = NULL;
	int index = 1;
	#endif


	char *result = NULL, *input = (char *)malloc(MAX_COMMAND_LEN);

	while (1) {
		result = fgets(input, MAX_COMMAND_LEN, stdin);

		// If fgets returns null, we reached EOF
		if (!result)
			break;

		#ifdef TASK_1
		handle_input_friends(input, matrix);
		#endif

		#ifdef TASK_2
		handle_input_posts(input, social_m, &index);
		#endif

		#ifdef TASK_3
		handle_input_feed(input);
		#endif
	}

	#ifdef TASK_1
		for (int i = 0; i < MAX_PEOPLE; i++)
			free(matrix[i]);
		free(matrix);
	#endif

	free(input);
	free_users();
	return 0;
}
