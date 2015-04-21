/* If the Fibonacci series is 1, 2, 3, 5, 8, 13, ..., then 10 can be 
 * written as 8 + 2 ==> 10010 and 17 can be written as 13 + 3 + 1 ==> 100101. 
 * Given n, find all possible representations of n in Fibonacci Binary 
 * Number System, such as 10 = 8 + 2 ==> 10010, also 10 = 5 + 3 + 2 ==> 1110.
 * Ref: 
 * http://www.mitbbs.com/article_t/JobHunting/31969197.html
 *
 */

#include <iostream>
#include <vector>

using namespace std;

// Array of Fibnacci numbers
vector<int> fibn;
// Accumulated sum of Fibnacci numbers
vector<int> sum;

// Recursive depth-first-search
void dfs(int val, string solution, int idx) {
  if (idx < 0) {
    if (val == 0) 
      cout << solution << endl;
    return;
  }

  /* If input value is negative or larger than sum of all Fibnacci numbers
   * up to the current index, then it is impossible to express this value
   * as a sum of Fibnacci series. */
  if (val < 0 || val > sum[idx]) 
   return;

  // Include the current Fibnacci number
  dfs(val - fibn[idx], solution + "1", idx - 1);

  // Exclude the current Fibnacci number
  if (solution.size() != 0)
    solution += "0";
  dfs(val, solution, idx - 1);
}

// Initialize fibn and sum vectors, then call dfs()
void express(int val) {
  fibn.resize(128);
  fibn[0] = 1;
  fibn[1] = 2;
        
  int idx = 2;
  while (fibn[idx-1] < val) {
    fibn[idx] = fibn[idx-1] + fibn[idx-2];
    idx++;
  }
        
  sum.resize(128);
  sum[0] = 1;
  for (int i = 1; i < idx; i++) 
    sum[i] = sum[i-1] + fibn[i];
    
  string foo;
  dfs(val, foo, idx - 1);
}
    
// Test harness
int main() 
{
  express(10);

}
