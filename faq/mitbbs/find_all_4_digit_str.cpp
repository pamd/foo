/* MITBBS: If a string includes 4 digits of 0~9, then totally there are 
 * 10,000 possible combinations. Generate the shortest string that includes 
 * all 10,000 combinations.
 *
 * Ref:
 * http://www.mitbbs.com/article_t/JobHunting/32517841.html
 * http://www.mitbbs.com/article_t/JobHunting/32518627.html
 */

// Input is an array of 4-digit string that is the starting point 
vector<string> input;

// Assume memory is not an issue here. 
// It is easy to find a memory efficiency way.
string calculate() {
  string result;
  for (int i = 0; i < input.size(); ++i) {
    result = input[i];
    unordered_set<string> visited;
    bool succeed = DFS(visited, input[i], result);
    if (succeed)
      return result;
  }

  // Can not generate
  return ""; 
}
    
bool DFS(unordered_set<string>& visited, const string& node, string& result) {
  visited.insert(node);
  if (visited.size() == 10000)
    return true;

  string nodeseg = node.substr(1, 3); // node segment
  for(int i = 0; i < 10; ++i)  {
    char ch = '0' + i;
    string nextNode = nodeseg;
    nextNode.push_back(ch);
    if (visited.find(nextNode) != visited.end()) {
      result.push_back(ch);
      bool bSucceed = DFS(visited, nextNode, result);
      if(bSucceed)
	return true;

      result.pop_back();
    }
  }
  visited.erase(node);
  
  return false;
}

// Code by DreamingBird
bool DFS2(vector<bool>& IsVisited, vector<char>& Result, int CurrNum){
  if (Result.size() == 10003) 
    return true;
  
  int pre = (CurrNum % 10000) * 10;
  for(int i = 0; i < 9; ++i){
    int NextNum = pre + i;
    if (IsVisited[NextNum]) 
      continue;
    Result.push_back('0' + i);
    IsVisited[NextNum] = true;

    if (DFS2(IsVisited, Result, NextNum)) 
      return true;

    Result.pop_back();
    IsVisited[NextNum] = false;
  }    

  return false;
}

// Wrapper that calls DFS2()
void DFS2_wrapper() {
  vector<bool> IsVisited(10000, false); 
  vector<char> Result(4, '0'); // starting from "0000"
  DFS2(IsVisited, Result, 0);
}

