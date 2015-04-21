/* Given a roman number, convert it to an integer.
 * Input is guaranteed to be within the range from 1 to 3999.
 */

#include <iostream>
#include <string>

using namespace std;

// dhu solution: 176ms for large dataset
class Solution {
public:
  // Helper function: parse one char
  int convert1(char c) {
    if (c == 'I')
      return 1;
    if (c == 'V')
      return 5;
    if (c == 'X')
      return 10;
    if (c == 'L')
      return 50;
    if (c == 'C')
      return 100;
    if (c == 'D')
      return 500;
    // M is 1000
    return 1000;
  }

  // Another helper function: parse two chars as a group
  int convert2(string char2) {
    if (char2 == "IV")
      return 4;
    if (char2 == "IX")
      return 9;
    if (char2 == "XL")
      return 40;
    if (char2 == "XC")
      return 90;
    if (char2 == "CD")
      return 400;
    if (char2 == "CM")
      return 900;
    // Return 0 otherwise
    return 0;
  }

  // Main function
  int romanToInt(string s) {
    if (s.size() == 0)
      return 0;

    int ret = 0;
    if (s.size() == 1) 
      return convert1(s[0]);

    // "prev_parsed" keeps track of whether previous char has been parsed or not
    bool prev_parsed = false; 
    for (size_t i = 1; i < s.size(); i++) {
      char prev = s[i - 1];
      char curr = s[i];
      if (!prev_parsed && prev == curr) {
	ret += 2 * convert1(curr);
	prev_parsed = true;
	continue;
      }

      /* If previous char has been parsed, do NOT parse the 
       * current char yet. Leave it to the next iteration. */
      if (prev_parsed) {
	prev_parsed = false;
	continue;
      }

      // Parse previous and current characters together as a group
      string combo = s.substr(i - 1, 2);
      int pair_val = convert2(combo);
      // If prev and curr form a valid pair, add the value
      if (pair_val) {
	ret += pair_val;
	prev_parsed = true;
      }
      // If prev and curr do not form a valid pair, only parse prev
      else {
	ret += convert1(prev);
	prev_parsed = false;
      }
    }
    // Make sure the last char will be parsed
    if (!prev_parsed) 
      ret += convert1(s[s.size() - 1]);
    
    return ret;
  }

};

// anson627 solution: very compact
class Solution {
public:
  map<char, int> dict;
  int romanToInt(string s) {
    dict['M'] = 1000;
    dict['D'] = 500;
    dict['C'] = 100;
    dict['L'] = 50;
    dict['X'] = 10;
    dict['V'] = 5;
    dict['I'] = 1;
    int res = 0;
    int i = 0;
    while (i < s.size() - 1) {
      if (dict[s[i]] < dict[s[i+1]]) 
	res -= dict[s[i]];
      else 
	res += dict[s[i]];
      i++;
    }
    res += dict[s[i]];

    return res;
  }
};

// Dropbox solution: too tedious, not checked yet
// -----------------------------------------------
#define MAX_LENGTH 3

enum DigitUnit
  {
    OneDigit = 1,
    TenDigit = 10,
    HundredDigit = 100,
    ThousandDigit = 1000,
  
    MaxDigit = 100000,
  };

//Trie node
struct RomeTrieNode
{
  char Latin;
  int Value;
  int NoOfChild;
  struct RomeTrieNode* Next[MAX_LENGTH];
};


/*

  Trie illustration:

  Latin Letter(Roman Number, Integer Number, Node Index)

  I(I,1,0)
  â”‚        
  â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
  â”‚           â”‚           â”‚
  â”‚           â”‚           â”‚
  I(II,2,2)   V(IV,4,3)   X(IX,9,4)
  â”‚
  â”‚
  I(III,3,5)
    
    
  V(V,5,1)â”€â”€â”€I(VI,6,6)â”€â”€â”€I(VII,7,7)â”€â”€â”€I(VIII,8,8)

*/

// Tries for each digit
struct RomeTrieNode Ones[9] = {
  /* Node 0 */    {'I', 1, 3, {Ones+2,Ones+3,Ones+4}},
  /* Node 1 */    {'V', 5, 1, {Ones+6, 0, 0}},
  /* Node 2 */    {'I', 2, 1, {Ones+5, 0, 0}},
  /* Node 3 */    {'V', 4, 0, {0, 0, 0}},
  /* Node 4 */    {'X', 9, 0, {0, 0, 0}},
  /* Node 5 */    {'I', 3, 0, {0, 0, 0}},
  /* Node 6 */    {'I', 6, 1, {Ones+7, 0, 0}},
  /* Node 7 */    {'I', 7, 1, {Ones+8, 0, 0}},
  /* Node 8 */    {'I', 8, 0, {0, 0, 0}},
};

