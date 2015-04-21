/* Code copied from:
 * http://en.wikipedia.org/wiki/Gray_code
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/* The purpose of this function is to convert an unsigned
 * binary number to reflected binary Gray code (from wikipedia). 
 */
unsigned int binaryToGray(unsigned int num)
{
  return (num >> 1) ^ num;
}
 
/* The purpose of this function is to convert a reflected binary
 * Gray code number to a binary number (from wikipedia). */
unsigned int grayToBinary(unsigned int num)
{
    unsigned int numBits = 8 * sizeof(num);
    unsigned int shift;
    for (shift = 1; shift < numBits; shift *= 2) {
      num ^= num >> shift;
    }

    return num;
}

/* Code by peking2: convert a binary format integer string 
 * such as "110" into 6. */
int Convert(const string& str) {
  int output = 0;
  for (unsigned i = 0; i < str.size(); i++) {
    output *= 2;
    
    if (str[i] == '1')
      output += 1;
  }
  
  return output;
}

// Code by peking2: recursive function
vector<string> GrayCode(int n) {
  vector<string> output(1<<n);
  
  if (n == 1) {
    output[0] = "0";
    output[1] = "1";
    
    return output;
  }
  
  vector<string> last = GrayCode(n - 1);
  
  for (unsigned int i = 0; i < last.size(); i++) {
    output[i] = "0" + last[i];
    output[output.size() - 1 - i] = "1" + last[i];
  }

  return output;
}

// Code by peking2: wrapper function
void GetGrayCode(int n) {
  vector<string> output = GrayCode(n);
  
  for (size_t i = 0; i < output.size(); i++)
    cout << Convert(output[i]) << endl;
}

// Code by bcloud7 
void gray(int bits) {
  int v = 0;
  for(int i = 1; i <= (1 << bits); i++) {
    cout << v << endl;
    
    int t = 0;
    while ((i & (1 << t)) == 0)
      t++;
    cout << "t = " << t << endl << endl;

    v = v ^ (1 << t);
  }
  cout << endl;
}

// DFS approach:
// http://www.mitbbs.com/article_t/JobHunting/32116371.html

/*void dfs(int i)
{
  if(i==n) 
    printf("%s\n",s); //到达底部就输出
  else {
    dfs(i+1); //深度优先搜索
    if(s[i]=='0') 
      s[i]='1';
    else 
      s[i]='0'; //把当前位逆转
    dfs(i+1); //继续向下搜索
  }
}
*/

// wwwhyx
// http://www.mitbbs.com/article_t/JobHunting/32128561.html
/*
The gray code is a binary numeral system where two successive values differ 
in only one bit.

Given a non-negative integer n representing the total number of bits in the 
code, print the sequence of gray code. A gray code sequence must begin with 
0.

For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:

00 - 0
01 - 1
11 - 3
10 - 2
*/

void _inner_sol(int& nCur, vector<int>& vec, int nStopPos, int nPos)
{
    if (nPos < 0)
    {
        vec.push_back(nCur);
        return;
    }

    _inner_sol(nCur, vec, nStopPos, nPos-1);

    if (nPos >= nStopPos)
        return;

    //flip nPos at nCur
    nCur ^= (1 << nPos);
    _inner_sol(nCur, vec, nStopPos, nPos-1);
}

vector<int> grayCode(int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<int> vec;

    if (0 == n)
        vec.push_back(0);
    else
    {
        int nCur = 0;
        _inner_sol(nCur, vec, n, 31);
    }

    return vec;
}

// peking2 java code
public ArrayList<Integer> grayCode(int n)
    {
        ArrayList<Integer> al = new ArrayList<Integer>();
        al.add(0);

        for (int i = 1; i <= n; i++)
        {
            int a = 1 << (i - 1);

            for (int j = al.size() - 1; j >= 0; j--)
            {
                al.add(al.get(j) | a);
            }
        }
        return al;
    }

// Test harness
int main() 
{
  gray(3);

  return 0;
}
