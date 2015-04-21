/* The gray code is a binary numeral system where two successive values 
 * differ in only one bit. Given a non-negative integer n representing 
 * the total number of bits in the code, print the sequence of gray code. 
 * A gray code sequence must begin with 0.
 */

#include <iostream>
#include <vector>

using namespace std;

// dhu solution: 24ms for large dataset
class Solution {
public:
  vector<int> grayCode(int n) {
    vector<int> prev;
    prev.push_back(0);
    vector<int> curr;
    for (int i = 1; i <= n; i++) {
      curr = prev;
      int foo = 1 << (i - 1);
      for (int i = prev.size() - 1; i >= 0; i--) 
	curr.push_back(prev[i] + foo); 
      prev = curr;
    }
    return prev;
  }
};

/* Dropbox solution
 * -------------------
 * The BinaryToGray method is based on the bit of gray code looply occur: 
 *     0, 1, 1, 0
 * Hence, we could calculate each bit of gray code by mod 4 to find the 
 * matching value.
 *
 * However, after searching on the website, the convert formula is just as 
 * simple as: 
 *           (i >> 1) ^ i.
 * In another word, the i-th gray code is equal to i plus i / 2 without carry.
 */

int BinaryToGray(int binary) {
  int gray = 0;
  int bit = 0;
  int convert[4] = {0, 1, 1, 0};
  while (binary) {
    int value = convert[binary % 4];
    gray |= (value << bit);
    ++bit;
    binary >>= 1;
  }

  return gray;
}

vector<int> GrayCode(int n) {
  vector<int> codes;
  for(int i=0; i< (1<<n); ++i)
    //codes.push_back((i >> 1) ^ i);
    codes.push_back(BinaryToGray(i));
        
  return codes;
}

int main() {
  //Solution foo;
  //vector<int> ret = foo.grayCode(2);
  vector<int> ret = GrayCode(3);
  for (size_t i = 0; i < ret.size(); i++)
    cout << ret[i] << endl;

  return 0;
}
