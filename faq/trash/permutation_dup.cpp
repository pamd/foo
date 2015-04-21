/* This program generates permutation of input string, in which 
 * duplicate characters are allowed.
 *
 * The algorithm is simple. Suppose we have input string "abc", 
 * the program first generate permutation of "bc", which is "bc" and "cb",
 * then add 'a' at the beginning of both "bc" and "cb", so "abc" and "acb" 
 * is generated. Then the program generates permutation of "ac", then add 
 * 'b' at the beginning, and so forth. 
 * Instead of adding the single letter at the beginning, we can add
 * it at the end, which will generate same output.
 *
 * To deal with duplicate characters, the input string must be sorted 
 * first so that duplicate characters are put together. If the character that
 * we want to remove is identical to the previous letter, this letter will be skipped.
 *
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string rmChar(const string& input_str, int index)
{
  string prev_str = input_str.substr(0, index);
  string after_str = input_str.substr(index + 1);
  
  return prev_str + after_str;
}

vector<string> perm_gen(const string& input_str)
{
  vector<string> tmpResult;
  if (input_str.length() == 1) {
    tmpResult.push_back(input_str);
    return tmpResult;
  }

  for (size_t i = 0; i < input_str.length(); i++) {
    // Assume the input string is already sorted, skip duplicates here
    if (i != 0 && input_str[i] == input_str[i - 1])
      continue;

    string single(" ");
    single[0] = input_str[i];
    string new_str = rmChar(input_str, i);

    vector<string> tmp2 = perm_gen(new_str);
    for (unsigned i = 0; i < tmp2.size(); i++) {
      tmp2[i] = single + tmp2[i];
      tmpResult.push_back(tmp2[i]);
    }
  }
  
  return tmpResult;
}

int main(int argc, char* argv[])
{
  if (argc != 2) {
    cout << "Usage: perm_dup <string>" << endl;
    return 0;
  }

  string input_str(argv[1]);
  vector<string> result = perm_gen(input_str);
  for (unsigned i = 0; i < result.size(); i++) 
    cout << result[i] << endl;
  
  return 0;
}
