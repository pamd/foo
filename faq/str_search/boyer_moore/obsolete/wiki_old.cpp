/* Boyer-Moore string search algorithm implementation,
 * copied from wikipedia 2011 webpage.
 *
 * Note that in this implementation, the length of good_suffix 
 * is needle_len + 1, but good_suffix[0] is never used.
 */

#include <limits.h>
#include <string.h>
#include <iostream>

using namespace std;
 
#define ALPHABET_SIZE (1 << CHAR_BIT)
 
void compute_prefix(const char* str, size_t size, int result[]) 
{
  size_t q;
  int k;
  result[0] = 0;
 
  k = 0;
  for (q = 1; q < size; q++) {
    while (k > 0 && str[k] != str[q])
      k = result[k-1];
 
    if (str[k] == str[q])
      k++;
    result[q] = k;
  }

}
 
void get_bad_char(const char* str, size_t size, int result[]) 
{ 
  size_t i;
 
  for (i = 0; i < ALPHABET_SIZE; i++)
    result[i] = -1;
 
  for (i = 0; i < size; i++)
    result[(size_t) str[i]] = i;
}
 
void get_good_suffix(const char* normal, size_t size, int result[]) 
{ 
  char *left = (char *) normal;
  char *right = left + size;
  char reversed[size+1];
  char *tmp = reversed + size;
  size_t i;
 
  /* reverse string */
  *tmp = 0;
  while (left < right)
    *(--tmp) = *(left++);
 
  int prefix_normal[size];
  int prefix_reversed[size];
 
  compute_prefix(normal, size, prefix_normal);
  compute_prefix(reversed, size, prefix_reversed);
 
  for (i = 0; i <= size; i++) {
    result[i] = size - prefix_normal[size-1];
  }
 
  for (i = 0; i < size; i++) {
    const int j = size - prefix_reversed[i];
    const int k = i - prefix_reversed[i]+1;
 
    if (result[j] > k)
      result[j] = k;
  }

}

// Boyer-Moore search algorithm
const char* bm_search(const char* haystack, const char* needle) 
{
  // Calc string sizes
  size_t needle_len, haystack_len;
  needle_len = strlen(needle);
  haystack_len = strlen(haystack);
 
  // Simple checks
  if(haystack_len == 0)
    return NULL;
  if(needle_len == 0)
    return haystack;
 
  // Initialize heuristics
  int bad_char[ALPHABET_SIZE];

  // In this implementation, the length of good_suffix 
  // is needle_len + 1, but good_suffix[0] is never used.
  int good_suffix[needle_len + 1];
 
  get_bad_char(needle, needle_len, bad_char);
  get_good_suffix(needle, needle_len, good_suffix);
 
  cout << "bad_char array: " << endl;
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (bad_char[i] != -1) 
      cout << (char)i << ": " << bad_char[i] << endl;
  }
  cout << endl;

  cout << "good_suffix array: " << endl;
  for (int i = 0; i < needle_len + 1; i++) {
    cout << i << ": " << good_suffix[i] << endl;
  }
  cout << endl;

  // Boyer-Moore search
  size_t s = 0;
  while (s <= haystack_len - needle_len) {
    size_t j = needle_len;
    while(j > 0 && needle[j - 1] == haystack[s + j - 1])
      j--;
 
    if (j > 0) {
      int k = bad_char[(size_t) haystack[s+j-1]];
      int m;
      if (k < (int)j && (m = j-k-1) > good_suffix[j])
	s += m;
      else
	s += good_suffix[j];
    }
    else {
      return haystack + s;
    }
  }
 
  return NULL; // not found
}

int main() {
  const char* target = "anpanman";
  const char* source = "asdfghrtyuewruhfkwetanpanmandert";

  const char* result = bm_search(source, target);
  if (result) 
    cout <<"I got it: " << result << endl;
  else 
    cout << "Not found" << endl;
}

/* output: 

bad_char array: 
a: 6
m: 5
n: 7
p: 2

good_suffix array: 
0: 6
1: 6
2: 6
3: 6
4: 6
5: 6
6: 3
7: 3
8: 1

I got it: anpanmandert

*/
