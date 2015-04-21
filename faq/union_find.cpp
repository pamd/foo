/* Union-Find algorithm
 * Code by longway2008, from:
 * http://www.mitbbs.com/article_t/JobHunting/32117513.html
 *
 * Traditionally, this problem was solved by using an array.
 * See Sedgewick "Algorithms" 4th edition, chapter 1.5,
 * and EPI book Problem 3.7 (Offline minimum).
 */

struct Union {
  unordered_map<string, string> T;  // <key, root>

  // Constructor reads from stdin, then calls Merge()
  Union(iostream & fin) {
    string a,b;
    while (!fin.eof()) {
      fin >> a >> b; 
      Merge(a, b);  
    }
  }
  
  // Merge() calls FindRoot() to merge the two 
  void Merge(const string &a, const string &b) {
    if (T.count(a) == 0)
      T[a] = "";
    
    if (T.count(b) == 0)
      T[b] = "";
  
    T[FindRoot[a]] = FindRoot[b];
  }

  /* Search input string's root recursively. Note that 
   * this function also modifies hashmap T (path compression). */
  const string & FindRoot(const string & s) {
    if (T[s].empty())
      return s;

    T[s] = FindRoot(T[s]);    
    return T[s];
  }

  // Do the two input string share same root? 
  // Return true if yes, false otherwise.
  bool CheckConnection(const string &a, const string &b) {
    return FindRoot(a) == FindRoot(b);
  }

};
