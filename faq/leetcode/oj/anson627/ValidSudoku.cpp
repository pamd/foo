//============================================================================
// Valid Sudoku
// Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.
//
// The Sudoku board could be partially filled, where empty cells are filled
// with the character '.'.
//============================================================================

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char> > &board) {
        int M = board.size();
        if (M == 0) return false;
        int N = board[0].size();
        if (N == 0) return false;
        if (M % 3 != 0 || N % 3 != 0) return false;

        bool visited[10];
        // check row
        for (int i = 0; i < M; i++) {
            memset(visited, false, sizeof(bool) * 10);
            for (int j = 0; j < N; j++) {
                if (board[i][j] != '.') {
                    int k = board[i][j] - '0';
                    if (visited[k]) return false;
                    visited[k] = true;
                }
            }
        }

        // check coloumn
        for (int j = 0; j < N; j++) {
            memset(visited, false, sizeof(bool) * 10);
            for (int i = 0; i < M; i++) {
                if (board[i][j] != '.') {
                    int k = board[i][j] - '0';
                    if (visited[k]) return false;
                    visited[k] = true;
                }
            }
        }

        // check block
        for (int i = 0; i < M; i++) {
            memset(visited, false, sizeof(bool) * 10);
            for (int j = 0; j < N; j++) {
                int r = i/3*3 + j/3;
                int c = i%3*3 + j%3;
                if (board[r][c] != '.') {
                    int k = board[r][c] - '0';
                    if (visited[k]) return false;
                    visited[k] = true;
                }
            }
        }
        return true;
    }
};


// Modified by dhu
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
  return 0;
}
