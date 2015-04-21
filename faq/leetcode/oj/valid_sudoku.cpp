/* Leetcode OJ: Determine if a Sudoku is valid according to Sudoku rules.
 * The Sudoku board could be partially filled, where empty cells are filled 
 * with the character '.'.
 *
 * dhu note: This problem only requires user to check whether the non-empty 
 * cell has any duplicate elements. It does NOT care whether the input Sudoku
 * has a valid solution or not. For example, for the following sudoku, 
 *
 *           1 . 3 4 5 6 7 8 9
 *           2 4 5 . . . . . .      
 *           6 7 8 . . . . . . 
 *           . . . . . . . . .
 *           . . . . . . . . .
 *           . . . . . . . . .
 *           . . . . . . . . .
 *           . . . . . . . . .
 *           . . . . . . . . .
 *
 * the solution reports that it is valid, but it does not have a valid solution,  
 * because the first row requires board[0][1] to be 2, but the upper left subsquare
 * requires it to be 9.
 * If we want to make sure that input sudoku is valid and it has a valid solution,
 * we have to call solve() to see whether a solution exists or not. See my code.
 */

#include <vector>
#include <iostream>
#include <string>

using namespace std;

// 48ms for large dataset
class Solution {
public:
  bool isValidSudoku(vector<vector<char> > &board) {
    return check(board);

    /* If we also want to know whether the input sudoku has a valid solution,
     * use the following code:
     * 
     *   if (!check(board))
     *     return false;
     *
     *   return solve(board, 0, 0);  
     *     
     */      
  }

  bool check(const vector<vector<char> >& board) {
    for (size_t i = 0; i < 9; i++) {
      if (!checkRow(board, i) || !checkCol(board, i))
	return false;
    }

    for (size_t i = 0; i < 9; i += 3) {
      if (!checkSubsquare(board, i))
	return false;
    }

    return true;
  }

  bool checkRow(const vector<vector<char> >& board, size_t row) {
    bool flags[9] = { false };
    for (size_t i = 0; i < 9; i++) {
      if (board[row][i] != '.') {
	int idx = board[row][i] - '1';
	if (flags[idx])
	  return false;
	flags[idx] = true;
      }
    }
    return true;
  }

  bool checkCol(const vector<vector<char> >& board, size_t col) {
    bool flags[9] = { false };
    for (size_t i = 0; i < 9; i++) {
      if (board[i][col] != '.') {
	int idx = board[i][col] - '1';
	if (flags[idx])
	  return false;
	flags[idx] = true;
      }
    }
    return true;
  }

  bool checkSubsquare(const vector<vector<char> >& board, size_t row) {
    for (size_t col = 0; col < 9; col += 3) {
      bool flags[9] = { false };
      for (size_t i = row; i < row + 3; i++) {
	for (size_t j = col; j < col + 3; j++) {
	  if (board[i][j] != '.') {
	    int idx = board[i][j] - '1';
	    if (flags[idx])
	      return false;
	    flags[idx] = true;
	  }
	}
      }
    }
    return true;
  }

  bool solve(vector<vector<char> >& board, size_t row, size_t col) {
    bool next = getNextEmptyCell(board, row, col);
    if (!next)
      return true;

    string choices;
    bool stat = getChoices(board, row, col, choices);
    if (!stat)
      return false;

    for (size_t i = 0; i < choices.size(); i++) {
      board[row][col] = choices[i];
      if (solve(board, row, col))
	return true;
      board[row][col] = '.';
    }

    return false;
  }

  bool getNextEmptyCell(vector<vector<char> >& board, size_t& row, size_t& col) {
    for (size_t i = row; i < 9; i++) {
      for (size_t j = col; j < 9; j++) {
	if (board[i][j] == '.') {
	  row = i;
	  col = j;
	  return true;
	}
      }
    }
    return false;
  }

  bool getChoices(vector<vector<char> >& board, size_t row, size_t col, 
		    string& choices) {
    bool flags[9] = { false };
    for (size_t i = 0; i < 9; i++) {
      if (board[row][i] != '.') {
	int idx = board[row][i] - '1';
	flags[idx] = true;
      }
	
      if (board[i][col] != '.') {
	int idx = board[i][col] - '1';
	flags[idx] = true;
      }
    }

    size_t row_lower = row / 3 * 3; 
    size_t col_lower = col / 3 * 3;
    for (size_t i = row_lower; i < row_lower + 3; i++) {
      for (size_t j = col_lower; j < col_lower + 3; j++) {
	if (board[i][j] != '.') {
	  int idx = board[i][j] - '1';
	  flags[idx] = true;
	}
      }
    }

    for (int i = 0; i < 9; i++) {
      if (!flags[i])
	choices.push_back(i + '1');
    }

    return true;
  }

};

int main() {
  vector<vector<char> > board;
  string str1("1.3456789");
  vector<char> r1(str1.begin(), str1.end()); 
  board.push_back(r1);

  string str2("245......");
  vector<char> r2(str2.begin(), str2.end()); 
  board.push_back(r2);

  string str3("678......");
  vector<char> r3(str3.begin(), str3.end()); 
  board.push_back(r3);

  string str4(".........");
  vector<char> r4(str4.begin(), str4.end()); 
  for (int i = 3; i < 9; i++) 
    board.push_back(r4);

  Solution foo;
  if (foo.isValidSudoku(board))
    cout << "valid" << endl;
  else
    cout << "invalid" << endl;
  for (size_t i = 0; i < 9; i++) {
    for (size_t j = 0; j < 9; j++)  
      cout << board[i][j] << " ";
    cout << endl;
  }

}

// Dropbox solution
bool Checked[10];
void ResetChecked() {
  for (int i = 0; i < 10; ++i)
    Checked[i] = false;
}

bool IsValidSudoku(char board[][10]) {
  // Validate rows
  for (int i = 0; i < 9; ++i) {
    ResetChecked();
    for (int j = 0; j < 9; ++j)
      if (board[i][j] != '.') {
	int index = board[i][j] - '0';
	// number collision!
	if (Checked[index]) 
	  return false;

	Checked[index] = true;
      }
  }

  // Validate columns
  for (int j = 0; j < 9; ++j) {
    ResetChecked();
    for (int i = 0; i < 9; ++i)
      if (board[i][j] != '.') {
	int index = board[i][j] - '0';
	// number collision!
	if (Checked[index]) 
	  return false;
	
	Checked[index] = true;
      }
  }

  // Validate sub-boxes
  for (int i = 0; i < 9; ++i) {
    ResetChecked();
    for (int j = 0; j < 9; ++j) {
      int r = i / 3 * 3 + j / 3;
      int c = i % 3 * 3 + j % 3;
      if (board[r][c] != '.') {
	int index = board[r][c] - '0';
	// number collision!
	if (Checked[index]) {
	  return false;
	}
				
	Checked[index] = true;
      }
			
    }
  }
  
  return true;
}

