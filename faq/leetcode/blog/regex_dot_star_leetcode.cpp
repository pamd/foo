#include <iostream>
#include <string>

using namespace std;

// AFI implementation
bool afi_matchStar(const string& text, char c, const string& after_star)
{
  if (match(text, after_star))
    return true;

  if (c != '.' && text[0] != c)
    return false;

  return matchStar(text.substr(1), c, after_star);
}

// AFI implementation
bool afi_match(const string& text, const string& pattern)
{
  if (text.size() == 0 && pattern.size() == 0)
    return true;
  if (text.size() == 0 || pattern.size() == 0)
    return false;

  if (pattern.size() >= 2 && pattern[1] == '*') 
    return matchStar(text, pattern[0], pattern.substr(2));

  if (text[0] == pattern[0])
    return match(text.substr(1), pattern.substr(1));

  return false;
}

// Leetcode implementation. The idea is very close to AFI implementation.
bool isMatch(const char *s, const char *p) {
  assert(s && p);
  if (*p == '\0') return *s == '\0';
 
  // next char is not '*': must match current character
  if (*(p+1) != '*') {
    assert(*p != '*');
    return ((*p == *s) || (*p == '.' && *s != '\0')) && isMatch(s+1, p+1);
  }
  // next char is '*'
  while ((*p == *s) || (*p == '.' && *s != '\0')) {
    if (isMatch(s, p+2)) return true;
    s++;
  }
  return isMatch(s, p+2);
}

int main()
{
  string text("abcbcd");
  string pattern("a.*c.*d");

  if (match(text, pattern))
    cout << "yes" << endl;
  else
    cout << "no" << endl;

}
