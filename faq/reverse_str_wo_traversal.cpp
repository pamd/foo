/* Program that reverses a C string without using traversal.
 * Asked by Genesis screener. 
 * Code copied from "C++ Random Notes" in Google Doc.
 */

#include <iostream>
#include <string.h>

using namespace std;

// Approach #1: Original approach (string length is not needed)
void reverse1(char* current, char*& new_str)
{
  if (!(*current))
    return;

  char tmp = *current;
  reverse1(current + 1, new_str);
  *(new_str++) = tmp;
}

// Approach #2 seem more intuitive, but length of input string is needed
void reverse2(char* str, int len, int level)
{
  if (!str[level])
    return;

  char tmp = str[level];
  reverse2(str, len, level + 1);
  str[len - 1 - level] = tmp;
}

// Main function
int main()
{
  char foo[] = "a";

  // Test approach #1
  
  char* new_str = foo;
  reverse1(foo, new_str);
  // Now foo points to reversed string, new_str points to '\0'
  cout << "foo1: " << foo << endl; 
  

  // Test of approch #2
  int len = strlen(foo);
  int level = 0;
  reverse2(foo, len, level);
  cout << "foo2: " << foo << endl; 
  
}
