#include "tests.h"
#include "string.h"

#define K_2 2
#define K_3 3
#define K_M1 -1
#define K_M3 -3
#define K_29 29



int test_pattern_encode (char in[], char out[], int shifts)
{
  encode (in, shifts);
  return strcmp (in, out) != 0;
}

int test_pattern_decode (char in[], char out[], int shifts)
{
  decode (in, shifts);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_non_cyclic_lower_case_positive_k ()
{
  char in[] = "abc", out[] = "def";
  return test_pattern_encode (in, out, K_3);
}

// See full documentation in header file
int test_encode_cyclic_lower_case_special_char_positive_k ()
{
  // your code goes here
  char in[] = "He,l!z", out[] = "Jg,n!b";
  return test_pattern_encode (in, out, K_2);
}

// See full documentation in header file
int test_encode_non_cyclic_lower_case_special_char_negative_k ()
{
  // your code goes here
  char in[] = "BRi!n", out[] = "AQh!m";
  return test_pattern_encode (in, out, K_M1);
}

// See full documentation in header file
int test_encode_cyclic_lower_case_negative_k ()
{
  // your code goes here
  char in[] = "abh", out[] = "xye";
  return test_pattern_encode (in, out, K_M3);
}

// See full documentation in header file
int test_encode_cyclic_upper_case_positive_k ()
{
  // your code goes here
  char in[] = "HI THERZ", out[] = "KL WKHUC";
  return test_pattern_encode (in, out, K_29);
}

// See full documentation in header file
int test_decode_non_cyclic_lower_case_positive_k ()
{
  char in[] = "def", out[] = "abc";
  return test_pattern_decode (in, out, K_3);
}

// See full documentation in header file
int test_decode_cyclic_lower_case_special_char_positive_k ()
{
  // your code goes here
  char in[] = "Jg,n!b", out[] = "He,l!z";
  return test_pattern_decode (in, out, K_2);
}

// See full documentation in header file
int test_decode_non_cyclic_lower_case_special_char_negative_k ()
{
  // your code goes here
  char in[] = "AQh!m", out[] = "BRi!n";
  return test_pattern_decode (in, out, K_M1);
}

// See full documentation in header file
int test_decode_cyclic_lower_case_negative_k ()
{
  // your code goes here
  char in[] = "xye", out[] = "abh";
  return test_pattern_decode (in, out, K_M3);
}

// See full documentation in header file
int test_decode_cyclic_upper_case_positive_k ()
{
  // your code goes here
  char in[] = "KL WKHUC", out[] = "HI THERZ";
  return test_pattern_decode (in, out, K_29);
}
