/* Ref:
 * http://www.mitbbs.com/article_t/JobHunting/31977797.html (Q2)
 */
#include <iostream>

using namespace std;

// Written by smalleye@mitbbs
int smalleye(int a[], int k)
{
  int p = 0;
  int i = 0;
  while (i <= k) {
    p = i;
    if (a[i] == 'L')
      i++;
    else
      i += 2;
  }
  return p;
}

// Written by bikelost@mitbbs
int bikelost(int a[], int k)
{
  int p = k - 1;
  while (p >= 0 && a[p] != 'L')
    p--;
  int i = p + 1;
  while ( i <= k) {
    p = i;
    if (a[i] == 'L')
      i++;
    else
      i += 2;
  }

  return p;
}

/* dhu revision, based on smalleye's algorithm.
 * Parameter is changed into string to make testing easier. 
 */
int dhu(const string& str, int k)
{
  int p = 0;
  int i = 0;
  while (i <= k) {
    p = i;
    if (str[i] == 'L')
      i++;
    else
      i += 2;
  }
  return p;
}

// Test harness
int main()
{
  string foo("HLHHHLHHH");
  string bar("HLHHHLHHH");
  cout << dhu(bar, 7) << endl;
}
