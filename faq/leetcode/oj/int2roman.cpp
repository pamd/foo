/* Given an integer, convert it to a roman numeral.
 * Input is guaranteed to be within the range from 1 to 3999.
 *
 * Symbol   Value
 * ---------------
 *  I	      1
 *  V	      5
 *  X  	     10
 *  L	     50
 *  C	    100
 *  D	    500
 *  M	  1,000
 */

#include <string>
#include <iostream>

using namespace std;

// dhu solution: 148ms for large dataset
class Solution {
public:
  string intToRoman(int num) {
    string ret;
    int factor = 1000;
    while (factor > 0) {
      int digit = num / factor; 
      num %= factor;
      ret += convert(digit, factor);
      factor /= 10;
    }
    
    return ret;
  }

  string convert(int digit, int factor) {
    if (digit == 0)
      return "";

    string ret;
    if (factor == 1000) {
      for (int i = 0; i < digit; i++)
	ret.push_back('M');
      return ret;
    }

    char upper, mid, lower;
    if (factor == 100) {
      upper = 'M';
      mid = 'D';
      lower = 'C';
    }
    else if (factor == 10) {
      upper = 'C';
      mid = 'L';
      lower = 'X';
    }
    else {
      upper = 'X';
      mid = 'V';
      lower = 'I';
    }

    if (digit < 4) {
      for (int i = 0; i < digit; i++)
	ret.push_back(lower);
    }
    else if (digit == 4) {
      ret.push_back(lower);
      ret.push_back(mid);
    }
    else if (digit < 9) {
      ret.push_back(mid);
      for (int i = 0; i < digit - 5; i++)
	ret.push_back(lower);
    }
    else {
      ret.push_back(lower);
      ret.push_back(upper);
    }

    return ret;
  }
};

// anson627 solution: very compact
class Solution {
public:
  map<int, string> dict;
  string intToRoman(int num) {
    dict.clear();
    dict[1] = "I";
    dict[4] = "IV";
    dict[5] = "V";
    dict[9] = "IX";
    dict[10] = "X";
    dict[40] = "XL";
    dict[50] = "L";
    dict[90] = "XC";
    dict[100] = "C";
    dict[400] = "CD";
    dict[500] = "D";
    dict[900] = "CM";
    dict[1000] = "M";
    string result = "";
    for (map<int, string>::reverse_iterator it = dict.rbegin(); it != dict.rend(); it++) {
      while (num >= it->first) {
	result += it->second;
	num -= it->first;
      }
    }

    return result;
  }

};

// dhu test harness
/*
int main() {
  int x = 12;
  Solution foo;
  cout << foo.intToRoman(x) << endl;

}
*/

// Dropbox solution
// -----------------
#define MAX_LENGTH 5

// Use a hard-coded 2-D array of strings
char roman[4][10][MAX_LENGTH] =
{
  "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX",
  "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC",
  "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM",
  "", "M", "MM", "MMM", "  ", " ", "  ", "   ", "    ", "  "
};

void IntegerToRoman(int n, char* s) {
  strcpy(s, "");
  if (n > 3999 || n < 1)
    return;
  
  int digit = 1;
  int m = 1;
  while ((m *= 10) <= n)
    ++digit;
  
  while ((m /= 10) > 0) {
    strcat(s, roman[--digit][n/m]);
    n %= m;
  }
}

int main(int argc, char** argv)
{

  return 0;
}
