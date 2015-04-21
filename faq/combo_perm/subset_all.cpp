/* Generate all subsets of an input string. */
 
#include <iostream>
#include <string>

using namespace std;

void subset(const string& inputStr, const string& intermStr, int start)
{
  /* No base condition here, because when start is equal to 
   * inputStr.length(), this function will exit automatically. */
  for (size_t i = start; i < inputStr.length(); i++) {
    string outStr = intermStr + inputStr.substr(i, 1);
    cout << outStr << endl;
 
    subset(inputStr, outStr, i + 1);
  }
}

// dhu approach
void subset2(const string& inputStr, string& intermStr, size_t level)
{
  if (level == inputStr.size()) {
    cout << intermStr << endl;
    return;
  }

  // Generate all subsets that has inputStr[level]
  intermStr.push_back(inputStr[level]);
  subset2(inputStr, intermStr, level + 1);
  intermStr.erase(intermStr.size() - 1);

  // Generate all subsets that doe not have inputStr[level]
  subset2(inputStr, intermStr, level + 1);
}

int main(int argc, char* argv[])
{
  if (argc != 2) {
    cout << "Usage: subset_all <input_string>" << endl;
    return 0;
  }

  string inputStr(argv[1]);
  string intermStr;
  subset(inputStr, intermStr, 0);

  return 0;
}

