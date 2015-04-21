/* Solution to CLRS 14-2(b) Josephus permutation (3rd edition, page 355):
 * Suppose that n people form a circle and that we are given a positive integer m <= n. 
 * Beginning with a deignated first person, we proceed around the circle, removing every m-th
 * person. After each person is removed, counting continues around the circle that remains.
 * This process continues until we have removed all n people. The order in which the people are 
 * removed from the circle defines the (n,m)-Josephus permutation of the integers 1, 2, ..., n.
 * For example, the (7, 3)-Josephus permutation is (3, 6, 2, 7, 5, 1, 4).
 *
 * Code is based on CLRS 2nd edition Instructor Manual page 14-17. Total time complexity is O(nlogn).
 */

#include <set>
#include <vector>
#include <iostream>

using namespace std;

vector<int> josephus(int n, int m) {
  vector<int> result;
  set<int> people;
  for (int i = 1; i <= n; i++) 
    people.insert(i);

  size_t j = 0; 
  while (people.size()) {
    // Always set j to the base-0 rank of the next element that will be removed  
    j = (j + m - 1) % n;
    set<int>::iterator it = people.begin();
    /* Move the iterator j times.
     * Note that std::set does NOT support it += j or it = it + j. */
    for (int i = 0; i < j; i++)
      it++;
    result.push_back(*it);
    people.erase(it);
    n--;
  }

  return result;
}

int main() {
  int n = 7;
  int m = 3;
  vector<int> result = josephus(n, m);
  for (size_t i = 0; i < result.size(); i++)
    cout << result[i] << endl;
}


