/* Leetcode OJ: Write a program to solve a Sudoku puzzle by filling the empty cells.
 * Empty cells are indicated by the character '.'.
 * You may assume that there will be only one unique solution.
 */

#include <iostream>
#include <vector>

using namespace std;

// anson627: 128ms for large dataset
class Solution {
public:
  void solveSudoku(vector<vector<char> > &board) {
    solve(board, 0, 0);
  }

  // Recursive function
  bool solve(vector<vector<char> > &board, int row, int col) {
    bool res = getNextEmpty(board, row, col);
    if (!res) 
      return true;

    vector<char> possible;
    getPossibleValues(board, possible, row, col);
    if (possible.size() == 0) 
      return false;

    for (size_t i = 0; i < possible.size(); i++) {
      board[row][col] = possible[i];
      if (solve(board, row, col)) 
	return true;
      //board[row][col] = '.';
    }
    /* IMPORTANT: Reset the next empty position back to blank.
     * It can also be done in the for loop above. */  
    board[row][col] = '.';
    return false;
  }

  /* Returns true if any empty cell from  board[row][col] is found,
   * then set row and col to the position of the next empty cell. 
   * Returns false if no empty cell exists on the board. */
  bool getNextEmpty(vector<vector<char> >& board, int &row, int &col) {
    while (row <= 8 && col <= 8) {
      if (board[row][col] == '.') 
	return true;
      row = (col == 8) ? row + 1 : row;
      col = (col == 8) ? 0 : col + 1;
    }
    return false;
  }
  
  /* Collect possible values for empty cell board[row][col] */
  void getPossibleValues(vector<vector<char> >& board, vector<char>& possible, 
			 int row, int col) {
    bool s[9] = { false };
    for (int i = 0; i < 9; i++) {
      if (board[row][i] != '.') 
	s[board[row][i] - '1'] = true;

      if (board[i][col] != '.') 
	s[board[i][col] - '1'] = true;

      char c = board[row / 3 * 3 + i / 3][col / 3 * 3 + i % 3];
      if (c !='.') 
	s[c - '1'] = true;
    }

    for (int i = 0; i < 9; i++) {
      if (!s[i]) 
	possible.push_back('1' + i);
    }
  }
};

/* The following class gets all solutions of a giver sudoku. 
 * Depending on the input sudoku, it may take a long time to
 * get all solutions.
 */
class Solution_all {
public:
  vector<vector<vector<char> > > solveSudoku(vector<vector<char> > &board) {
    vector<vector<vector<char> > > solutions;
    solve(board, 0, 0, solutions);
    return solutions;
  }

  // Recursive function
  void solve(vector<vector<char> > &board, int row, int col, 
	     vector<vector<vector<char> > >& solutions) {
    bool res = getNextEmpty(board, row, col);
    if (!res) {
      solutions.push_back(board);
      return;
    }

    vector<char> candidates;
    getPossibleValues(board, candidates, row, col);
    if (candidates.size() == 0) 
      return;

    for (size_t i = 0; i < candidates.size(); i++) {
      board[row][col] = candidates[i];
      solve(board, row, col, solutions);
    }
    /* IMPORTANT: Reset the next empty position back to blank.
     * It can also be done in the for loop above. */  
    board[row][col] = '.';
  }

  /* Returns true if any empty cell from  board[row][col] is found,
   * then set row and col to the position of the next empty cell. 
   * Returns false if no empty cell exists on the board. */
  bool getNextEmpty(vector<vector<char> >& board, int &row, int &col) {
    while (row <= 8 && col <= 8) {
      if (board[row][col] == '.') 
	return true;
      row = (col == 8) ? row + 1 : row;
      col = (col == 8) ? 0 : col + 1;
    }
    return false;
  }
  
  /* Collect possible values for empty cell board[row][col] */
  void getPossibleValues(vector<vector<char> >& board, vector<char>& possible, 
			 int row, int col) {
    bool s[9] = { false };
    for (int i = 0; i < 9; i++) {
      if (board[row][i] != '.') 
	s[board[row][i] - '1'] = true;

      if (board[i][col] != '.') 
	s[board[i][col] - '1'] = true;

      char c = board[row / 3 * 3 + i / 3][col / 3 * 3 + i % 3];
      if (c !='.') 
	s[c - '1'] = true;
    }

    for (int i = 0; i < 9; i++) {
      if (!s[i]) 
	possible.push_back('1' + i);
    }
  }
};

/* Print all solutions on screen. */
class Solution_all2 {
public:
  double counter;
  void solveSudoku(vector<vector<char> > &board) {
    counter = 0;
    solve(board, 0, 0);
  }

  // Recursive function
  void solve(vector<vector<char> > &board, int row, int col) {
    bool res = getNextEmpty(board, row, col);
    if (!res) {
      if (!isValid(board)) {
	cout << "Invalid solution!" << endl;
	for (size_t i = 0; i < board.size(); i++) {
	  string row(board[i].begin(), board[i].end());
	  cout << row << endl;
	}
	cout << endl;
      }
      else
	++counter;

      return;
    }

    vector<char> candidates;
    getPossibleValues(board, candidates, row, col);
    if (candidates.size() == 0) 
      return;

    for (size_t i = 0; i < candidates.size(); i++) {
      board[row][col] = candidates[i];
      solve(board, row, col);
    }
    /* IMPORTANT: Reset the next empty position back to blank.
     * It can also be done in the for loop above. */  
    board[row][col] = '.';
  }

