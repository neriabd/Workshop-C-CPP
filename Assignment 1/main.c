#include "cipher.h"
#include "tests.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

#define ARGS4 5
#define ARGS1 2
#define BUFFER_LENGTH 1025

/**
 * Functions declaration
 */
int is_integer (const char shifts[]);

int apply_initial_tests (int argc, char argv1[], char argv2[]);

int apply_tdd_tests ();

int main (int argc, char *argv[])

/**
 * The main function consists
 * @param argc consists the number of arguments given
 * @param argv consists the data of the arguments given
 * @return EXIT_FAILURE if the given arguments were not valid
 * @return EXIT_SUCCESS if the given arguments were valid
 */
{
  if (argc == ARGS1 && (!strcmp (argv[1], "test")))
    {
      if (apply_tdd_tests ())
        {
          return EXIT_FAILURE;
        }
      else
        {
          return EXIT_SUCCESS;
        }
    }
  if (apply_initial_tests (argc, argv[1], argv[2]))
    {
      return EXIT_FAILURE;
    }
  char cipher[BUFFER_LENGTH];

  FILE *file_input = fopen (argv[3], "r");
  if (file_input == NULL)
    {
      fprintf (stderr, "The given file is invalid.\n");
      return EXIT_FAILURE;
    }
//  create_output_file (argv[4], cipher);
  FILE *file_output;
  file_output = fopen (argv[4], "w");
  while (fgets (cipher, sizeof (cipher), file_input) != NULL)
    {
      if (!strcmp (argv[1], "encode"))
        {
          encode (cipher, strtol (argv[2], NULL, 0));
        }
      else if (strcmp (argv[1], "decode") == 0)
        {
          decode (cipher, strtol (argv[2], NULL, 0));
        }
      fprintf (file_output, cipher);
    }
  fclose (file_input);
  fclose (file_output);
  return EXIT_SUCCESS;
}

int apply_initial_tests (int argc, char argv1[], char argv2[])
/**
 * Check the validation of the arguments that were given
 * @return EXIT_FAILURE if one of the tests failed
 * @return EXIT_SUCCESS if all the tests passed successfully
 */
{
  if (argc != ARGS1 && argc != ARGS4)
    {
      fprintf (stderr, "The program receives 1 or 4 arguments only.\n");
      return EXIT_FAILURE;
    }
  else if (argc == ARGS1)
    {
      fprintf (stderr, "Usage: cipher test\n");
      return EXIT_FAILURE;
    }
  else if ((strcmp (argv1, "encode")) && (strcmp (argv1, "decode")))
    {
      fprintf (stderr, "The given command is invalid.\n");
      return EXIT_FAILURE;
    }
  else if (is_integer (argv2))
    {
      fprintf (stderr, "The given shift value is invalid.\n");
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}

int is_integer (const char shifts[])
/**
 * Checks if argv[2] (the number of shifts) consists only integers
 * @param shifts consists the number of shifts to encrypt
 * @return EXIT_FAILURE if the string has chars that are not integers
 * @return EXIT_SUCCESS if the string consists only integers
 */
{
  for (int i = 0; shifts[i] != 0; i++)
    {
      if (!(isdigit (shifts[i]) || ((i == 0) && (shifts[0] == '-'))))
        {
          return EXIT_FAILURE;
        }
    }
  return EXIT_SUCCESS;
}

int apply_tdd_tests ()
/**
 * Apply the TDD tests to check if encode and decode functions are
 * working properly
 * @return EXIT_FAILURE if test failed
 * @return EXIT_SUCCESS if test passed
 */
{
  if (test_encode_non_cyclic_lower_case_positive_k ())
    {
      return EXIT_FAILURE;
    }
  if (test_encode_cyclic_lower_case_special_char_positive_k ())
    {
      return EXIT_FAILURE;
    }
  if (test_encode_non_cyclic_lower_case_special_char_negative_k ())
    {
      return EXIT_FAILURE;
    }
  if (test_encode_cyclic_lower_case_negative_k ())
    {
      return EXIT_FAILURE;
    }
  if (test_encode_cyclic_upper_case_positive_k ())
    {
      return EXIT_FAILURE;
    }
  if (test_decode_non_cyclic_lower_case_positive_k ())
    {
      return EXIT_FAILURE;
    }
  if (test_decode_cyclic_lower_case_special_char_positive_k ())
    {
      return EXIT_FAILURE;
    }
  if (test_decode_non_cyclic_lower_case_special_char_negative_k ())
    {
      return EXIT_FAILURE;
    }
  if (test_decode_cyclic_lower_case_negative_k ())
    {
      return EXIT_FAILURE;
    }
  if (test_decode_cyclic_upper_case_positive_k ())
    {
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
