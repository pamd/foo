/* Given an array of integers, find two numbers such that they add up to a specific target number.
 * The function twoSum should return indices of the two numbers such that they add up to the target, 
 * where index1 must be less than index2. Please note that your returned answers (both index1 and index2) 
 * are not zero-based.
 * You may assume that each input would have exactly one solution.
 * Input: numbers={2, 7, 11, 15}, target=9
 * Output: index1=1, index2=2
 */

// 8ms for large dataset
class Solution {
public:
  vector<int> twoSum(vector<int> &numbers, int target) {
    vector<int> answer(2, -1);
    unordered_map<size_t, size_t> hashmap;
    for (size_t i = 0; i < numbers.size(); i++) {
      int foo = target - numbers[i];
      if (hashmap.find(foo) != hashmap.end()) {
	// Since we scan numbers from left to right, i + 1 will be always larger than hashmap[foo]
	answer[0] = hashmap[foo];
	answer[1] = i + 1;
	break;
      }
      hashmap[numbers[i]] = i + 1;
    }
    return answer;
  }
};
