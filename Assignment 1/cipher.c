#include "cipher.h"


#define CAP 1
#define LOW 2

void apply_cipher (char cipher[], int shifts)
/**
 * Encrypt the cipher based on the number of shifts.
 * @param cipher - consists the string to encrypt.
 * @param shifts - given shift value.
 */
{
  const int num_letters = 26, cap_to_index = 64, low_to_index = 96;
  int num, type;
  for (int i = 0; cipher[i] != 0; i++)
    {
      if ((cipher[i] >= 'A') && (cipher[i] <= 'Z'))
        {
          cipher[i] = cipher[i] - cap_to_index;
          type = CAP;
        }
      else if ((cipher[i] >= 'a') && (cipher[i] <= 'z'))
        {
          cipher[i] = cipher[i] - low_to_index;
          type = LOW;
        }
      else
        {
          continue;
        }
      num = shifts % num_letters;
      if (num < 0)
        {
          num += num_letters;
        }
      cipher[i] += num;
      if (cipher[i] > num_letters)
        {
          cipher[i] = cipher[i] % num_letters;
        }
      if (type == CAP)
        {
          cipher[i] += cap_to_index;
        }
      else
        {
          cipher[i] += low_to_index;
        }
    }
}


void encode (char s[], int k)
/**
 * Encodes the given string according to the given shift value - k.
 * @param s - given string.
 * @param k - given shift value.
 */
{
  apply_cipher (s, k);
}

void decode (char s[], int k)
/**
 * Encodes the given string according to the given shift value - k.
 * @param s - given string.
 * @param k - given shift value.
 */
{
  apply_cipher (s, -k);
}

