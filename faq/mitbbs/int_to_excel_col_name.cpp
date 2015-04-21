/* Convert an input int into column name in Excel format. 
 * For example: 0 -> A, 1 -> B, ..., 25 -> Z, 26: AA, 27: AB
 * 
 * Refer to:
 * http://www.mitbbs.com/article_t/JobHunting/32126949.html
 *
 */

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cassert>

using namespace std;

// dhu
string dhu(int x) {
  if (x == 0)
    return string("A");

  string str;
  while (x > 0) {
    int rem = x % 26;
    if (str.size() == 0) {
      //int rem = x % 26;
      str.insert(0, 1, rem + 'A');
    }
    else {
      if (rem == 0) {
	x -= 26;
	rem = 26;
      } 
      str.insert(0, 1, rem - 1 + 'A');
    }
    x = x / 26;
  }

  return str;
}

/* dhu #2: a better solution
*****************************/
string dhu2(int x) {
  string str;
  x++;
  while (x) {
    char c = (x - 1) % 26 + 'A';
    str.push_back(c);
    x = (x - 1) / 26;
  }

  reverse(str.begin(), str.end());
  return str;
}

// lolhaha
string lolhaha(int x) {
  string str;
  // Step 1: increment x by 1
  x++;

  // Step 2:
  while ( x > 0) {
    int rem = x % 26;
    if (x % 26 == 0) {  
      str.insert(0, 1, 'Z');
      x = x - 26;
    }
    else {
      str.insert(0, 1, rem - 1 + 'A');    
    } 
    x /= 26;
  }

  return str;
}

// realife
string realife(int n) {
  if (n < 0) 
    return "";

  string str(1, 'A' + n % 26); 
  n = n / 26;
  while (n) {
    str.insert(str.begin(), 1, (n - 1) % 26 + 'A');
    n = (n - 1) / 26;
  }

  return str;
}

// Test harness
int main(int argc, char** argv) {
  /*
  if (argc != 2) {
    cout << "Need input int" << endl;
    return 0;
  }

  int x = atoi(argv[1]);
  cout << dhu(x) << endl;
  */

  for (int i = 0; i < 10000; i++) {
    if (dhu2(i) != lolhaha(i))
      cout << i << ": " << dhu(i) << " " << lolhaha(i) << endl;
  }
}

