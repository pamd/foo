/* Given two words (start and end), and a dictionary, find all shortest 
 * transformation sequence(s) from start to end, such that:
 * Only one letter can be changed at a time
 * Each intermediate word must exist in the dictionary
 * For example, given:
 * start = "hit"
 * end = "cog"
 * dict = ["hot","dot","dog","lot","log"]
 *
 * Return
 *
 * [
 *  ["hit","hot","dot","dog","cog"],
 *  ["hit","hot","lot","log","cog"]
 * ]
 *
 * Note:
 * All words have the same length.
 * All words contain only lowercase alphabetic characters.
 */

#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <fstream>
#include <iostream>

using namespace std;

// dhu solution, time limit exceeded on large dataset
class Solution_dhu1 {
public:
  vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
    vector<vector<string> > ret;
    queue<pair<vector<string>, int> > Q;
    unordered_set<string> visited;
    Q.push(pair<vector<string>, int>(vector<string>(1, start), 1));
    while (!Q.empty()) {
      pair<vector<string>, int> curr = Q.front();
      Q.pop();
      if (ret.size() && curr.second > (int) ret.back().size())
	break;

      if (curr.first.back() == end)
	ret.push_back(curr.first);

      string tmp = curr.first.back();
      for (size_t i = 0; i < tmp.size(); i++) {
	char c = tmp[i];
	for (int j = 0; j < 26; j++) {
	  if (c == 'a' + j)
	    continue;

	  tmp[i] = 'a' + j;
	  if (dict.find(tmp) != dict.end() && visited.find(tmp) == visited.end()) {
	    curr.first.push_back(tmp);
	    Q.push(pair<vector<string>, int>(curr.first, curr.second + 1));
	    curr.first.pop_back();
	  }
	}
	tmp[i] = curr.first.back()[i];
      }
      visited.insert(curr.first.back());
    }

    return ret;
  }


};

// dhu solution #2
class Solution_dhu2 {
public:
  vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
    vector<vector<string> > ret;
    int max_step = get_max_step(start, end, dict);
    if (max_step == 0)
      return ret;

    unordered_map<string, vector<vector<string> > > start_cache;
    start_cache[start].push_back(vector<string>(1, start));

    unordered_map<string, vector<vector<string> > > end_cache;
    end_cache[end].push_back(vector<string>(1, end));

    int start_step = (max_step + 1) / 2;
    int end_step = max_step - start_step + 1; // Make sure starts and ends will overlap
    BFS(start, start_step, dict, start_cache);
    BFS(end, end_step, dict, end_cache);

    unordered_map<string, vector<vector<string> > >::iterator it1 = start_cache.begin();
    for (; it1 != start_cache.end(); it1++) {
      if (it1->second[0].size() < (size_t) start_step)
	continue;

      unordered_map<string, vector<vector<string> > >::iterator it2 = end_cache.find(it1->first);
      if (it2 != end_cache.end()) {
	vector<vector<string> > heads(it1->second);
	vector<vector<string> > tails(it2->second);
	for (size_t i = 0; i < heads.size(); i++) {
	  for (size_t j = 0; j < tails.size(); j++) {
	    if (heads[i].size() + tails[j].size() == (size_t) max_step + 1)
	      ret.push_back(combine(heads[i], tails[j]));
	  }
	}
      }
    }

