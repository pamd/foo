/* Google phone: Find a vowel product sum of an ASCII string. 
 *
 * There are 26 English upper and lower-case letters. Consider 
 * the encoding where vowels are mapped to numbers as follows: 
 * (a=1, e=5, i=9, o=15, u=21, y=25 or 0). 
 * A vowel sequence is a maximal substring of consecutive vowels. 
 * A vowel product is the product of the vowel encoding of all vowels 
 * in a vowel sequence. The vowel product sum is the sum of the vowel 
 * product of all vowel sequences in the string.
 * A letter in [AEIOUaeiou] is always a vowel. 'y' or 'Y' is a vowel 
 * if it is preceded by a consonant; otherwise, it is a consonant. 
 * An ASCII character is either a vowel, a consonant, or a non-letter. 
 * Treat all upper-case letters the same as lower-case letters.
 *
 * Examples:
 * "Google Guy" has vowel sequences of "oo", "e", and "u". 
 * Its score is 15 * 15 + 5 + 21 = 251.
 *
 * "Yyyyy" has vowel sequences of "y" and "y". 
 * Its score is 25 + 25 = 50.
 *
 * "myopia" has vowel sequences of "yo" and "ia". 
 * Its score is 25 * 15 + 9 * 1 = 384.
 *
 * "Quietly" has vowel sequences of "uie" and "y". 
 * Its score is 21 * 9 * 5 + 25 = 970.
 *
 * "I'm Feeling Yucky!" has vowel sequences of "I", "ee", "i", "u", and "y". 
 * Its score 9 + 5 * 5 + 9 + 21 + 25 = 89. The first 'Y' in "Yucky" is 
 * preceded by a space (non-letter), so it is not considered a vowel.
 */

#include <string>
#include <iostream>

using namespace std;

int readLetter(char c) {
  if (c >= 'a' && c <= 'z') {
    if (c == 'a' || c == 'o' || c == 'e' || c == 'i' || c == 'u' || c == 'y')
      return c - 'a' + 1;
  }

  if (c >= 'A' && c <= 'Z') {
    if (c == 'A' || c == 'O' || c == 'E' || c == 'I' || c == 'U' || c == 'Y')
      return c - 'A' + 1;
  }

  return 0;
}

int getSum(const string& str) {
  bool prev_vowel = true;
  int sum = 0;
  int product = 0;
  for (size_t i = 0; i < str.size(); i++) {
    int curr = readLetter(str[i]);
    // Consonant letter, or 'y'/'Y' that is right after vowel
    if (curr == 0 || (curr == 25 && prev_vowel)) {
      sum += product;
      product = 0;
      prev_vowel = false;
      // If current letter is space, tab or new line, treat it as vowel
      if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
	prev_vowel = true;
    }
    else {  // Vowel letter
      if (product == 0)
	product = curr;
      else
	product *= curr;
      prev_vowel = true;
    }
  }

  sum += product;
  return sum;
}

int main() {
  string str[5] = { "Google Guy", 
		    "Yyyyy", 
		    "myopia",
		    "Quietly",
		    "I'm Feeling Yucky!"};

  for (int i = 0; i < 5; i++) {
    int sum = getSum(str[i]);
    cout << str[i] << ": " << sum << endl;
  }

  return 0;
}
