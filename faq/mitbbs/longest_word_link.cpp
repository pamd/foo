/* Q404: 
 * http://www.mitbbs.com/article_t/JobHunting/32135845.html
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

/* longway2008: Original code (with a lot of errors)
int longestCircle(vector<string> &ss)
   {
  int len[26][26];
  memset(len, 0, 26*26*sizeof(int));

  int maxLen = 0;
  for (int i=0; i<ss.size(); ++i) {
      string &str = v[i];
      int vFrom = str[0] - '0'; 
      int vTo = str[str.size()-1] - '0';
      
      for(int j=0; j<26; ++j)
         len[j][vTo] = max(len[j][vTo], len[j][vFrom]+len[vFrom][vTo]);

      maxLen = max(maxLen, len[vTo][vTo];
  }  

   return maxLen;
}
*/

// longway2008: errors in original code have been corrected   
int longway2008(const vector<string>& ss) {
  size_t len[26][26];
  memset(len, 0, 26 * 26 * sizeof(size_t));
  size_t maxLen = 0;
  for (size_t i = 0; i < ss.size(); ++i) {
    string str = ss[i];
    int vFrom = str[0] - 'a'; // error corrected
    int vTo = str[str.size() - 1] - 'a'; // error corrected
    
    //if (!len[vFrom][vTo])
    //  len[vFrom][vTo] = str.size();

    for(int j = 0; j < 26; ++j) {
      //if (len[j][vFrom])
	len[j][vTo] = max(len[j][vTo], len[j][vFrom] + str.size()); // error corrected
      maxLen = max(maxLen, len[j][j]); // error corrected
    }
  }
 
  return maxLen;
}

// dhu test harness

int main() {
  vector<string> v;
  v.push_back("abc");
  v.push_back("ca");
  v.push_back("m123a");
  v.push_back("cba");
  v.push_back("cxym");
  // This example shows that longway2008 algorithm is not 
  // correct even after my correction! 
  cout << longway2008(v) << endl;
}