struct RomeTrieNode Tens[9] = {
  /* Node 0 */    {'X', 10, 3, {Tens+2,Tens+3,Tens+4}},
  /* Node 1 */    {'L', 50, 1, {Tens+6, 0, 0}},
  /* Node 2 */    {'X', 20, 1, {Tens+5, 0, 0}},
  /* Node 3 */    {'L', 40, 0, {0, 0, 0}},
  /* Node 4 */    {'C', 90, 0, {0, 0, 0}},
  /* Node 5 */    {'X', 30, 0, {0, 0, 0}},
  /* Node 6 */    {'X', 60, 1, {Tens+7, 0, 0}},
  /* Node 7 */    {'X', 70, 1, {Tens+8, 0, 0}},
  /* Node 8 */    {'X', 80, 0, {0, 0, 0}},
};

struct RomeTrieNode Hundreds[9] = {
  /* Node 0 */    {'C', 100, 3, {Hundreds+2,Hundreds+3,Hundreds+4}},
  /* Node 1 */    {'D', 500, 1, {Hundreds+6, 0, 0}},
  /* Node 2 */    {'C', 200, 1, {Hundreds+5, 0, 0}},
  /* Node 3 */    {'D', 400, 0, {0, 0, 0}},
  /* Node 4 */    {'M', 900, 0, {0, 0, 0}},
  /* Node 5 */    {'C', 300, 0, {0, 0, 0}},
  /* Node 6 */    {'C', 600, 1, {Hundreds+7, 0, 0}},
  /* Node 7 */    {'C', 700, 1, {Hundreds+8, 0, 0}},
  /* Node 8 */    {'C', 800, 0, {0, 0, 0}},
};

struct RomeTrieNode  Thousands[9] = {
  /* Node 0 */    {'M', 1000, 1, {Thousands+1,0, 0}},
  /* Node 1 */    {'M', 2000, 1, {Thousands+2, 0, 0}},
  /* Node 2 */    {'M', 3000, 0, {0, 0, 0}},
};


// Find the trie root base on the begin letter.
// If the digit that already analyzed is less than than next digit,
// or the latin letter is not a valid roman letter,
// empty pointer would be returned.
struct RomeTrieNode* FindBegin(char latin, DigitUnit* curDigit)
{
  DigitUnit nextDigit = MaxDigit;
  struct RomeTrieNode* head = 0;
  switch(latin) {
  case 'I': 
    nextDigit = OneDigit;
    head = Ones;
    break;
  case 'V': 
    nextDigit = OneDigit;
    head = Ones+1;
    break;
  case 'X': 
    nextDigit = TenDigit;
    head = Tens;
    break;
  case 'L': 
    nextDigit = TenDigit;
    head = Tens+1;
    break;
  case 'C': 
    nextDigit = HundredDigit;
    head =  Hundreds;
    break;
  case 'D': 
    nextDigit = HundredDigit;
    head =  Hundreds+1;
    break;
  case 'M': 
    nextDigit = ThousandDigit;
    head = Thousands;
    break;
    
  default: 
    return 0; //invalid latin letter for roman number
  }
  
  // check if the order of latin letter is correct
  if (nextDigit < *curDigit) {
    *curDigit = nextDigit; //update current digit
    return head;
  }
	
  // else, the order of latin letter in roman number is misranged
  return 0;
}

int RomeToInteger(char* roman) {
  //the string is empty
  if (*roman == '\0') 
    return 0;

  int value = 0;
  struct RomeTrieNode* curNode = 0;
  struct RomeTrieNode* nextNode = 0;
  DigitUnit curDigit = MaxDigit;  
	
  // Find the begin root for current digit
  curNode = FindBegin(*roman,&curDigit);
  // Invalid latin letter for roman number,
  // or the order of latin letter is not correct
  if (!curNode) 
    return 0;

  for(char* r = roman+1; *r; ++r) {
    nextNode = 0;
    //search for next on trie
    for (int i = 0; i < curNode->NoOfChild ; ++i)
      if (curNode->Next[i]->Latin == *r) {
	nextNode = curNode->Next[i];
	break;
      }

      if (!nextNode) {
	value += curNode->Value; //add up the value
	//a new begin digit
	curNode = FindBegin(*r, &curDigit);
	if (!curNode) 
	  return 0;
      }
      else {
	curNode = nextNode;
      }
  }

  value += curNode->Value; // add up the value
	
  return value;
}


int main(int argc, char** argv)
{
  char roman[10] ="MMXII";

  printf("%s: %d",roman, RomeToInteger(roman));

  return 0;
}
