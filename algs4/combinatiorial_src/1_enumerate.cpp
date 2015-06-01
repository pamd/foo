/********************************************************************
 * Enumerate N-bit strings: C++ code based on java code on slide #5.
 ********************************************************************/

#include <iostream>
#include <vector>

using namespace std;

const int N = 10;
vector<int> a(N);

// Print out elements in a[]
void process() {
  for (int i = 0; i < N; i++) 
    cout << a[i] << " ";
  cout << endl;
}

// Recursive function.
// This approach assumes that all elements in a[] are initialized to 0.
// If not, the output will be wrong. See code in main().
void enumerate(int k) {
  if (k == N) { 
    process(); 
    return; 
  }

  enumerate(k+1);
  a[k] = 1;
  enumerate(k+1);
  a[k] = 0; // clean up: VERY IMPORTANT
}

// dhu revision: move "a[k] = 0" right after "if" section.
// In this approach, the initial values in a[] are irrelevant,
// because we always reset a[] to the right values.   
void enumerate_dhu(int k) {
  if (k == N) { 
    process(); 
    return; 
  }

  a[k] = 0; // dhu revision
  enumerate_dhu(k+1);
  a[k] = 1;
  enumerate_dhu(k+1);
}

// Test harness
int main() {
  // If we reset a[] to other values, enumerate() will give incorrect outputs,
  // but enumerate_dhu() will be still correct.
  //for (int i = 0; i < N; i++)
  // a[i] = 5+i;
  
  enumerate(0);

  return 0;
}
