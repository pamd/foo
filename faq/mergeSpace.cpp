/* Merge consecutive space characters into one space in input string.
 * Ref:
 * http://www.mitbbs.com/article_t/JobHunting/31977961.html
 */

#include <iostream>

using namespace std;

// Function written by dawninghu@mitbbs
void dawninghu(char p[])
{
  char *r=p, *w=p; //r: read, w: write
  while (*r != '\0') {
    if (*r!=' ' || *(w-1) != ' ') { 
      *w = *r; 
      w++; 
      r++;
    }
    else
      r++;
  }

  if (r!=w) 
    *w = '\0';
}

void dhu_merge(char* str) 
{
  int rp = 0;
  int wp = 0;
  int prev_space = false;
  while (str[rp] != '\0') {
    if (str[rp] != ' ') {
      str[wp++] = str[rp++];
      prev_space = false;
    }
    else if (prev_space)
      rp++;
    else {
      str[wp++] = str[rp++];
      prev_space = true;
    }
  }
  str[wp] = '\0';
}

int main()
{
  char str[] = "   a   b cd   ";
  dhu_merge(str);
  cout << str << endl;
}
