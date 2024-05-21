#ifndef POSTS_H
#define POSTS_H

#define DIE(assertion, call_description)				\
	do {								                \
		if (assertion) {					            \
			fprintf(stderr, "(%s, %d): ",			    \
					__FILE__, __LINE__);		        \
			perror(call_description);			        \
			exit(errno);				                \
		}							                    \
	} while (0)

/**
 * Structure that defines a node in the tree
 * 
 * @param title - the title of the post
 * @param id - the id of the post
 * @param user_id - the id of the user that created the post
 * @param children - a vector of children of the current post
 * @param children_count - the number of elements in the vector of children
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

/**
 * Structure that defines a tree
 * 
 * @param root - the root of the tree
*/
typedef struct g_tree_t g_tree_t;
struct g_tree_t
{
	g_node_t *root;
};

/**
 * Structure that defines the posts and reposts
 * 
 * @param pr - a vector of trees
 * @param count - the number of elements in the vector
 * @param max - the maximum number of elements in the vector
 * @param index - the index of the next post
*/
typedef struct posts_and_reposts_t posts_and_reposts_t;
struct posts_and_reposts_t
{
	g_tree_t **pr;
	int count;
	int max;
	int index;
};

/**
 * Function that creates a post
 *
 * @param index - the index of the post
 * @param cmd - the post details
 * @return the created post
*/
g_node_t *create_post(int *index, char *cmd);

/**
 * Function that adds a post to the social media
 *
 * @param social_m - the social media
 * @param cmd - the post details
*/
void add_post(posts_and_reposts_t *social_m, char *cmd);

/**
 * Function that handles the calling of every command from task 2
 * 
 * @param input - the input command
 * @param social_m - the social media
*/
void handle_input_posts(char *input, posts_and_reposts_t *social_m);

#endif // POSTS_H
