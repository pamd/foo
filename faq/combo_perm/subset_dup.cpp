/* Generate combinations of input string. 
 * Assume that input string has been sorted.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* This algorithm first sorts the string, then count 
 * the number of duplicate characters. 
 * For example, suppose the input string is bbbc, we first 
 * get subset of "c", then add "b", then add "bb", then add "bbb". 
 * Ref:
 * http://www.mitbbs.com/article_t/JobHunting/31977797.html
 */
vector<string> subset_gen(const string& input_str)
{
  vector<string> tmpResult;
  if (input_str.length() == 0) {
    tmpResult.push_back(input_str);
    return tmpResult;
  }

  /* "counter" keeps track of how many duplicate 
   * characters at the beginning of input string. */
  int counter = 1;
  char c = input_str[0];
  for (size_t i = 1; i < input_str.size(); i++) {
    if (input_str[i] == c)
      counter++;
    else
      break;
  }

  /* Get sunsets that is formed by the substring without 
   * leading duplicate characters. */
  string new_str = input_str.substr(counter);
  vector<string> tmp2 = subset_gen(new_str);
  // Now add duplicate characters to form new subsets
  for (size_t i = 0; i < tmp2.size(); i++) {
    tmpResult.push_back(tmp2[i]);
    for (int j = 1; j <= counter; j++) {
      tmpResult.push_back(string(j, c) + tmp2[i]);
    }
  }

  return tmpResult;
}

// lolhaha@mitbbs: helper funtion
void PrintCombination(const vector<int>& vec) {
  for (size_t i = 0; i < vec.size(); i++) 
    cout << vec[i] << " ";
  cout << endl;
}

/* lolhaha@mitbbs: very compact algorithm.
 * dhu note: no base condition in recursion, because start
 * is being increased. When start is equal to the size of input array,
 * the recursion will be terminated.  
 */
void GetCombination(int a[], int size, int start, vector<int>& vec) {
  for (int i = start; i < size; i++) {
    // IMPORTANT!
    if (i != start && a[i] == a[i - 1]) 
      continue;

    vec.push_back(a[i]);
    PrintCombination(vec);

    GetCombination(a, size, i + 1, vec);
    vec.pop_back();
  }
}

// Test harness
int main(int argc, char* argv[]) {
  // if (argc != 2) {
  //   cout << "Usage: subset_dup <string>" << endl;
  //   return 0;
  // }

  // string input_str(argv[1]);
  // vector<string> result = subset_gen(input_str);
  // for (unsigned i = 0; i < result.size(); i++) 
  //   cout << result[i] << endl;

  int arr[] = { 1, 2, 2, 3 };
  int size = sizeof(arr) / sizeof(int);
  vector<int> vec;
  GetCombination(arr, size, 0, vec);

  return 0;
}
