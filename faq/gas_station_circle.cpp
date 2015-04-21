// This is the program that calculates the optimal starting point for gas station problem.
// "position" is the index of the optimal gas station. Note that it is incremented by 1 at the end.  

#include <iostream>

using namespace std;

int main()
{
  int gas[] = { 3, 5, 7, 5, 8, 2 };
  int len[] = { 4, 9, 1, 3, 5, 8 };

  int result = gas[0] - len[0];
  int tmp = result;
  int position = 0;
  int n =  sizeof(gas) / sizeof(int); 
  //cout << tmp << endl;
  for (int i = 1; i < n; i++) {
    tmp += gas[i] - len[i];
    if (result > tmp) {
      result = tmp;
      position = i;
    }
    //cout << tmp << endl;
  }

  //cout << "position: " << position << endl;
  //cout << "result: " << result << endl;

  position++;

  return position;

}
