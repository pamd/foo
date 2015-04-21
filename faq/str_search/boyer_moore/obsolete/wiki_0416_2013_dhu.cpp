/* dhu C++ implementation of Boyer-Moore algorithm, based on the C 
 * implementation on:
 * http://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string_search_algorithm
 *
 * "Time limit exceeded" error when testing Leetcode OJ large dataset.
 */

#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

const int ALPHABET_LEN = 256;
 
// Helper function that returns the maximum of two input integers
int max(int a, int b) {
  if (a > b)
    return a;

  return b;
}

// Bad character table: bad_char[c] contains the distance between the last 
// character of needle string and the rightmost occurence of c in needle.
//
// If c is not found in pat, then bad_char[c] = needle_len.
// If c is at haystack[i] and c != needle[needle_len - 1], we can
// safely shift i over by bad_char[c], which is the minimum distance
// needed to shift needle string forward to get haystack[i] lined up 
// with some character in needle.
//
// This algorithm runs in O(alphabet_len + needle_len) time.
void get_bad_char(int* bad_char, const string& needle) {
  for (int i = 0; i < ALPHABET_LEN; i++) {
    bad_char[i] = needle.size();
  }

  for (int i = 0; i < (int) needle.size() - 1; i++) {
    bad_char[(int) needle[i]] = needle.size() - 1 - i;
  }
}
 
// Helper function for get_good_suffix().
// Returns true if the suffix of word starting from 
// word[position] is a prefix of word; returns false otherwise.
//
// dhu: Due to the for loop in this function, the time to 
// build good_suffix table is O(M^2), instead of O(M). 
// NOT good.
int is_prefix(const string& word, int position) {
  int suffix_len = word.size() - position;
  // could also use the strncmp() library function here
  for (int i = 0; i < suffix_len; i++) {
    if (word[i] != word[position + i]) {
      return false;
    }
  }

  return true;
}
 
// Helper functionfor get_good_suffix().
// Returns length of the longest suffix of word ending on word[position].
// For example, suffix_length("dddbcabc", 4) = 2.
int suffix_length(const string& word, int position) {
  int word_len = word.size();

  // Increment suffix length i to the first mismatch or beginning of the word
  int idx = 0;
  while (word[position - idx] == word[word_len - 1 - idx] && idx < position)
    idx++;

  return idx;
}
 
// Good suffix table: given a mismatch at needle[position], we want to align 
// the needle with the next possible full match based on what we already know 
// about needle[position + 1] to needle[needle_len - 1].
//
// Case #1:
// needle[position  + 1] to needle[needle_len - 1] does not occur elsewhere
// in needle, the next plausible match starts at or after the mismatch.
// If, within the substring needle[position + 1 ... needle_len - 1], lies 
// a prefix of needle, the next plausible match is here (if there are multiple
// prefixes in the substring, pick the longest). Otherwise, the next plausible 
// match starts past the character aligned with needle[needle_len - 1].
// 
// Case #2:
// needle[position + 1] to needle[needle_len - 1] does occur elsewhere in needle. 
// The mismatch tells us that we are not looking at the end of a match in haystack. 
// We may, however, be looking at the middle of a match.
// 
// The first loop, which takes care of Case #1, is analogous to the KMP table, 
// adapted for a "backwards" scan order with the additional restriction that 
// the substrings it considers as potential prefixes are all suffixes. 
// In the worst case scenario, needle consists of the same letter repeated, 
// so every suffix is a prefix. 
// This loop alone is not sufficient, however:
// Suppose that needle is "ABYXCDEYX", and haystack is ".....ABYXCDEYX".
// In haystack, we will match haystack[8], which is 'X', then haystack[7],
// which is 'Y', then haystack[6], and find that 'B' != 'E'. There is no prefix 
// of needle in the suffix "YX", so the first loop tells us to skip forward 
// by 9 characters, but this is NOT correct.
//
// Although superficially similar to the KMP table, the KMP table
// relies on information about the beginning of the partial match
// that the Boyer-Moore algorithm does not have.
//
// The second loop addresses Case #2. Since suffix_length may not be
// unique, we want to take the minimum value, which will tell us
// how far away the closest potential match is.
void get_good_suffix(vector<int>& good_suffix, const string& needle) {
  int needle_len = needle.size();
  int last_prefix_index = needle_len - 1;
 
  // First loop
  for (int p = needle_len - 1; p >= 0; p--) {
    if (is_prefix(needle, p + 1)) 
      last_prefix_index = p + 1;
    
    good_suffix[p] = last_prefix_index + (needle_len - 1 - p);
  }
 
  // Second loop
  for (int p = 0; p < needle_len - 1; p++) {
    int slen = suffix_length(needle, p);
    if (needle[p - slen] != needle[needle_len - 1 - slen]) {
      good_suffix[needle_len - 1 - slen] = needle_len - 1 - p + slen;
    }
  }

}
 
// Return the starting index of needle substring in haystack;
// return -1 if need le is not found. 
int boyer_moore_dhu(const string& haystack, const string& needle) {
  int N = haystack.size();
  int M = needle.size();

  if (M == 0)
    return 0;

  int bad_char[ALPHABET_LEN];
  vector<int> good_suffix(M);

  get_bad_char(bad_char, needle);
  get_good_suffix(good_suffix, needle);

  // /*
  cout << "bad char table:" << endl; 
  for (int i = 0; i < ALPHABET_LEN; i++) {
    if (bad_char[i] != (int) needle.size()) {
      cout << (char) i << ": " << bad_char[i] << endl;
    }
  }

  cout << "Good suffix: " << endl;
  for (size_t i = 0; i < good_suffix.size(); i++) {
    cout << i << ": " << good_suffix[i] << endl;
  }
  cout << endl;
  // */

  int i = M - 1; // Index of char being matched in haystack 
  while (i < N) {
    int j = M - 1; // Index of char being matched in needle
    while (j >= 0 && (haystack[i] == needle[j])) {
      --i;
      --j;
    }

    if (j < 0) // We found the match!
      return i + 1;
    
    i += max(bad_char[(int) haystack[i]], good_suffix[j]);
  }

  return -1; // NOT found
}

// Test harness
int main() {
  string haystack = "asdfghrtyuewruhfkwetanpanmandert";
  string needle = "anpanman";

  int ret = boyer_moore_dhu(haystack, needle);
  if (ret != -1) 
    cout << "Found it: " << haystack.substr(ret) << endl;
  else 
    cout << "Not found" << endl;

  return 0;
}

/* 
 * For needle string "anpanman":
 * Bad char table:
 *   a: 1
 *   m: 2
 *   n: 3
 *   p: 5
 *
 * Good suffix: 
 *   0: 13
 *   1: 12
 *   2: 11
 *   3: 10
 *   4: 9
 *   5: 5
 *   6: 9
 *   7: 1
 *
 */
