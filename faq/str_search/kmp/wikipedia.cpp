/* Knuth-Morris-Pratt string searching algorithm, based on wikipedia. */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Pre-process the needle (pattern) string and set the overlap vector.
 * 
 * Wikipedia: 
 * http://en.wikipedia.org/wiki/Knuth-Morris-Pratt_algorithm
 *-----------------------------------------------------------------------------------
 * The time complexity of building the table is O(n), where n is the length of needle
 * string. As except for some initialization, all the work is done in the while loop, 
 * it is sufficient to show that this loop executes in O(n) time, which will be done 
 * by simultaneously examining the quantities index and (index - candidate). 
 *
 * In the first branch, (index - candidate) is preserved, as both index and 
 * candidate are incremented simultaneously, but naturally, index is increased. 
 *
 * In the second branch, candidate is replaced by overlap[candidate], 
 * which we saw above is always strictly less than candidate, thus increasing 
 * (index - candidate). 
 *
 * In the third branch, index is incremented and candidate is not, so both index 
 * and (index - candidate) increase. 

 * Since index >= (index - candidate), this means that at each stage, either index 
 * or a lower bound for index increases; therefore since the algorithm terminates 
 * when index == n, it must terminate after at most 2*n iterations of the loop, 
 * because (index - candidate) begins at 2. 
 *
 * Therefore the complexity of the table algorithm is O(n).
 * 
 * dhu: we can imagine that index and candidate are two cursors on a ruler. 
 * Initially index is at 2, and candidate is at 0. In each step, either both 
 * cursors will move forward one unit, or candidate will move backward, 
 * or only index moves forward one unit (when candidate already reaches the 
 * left side of the ruler). So in each step, the distance between index and 
 * candidate (index - candidate) will either remain constant, or increase by 
 * at least one unit. When index reaches the right side of the ruler 
 * (index == len), the program is done. So the total number of steps in the 
 * "while" loop will be at most 2 * len. 
 * (Note that when both index and candidate move forward one unit, 
 * these two movements are done in one iteration of the loop.)
 */ 
void getOverlap_wiki(const string& needle, int overlap[]) {
  size_t len = needle.size();
  overlap[0] = -1;
  if (len > 1)
    overlap[1] = 0;

  int candidate = 0;
  size_t index = 2;
  while (index < len) {
    // If the suffix that ends with needle[index - 1] is a valid 
    // prefix of original string, increment both candidate and index. 
    if (needle[index - 1] == needle[candidate]) {
      candidate++;
      overlap[index] = candidate;
      index++;
    }

    // If it doesn't match, we will check back.
    // dhu: note that in this branch, we can not simply write:
    // 
    //    else if (candidate > 0) {
    //      candidate = 0;
    //    }
    // ---------------------------------------------------- 
    // To see why this is wrong, set needle to "ABAABABX", 
    //-----------------------------------------------------
    // then compare the results from this function and the results
    // from getOverlap_bug(), which is defined below.  
    else if (candidate) // aka. else if (candidate > 0)
      candidate = overlap[candidate];

    // If candidate is 0, then we have run out of candidates, 
    // so we set overlap[index] to 0, then move index forward. 
    // Here we do not need to set candidate to 0, since it already is.
    else {
      overlap[index] = 0;
      index++;
    }
  } // end of "while" loop

}

// Buggy Approach to build overlap table
void getOverlap_wiki_bug(const string& needle, int overlap[]) {
  size_t len = needle.size();
  overlap[0] = -1;
  if (len > 1)
    overlap[1] = 0;

  int candidate = 0;
  size_t index = 2;
  while (index < len) {
    if (needle[index - 1] == needle[candidate]) {
      candidate++;
      overlap[index] = candidate;
      index++;
    }

    // Start buggy section
    else if (candidate > 0) 
      candidate = 0;
    // End of buggy section

    else {
      overlap[index] = 0;
      index++;
    }
  }

}