    return ret;
  }

  // Combine two string vectors into one, the second input vector is combined 
  // in backward direction, and the last element is excluded on purpose. 
  vector<string> combine(const vector<string>& head, const vector<string>& tail) {
    vector<string> ret = head;
    for (int i = tail.size() - 2; i >= 0; i--) {
      ret.push_back(tail[i]);
    }

    return ret;
  }

  bool is_unique(const vector<string>& path, const vector<vector<string> >& v) {
    for (size_t i = 0; i < v.size(); i++) {
      if (path == v[i])
	return false;
    }

    return true;
  }

  // BFS a certain number of steps
  void BFS(const string& source, int steps, const unordered_set<string>& dict,
	   unordered_map<string, vector<vector<string> > >& history) {
    queue<pair<string, int> > Q;
    Q.push(pair<string, int>(source, 1));
    while (!Q.empty() && Q.front().second < steps) {
      pair<string, int> curr = Q.front();
      Q.pop();

      vector<vector<string> > parents = history[curr.first];
      string tmp = curr.first;
      for (size_t i = 0; i < tmp.size(); i++) {
	for (int j = 0; j < 26; j++) {
	  tmp[i] = 'a' + j;
	  if (dict.find(tmp) != dict.end()) {
	    // New word not in history
	    if (history.find(tmp) == history.end()) {
	      history[tmp] = parents;
	      for (size_t k = 0; k < history[tmp].size(); k++) 
		history[tmp][k].push_back(tmp);
	      Q.push(pair<string, int>(tmp, curr.second + 1));
	    }
	    else if (history[tmp][0].size() == (size_t) curr.second + 1) {
	      for (size_t k = 0; k < parents.size(); k++) {
		vector<string> path = parents[k];
		path.push_back(tmp);
		if (is_unique(path, history[tmp]))
		  history[tmp].push_back(path);
	      }
	    }
	  }
	}
	tmp[i] = curr.first[i];
      }
    }
    
  }

  // Get shortest path from start to end
  int get_max_step(const string& start, const string& end, const unordered_set<string> &dict) {
    unordered_set<string> dict2(dict);
    queue<pair<string, int> > Q;
    Q.push(pair<string, int>(start, 1));
    dict2.erase(start);
    while (!Q.empty()) {
      pair<string, int> curr = Q.front();
      Q.pop();
      if (curr.first == end)
	return curr.second;

      string tmp = curr.first;
      for (size_t i = 0; i < tmp.size(); i++) {
	for (int j = 0; j < 26; j++) {
	  tmp[i] = 'a' + j;
	  if (dict2.find(tmp) != dict2.end()) {
	    Q.push(pair<string, int>(tmp, curr.second + 1));
	    dict2.erase(tmp);
	  }
	}
	tmp[i] = curr.first[i];
      }
    }

    return 0;
  }

};

// dhu solution #3: BFS from both sides, 552ms for large dataset
class Solution_dhu3 {
public:
  vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
    vector<vector<string> > ret;
    unordered_map<string, vector<vector<string> > > cache1;
    cache1[start].push_back(vector<string>(1, start));

    unordered_map<string, vector<vector<string> > > cache2;
    cache2[end].push_back(vector<string>(1, end));

    queue<pair<string, int> > Q1, Q2;
    Q1.push(pair<string, int>(start, 1));
    Q2.push(pair<string, int>(end, 1));
    while (!Q1.empty() && !Q2.empty()) {
      pair<string, int> curr1 = Q1.front();
      Q1.pop();

      pair<string, int> curr2 = Q2.front();
      Q2.pop();

      // Must be "curr1.second + curr2.second - 2",
      // "curr1.second + curr2.second - 1" is a serious bug!
      if (ret.size() && curr1.second + curr2.second - 2 > (int) ret[0].size()) {
	break;
      }

      if (cache1.find(curr2.first) != cache1.end()) {
	merge(cache1[curr2.first], cache2[curr2.first], ret);
      }
      if (curr1.first != curr2.first && cache2.find(curr1.first) != cache2.end()) {
	merge(cache1[curr1.first], cache2[curr1.first], ret);
      }

      updateQ(Q1, cache1, curr1, dict); 
      updateQ(Q2, cache2, curr2, dict);
    }

