/* Implement strStr().
 * 
 * Returns a pointer to the first occurrence of needle in haystack, 
 * or null if needle is not part of haystack.
 */

#include <iostream>

using namespace std;

// Idea cpied from Robert Sedgewick "Algorithms" 4th edition,
// 24ms for large dataset.
class Solution {
public:
  char *strStr(char *haystack, char *needle) {
    if (!haystack)
      return 0;
    if (!needle || !needle[0])
      return haystack;

    int i = 0;
    int j = 0;
    while (haystack[i + j]) {
      if (haystack[i + j] == needle[j]) {
	j++;
      	if (!needle[j])
	  return haystack + i;
      }
      else {
	i++;
	j = 0;
      }
    }

    return 0;
  }

};

// Improved dhu solution: 20ms for large dataset
const char* strstr_dhu(const char* haystack, const char* needle) {
  if (!haystack || !needle)
    return 0;

  if (*needle == 0)
    return haystack;

  const char* p_end = haystack;
  const char* pd = needle;
  while (*++pd) {
    p_end++;
  }

  while (*p_end) {
    const char* s = haystack;
    const char* d = needle;
    int i = 0;
    while (s[i] == d[i]) {
      if (!d[++i])
	return s;
    }

    p_end++;
    haystack++;
  }

  return 0;
}

// Leetcode solution #1
char* StrStr(const char *str, const char *target) {
  if (!*target) 
    return str;

  char *p1 = (char*) str;
  while (*p1) {
    char* p1Begin = p1;
    char* p2 = (char*) target;
    while (*p1 && *p2 && *p1 == *p2) {
      p1++;
      p2++;
    }

    if (!*p2)
      return p1Begin;

    p1 = p1Begin + 1;
  }

  return NULL;
}

// Leetcode solution #2, similar idea as strstr_dhu()
char* StrStr(const char *str, const char *target) {
  if (!*target) 
    return str;

  char* p1 = (char*) str;
  char* p2 = (char*) target;
  char* p1Adv = (char*) str;
  while (*++p2)
    p1Adv++;

  while (*p1Adv) {
    char *p1Begin = p1;
    p2 = (char*)target;
    while (*p1 && *p2 && *p1 == *p2) {
      p1++;
      p2++;
    }
    if (!*p2)
      return p1Begin;

    p1 = p1Begin + 1;
    p1Adv++;
  }

  return NULL;
}


// test harness
int main() {
  const char* haystack = "abcdefgh";
  const char* needle = "cd";
  Solution foo;
  cout << foo.strStr(haystack, needle) << endl;;

}
