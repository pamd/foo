/* Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.
 * A region is captured by flipping all 'O's into 'X's in that surrounded region .
 * For example,
 *
 *   X X X X
 *   X O O X
 *   X X O X
 *   X O X X
 * 
 * After running your function, the board should be:
 *
 *   X X X X
 *   X X X X
 *   X X X X
 *   X O X X
 */

class Solution {
public:
  // dhu DFS solution, runtime error when testing large dataset
  void solve(vector<vector<char>> &board) {
    if (board.size() == 0 || board[0].size() == 0)
      return;

    vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size(), false));
    for (size_t i = 0; i < board[0].size(); i++) {
      DFS(board, 0, i, visited); // top edge
      DFS(board, board.size() - 1, i, visited); // bottom edge
    }

    for (size_t i = 1; i < board.size() - 1; i++) {
      DFS(board, i, 0, visited); // left edge
      DFS(board, i, board[i].size() - 1, visited); // right edge
    }

    for (size_t i = 0; i < board.size(); i++) {
      for (size_t j = 0; j < board[i].size(); j++) {
	if (board[i][j] == 'O' && !visited[i][j])
	  board[i][j] = 'X';
      }
    }
  }

  void DFS(const vector<vector<char>> &board, int row, int col, 
	   vector<vector<bool>>& visited) {
    if (row < 0 || row >= board.size())
      return;
    if (col < 0 || col >= board[0].size())
      return;

    if (board[row][col] == 'X')
      return;
    if (visited[row][col])
      return;

    visited[row][col] = true;
    DFS(board, row + 1, col, visited);
    DFS(board, row - 1, col, visited);
    DFS(board, row, col + 1, visited);
    DFS(board, row, col - 1, visited);
  }

};

// anson627
class Solution_anson {
public:
  void solve(vector<vector<char>> &board) {
    solve1(board);
  }

  // DFS solution: runtime error for large dataset
  void solve1(vector<vector<char>> &board) {
    if (board.empty()) 
      return;

    int M = board.size();
    int N = board[0].size();

    for (int i = 0; i < M; i++) {
      if (board[i][0] == 'O') 
	dfs(board, M, N, i, 0);
      if (board[i][N-1] == 'O') 
	dfs(board, M, N, i, N-1);
    }

    for (int j = 1; j < N-1; j++) {
      if (board[0][j] == 'O') 
	dfs(board, M, N, 0, j);
      if (board[M-1][j] == 'O') 
	dfs(board, M, N, M-1, j);
    }

    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
	if (board[i][j] == 'O') 
	  board[i][j] = 'X';
	else if (board[i][j] == 'D') 
	  board[i][j] = 'O';
      }
    }
  }

  // DFS called by solve1() 
  void dfs(vector<vector<char>> &board, int M, int N, int i, int j) {
    board[i][j] = 'D';
    if (i > 0 && board[i-1][j] == 'O') 
      dfs(board, M, N, i-1, j);

    if (i < M-1 && board[i+1][j] == 'O') 
      dfs(board, M, N, i+1, j);

    if (j > 0 && board[i][j-1] == 'O') 
      dfs(board, M, N, i, j-1);

    if (j < N-1 && board[i][j+1] == 'O') 
      dfs(board, M, N, i, j+1);
  }

  // BFS soolution: 60ms for large dataset
  void solve2(vector<vector<char>> &board) {
    if (board.empty()) 
      return;
    int M = board.size();
    int N = board[0].size();
    
    for (int i = 0; i < M; i++) {
      if (board[i][0] == 'O') 
	bfs(board, M, N, i, 0);
      if (board[i][N-1] == 'O') 
	bfs(board, M, N, i, N-1);
    }

    for (int j = 1; j < N-1; j++) {
      if (board[0][j] == 'O') 
	bfs(board, M, N, 0, j);
      if (board[M-1][j] == 'O') 
	bfs(board, M, N, M-1, j);
    }

    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
	if (board[i][j] == 'O') 
	  board[i][j] = 'X';
	else if (board[i][j] == 'D') 
	  board[i][j] = 'O';
      }
    }
  }

  // BFS called by solve2()
  void bfs(vector<vector<char>> &board, int M, int N, int i, int j) {
    queue<pair<int, int>> queue;
    board[i][j] = 'D';
    queue.push(make_pair(i, j));
    
    while (!queue.empty()) {
      i = queue.front().first;
      j = queue.front().second;
      queue.pop();
      if (i > 1 && board[i-1][j] == 'O') {
	board[i-1][j] = 'D';
	queue.push(make_pair(i-1, j));
      }

      if (i < M-1 && board[i+1][j] == 'O') {
	board[i+1][j] = 'D';
	queue.push(make_pair(i+1, j));
      }

      if (j > 1 && board[i][j-1] == 'O') {
	board[i][j-1] = 'D';
	queue.push(make_pair(i, j-1));
      }
       
     if (j < N-1 && board[i][j+1] == 'O') {
       board[i][j+1] = 'D';
       queue.push(make_pair(i, j+1));
     }
    }
  }
};


