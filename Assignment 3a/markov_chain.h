#ifndef _MARKOV_CHAIN_H
#define _MARKOV_CHAIN_H

#include "linked_list.h"
#include <stdio.h>  // For printf(), sscanf()
#include <stdlib.h> // For exit(), malloc()
#include <stdbool.h> // for bool
#include <string.h>

#define SEED 1
#define TWEETS_TO_PRINT 2
#define PATH 3
#define WORDS_TO_READ 4
#define MIN_ARGS 4
#define MAX_ARGS 5
#define NUM_BASE 10
#define MAX_SIZE_SENTENCE 20
#define INPUT_BUFFER 1001
#define NEW_LINE "\n"
#define STR_MSG "%s "
#define STR_NEW_LINE_MSG "%s\n"
#define DOT '.'
#define SPACE " "
#define TWEET_MSG "Tweet %d: "
#define READ_MODE "r"
#define ERROR_OPEN_FILE_MSG "Error: Can't access the tweets file"
#define ERROR_WRONG_ARGC_MSG "USAGE: Wrong number of arguments"
#define ERROR_ALLOCATION_FAILURE_MSG "Allocation failure: memory allocation failed"

typedef struct MarkovChain
{
  struct LinkedList *database;
} MarkovChain;

typedef struct MarkovNode
{
  char *word;
  int size;
  int sum_freq;
  struct NextNodeCounter **counter_list;
} MarkovNode;

typedef struct NextNodeCounter
{
  struct MarkovNode *markov_node;
  int freq;
} NextNodeCounter;

/**
* Get random number between 0 and max_number [0, max_number).
* @param max_number maximal number to return (not including)
* @return Random number
*/
int get_random_number (int max_number);

/**
 * Get one random state from the given markov_chain's database.
 * @param markov_chain
 * @return
 */
MarkovNode *get_first_random_node (MarkovChain *markov_chain);

/**
 * Choose randomly the next state, depend on it's occurrence frequency.
 * @param state_struct_ptr MarkovNode to choose from
 * @return MarkovNode of the chosen state
 */
MarkovNode *get_next_random_node (MarkovNode *state_struct_ptr);

/**
 * Receive markov_chain, generate and print random sentence out of it. The
 * sentence most have at least 2 words in it.
 * @param markov_chain
 * @param first_node markov_node to start with,
 *                   if NULL- choose a random markov_node
 * @param  max_length maximum length of chain to generate
 */
void generate_random_sequence (MarkovChain *markov_chain, MarkovNode *
first_node, int max_length);

/**
 * Free markov_chain and all of it's content from memory
 * @param markov_chain markov_chain to free
 */
void free_markov_chain (MarkovChain **ptr_chain);

/**
 * Add the second markov_node to the counter list of the first markov_node.
 * If already in list, update it's counter value.
 * @param first_node
 * @param second_node
 * @param markov_chain
 * @return success/failure: true if the process was successful, false if in
 * case of allocation error.
 */
bool
add_node_to_counter_list (MarkovNode *first_node, MarkovNode *second_node);

/**
* Check if data_ptr is in database. If so, return the markov_node wrapping
 * it in the markov_chain, otherwise return NULL.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return Pointer to the Node wrapping given state, NULL if state not in
 * database.
 */
Node *get_node_from_database (MarkovChain *markov_chain, char *data_ptr);

/**
* If data_ptr in markov_chain, return it's markov_node. Otherwise, create new
 * markov_node, add to end of markov_chain's database and return it.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return markov_node wrapping given data_ptr in given chain's database,
 * returns NULL in case of memory allocation failure.
 */
Node *add_to_database (MarkovChain *markov_chain, char *data_ptr);

bool create_new_counter_list (MarkovNode *first_node);

bool append_nnc_to_counter_list (MarkovNode *first_node, MarkovNode
*second_node);

bool extend_counter_list (MarkovNode *first_node);

bool in_counter_list (MarkovNode *first_node, MarkovNode *second_node);

bool check_arguments_validation (int argc, char *argv[]);

bool create_markov_chain (MarkovChain **markov_chain);

bool
open_file_and_fill_mc (MarkovChain *markov_chain, char *corpus_path,
                       int words_to_read);

bool allocate_word (char **cur_word, char *tweet);

void
recast_args_and_set_seed (int argc, char *argv[], int *num_of_tweets, int
*words_to_read);

void create_and_print_sequence (int num_of_tweets, MarkovChain *markov_chain);

bool
add_node_to_markov_chain (MarkovChain *markov_chain, char *token,
                          Node **cur_node);

int fill_database (FILE *fp, int words_to_read, MarkovChain *markov_chain);

bool add_nnc_to_counter_list (Node *prev_node, Node *cur_node);

#endif /* markovChain_h */
