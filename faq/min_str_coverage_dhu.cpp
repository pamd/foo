/* Coding: A long string text, given some characters, find the shortest
 * substring covering all given characters. 
 * http://mitbbs.com/article_t/JobHunting/31731763.html
 */

#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

// User-defined struct
struct Range
{
  int begin;
  int end;
};

/* Get the shortest coverage of target substring in text string.
 * Note that this algorithm will still work even if the input target 
 * string has duplicate characters, because every time the current 
 * char in input text string matches a char in target string, we will
 * increment counter by 1. So we are keeping track of how many chars 
 * in target string have been found.   
 */
Range shortestSubstring(const char* text, const char* target) {
  int text_sz = strlen(text);
  int target_sz = strlen(target);

  int* target_tab = new int[256];
  int* text_tab = new int[256];
    
  for(int i = 0; i < 256; i++) {
    target_tab[i] = 0;
    text_tab[i] = 0;
  }
    
  for(int i = 0; i < target_sz; i++) {
    int c = target[i];
    target_tab[c]++;
  }
    
  int begin = 0;

  /* counter keeps track of how many chars in target string have 
   * been matched in text substring from begin to end.
   * When counter == target_sz, we have found a valid range. */
  int counter = 0; 
    
  Range minRange;
  minRange.begin = -1; // dummy starting index 
  minRange.end = -1;   // dummy ending index
    
  int minLength = text_sz + 1;
  int length = 0;
  for (int end = 0; end < text_sz; end++) {
    int c = text[end];
    if (target_tab[c] > 0) {
      // IMPORTANT!!! The next line MUST use <, not == or >
      if (text_tab[c] < target_tab[c])
	counter++;
      text_tab[c]++;
    }
        
    // text[begin:end] is not valid, so we keep moving end pointer forward
    if (counter != target_sz)
      continue;

    // text[begin:end] is valid, so we truncate leading unnecessary characters 
    while (begin < end) {
      c = text[begin];
      if (target_tab[c] == 0)
	begin++;
      else if (text_tab[c] > target_tab[c]) {
	begin++;
	text_tab[c]--;
      }
      else {
	length = end - begin + 1;
	// Update current minimum range 
	if (length < minLength) {
	  minLength = length;
	  minRange.begin = begin;
	  minRange.end = end;
	}	
	begin++;
	text_tab[c]--;
	counter--;
	break;
      }
    }
        
  }
    
  return minRange;
}

// Test harness
int main()
{
  //                  012345678901234567890
  const char* text = "ADOBECODEBANC xyzABC";
  const char* target = "BANC";
  //const char* target = "ABCDA";

  Range ret = shortestSubstring(text, target);
  cout << "begin: " << ret.begin << endl;
  cout << "end: " << ret.end << endl;

  return 0;
}
