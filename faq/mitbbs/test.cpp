#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

using namespace std;

int rand01() {
  return rand() % 2;
}

int main() {
  //srand (time(NULL));
  cout << sizeof(long) << endl;

  return 0;
}
 
