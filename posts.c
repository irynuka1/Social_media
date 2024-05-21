#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "users.h"
#include "posts.h"

g_node_t *create_post(int *index, char *cmd)
{
	// Get the user id
	cmd = strtok(NULL, " \n");
	int id = get_user_id(cmd);

	// Get the post title
	cmd = strtok(NULL, "\n");

	// Create a new post
	g_node_t *root = malloc(sizeof(g_node_t));
	DIE(!root, "Malloc failed");

	// Initialize the post
	root->title = strdup(cmd);
	root->id = (*index)++;
	root->user_id = id;
	root->children = NULL;
	root->children_count = 0;

	printf("Created %s for %s\n", cmd, get_user_name(id));

	return root;
}

void add_post(posts_and_reposts_t *social_m, char *cmd)
{
	// Allocate memory for the new post
	social_m->pr[social_m->count] = malloc(sizeof(g_tree_t));
	DIE(!social_m->pr[social_m->count], "Malloc failed");
	// Add the new post to the vector
	social_m->pr[social_m->count]->root = create_post(&social_m->index, cmd);

	social_m->count++;

	// Resize the vector if necessary
	if (social_m->count == social_m->max) {
		social_m->max *= 2;
		social_m->pr = realloc(social_m->pr, social_m->max *
							   sizeof(g_tree_t *));
	}
}

void handle_input_posts(char *input, posts_and_reposts_t *social_m)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "create"))
		add_post(social_m, cmd);
	else if (!strcmp(cmd, "repost"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "common-repost"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "like"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "ratio"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "delete"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "get-likes"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "get-reposts"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "get-likes"))
		(void)cmd;
		// TODO: Add function

	free(commands);
}
