/* This is the C implementation of Boyer-Moore algorithm based on:
 * http://www-igm.univ-mlv.fr/~lecroq/string/node14.html
 * The functions are renamed to make it easier to understand. */

#include <cstring>
#include <limits.h>
#include <iostream>

using namespace std;

#define ASIZE (1 << CHAR_BIT)

// Compute bad character shift array
void get_bad_char(const char* needle, int needle_sz, int bad_char[]) {
  for (int i = 0; i < ASIZE; ++i)
    bad_char[i] = needle_sz;

  for (int i = 0; i < needle_sz - 1; ++i)
    bad_char[(int) needle[i]] = needle_sz - i - 1;
}
 
// Inline function that returns the maximum of two integers
inline int get_max(int a, int b) {
  return (a > b) ? a : b;
}

// Helper function to get good suffix shift array
void get_suffix(const char* needle, int needle_sz, int* suffix) {
  suffix[needle_sz - 1] = needle_sz;
  int g = needle_sz - 1;
  int f;
  for (int i = needle_sz - 2; i >= 0; --i) {
    if (i > g && suffix[i + needle_sz - 1 - f] < i - g)
      suffix[i] = suffix[i + needle_sz - 1 - f];
    else {
      if (i < g)
	g = i;
      f = i;
      while (g >= 0 && needle[g] == needle[g + needle_sz - 1 - f])
	--g;
      suffix[i] = f - g;
    }
  }
}
 
// Compute good suffix shift array
void get_good_suffix(const char* needle, int needle_sz, int good_suffix[]) {
  int suffix[needle_sz];
  get_suffix(needle, needle_sz, suffix);

  for (int i = 0; i < needle_sz; ++i)
    good_suffix[i] = needle_sz;

  int j = 0;
  for (int i = needle_sz - 1; i >= 0; --i) {
    if (suffix[i] == i + 1)
      for (; j < needle_sz - 1 - i; ++j)
	if (good_suffix[j] == needle_sz)
	  good_suffix[j] = needle_sz - 1 - i;
  }

  for (int i = 0; i <= needle_sz - 2; ++i)
    good_suffix[needle_sz - 1 - suffix[i]] = needle_sz - 1 - i;
}
 
/* dhu version to compute suffix array.
 * suffix[i] is the maximum number of characters that overlap between
 * the substring needle[0...i] and the full needle string. */
void get_suffix_dhu(const char* needle, int needle_sz, int* suffix) {
  suffix[needle_sz - 1] = needle_sz;  // the last element in suffix is always needle_sz
  for (int i = needle_sz - 2; i >= 0; i--) {
    int counter = 0;
    for (int j = i; j >= 0; j--) {
      if (needle[j] == needle[needle_sz - 1 - counter])
	counter++;
      else
	break;
    }
    suffix[i] = counter;
  }
}

/* New function by dhu.
 * Compare shifted needle string with original string. 
 * Return true if the shift is valid, false otherwise. */
bool shift_dhu(const char* needle, int needle_sz, int mismatch_idx, int shift_val)
{
  for (int i = needle_sz - 1; i > mismatch_idx; i--) {
    if (i < shift_val)
      return true;

    if (needle[i - shift_val] != needle[i])
      return false;
  }
 
  // If the mismatched character is identical to the shifted one, the shift is still invalid
  // Consider string "anpanman", when mismatch_idx is 6, and shift is 3:

  //   index: 0 1 2 3 4 5 6 7 
  //  needle: a n p a n m a n
  // shifted:       a n p a n m a n

  // Although needle[7] is identical to shifted[4], but because needle[mismatch_idx] = 'a',
  // shift 3 is not a valid.   
  if (mismatch_idx >= shift_val && needle[mismatch_idx - shift_val] == needle[mismatch_idx])
    return false;

  return true;
      
}

// dhu version to get good suffix shift array.
void get_good_suffix_dhu(const char* needle, int needle_sz, int good_suffix[]) {
  good_suffix[needle_sz - 1] = 1; // the last element in good_suffix is always 1
  for (int i = needle_sz - 2; i >= 0; i--) {
    good_suffix[i] = needle_sz;
    // Shift needle string one by one and compare the new shifted string and original 
    // needle string. If characters match each other in valid range, it must be a good shift 
    for (int shift_val = 1; shift_val <= needle_sz - 1; shift_val++) {
      if (shift(needle, needle_sz, i, shift_val)) {
	good_suffix[i] = shift_val;
	break;
      }  // end if
    }  // end of for loop of shift_val
  }  // end of i for loop of i

}

// Boyer-Moore string search function, which calls get_bad_char() and get_good_suffix().
void boyer_moore(const char *needle, int needle_sz, const char *haystack, int haystack_sz) {
  int bad_char[ASIZE];
  int good_suffix[needle_sz];

  // Preprocessing
  get_bad_char(needle, needle_sz, bad_char);
  get_good_suffix(needle, needle_sz, good_suffix);

  // Searching
  int i;     // index of needle string char that is being matched
  int j = 0; // index of starting point of a possible match in haystack 
  while (j <= haystack_sz - needle_sz) {
    for (i = needle_sz - 1; i >= 0 && needle[i] == haystack[i + j]; --i)
      ;

    if (i < 0) {
      cout << "Got it: " << haystack + j << endl; // We found it!
      j += good_suffix[0]; // Keep searching for the next match
    }
    else
      j += get_max(good_suffix[i], bad_char[(int) haystack[i + j]] - needle_sz + 1 + i);
  }
}
   
// Test harness
int main()
{
  //const char* needle = "anpanman";
  //const char* haystack = "asertgderyfsanpanmanertanpanmanvcfgtr";
  //boyer_moore(needle, strlen(needle), haystack, strlen(haystack));

  //const char* needle = "GCAGAGAG";

  const char* needle = "anpanman";
  int needle_sz = strlen(needle);

  int bad_char[ASIZE];
  get_bad_char(needle, needle_sz, bad_char);
  // Print bad char shift table
  for (int i = 0; i < ASIZE; i++) {
    if (bad_char[i] != needle_sz) {
      cout << (char) i << ": " << bad_char[i] << endl;
    }
  }

  int suffix[needle_sz];
  get_suffix(needle, needle_sz, suffix);
  // Print suffix table 
  for (int i = 0; i < needle_sz; i++)
    cout << "suffix[" << i << "]: " << suffix[i] << endl;
  cout << endl;

  int good_suffix[needle_sz];
  get_good_suffix(needle, needle_sz, good_suffix);
  // Print good suffix shift table
  for (int i = 0; i < needle_sz; i++)
    cout << "good_suffix[" << i << "]: " << good_suffix[i] << endl;
  cout << endl;

  return 0;
}

// ****************************
//  needle string "anpanman"

//   bad_char[]: 
// ---------------
//   a: 1
//   m: 2
//   n: 3
//   p: 5
//   other: 8

//   suffix[]:
// ---------------
//   0: 0
//   1: 2
//   2: 0
//   3: 0
//   4: 2
//   5: 0
//   6: 0
//   7: 8

//   good_suffix[]:
// -----------------
//   0: 6
//   1: 6
//   2: 6
//   3: 6
//   4: 6
//   5: 3
//   6: 8
//   7: 1

// ***************************