    /* // dhu debug
    cout << "cache1: " << endl;
    unordered_map<string, vector<vector<string> > >::iterator it1 = cache1.begin();
    for (; it1 != cache1.end(); ++it1) {
      cout << it1->first << ": " << endl;
      print_vv(it1->second);
    }
    cout << endl;
    cout << "cache2: " << endl;
    unordered_map<string, vector<vector<string> > >::iterator it2 = cache2.begin();
    for (; it2 != cache1.end(); ++it2) {
      cout << it2->first << ": " << endl;
      print_vv(it2->second);
    }
    cout << endl;
    */

    return ret;
  }

  // dhu debug function
  void print_vv(vector<vector<string> > vv) {
    for (size_t i = 0; i < vv.size(); i++) {
      for (size_t j = 0; j < vv[i].size(); j++) 
	cout << vv[i][j] << " ";
      cout << endl;
    }
  }

  // Add new words into the queue
  void updateQ(queue<pair<string, int> >& Q, 
	       unordered_map<string, vector<vector<string> > >& cache,
	       const pair<string, int>& curr, const unordered_set<string> &dict) {
    vector<vector<string> > parents = cache[curr.first];
    string tmp = curr.first;
    for (size_t i = 0; i < tmp.size(); i++) {
      for (int j = 0; j < 26; j++) {
	tmp[i] = 'a' + j;
	if (dict.find(tmp) == dict.end() || tmp[i] == curr.first[i]) 
	  continue;

	// tmp is a word that is not in cache
	if (cache.find(tmp) == cache.end()) {
	  cache[tmp] = parents;
	  for (size_t k = 0; k < cache[tmp].size(); k++) 
	    cache[tmp][k].push_back(tmp);
	  Q.push(pair<string, int>(tmp, curr.second + 1));
	}
	// tmp is a word that is found in cache
	else if (cache[tmp][0].size() == (size_t) curr.second + 1) {
	  for (size_t k = 0; k < parents.size(); k++) {
	    vector<string> path = parents[k];
	    path.push_back(tmp);
	    cache[tmp].push_back(path);
	  }
	}
      }
      tmp[i] = curr.first[i];
    }
  }

  // Merge twostring vectors
  void merge(const vector<vector<string>>& heads, const vector<vector<string>>& tails,
	     vector<vector<string>>& merged) {
    for (size_t i = 0; i < heads.size(); i++) {
      for (size_t j = 0; j < tails.size(); j++) {
	if (!merged.size() || heads[i].size() + tails[j].size() - 1 == merged[0].size()) {
	  vector<string> new_path = combine(heads[i], tails[j]);
	  if (is_unique(new_path, merged)) 
	    merged.push_back(new_path);
	}
      }
    }
  }

  // Combine two string vectors into one, the second input vector is combined 
  // in backward direction, and the last element is excluded on purpose. 
  vector<string> combine(const vector<string>& head, const vector<string>& tail) {
    vector<string> ret = head;
    for (int i = tail.size() - 2; i >= 0; i--) {
      ret.push_back(tail[i]);
    }

    return ret;
  }

  // Does input string vector already exist in vector of vector? 
  bool is_unique(const vector<string>& path, const vector<vector<string> >& v) {
    for (size_t i = 0; i < v.size(); i++) {
      if (path == v[i])
	return false;
    }

    return true;
  }

};

// Solution by Leetcode: 1668ms for large dataset.
// http://www.mitbbs.com/article_t1/JobHunting/32325007_0_2.html
class Solution_leetcode {
  typedef unordered_multimap<string, string> Map;
  typedef pair<Map::iterator, Map::iterator> PairIter;
  vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
    // map: words that have been visited
    // map2: new words generated from the current level
    Map map, map2;

