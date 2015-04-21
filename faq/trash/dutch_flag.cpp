/* Dutch flag problem, code by zhangchitc
 * http://www.mitbbs.com/article_t/JobHunting/32089461.html
 */

// From left to right, the expected order of colors is: red, white, blue 
void dutchFlag (int A[], int n) {
  int red = -1;
  int blue = n;
  int white = 0;
  while (white < blue) {
    // Current color is red, so it will be put on left side
    if (is_red(A[white])) {
      swap(A[white], A[red + 1]);
      white++;
      red++;
    } 
    // Current color is blue, so it will be put on right side
    else if (is_blue(A[white])) {
      swap(A[white], A[blue - 1]);
      blue--;
    } 
    // Current color is white, do not swap it with any other elements
    else {
      white++;
    }
  }
}

// This approach has a bug, see:
// http://www.mitbbs.com/article_t/JobHunting/32123477.html
void DutchFlag(int A[], int n)
{
  if (A == NULL || n <= 1)
    return;

  int red = 0;
  int blue = n - 1;
  int current = 0;

  while (current < blue) {
    if (is_red(A[current])) {
      swap(A, red, current);
      red++;
      current++;
    }
    else if (is_blue(A[current])) {
      swap(A, current, blue);
      blue--;
    }
    else
      current++;
  }
}
