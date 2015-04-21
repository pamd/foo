/* Google: Given a matrix whose elements are integers. Each cell represents 
 * the altitude of an area. Suppose the left side of matrix is Pacific Ocean, 
 * and right side Atlantic Ocean. Print out all paths along which water can 
 * flow from Pacific to Atlantic, or from Atlantic to Pacific.
 *
 * Refer to:
 * http://www.mitbbs.com/article_t/JobHunting/32549767.html
 */

#include <iostream>

// Code by smilenceyu
class point{
public:
  int row;
  int col;
};

bool isValid( int row, int col, bool used[HEIGHT][WIDTH]){
  if (row > HEIGHT || col > WIDTH || row < 0 || col < 0 )
    return false;

  if (used[row][col])
    return false;

  return true;
}

void flow(int row, int col, vector<point> &path, vector<list<point> >& paths, 
	   int mat[HEIGHT][WIDTH], bool used[HEIGHT][WIDTH]) {
  int value = mat[row][col];
  used[row][col] = true;
  point p;
  p.row = row;
  p.col = col;
  path.push_back(p); 
  if (col == WIDTH - 1) {
    list<point> tmp(path.begin(), path.end());
    paths.push_back(tmp);
    //return; wrong!
  }

  if (isValid(row - 1, col, used) && mat[row - 1][col] <= value)
    flow(row - 1, col, path, paths, mat, used); 

  if (isValid(row - 1, col - 1, used) && mat[row - 1][col - 1] <= value)
    flow(row - 1, col - 1, path, paths, mat, used);

  if (isValid(row , col - 1, used) && mat[row ][col - 1] <= value)
    flow(row, col - 1, path, paths, mat, used);

  if (isValid(row + 1, col - 1, used) && mat[row + 1][col - 1] <= value)
    flow(row + 1, col - 1, path, paths, mat, used);

  if (isValid(row + 1, col, used) && mat[row + 1][col] <= value)
    flow(row + 1, col, path, paths, mat, used);

  if (isValid(row + 1, col + 1, used) && mat[row + 1][col + 1] <= value)
    flow(row + 1, col + 1, path, paths, mat, used);

  if (isValid(row + 1, col - 1, used) && mat[row + 1][col - 1] <= value)
    flow(row + 1, col - 1, path, paths, mat, used);

  if (isValid(row , col + 1, used) && mat[row][col + 1] <= value)
    flow(row, col + 1, path, paths, mat, used);

  path.pop_back();
  used[row][col] = false;
}

vector<list<point> > calPaths(int mat[HEIGHT][WIDTH]) {
  vector<point> path;
  vector<list<point> > paths;
  bool used[HEIGHT][WIDTH];
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      used[i][j] = false;
    }
  }

  for (int i = 0; i < HIEGHT; i++) {
    flow(i, 0, path, paths, mat, used);
  }

  return paths;
}