    // q: words in current level
    // q2: words in next level
    queue<string> q, q2;
    q.push(start);
    bool goal = false;
    while (!q.empty()) {
      string word = q.front();
      q.pop();
      for (int i = 0; i < start.length(); i++) {
	string s = word;
	for (char c = 'a'; c <= 'z'; c++) {
	  s[i] = c;
	  if (s == word) 
	    continue;
	  if (s == end) 
	    goal = true;
	  // Find a new valid word 
	  if (map.find(s) == map.end() && dict.find(s) != dict.end()) {
	    if (map2.find(s) == map2.end()) {
	      q2.push(s);
	    }
	    map2.insert(make_pair(s, word));
	  }
	}
      }

      // If we have visited all nodes in current level, move to the next level 
      // by swapping q and q2, then dump all elements in map2 into map. 
      if (q.empty()) {
	swap(q, q2);
	map.insert(map2.begin(), map2.end());
	map2.clear();
	if (goal) // We found it!
	  return print(map, end, start);
      }
    }

    return vector<vector<string>>();
  }

  // Recursive function: backtrack to reconstruct the path from start -> end.
  vector<vector<string>> print(Map &map, string s, string start, int depth = 0) {
    if (depth > 0 && s == start) {
      return vector<vector<string>>(1, vector<string>(1, s));
    }
    
    vector<vector<string>> ret;
    for (PairIter it = map.equal_range(s); it.first != it.second; ++it.first) {
      vector<vector<string>> temp = print(map, it.first->second, start, depth+1);
      for (int i = 0; i < temp.size(); i++) {
	temp[i].push_back(s);
      }
      ret.insert(ret.end(), temp.begin(), temp.end());
    }

    return ret;
  }

};

// dhu: Read input dictionary file into dict
void read_dict(const string filename, unordered_set<string>& dict) {
  ifstream ifs(filename);
  if (!ifs) {
    cout << "Error when reading " << filename << endl;
    exit(1);
  }

  string curr_line;
  while (getline(ifs, curr_line)) 
    dict.insert(curr_line);
}

// Test harness
int main() {
  /*
  unordered_set<string> dict;
  read_dict("word_ladder_II.dict", dict);
  string start("sand");
  string end("acne");
  */
  
  unordered_set<string> dict;
  string a[] = { "ted","tex","red","tax","tad","den","rex","pee" };
  for (int i = 0; i < 8; i++) 
    dict.insert(a[i]);
  string start = "red";
  string end = "tax";
  

  // Solve the problem
  Solution_dhu3 foo;
  vector<vector<string>> ans = foo.findLadders(start, end, dict);
  cout << endl << "answer: " << endl;
  for (size_t i = 0; i < ans.size(); i++) {
    for (size_t j = 0; j < ans[i].size(); j++) 
      cout << ans[i][j] << " ";
    cout << endl;
  }

  return 0;
}

// from "sand" to "acne", output by Solution_dhu1:
//----------------------------------------------------------
/*
sand band bind bins bids aids ands ants ante anne acne 
sand band bans bins bids aids ands ants ante anne acne 
sand sane sine side aide aids ands ants ante anne acne 
sand sane sade side aide aids ands ants ante anne acne 
sand sans bans bins bids aids ands ants ante anne acne 
sand sans kans kins kids aids ands ants ante anne acne 
sand sans sins bins bids aids ands ants ante anne acne 
sand sans sins kins kids aids ands ants ante anne acne 
sand sans sins sims aims arms arts ants ante anne acne 
sand sans sins sims aims aids ands ants ante anne acne 
sand sans sins sirs airs aids ands ants ante anne acne 


Small test #5:
-------------------------------
"hot", "dog", 
["hot","cog","dog","tot","hog","hop","pot","dot"]	
Expected:  
"hot","dot","dog"
"hot","hog","dog"

Small test #9:
--------------
"red", "tax", 
["ted","tex","red","tax","tad","den","rex","pee"]	
Expected:  
"red","ted","tad","tax"
"red","ted","tex","tax"
"red","rex","tex","tax"	

cache1[tex]:
------------
red ted tex 
red rex tex 

cache2[tex]:
------------
tax tex 

Wrong result:
---------------
red ted tad tax 
red rex tex tax 
*/
