/* Given two binary strings, return their sum (also a binary string).
 * For example, a = "11", b = "1", the sum should be "100".
 */

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
  string addBinary(string a, string b) {
    int ai = a.size() - 1;
    int bi = b.size() - 1;
    int carry = 0;
    string result;
    char tmp;
    while (ai >= 0 && bi >= 0) {
      if (a[ai] == '1' && b[bi] == '1') { 
	if (carry == 1)
	  tmp = '1';
	else
	  tmp = '0';
	carry = 1;
      }
      else if (a[ai] == '1' && b[bi] == '0') {
	if (carry == 1) {
	  tmp = '0';
	}
	else
	  tmp = '1';
      }
      else if (a[ai] == '0' && b[bi] == '1') {
	if (carry == 1) {
	  tmp = '0';
	  carry = 1;
	}
	else
	  tmp = '1';
      }
      else {
	if (carry == 1) 
	  tmp = '1';
	else
	  tmp = '0';
	carry = 0;
      }
      result.insert(0, 1, tmp);
      ai--;
      bi--;
    }

    while (ai >= 0) {
      if (a[ai] == '1' && carry == 1) 
	tmp = '0';
      else if (a[ai] == '0' && carry == 1) {
	tmp = '1';
	carry = 0;
      }
      else
	tmp = a[ai];
      result.insert(0, 1, tmp);
      ai--;
    }

    while (bi >= 0) {
      if (b[bi] == '1' && carry == 1) 
	tmp = '0';
      else if (b[bi] == '0' && carry == 1) {
	tmp = '1';
	carry = 0;
      }
      else
	tmp = b[bi];
      result.insert(0, 1, tmp);
      bi--;
    } 

    if (carry)
      result.insert(0, 1, '1');

    return result;
  }
};

/*
int main() {
  string a("0");
  string b("1");
  Solution foo;
  cout << foo.addBinary(a, b) << endl;
}
*/

/* Online solution */
string AddBinary(string s1, string s2) {
  int len1 = s1.size()-1;
  int len2 = s2.size()-1;
  string s = len1 > len2? s1 : s2;
  int len = s.size() - 1;
  char carry = '0';

  while (len1 >= 0 && len2 >= 0) {
    s[len] = (s1[len1] ^ s2[len2] ^ carry);
    /* Among three values of s1[len1], s2[len2] and carry, 
     * if any two of them are '1', then carry must be '1' too. */
    carry = (s1[len1] & s2[len2]) | (carry & s1[len1]) |  (carry & s2[len2]);
    --len, --len1, --len2;
  }
	
  while(len1 >= 0) {
    s[len] = (s1[len1] ^ carry) + '0';
    carry = s1[len1] & carry;
    --len, --len1;
  }
	
  while(len2 >= 0) {
    s[len] = (s2[len2] ^ carry) + '0';
    carry = s2[len2] & carry;
    --len, --len2;
  }
	
  if (carry ^ '0') // If carry is '1', insert carry 
    s.insert(s.begin(), carry);

  return s;
}

// Test harness
int main(int argc, char** argv)
{
  string s = AddBinary("1", "111");
  cout << s << endl;

  //
  //	
  //	s = AddBinary("11", "1");
  //    cout << s << endl;
  //	
  //	s = AddBinary("101", "10");
  //    cout << s << endl;

  return 0;
}
