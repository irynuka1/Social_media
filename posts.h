#ifndef POSTS_H
#define POSTS_H

/**
 * Function that handles the calling of every command from task 2
 *
 * Please add any necessary parameters to the functions
*/

typedef struct g_node_t g_node_t;
struct g_node_t
{
	char *title;
	int id;
	int user_id;
	g_node_t **children;
	int children_count;
};

typedef struct g_tree_t g_tree_t;
struct g_tree_t
{
	g_node_t *root;
};

typedef struct posts_and_reposts_t posts_and_reposts_t;
struct posts_and_reposts_t
{
	g_tree_t **pos_and_repos;
	int pos_count;
};

void handle_input_posts(char *input, posts_and_reposts_t *social_m, int *index);

void add_post(posts_and_reposts_t *social_m, char *cmd, int *index);

g_node_t *create_post(int *index, char *cmd);

#endif // POSTS_H
