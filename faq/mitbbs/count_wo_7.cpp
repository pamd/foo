/* Count numbers from 1, but avoid any number that includes 7.
 * For example, we have: 
 * 1, 2, 3, 4, 5, 6, 8, 9, ... 16, 18, 19, ..., 699, 800, 801, ...
 */

#include <iostream>
#include <cassert>

using namespace std;

// Helper function for brute force method: determines whether x includes 7
bool hasSeven(unsigned x) {
  while (x) {
    if (x % 10 == 7)
      return true;
    x /= 10;
  }

  return false;
}

// Brute force method
unsigned bf(unsigned x) {
  unsigned ret = 1;
  unsigned cnt = 1;
  while (cnt < x) {
    ret++;
    if (!hasSeven(ret))
      cnt++;
  }

  return ret;
}

/* Better solution: convert x from base 10 to base 9 with the 
 * following map: 0->0, 1->1, 2->2, ..., 6->6, 7->8, 8->9. */
unsigned convert(unsigned x) {
  unsigned result = 0;
  int map[9] = { 0, 1, 2, 3, 4, 5, 6, 8, 9 };
  unsigned power = 1;
  while (x) {
    int digit = x % 9;
    result += power * map[digit]; 
    x /= 9;
    power *= 10;
  }

  return result;
}

int main() {
  for (unsigned i = 1; i <= 10000; i++) {
    unsigned r1 = bf(i);
    unsigned r2 = convert(i);
    //cout << i << endl;
    assert(r1 == r2);
  }

}
