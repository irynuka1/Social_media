#ifndef FRIENDS_H
#define FRIENDS_H

#define MAX_COMMAND_LEN 280
#define MAX_PEOPLE 550

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
 * Function that adds or removes a friend
 *
 * @param matrix - the matrix of friends
 * @param names - the names of the users
 * @param op_type - the operation type (1 for add, 0 for remove)
*/
void add_remove_friend(int ***matrix, char *names, int op_type);

/**
 * Function that finds the suggestions for a user
 *
 * @param matrix - the matrix of friends
 * @param name - the name of the user
*/
void suggestions(int ***matrix, char *name);

/**
 * Function that finds the distance between two users
 *
 * @param matrix - the matrix of friends
 * @param names - the names of the users
*/
void distance(int ***matrix, char *names);

/**
 * Function that finds the common friends between two users
 *
 * @param matrix - the matrix of friends
 * @param names - the names of the users
*/
void common(int ***matrix, char *names);

/**
 * Function that finds the number of friends of a user
 *
 * @param matrix - the matrix of friends
 * @param name - the name of the user
*/
void friends(int ***matrix, char *name);

/**
 * Function that finds the most popular user
 *
 * @param matrix - the matrix of friends
 * @param name - the name of the user
*/
void popular(int ***matrix, char *name);

/**
 * Function that handles the input for the friends task
 *
 * @param input - the input string
 * @param matrix - the matrix of friends
*/
void handle_input_friends(char *input, int ***matrix);

#endif // FRIENDS_H
