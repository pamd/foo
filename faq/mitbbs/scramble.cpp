/* http://www.mitbbs.com/article_t/JobHunting/32107851.html
 */

// swanswan: Recursive (non-DP)
bool isScramble(char* str1, char* str2, int length) {
  if (length==1) 
    return *str1 == *str2;

  for (int i = 1; i < length; i++) {
   if (isScramble(str1, str2 + (length - i), i) && isScramble(str1 + i, str2, length-i))
     return true;

   if (isScramble(str1, str2, i) && isScramble(str1+i, str2+i, length-i))
     return true;
  }

  return false;
}

// Recursive DP
class Solution {
char* str1;
char* str2;
int m;
int m2;
int m3;
int* DP;
#define dp(i,j,k) DP[m2 * (i) + m * (j) + (k) ]

public:
Solution(char* s1, char *s2) {
   assert( s1 && s2 );
   str1 = s1; str2 = s2;
   m = strlen(str1);
   assert(m && strlen(str2)==m);
   m2 = m*m;
   m3 = m2*m
   DP = new int[m3];
   for (int i=0; i<m3; i++) DP[i]=-1;
}

bool isScramble() {
   return isScramble(0, 0, m);
}

private:
bool isScramble(int pos1, int pos2, int length) {

if (length==1) return str1[pos1] == str2[pos2];
if (dp(pos1, pos2, length-1)!=-1) return dp(pos1, pos2, length-1);
for (int i=1; i<length; i++) {
   if (isScramble(pos1,  pos2+(length-i), i) && isScramble(pos1+i,  pos2, length-i)
     || isScramble(pos1,  pos2, i) && isScramble(pos1+i,  pos2+i, length-i)) {
      dp(pos1, pos2, length-1) = 1;
      return true;
   }
}
dp(pos1, pos2, length-1) = 0;
return false;

}
}

// todayzj
// http://www.mitbbs.com/article_t/JobHunting/32114513.html
bool isSubAnargm(string parent, string child)
{
    if(parent.empty() && child.empty()) return true;

    for(unsigned int i = 0; i< child.size(); i++)
    {
        if (parent.find(child[i]) < 0) return false;
    }

    if (parent.find(child[0]) > parent.find(child[child.size()-1]))
    {
        reverse(parent.begin(), parent.end());
    };

    if (parent.compare(child) == 0) return true;

    int currentMaxPosition = -1;
    int validMaxLength = -1;

    for(unsigned int i = 0; i< child.size()-1; i++)
    {
        if (currentMaxPosition < (signed int)(parent.find(child[i])))
        {
            currentMaxPosition = parent.find(child[i]);
        }
        if (currentMaxPosition == i)
        {
            validMaxLength = currentMaxPosition;
        }
    }
    if(validMaxLength == -1)
    {
        return false;
    };
    
    return isSubAnargm(parent.substr(0,validMaxLength+1),   
		       child.substr(0, validMaxLength+1)) && 
      isSubAnargm(parent.substr(validMaxLength+1, parent.size() - validMaxLength-1), 
		  child.substr(validMaxLength+1, parent.size() - validMaxLength-1));
}