  /* Returns true if any empty cell from  board[row][col] is found,
   * then set row and col to the position of the next empty cell. 
   * Returns false if no empty cell exists on the board. */
  bool getNextEmpty(vector<vector<char> >& board, int &row, int &col) {
    while (row <= 8 && col <= 8) {
      if (board[row][col] == '.') 
	return true;
      row = (col == 8) ? row + 1 : row;
      col = (col == 8) ? 0 : col + 1;
    }
    return false;
  }
  
  /* Collect possible values for empty cell board[row][col] */
  void getPossibleValues(vector<vector<char> >& board, vector<char>& possible, 
			 int row, int col) {
    bool s[9] = { false };
    for (int i = 0; i < 9; i++) {
      if (board[row][i] != '.') 
	s[board[row][i] - '1'] = true;

      if (board[i][col] != '.') 
	s[board[i][col] - '1'] = true;

      char c = board[row / 3 * 3 + i / 3][col / 3 * 3 + i % 3];
      if (c !='.') 
	s[c - '1'] = true;
    }

    for (int i = 0; i < 9; i++) {
      if (!s[i]) 
	possible.push_back('1' + i);
    }
  }

  // Determine whether input board is a valid solution
  bool isValid(const vector<vector<char> >& board) {
    // Check each row
    for (size_t row = 0; row < 9; row++) {
      vector<bool> flags(9, false);      
      for (size_t col = 0; col < 9; col++) {
	char c = board[row][col];
	if (c < '1' || c > '9')
	  return false;
	int idx = c - '1';
	if (flags[idx])
	  return false;
	flags[idx] = true;
      }
    }

    // Check each column
    for (size_t col = 0; col < 9; col++) {
      vector<bool> flags(9, false);      
      for (size_t row = 0; row < 9; row++) {
	char c = board[row][col];
	int idx = c - '1';
	if (flags[idx])
	  return false;
	flags[idx] = true;
      }
    }

    // Check each 3x3 subsquare
    for (size_t row = 0; row < 9; row += 3) {
      for (size_t col = 0; col < 9; col += 3) {
	vector<bool> flags(9, false);   
	for (size_t i = row; i < row + 3; i++) {
	  for (size_t j = col; j < col + 3; j++) {
	    char c = board[i][j];
	    int idx = c - '1';
	    if (flags[idx])
	      return false;
	    flags[idx] = true;
	  }
	}
      }
    }

    return true;
  }
};

int main() {
  // This sudoku has 3.79354e+07 solutions, and it takes ajax ~40 minutes.
  string arr[] = { "123456789","789123456",".........",".........",".........",".........",
		   ".........",".........","234567891" };

  vector<vector<char> > board;
  for (int i = 0; i < 9; i++) 
    board.push_back(vector<char>(arr[i].begin(), arr[i].end()));

  // Test code for Solution_all
  /*
    Solution_all foo;
    vector<vector<vector<char> > > solutions = foo.solveSudoku(board);
    for (size_t i = 0; i < solutions.size(); i++) {
    for (size_t j = 0; j < 9; j++) {
    string row(solutions[i][j].begin(), solutions[i][j].end());
    cout << row << endl;
    }
    cout << endl;
    }
  */

  // Test code for Solution_all2
  Solution_all2 foo;
  foo.solveSudoku(board);
  cout << "Number of valid solutions: " << foo.counter << endl;
}
 /*
  "..9748...","7........",".2.1.9...","..7...24.",".64.1.59.",".98...3..","...8.3.2.","........6","...2759.."]	["519748632","783652419","426139875","357986241","264317598","198524367","975863124","832491756","641275983"]
   
["53..7....","6..195...",".98....6.","8...6...3","4..8.3..1","7...2...6",".6....28.","...419..5","....8..79"]	["534678912","672195348","198342567","859761423","426853791","713924856","961537284","287419635","345286179"]	["534678912","672195348","198342567","859761423","426853791","713924856","961537284","287419635","345286179"]	
   
[".265...9.","5...79..4","3...1....","6.....8.7",".75.2..1.",".1....4..","...3.89.2","7...6..4.",".3.2..1.."]	["426583791","581679234","397412586","643195827","975824613","218736459","164358972","752961348","839247165"]	["426583791","581679234","397412586","643195827","975824613","218736459","164358972","752961348","839247165"]	
   
["...2...63","3....54.1","..1..398.",".......9.","...538...",".3.......",".263..5..","5.37....8","47...1..."]	["854219763","397865421","261473985","785126394","649538172","132947856","926384517","513792648","478651239"]	["854219763","397865421","261473985","785126394","649538172","132947856","926384517","513792648","478651239"]	
   
["1...7..3.","83.6.....","..29..6.8","6....49.7",".9.....5.","3.75....4","2.3..91..",".....2.43",".4..8...9"]	["169875432","834621795","572943618","625134987","498267351","317598264","283459176","956712843","741386529"]	["169875432","834621795","572943618","625134987","498267351","317598264","283459176","956712843","741386529"]	
  */   
