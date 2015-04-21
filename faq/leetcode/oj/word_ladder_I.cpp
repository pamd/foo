/* Given two words (start and end), and a dictionary, find the length of 
 * shortest transformation sequence from start to end, such that:
 *
 * Only one letter can be changed at a time
 * Each intermediate word must exist in the dictionary
 * For example, given:
 * start = "hit", end = "cog"
 * dict = ["hot","dot","dog","lot","log"]
 *
 * As one shortest transformation is:
 * "hit" -> "hot" -> "dot" -> "dog" -> "cog",
 * return its length 5.
 *
 * Note:
 * Return 0 if there is no such transformation sequence.
 * All words have the same length.
 * All words contain only lowercase alphabetic characters.
 */	

// 576ms for large dataset
class Solution {
public:
  int ladderLength(string start, string end, unordered_set<string> &dict) {
    queue<pair<string, int> > Q;
    dict.insert(end);
    Q.push(pair<string, int>(start, 1));
    while (!Q.empty()) {
      pair<string, int> curr = Q.front();
      Q.pop();
      if (curr.first == end)
	return curr.second;

      dict.erase(curr.first);
      string tmp = curr.first;
      for (size_t i = 0; i < tmp.size(); i++) {
	for (int j = 0; j < 26; j++) {
	  tmp[i] = 'a' + j;
	  if (dict.find(tmp) != dict.end()) {
	    Q.push(pair<string, int>(tmp, curr.second + 1));
	    dict.erase(tmp); // key reason that why large dataset can be passed
	  }
	}
	tmp[i] = curr.first[i];
      }
    }

    return 0;
  }

};

// anson627: 616 ms for large dataset
class Solution_anson {
public:
  int ladderLength(string start, string end, unordered_set<string> &dict) {
    queue<pair<string, int> > queue;
    queue.push(make_pair(start, 1));
    dict.insert(end);
    while (!queue.empty()) {
      pair<string, int> cur = queue.front();   
      queue.pop();
      if (cur.first == end)
	return cur.second;
      
      for (string word : getNeighbors(cur.first, dict)) {
	queue.push(make_pair(word, cur.second+1));
      }
    }

    return 0;
  }

  vector<string> getNeighbors(string const & word, unordered_set<string> &dict) {
    vector<string> res;
    for (size_t i = 0; i < word.size(); i++) {
      string copy(word);
      for (char c = 'a'; c <= 'z'; c++) {
	copy[i] = c;
	if (dict.find(copy) != dict.end()) {
	  res.push_back(copy);
	  dict.erase(copy);
	}
      }
    }
    return res;
  }
};

       
