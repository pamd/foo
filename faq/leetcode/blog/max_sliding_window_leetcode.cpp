/* http://www.leetcode.com/2011/01/sliding-window-maximum.html
 * A long array A[] is given to you. There is a sliding window of size w 
 * which is moving from the very left of the array to the very right. 
 * You can only see the w numbers in the window. Each time the sliding 
 * window moves rightwards by one position. 
 */

#include <iostream>
#include <deque>

using namespace std;

// Debug function
void printDeq(const deque<int>& deq)
{
  cout << "front ... ";
  for (size_t i = 0; i < deq.size(); i++)
    cout << deq[i] << " ";
  cout << " ... back" << endl;
}

// leetcode algorithm
void maxSlidingWindow(int A[], int n, int w, int B[]) {
  // The elements in deque is the INDEX of element, NOT value of element
  deque<int> Q;

  for (int i = 0; i < w; i++) {
    while (!Q.empty() && A[i] >= A[Q.back()])
      Q.pop_back();
    Q.push_back(i);
  }
  cout << "Initial Q: " << endl;
  printDeq(Q);
  cout << endl;

  for (int i = w; i < n; i++) {
    cout << "i: " << i << endl;
    B[i-w] = A[Q.front()];
    while (!Q.empty() && A[i] >= A[Q.back()])
      Q.pop_back();

    cout << "After 1st while" << endl;
    printDeq(Q);

    Q.push_back(i);

    while (!Q.empty() && Q.front() <= i-w)
      Q.pop_front();


    cout << "After 2nd while" << endl;
    printDeq(Q);
    cout << endl;
  }
  B[n-w] = A[Q.front()];
}

// Test harness
int main()
{
  int A[] = { 7, 6, 5, 4, 3, 2, 1 };
  int n = sizeof(A) / sizeof(int);
  int w = 3;
  int B[n - w + 1];
  
  maxSlidingWindow(A, n, w, B);

  for (int i = 0; i < n - w + 1; i++)
    cout << i << ": " << B[i] << endl;

}
