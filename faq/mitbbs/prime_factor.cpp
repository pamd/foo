/* Print out prime factors of a giver positive integer.
 * Code is based on Python code from:
 * http://www.mitbbs.com/article_t/JobHunting/32137389.html
 */

#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

// Based on Python code by QuickTime
void getFactor(int n) {
  if (n <= 1) {
    cout << n << endl;
    return;
  }

  int factor = 2;
  while (n > 1) {
    if (n % factor == 0) {
      cout << factor << " ";
      n /= factor;
    }
    else 
      factor++;
  }
  cout << endl;
}

// dhu
vector<int> dhu(int x) {
  if (x <= 1)
    return vector<int>(1, 1);

  vector<int> ret;
  int i = 2;
  while (i <= x) {
    if (x % i) {
      i++;
    }
    else {
      ret.push_back(i);
      x /= i;
    }
  }

  return ret;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    cout << "Input integer not found." << endl;
    return 0;
  }

  int n = atoi(argv[1]);
  vector<int> ret = dhu(n);
  for (size_t i = 0; i < ret.size(); i++) {
    cout << ret[i] << endl;
  }

  return 0;
}

