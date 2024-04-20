#include "markov_chain.h"
#include "linked_list.h"

int main (int argc, char *argv[])
{
  if (!check_arguments_validation (argc, argv))
  {
    return EXIT_FAILURE;
  }
  int num_of_tweets = 0, words_to_read = 0;
  MarkovChain *markov_chain = NULL;
  if (!create_markov_chain (&markov_chain))
  {
    printf (ERROR_ALLOCATION_FAILURE_MSG);
    return EXIT_FAILURE; // allocation failure
  }
  recast_args_and_set_seed (argc, argv, &num_of_tweets, &words_to_read);
  if (!open_file_and_fill_mc (markov_chain, argv[PATH], words_to_read))
  {
    printf (ERROR_ALLOCATION_FAILURE_MSG);
    return EXIT_FAILURE; // allocation failure
  }
  create_and_print_sequence (num_of_tweets, markov_chain);
  free_markov_chain (&markov_chain);
  return EXIT_SUCCESS;
}

bool check_arguments_validation (int argc, char *argv[])
{
  FILE *file_ptr = fopen (argv[PATH], READ_MODE);
  if (file_ptr == NULL)
  {
    printf (ERROR_OPEN_FILE_MSG);
    return false;
  }
  else
  {
    fclose (file_ptr);
  }
  if (argc != MIN_ARGS && argc != MAX_ARGS)
  {
    printf (ERROR_WRONG_ARGC_MSG);
    return false;
  }
  return true;
}

bool create_markov_chain (MarkovChain **markov_chain)
{
  *markov_chain = (MarkovChain *) malloc (sizeof (MarkovChain));
  if ((*markov_chain) == NULL)
  {
    return false; // allocation failure
  }
  LinkedList *linked_list = (LinkedList *) malloc (sizeof (LinkedList));
  if (linked_list == NULL)
  {
    free (markov_chain);
    markov_chain = NULL; // allocation failure
    return false;
  }
  *linked_list = (LinkedList) {NULL, NULL, 0};
  (*markov_chain)->database = linked_list;
  return true;
}

void
recast_args_and_set_seed (int argc, char *argv[], int *num_of_tweets, int
*words_to_read)
{
  long int seed = strtol (argv[SEED], NULL, NUM_BASE);
  srand (seed);
  long int tweets = strtol (argv[TWEETS_TO_PRINT], NULL, NUM_BASE);
  *num_of_tweets = (int) tweets;
  if (argc == MAX_ARGS)
  {
    long int word_read = strtol (argv[WORDS_TO_READ], NULL, NUM_BASE);
    *words_to_read = (int) word_read;
  }
  else
  {
    *words_to_read = -1;
  }
}

bool open_file_and_fill_mc (MarkovChain *markov_chain, char *corpus_path,
                            int words_to_read)
{
  FILE *fp = fopen (corpus_path, READ_MODE);
  if (fp == NULL) // check if file failed to open
  {
    free ((markov_chain)->database);
    free (markov_chain);
    return false; // allocation failure
  }
  int fill_res = fill_database (fp, words_to_read, markov_chain);
  fclose (fp);
  if (fill_res)
  {
    free_markov_chain (&markov_chain);
    markov_chain = NULL;
    return false; // allocation failure
  }
  return true;
}

int fill_database (FILE *fp, int words_to_read, MarkovChain *markov_chain)
{
  char tweet[INPUT_BUFFER]; //1000 words in tweet + '\0'
  char *token = NULL;
  Node *prev_node = NULL, *cur_node = NULL;

  while (fgets (tweet, INPUT_BUFFER, fp) && words_to_read)
  {
    token = strtok (tweet, SPACE);
    while (token && words_to_read) //read until the tweet is over
    {
      words_to_read--;
      if (!add_node_to_markov_chain (markov_chain, token, &cur_node))
      {
        return 1; // allocation failure
      }
      if (!add_nnc_to_counter_list (prev_node, cur_node))
      {
        return 1; // allocation failure
      }
      prev_node = cur_node; // pointer to previous node to add to counter list
      token = strtok (NULL, SPACE);
    }
  }
  return 0;
}

bool
add_node_to_markov_chain (MarkovChain *markov_chain, char *token,
                          Node **cur_node)
{
  token[strcspn (token, NEW_LINE)] = 0;
  *cur_node = add_to_database (markov_chain, token);
  if (*cur_node == NULL)
  {
    return false; // allocation failure
  }
  return true;
}

bool allocate_word (char **cur_word, char *tweet)
{
  tweet[strcspn (tweet, NEW_LINE)] = 0; //remove '\n' in end of word
  *cur_word = (char *) malloc (strlen (tweet) + 1);
  if (*cur_word == NULL)
  {
    return false; // allocation failure
  }
  strcpy (*cur_word, tweet); // copy string to dynamic memory
  return true;
}

bool add_nnc_to_counter_list (Node *prev_node, Node *cur_node)
{
  if (prev_node &&
      prev_node->data->word[strlen (prev_node->data->word) - 1] != DOT)
  {
    if (!add_node_to_counter_list (prev_node->data, cur_node->data))
    {
      return false; // allocation failure
    }
  }
  return true;
}

void create_and_print_sequence (int num_of_tweets, MarkovChain *markov_chain)
{
  for (int i = 0; i < num_of_tweets; i++)
  {
    printf (TWEET_MSG, (i + 1));
    generate_random_sequence (markov_chain, NULL, MAX_SIZE_SENTENCE);
  }
}