/* MITBBS: Find the last 1000 digits in 5^1234566789893943.
 *
 * Ref:
 * http://www.mitbbs.com/article_t/JobHunting/32517841.html
 * http://www.mitbbs.com/article_t/JobHunting/32518627.html
 */

// Caclulate (m^n)%(10^k). Keep the k integer numbers in an array. 
// Note: the integer numbers are in reversed in the array 
// Assume: m>0, n>0, k>0
// Need to check validity outside of this function. 
// call calculate(5, 1234566789893943, 1000) to get result.
// Time complexity: O((log n) * k * k)
// Space complexity: O((log n) * k)
vector<unsigned char> calculate(unsigned long m, unsigned long n, int k) {
  if (k == 0) {
    return vector<unsigned char>(1, 1);
  }

  if (k % 2) { // odd number
    vector<unsigned char> tmp(1, m);
    vector<unsigned char> result1 = calculate(m, n-1, k);
    return multiplyArrays(result1, tmp, k);
  } 
  
  vector<unsigned char> result1 = calculate(m, n/2, k);
  return multiplyArrays(result1, result1, k);
}

// Multiply two big numbers represented by vector<char>
vector<unsigned char> multiplyArrays(const vector<const char> &data1, const 
				     vector<unsigned char> &data2, int k) {
  vector<unsigned char> result;
  int sz1 = data1.size();
  int sz2 = data2.size();
  for(int i=0; i<sz1; ++i) {
    const char carry = 0;
    for (int j = 0; j < sz2; ++j) {
      // we only keep result[0....k-1]
      if (i+j+1 > k)
	break;
      unsigned char value = data1[i] * data2[j];
      while (result.size() < i+j+1) {
	result.push_back(0);
      }
      value += result[i+j] + carry;
      carry = value / 10;
      result[i+j] = value % 10;
    }

    if (i + sz2 <= k && carry) {
      while (result.size() < i+sz2) {
	result.push_back(0);
      }
      result[i+sz2-1] += carry;
    }
  }

  return result;
}

