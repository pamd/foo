/* http://www.mitbbs.com/article_t/JobHunting/32303629.html
 * Given an array list of lots of strings that are sorted in some 
 * unknown alphabetical order, print all possible alphabetical orders.
 * Written by wwwyhx.
 *
 * This implementation does NOT handle cycle well. If cycle exists in
 * input words, the program will sileently try all possibilities w/o 
 * printing out anything. It will be much better to print out an error 
 * message and terminate the program when cycle is found.
 */

#include <iostream>
#include <cassert>

using namespace std;

// Recursively build DAG among 26 letters, called by printAllOrder().
void buildMap(const char* str[], int n, int nBeg, bool bMap[26][26]) {
  if (str == NULL || n <= 1)
    return;


  cout << "nBeg: " << nBeg << endl;
  for (int i = 0; i < n; i++) 
    cout << str[i] << " ";
  cout << endl << endl;

  int nPrev = 0;
  // Skip blank word in dictionary
  while (str[nPrev][nBeg] == 0 && nPrev < n) 
    nPrev++;

  /* Starting from the first non-blank word in dictionay, compare each word 
   * with the word right after it, find the first char that is different 
   * between the two words, then build a directed edge from the letter in
   * the first word to the letter in second word. The DAG is represented
   * by bMap[26][26]. For example, If bMap[i][j] is true, then 'a' + i must 
   * be before 'a' + j in the new alphabetical order.  
   *
   * dhu: The following comparison algorithm is not intuitive at all.
   * It will be much natual to write a separate function to compare each word
   * with its next neighbor. See my function:
   *  pair<char, char> getEdge(const char*, const char*)
   * (If either of the char in returned pair is 0, no edge will be built.)
   */
  int nIter = nPrev + 1;
  while (nIter < n) {
    if (str[nPrev][nBeg] != str[nIter][nBeg]) {
      // Make sure each letter in a word is a-z
      assert(str[nPrev][nBeg] >= 'a' && str[nPrev][nBeg] <= 'z');
      assert(str[nIter][nBeg] >= 'a' && str[nIter][nBeg] <= 'z');
      
      // Build directed edge
      bMap[str[nPrev][nBeg] - 'a'][str[nIter][nBeg] - 'a'] = true;

      /* Now compare the next letter among words that we have skipped 
       * earlier. Weird idea, hard to follow. */ 
      buildMap(str + nPrev, nIter - nPrev, nBeg + 1, bMap);

      nPrev = nIter;
    } // end of "if"

    nIter++;

  } // end of "while" loop

  buildMap(str + nPrev, nIter - nPrev, nBeg + 1, bMap);
}

/* Topsort to print out all possible alphabetical orders 
 * based on the DAG. Called by printAllOrder(). 
 * order[26]: current topsort order;
 * rec[26]: in-degree of a certain node;
 * visit[26]: is a certain letter already visited? 
 */
void printOrder(bool bMap[26][26], int rec[26], bool visit[26], 
		char order[26], int nIndex) {
  if (nIndex >= 26) {
    for (int i = 0; i < 26; i++)
      cout << order[i] << " ";
    cout << endl;

    return;
  }

  //cout << order << endl;

  for (int i = 0; i < 26; i++) {
    if (visit[i] || rec[i] != 0) 
      continue;

    visit[i] = true;
    order[nIndex] = 'a' + i;
    // Decrement in-degree of vertices that are directly connected to vertex i.
    for (int j = 0; j < 26; j++) {
      if (bMap[i][j]) 
	rec[j]--;
    }

    // Recursive call
    printOrder(bMap, rec, visit, order, nIndex+1);

    // Recover in-degree of vertices that are directly connected to vertex i.     
    for (int j = 0; j < 26; j++) {
      if (bMap[i][j]) 
	rec[j]++;
    }

    visit[i] = false; // reset visit flag back to false.
  } 

}

/* The input array of strings str[] is the dictionary 
 * that have been sorted in the new alphabetical order. */
void printAllOrder(const char* str[], int n) {
  // Do nothing if the dictionary is empty or has only one word.
  if (str == NULL || n <= 0)
    return;
  
  bool bMap[26][26] = { { false } };
  buildMap(str, n, 0, bMap);

  return;

  int rec[26] = { 0 };
  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < 26; j++) {
      if (bMap[i][j]) 
	rec[j]++;
    }
  }

  char order[26];
  bool visit[26] = { false };
  printOrder(bMap, rec, visit, order, 0);
}

/* dhu function: return the first pair of characters in str1 and str2 
 * that are different when scanned from left to right. */  
pair<char, char> getEdge(const char* str1, const char* str2) {
  int i1 = 0, i2 = 0;
  while (str1[i1] && str2[i2] && str1[i1] == str2[i2]) {
    i1++;
    i2++;
  }

  return pair<char, char>(str1[i1], str2[i2]);
}

// dhu test harness
int main() {
  const char* str[26];
  str[0] = "a";
  str[1] = "ab";
  str[2] = "c";
  str[3] = "d";

  str[4] = "e";
  str[5] = "f";
  str[6] = "g";
  str[7] = "h";
  str[8] = "i";
  str[9] = "j";

  str[10] = "k";
  str[11] = "l";
  str[12] = "m";
  str[13] = "n";
  str[14] = "o";
  str[15] = "p";
  str[16] = "q";
  str[17] = "r";
  str[18] = "s";
  str[19] = "t";

  str[20] = "u";
  str[21] = "v";
  str[22] = "w";
  str[23] = "x";
  str[24] = "y";
  str[25] = "z";

  // dhu: why the above input dictionary can not determine the position of 'b'?

 
  /* If str[25] line is not commented out, the following call will 
   * print out only one order, because each letter's position is fixed. */

  //printAllOrder(str, 4); 

  /* If str[25] line is commented out, the following call will 
   * print 26 orders, because 'z' can be in any position. */
  //printAllOrder(str, 25); 

  pair<char, char> edge = getEdge(str[0], str[1]);
  cout << edge.first << " " << edge.second << endl;

  return 0;
}
