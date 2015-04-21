// Leetcode OJ: Edit Distance (classic Dynamic Programming problem)

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
  int min(int a, int b) {
    if (a < b)
      return a;
    return b;
  }

  // dhu solution: 96ms for large dataset
  int minDistance(string word1, string word2) {
    int len1 = word1.size();
    int len2 = word2.size();
    int M[len1 + 1][len2 + 1];
    for (int i = 0; i < len1 + 1; i++) 
      M[i][0] = i;
    for (int i = 0; i < len2 + 1; i++)
      M[0][i] = i;
    for (int i = 1; i < len1 + 1; i++) {
      for (int j = 1; j < len2 + 1; j++) {
	int foo = min(M[i-1][j], M[i][j-1]) + 1;
	int bar = M[i-1][j-1];
	if (word1[i-1] != word2[j-1])
	  bar++;
	M[i][j] = min(foo, bar);
      }
    }

    return M[len1][len2];
  }

};

// Dropbox solution: identical to dhu implementation
/*
**	Dynamic Programming, very similar to longest common substring question
**
**	dis[i,j] means the distance from transform s1s2..si to t1t2...tj
**	then the value of dis[i,j] should the minimus value of following:
**		d[i-1, j] + deletion	 (just delete si to have d[i-1, j] situation)
**		d[i, j-1] + inserstion	 (based on d[i, j-1], insert tj to s become d[i, j])
**		d[i-1, j-1]+substitution (based on d[i-1,j-1], replace si with tj becom d[i, j])
*/

int GetMin(int a, int b, int c) {
  return a > b? (b > c? c : b) : (a > c? c : a);
}

int MinDistance(string source, string target) 
{
  int m = source.length()+1;
  int n = target.length()+1;
  
  int dis[m][n];
  
  for (int i = 0; i < m; ++i)
    dis[i][0] = i;
  for (int i = 0; i < n; ++i)
    dis[0][i] = i;
  
  for (int i = 1; i < m; ++i)
    for (int j = 1; j < n; ++j)
      dis[i][j] = GetMin(dis[i-1][j] +1, dis[i][j-1]+1, dis[i-1][j-1] 
			 + (source[i-1] == target[j-1]? 0 : 1));
  
  return dis[source.length()][target.length()];      
}

int main() {
  string s1("exponential");
  string s2("polynomial");
  Solution s;
  cout << s.minDistance(s1, s2) << endl;
}
