/* Finding a duplicated integer. Given a read-only array of n integers between 
 * 1 and n-1, design an O(n) time algorithm to find a duplicated integer. 
 * Use only O(1) space. 
 * Hint: equivalent to finding a loop in a singly linked structure. 
 * Reference:
 * http://www.mitbbs.com/article_t/JobHunting/31947559.html
 */

#include <iostream>

using namespace std;

int main()
{
  int a[] = { 3, 7, 5, 1, 7, 8, 6, 4, 2 };
  int v1 = a[0];
  int v2 = a[v1];
  while (v1 != v2) {
    v1 = a[v1];
    v2 = a[a[v2]];
  }
  // v1 here is the node where slow and fast pointers overlap, but it is not necessarily
  // th eduplicate elements. To find the duplicate, use the same idea to find the starting
  // point of the loop:
  v1=a[0];
  while (v1 != v2) {
    v1 = a[v1];
    v2 = a[v2];
  }
  cout << "Duplucate: " << v1 << endl;

  return 0;
}