/* KMP algorithm. If needle string is found, return the index of the character
 * where needle substring starts; returns -1 if needle string is not found. 
 *
 * wikipedia:
 *----------------
 * Assuming the prior existence of the table overlap[], the search portion of 
 * the Knuth–Morris–Pratt algorithm has complexity O(k), where k is the length 
 * of haystack and the O is big-O notation. As except for the fixed overhead 
 * incurred in entering and exiting the function, all the computations are 
 * performed in the while loop, we will calculate a bound on the number of 
 * iterations of this loop; in order to do this we first make a key observation 
 * about the nature of overlap[]. By definition it is constructed so that if a 
 * match which had begun at haystack[m] fails while comparing haystack[m + i] to 
 * needle[i], then the next possible match must begin at haystack[m + (i - needle[i])].
 * In particular the next possible match must occur at a higher index than m, 
 * so that T[i] < i.
 *
 * Using this fact, we will show that the loop can execute at most 2k times. 
 * For in each iteration, it executes one of the two branches in the loop. 
 * The first branch invariably increases i and does not change m, so that the 
 * index m + i of the currently scrutinized character of haystack is increased. 
 * The second branch adds i - T[i] to m, and as we have seen, this is always a 
 * positive number. Thus the location m of the beginning of the current potential 
 * match is increased. Now, the loop ends if m + i = k; therefore each branch of 
 * the loop can be reached at most k times, since they respectively increase 
 * either m + i or m, and m <= m + i: if m = k, then certainly m + i >= k, so that
 * since it increases by unit increments at most, we must have had m + i = k at some
 * point in the past, and therefore either way we would be done.

 * Thus the loop executes at most 2k times, showing that the time complexity of the 
 * search algorithm is O(k).

 * Here is another way to think about the runtime: Let's say we begin to match needle
 * and haystack at position i and p, if needle exists as a substring of haystack at p, 
 * then needle[0 : m] == haystack[p : p+m]. Upon success, that is, the word and the 
 * text matched at the positions (needle[i] == haystack[p+i]), we increase i by 1
 * (i++). Upon failure, that is, the word and the text does not match at the positions 
 * (needle[i] != haystack[p+i]), the text pointer is kept still, while the word pointer 
 * rolls back a certain amount (i = overlap[i], where overlap is the jump table). And 
 * we attempt to match needle[overlap[i]] with haystack[p+i]. The maximum number of 
 * roll-back of i is bounded by i, that is to say, for any failure, we can only roll back 
 * as much as we have progressed up to the failure. Then it is clear the runtime is 2k.
 *
 * dhu: We can imagine that m and m+i are two cursors on the a ruler. Initially both are
 * on the left side of the ruler. In each step, either m+i moves forward one unit, or
 * m moves forward x steps (0 < x <= i), so cursor m will never be on the right side of 
 * m+i (but they could be at the same position when i is 0). The runtime is actually the
 * sum of distances that m and m+i will move before m+i reaches the right side of the ruler.
 * We can see that the sum will be at most twice the length of the ruler.
 *
 * 20 ms for leetcode OJ large dataset. 
 */
int wikipedia(const string& haystack, const string& needle) {
  int needle_len = needle.size();
  // If needle str is empty, return 0 immediately
  if (needle_len == 0)
    return 0;

  int txt_len = haystack.size(); 
  int overlap[needle_len];
  getOverlap_wiki(needle, overlap);

  int m = 0; // Starting index of a possible needle match in haystack string
  int i = 0; // Index of current char that is being compared in needle string 
  while (m + i < txt_len) {
    if (haystack[m + i] == needle[i]) {
      i++;
      if (i == needle_len) // We found it!
	return m;
    }
    else {
      m = m + i - overlap[i];
      /*
      if (overlap[i] > -1)
	i = overlap[i];
      else
	i = 0;
      */
      // Equivalent to:
      if (i)
	i = overlap[i];
    }
  }

  // Return -1 if needle string is not found.
  return -1;
}

// Test harness
int main(int argc, char** argv) {
  //               01234567890123456789
  string haystack("ABAAABABABABABAB");
  string needle("ABABAB");
  cout << wikipedia(haystack, needle) << endl;

  /*
  // For debugging only
  if (argc != 2) {
    cout << "Needle string not found" << endl;
    return 0;
  }
  */

  return 0;
}
