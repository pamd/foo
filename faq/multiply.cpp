/* Multiplication algorithm, based on:
 * http://en.wikipedia.org/wiki/Multiplication_algorithm#Space_complexity
 * http://www.mitbbs.com/article_t/JobHunting/31741707.html, post #7
 */

#include <iostream>
#include <vector>

using namespace std;

int max(int v1, int v2) {
  if (v1 > v2)
    return v1;
  return v2;
}

int min(int v1, int v2) {
  if (v1 < v2)
    return v1;
  return v2;
}

// Default base is 10
int multiply(const vector<int>& a, const vector<int>& b, int base = 10) {
  int x = 0;
  int n = a.size();
  vector<int> result(2 * n);
  for (int i = 0; i < 2 * n; i++) {  // i is the index of current digit in result (starting from right side)
    int tmp1 = max(0, i + 1 - n);    // 0 <= tmp1 <= n forever
    int tmp2 = min(i, n - 1);        // 0 <= tmp2 <= (n - 1) forever  

    //cout << "tmp1: " << tmp1 << endl;
    //cout << "tmp2: " << tmp2 << endl;

    // j is the index of digit in a (starting from right side)  that will contribute to i-th digit in result
    for (int j = tmp1; j <= tmp2; j++) {  
      // k is the index of digit in b (starting from right side) that will contribute to i-th digit in result
      int k = i - j;  
      //cout << "a[" << j << "] * b[" << k << "]" << endl;
      x = x + (a[j] * b[k]);
    }
    result[i] = x % base;
    //cout << i << ": " << result[i] << endl << endl;
    x = x / base;
  }
  
  int product = 0;
  int power = 1;
  for (unsigned i = 0; i < result.size(); i++) {
    product += power * result[i];
    power *= base;
  }

  return product;
}

int main() {
  vector<int> a(3), b(3);
  //base = 2;
  a[0] = 5, a[1] = 1; 
  b[2] = 6, b[1] = 3, b[0] = 7;

  cout << "Product: " << multiply(a, b) << endl;

  return 0;
}
