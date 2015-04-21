/* OJ problem: Validate if a given string is numeric.
 * Some examples:
 * "0" => true
 * " 0.1 " => true
 * "abc" => false
 * "1 a" => false
 * "2e10" => true
 *
 * dhu approach is embarassingly tedious.
 */

#include <stdio.h>

// Modified Dropbox solution to make code easier to follow 
class Solution {
 public: 
  bool isNumber(const char *s) {
    bool ret = false; // Final result
    bool dot = false; // decimal point '.' found
    bool exp = false; // exponential sign 'e' found
    bool spa = false; // space char ' ' found after non-space char

    // Remove all leading space characters
    while (*s == ' ') 
      ++s;

    /* Remove the leading +/- character 
     * Note that if input string starts with multiple +/- signs, 
     * only the first one will be removed. */
    if (*s == '+' || *s == '-')
      ++s;

    while (*s != '\0') {
      if (*s == ' ') 
	spa = true;
      else if (spa) 
	return false; // Any non-space char after space char invalidates input string.
        
      else if (*s >= '0' && *s <= '9')
	ret = true;
		
      else if (*s == 'e') {
	/* If exponential sign already exists, or 'e' is the first 
	 * non-space char, then the string is NOT a valid number. */
	if (exp || !ret) 
	  return false;
	exp = true;
	ret = false; // Number is required after 'e', so make ret flag false
      }
      else if (*s == '.') {
	// Decimal point is NOT allowed after 'e' or '.'
	if (exp || dot) 
	  return false;
	dot = true;
      }
      else if (*s == '-' || *s == '+') {
	/* Since the first leading +/- sign (if available) has been 
	 * removed, only '+/-' that is right after 'e' is allowed now. */
	if (*(s - 1) != 'e') 
	  return false;
      }
      // Any other character would make number invalid. 
      else 
	return false;

      ++s;
    }

    return ret;
  }

};

// MITBBS discussion on using Deterministic Finite-state Automaton (DFA) 
// http://www.mitbbs.com/article_t/JobHunting/32291899.html

// Test harness
int main(int argc, char** argv)
{
  char s1[] = "abc";
  char s2[] = "  +1.e-2  ";
  char s3[] = " .0e200";
  char s4[] = "0+00";

  Solution foo;
  printf("%s\n", foo.isNumber(s1)?"true":"false");
  printf("%s\n", foo.isNumber(s2)?"true":"false");
  printf("%s\n", foo.isNumber(s3)?"true":"false");
  printf("%s\n", foo.isNumber(s4)?"true":"false");
	
  return 0;
}
