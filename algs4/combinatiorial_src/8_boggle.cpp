/***************************************************************
 * Find all words that can be formed by tracing a simple path of
 * adjacent cubes (left, right, up, down, diagonal).
 * Based on Java code on slides #42 and #43.
 * 
 * dhu: code is incomplete.
 * -------------------------
 */

// Recursive DFS
void dfs(String prefix, int i, int j) {
  // Backtrack
  if (i < 0 || i >= N || j < 0 || j >= N || visited[i][j] || !dictionary.containsAsPrefix(prefix)) 
    return;  

  visited[i][j] = true; 
  prefix = prefix + board[i][j]; // add current character 

  if (dictionary.contains(prefix)) // add to set of found words
    found.add(prefix); 

  // Try all possibilities
  for (int ii = -1; ii <= 1; ii++) {
    for (int jj = -1; jj <= 1; jj++) 
      dfs(prefix, i + ii, j + jj); 
  }

  visited[i][j] = false; // clean up
}
