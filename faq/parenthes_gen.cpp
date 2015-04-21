// Generate pairs of parentheses

#include <iostream>
#include <cstdlib>

using namespace std;

void pgen(int left, int right, int index, char* out_str) 
{
  if (left < 0 || right < 0 || left > right) {
    cout << "Invalid input: " << left << " " << right << endl;
    return;
  }

  if (left == 0 && right == 0) {
    cout << out_str << endl;
    return;
  }

  if (left > 0) {
    out_str[index] = '(';
    pgen(left - 1, right, index + 1, out_str);
  }

  if (right > left) {
    out_str[index] = ')';
    pgen(left, right - 1, index + 1, out_str);
  }
}

int main(int argc, char* argv[])
{
  if (argc != 2) {
    cout << "Usage: pgen <number_of_pairs>" << endl;
    exit(1);
  }

  int pair_no = atoi(argv[1]);
  if (pair_no <= 0) {
    cout << "Usage: pgen <number_of_pairs>" << endl;
    exit(1);
  }

  char* out_str = new char[pair_no * 2 + 1];
  out_str[pair_no * 2] = '\0';
  pgen(pair_no, pair_no, 0, out_str);

  delete out_str;
  return 0;
}
