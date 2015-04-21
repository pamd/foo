/* Leetcode OJ: 
 * Given a 2D binary matrix filled with 0's and 1's, 
 * find the largest rectangle containing all ones and return its area.
 */

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
  // 88ms for large dataset
  int maximalRectangle(vector<vector<char> > &matrix) {
    if (matrix.size() == 0)
      return 0;

    size_t row = matrix.size();
    size_t col = matrix[0].size();
    int max_area = 0;
    vector<int> curr_row(col, 0);
    for (size_t r = 0; r < row; r++) {
      for (size_t c = 0; c < col; c++) {
	if (matrix[r][c] == '0')
	  curr_row[c] = 0;
	else
	  curr_row[c]++;
      }
      int tmp_area = getMaxHistgram(curr_row);
      if (max_area < tmp_area)
	max_area = tmp_area;
    }
    
    return max_area;
  }

  int getMaxHistgram(const vector<int>& v) {
    vector<int> left_border(v.size());
    vector<int> stack;
    left_border[0] = 0;
    stack.push_back(0);
    for (size_t i = 1; i < v.size(); i++) {
      while (stack.size() && v[stack.back()] >= v[i])
	stack.pop_back();

      if (stack.size() == 0)
	left_border[i] = 0;
      else
	left_border[i] = stack.back() + 1;

      stack.push_back(i);
    }

    stack.clear();
    vector<int> right_border(v.size());
    right_border[v.size() - 1] = v.size();
    stack.push_back(v.size() - 1);
    for (int i = (int) v.size() - 2; i >= 0; i--) {
      while (stack.size() && v[stack.back()] >= v[i]) 
	stack.pop_back();

      if (stack.size() == 0)
	right_border[i] = v.size();
      else
	right_border[i] = stack.back();

      stack.push_back(i);
    }

    int max_area = 0;
    for (size_t i = 0; i < v.size(); i++) {
      int tmp = v[i] * (right_border[i] - left_border[i]);
      if (max_area < tmp)
	max_area = tmp;
    }
	
    return max_area;
  }

};

int main() {
  // "0010","1111","1111","1110","1100","1111","1110"]

  vector<int> v;
  v.push_back(6);
  v.push_back(6);
  v.push_back(2);
  v.push_back(0);

  Solution foo;
  cout << foo.getMaxHistgram(v) << endl;
}
