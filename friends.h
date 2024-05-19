#ifndef FRIENDS_H
#define FRIENDS_H

#define MAX_COMMAND_LEN 280
#define MAX_PEOPLE 550

/**
 * Function that handles the input for the friends task
 *
 * @param input - the input string
 * @param matrix - the matrix of friends
*/
void handle_input_friends(char *input, int ***matrix);

void add_friend(int ***matrix, char *name);

void remove_friend(int ***matrix, char *name);

void suggestions(int ***matrix, char *name);

void distance(int ***matrix, char *name);

void common(int ***matrix, char *name);

void friends(int ***matrix, char *name);

void popular(int ***matrix, char *name);

#endif // FRIENDS_H
