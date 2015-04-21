/* Facebook questions:

(1) Simple regular expression match:
  
  a-z : match a-z
  a+   : match any numbers of a
  .+    : repeat 1 - arbitrary times
 
For example:
  a+b     matches:  ab, aab, aaaaaaaaaaab
  b.+b    matches:  bb, bab, b12345b

(2) boggle puzzle: find all valid words

(3) Given preorder of a binary tree, print out all the binary trees

*/

// wwwyhx: (3) Get all binary trees according to preorder
struct NODE {
  int nVal;
  NODE* pLft;
  NODE* pRgt;

  NODE(int n) : nVal(n), pLft(NULL), pRgt(NULL) {}
};

void GetComb(int a[], int n, vector<NODE*>& vec) {
  if (n <= 0) 
    return ;

  if (n == 1) {
    vec.push_back(new NODE(a[0]));
    return;
  }

  vector<NODE*> vecTmp1;
  GetComb(a+1, n-1, vecTmp1);
  for (vector<NODE*>::iterator it = vecTmp1.begin(); it != vecTmp1.end(); it++) {
    NODE* pRoot = new NODE(a[0]);
    pRoot->pRgt = *it;
    vec.push_back(pRoot);
    
    pRoot = new NODE(a[0]);
    pRoot->pLft = *it;
    vec.push_back(pRoot);
  }

  for (int i = 1; i < n-1; i++) {
    vector<NODE*> vecLft;
    GetComb(a+1, i, vecLft);
    vector<NODE*> vecRgt;
    GetComb(a+1+i, n-1-i, vecRgt);
    
    for(vector<NODE*>::iterator itl = vecLft.begin(); itl != vecLft.end(); itl++) {
      for(vector<NODE*>::iterator itr = vecRgt.begin(); itr != vecRgt.end(); itr++) {
	NODE* pNode = new NODE(a[0]);
	pNode->pLft = *itl;
	pNode->pRgt = *itr;
	
	vec.push_back(pNode);
      }
    }
  }
}

// nooneknow: (1) regex
// test过了，要源码的话站内吧。
/*
bool regex(char* str, char* pattern)
    if(!str && !pattern) return true;
    if(!str || !pattern) retrun false;

    if(pattern+1 && *(pattern+1) == '-' && pattern+2) //handle a-z
        return *str >= *pattern && *str <= *(pattern+2) && regex(str+1, 
pattern+3);

    if(pattern+1 && *(pattern+1) == '+')
        if(*pattern == '.')  //handle .+
            bool tmp = false;
            char* iter = pattern;
            while(iter) //iterater over all possible repeated times
                ++iter;
                tmp = tmp || regex(iter, pattern+2);
            return tmp; //can optimize here, return true once tmp is true in
loop
        else  //handle a+
            if(*str == *pattern)
                //repeat       1               or      more times
                return regex(str+1, pattern+2) || regex(str+1, pattern);
            return false;

    return *str == *pattern && regex(str+1, pattern+1);

(2) boggle
这个太经典。没做过的话感觉面试只能考虑递归。以前做过的话，可以用数据结构提高
效率。我做过7*7的方格，字典100万单词，需要0.2秒多点，包括所有时间。下面给个
递归的。需要源码的站内。

boggle(char[][] char_map, dict_t dict)
    //status_map记录每个位置是不是已经走过
    bool[][] status_map = false; //initilized to false
    string cur_str;
    vector<string> results;  

    //for each position as starting
    for(x is from 0 to char_map.length -1)
        for(y is from 0 to char_map[0].length -1)
            cur_str=char_map[x][y];
            status_map[x][y] = true;
            search(char_map, status_map, dict, x, y, cur_str, results);
            status_map[x][y] = false;


search(char[][] char_map, bool[][] status_map, dict_t dict, int x, int y, 
       string cur_str, vector<string> results)
    if(dict.contains(cur_str)) results.push_back(cur_str);
    if(cur_str.length == MAX_WORD_LEN) return;

    for (all 8 possible directions)
         next_pos(status_map, x, y, next_x, next_y);
         cur_str.append(char_map[next_x][next_y]);
         status_map[next_x][next_y] = true;
         search(char_map, status_map, dict, next_x, next_y, cur_str, results
);
         status_map[next_x][next_y] = false;


next_pos函数需要考虑某一个位置相邻的8个位置是不是valid。并且需要查status_map
，已经走过的地方不valid。
*/
