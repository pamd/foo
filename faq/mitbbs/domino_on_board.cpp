/* Given a board that has n rows and m columns, 
 * suppose m*n is an even number, how many ways 
 * can we cover it completely by a 1x2 domino?
 * 
 * Reference:
 * http://www.mitbbs.com/article_t/JobHunting/32528755.html
 * http://eurce.me/?p=259
 * http://blog.csdn.net/hopeztm/article/details/7841917
 */

#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <algorithm>
#include <iostream>

using namespace std;

// Based on solution in:
// http://blog.csdn.net/hopeztm/article/details/7841917

#define MAX_ROW 11
#define MAX_STATUS 2048

// DP[i][j]: the # of different tiling ways when we finished row #i 
// and the binary representation of row #i is j.
long long DP[MAX_ROW][MAX_STATUS];

int width = 0;
int height = 0;

// Check the first row
bool ChkFirstRow(int nStatus) { 
  int i = 0; // i is the bit index (from the least significant side)
  while (i < width) {
    // If the i-th bit of nStatus is set
    if ((nStatus & (0x1 << i)) != 0) {  
      // If i is the last bit, or the (i+1)-th bit of nStatus 
      // is NOT set, then nStatus can never be reached.
      if (i == width - 1 || (nStatus & (0x1 << (i+1))) == 0) {
	return false;
      }
      // i < width-1 and the (i+1)-th bit of nStatus is set, increment i by 2
      i += 2;
    }
    // If the i-th bit of nStatus is not set, then check (i+1)-th bit.
    else {
      i++;
    }
  }

  return true;
}

// Test whether status (i, nStatusA) and (i-1, nStatusB) is compatible or not.
bool isCompatable(int nStatusA, int nStatusB) {
  int i = 0;
  while (i < width) {
    // When the i-th bit of nStatusA is not set
    if ((nStatusA & (0x1 << i)) == 0) {
      // If the i-th bit of nStatusB is not set either, 
      // then nStatusA can never be reached.
      if ((nStatusB & (0x1 << i)) == 0) 
	return false;
      // If the i-th bit of nStatusB is set, then check the next bit.  
      i++;
    }

    // When the i-th bit of nStatusA is set, and the i-th bit of nStatusB 
    // is not set, then a vertical domino must have been put at rows #(i-1) and #i.
    // So we check the next bit.
    else if ((nStatusB & (0x1 << i)) == 0) 
      i++;

    // If the i-th bits of both nStatusA and nStatusB are set, and we have 
    // the following three cases, then nStatusA can never be reached.
    else if ((i == width - 1) ||                 // (1) We reached the last bit;
	     (nStatusA & (0x1 << (i+1))) == 0 || // (2) (i+1)-th bit of nStatusA is not set;
	     (nStatusB & (0x1 << (i+1))) == 0)   // (3) (i+1)-th bit of nStatusB is not set;
      return false;
    else 
      i += 2;
  }

  return true;
}

// Solution based on:
// http://eurce.me/?p=259
int N;
long long dp_eurce[11][1<<11];

// Top down DP with recursion
// In this approach, the domino that is put horizontally will be denoted 
// as "00", and the domino that is put vertically will be denoted as "1".
// This denotion system is exactly  from the first approach!
void eurce(int h, int w, int d) {
  if (w > width) 
    return;
    
  if (w < width) {   // w < width
    eurce(h, w + 1, (d<<1) + 1); // vertical domino at (h, w)
    eurce(h, w + 2, d<<2); // horizontal domino at (h, w) and (h, w+1)
  }

  else if (h == 0) { // w == width and h == 0 
    dp_eurce[h][d]++;
  }

  else { // w == width and h > 0
    // The binary representation of x is the domino 
    // configuration of the previous row.   
    for (int x = 0; x < N; x++) {
      // If d^x is equal to d-x, then d^x can be reached from x of previous row. 
      if ((d ^ x) == d - x) 
	dp_eurce[h][d^x] += dp_eurce[h-1][x];
    }
  }

}

// Test harness
int main() {    
  width = 4;
  height = 2;

  /* 
  // Test of CSDN approach 
  if(width > height) {
    swap(width, height);
  }
    
  memset(DP, 0, sizeof(DP)); // Initialize all elements in DP table to 0

  int nAllStatus = 1 << width;
  for (int j = 0; j < nAllStatus; j++) { // Set the first row of DP table
    if (ChkFirstRow(j)) {
      DP[0][j] = 1;
    }
  }
    
  for (int i = 1; i < height; i++) {    
    for (int j = 0; j < nAllStatus; j++) {    // iterate all status for row i
      for (int k = 0; k < nAllStatus; k++)  { // iterate all status for the previous row (i-1)
	if (isCompatable(j, k)) 
	  DP[i][j] += DP[i-1][k];
      }
    }
  }
  cout << "CSDN:\t" << DP[height-1][nAllStatus - 1] << endl;
  */

  // Eurce test
  memset(dp_eurce, 0, sizeof(dp_eurce)); 
  N = 1 << width;
  for (int h = 0; h < height; h++) 
    eurce(h, 0, 0);
  
  for (int i = 0; i < N; i++) {
    cout << i % 10 << " ";
  }
  cout << endl;

  for (int r = 0; r < 2; r++) {
    for (int i = 0; i < N; i++) {
      cout << dp_eurce[r][i] << " ";
    }
    cout << endl;
  }
  //  cout << "Eurce:\t" << dp_eurce[height-1][0] << endl;

  return 0;
}
