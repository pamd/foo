/* Find a 9-digit number that is composed of 1, 2, ..., 9, 
 * and the first two digits are divisible by 2, the first three digits 
 * divisible by 3, ...
 * Refer to:
 * http://www.mitbbs.com/article_t/JobHunting/32192871.html
 *
 * dhu: only one valid number is found: 381,654,729
 */

#include <iostream>

using namespace std;

// Terminate when the first valid number is found
int find(int prev, bool used[], int level) {
  if (level == 10) 
    return prev;

  if (level == 5) {
    prev = prev * 10 + 5;
    //used[5] = true;
    return find(prev, used, 6);
  }

  for (int i = 1; i <= 9; i++) {
    if (used[i] || i == 5)
      continue;
    int next = prev * 10 + i;
    if (next % level) 
      continue;
      
    used[i] = true;
    int target = find(next, used, level + 1);
    if (target > 0)
      return target;
    used[i] = false;
  }

  return -1;
}

// Print out all valid numbers
void findAll(int prev, bool used[], int level) {
  if (level == 10) 
    cout << prev << endl;

  if (level == 5) {
    prev = prev * 10 + 5;
    findAll(prev, used, 6);
    return;
  }

  for (int i = 1; i <= 9; i++) {
    if (used[i] || i == 5)
      continue;
    int next = prev * 10 + i;
    if (next % level) 
      continue;
      
    used[i] = true;
    findAll(next, used, level + 1);
    used[i] = false;
  }

  //return -1;
}

int main() {
  bool used[10] = { false };
  used[5] = true; // 5th digit will be always 5
  int prev = 0;
  findAll(prev, used, 1);

}
  
