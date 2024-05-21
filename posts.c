#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"
#include "posts.h"
g_node_t *create_post(int *index, char *cmd)
{
	cmd = strtok(NULL, " \n");

	int id = get_user_id(cmd);

	char *title = strtok(NULL, "\n");

	g_node_t *root = calloc(1, sizeof(g_node_t));

	root->title = strdup(title);

	root->id = *index;

	root->user_id = id;

	root->children = NULL;

	root->children_count = 0;

	(*index)++;

	printf("Created %s for %s\n", title, get_user_name(id));

	return root;
}

void add_post(posts_and_reposts_t *social_m, char *cmd, int *index)
{
	social_m->pos_and_repos[social_m->pos_count]->root = create_post(index,
																	 cmd);

	social_m->pos_count++;

	social_m->pos_and_repos = realloc(social_m->pos_and_repos,
									  social_m->pos_count * sizeof(g_tree_t *));
}

void handle_input_posts(char *input, posts_and_reposts_t *social_m, int *index)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "create"))
		add_post(social_m, cmd, index);
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
