//============================================================================
// Sudoku Solver
// Write a program to solve a Sudoku puzzle by filling the empty cells.
//
// Empty cells are indicated by the character '.'.
//
// You may assume that there will be only one unique solution.
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void solveSudoku(vector<vector<char> > &board) {
        solve(board, 0, 0);
    }

    bool solve(vector<vector<char> > &board, int row, int col) {
        bool res = getNextEmpty(board, row, col);
        if (!res) return true;
        vector<char> possible;
        getPossibleValues(board, possible, row, col);
        if (possible.size() == 0) return false;
        for (size_t i = 0; i < possible.size(); i++) {
            board[row][col] = possible[i];
            if (solve(board, row, col)) return true;
            board[row][col] = '.';
        }
        return false;
    }

    bool getNextEmpty(vector<vector<char> > &board, int &row, int &col) {
        while (row <= 8 && col <= 8) {
            if (board[row][col] == '.') return true;
            row = (col == 8) ? row + 1 : row;
            col = (col == 8) ? 0 : col + 1;
        }
        return false;
    }

    void getPossibleValues(vector<vector<char> > &board, vector<char> &possible, int row, int col) {
        bool s[9] = { false };
        for (int i = 0; i < 9; i++) {
            if (board[row][i] != '.') s[board[row][i]-'1'] = true;
            if (board[i][col] != '.') s[board[i][col]-'1'] = true;
            char c = board[row/3*3+i/3][col/3*3+i%3];
            if (c!='.') s[c-'1'] = true;
        }
        for (int i = 0; i < 9; i++) {
            if (!s[i]) possible.push_back('1'+i);
        }
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
  foo.solveSudoku(board);
  for (size_t i = 0; i < 9; i++) {
    for (size_t j = 0; j < 9; j++)  
      cout << board[i][j] << " ";
    cout << endl;
  }

  return 0;
}
