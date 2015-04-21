// This program tests integer overflow in C/C++

#include <iostream>

using namespace std;

int main()
{
  int i = 1 << 31;
  cout << i << endl;
  long j = i;
  cout << j << endl;
}
