/* Google: Give an unsorted array, find count of pairs of numbers[a, b] where a > b 
 * and b comes after a in the array. For example, for array { 8, 3, 6, 10, 5 }, 
 * the count of such numbers is 5: (8,3), (8,6), (8,5), (6,5) and (10,5).
 * Ref: http://www.mitbbs.com/article_t/JobHunting/31951147.html (dead)
 * Code copied from post #17.
 */

#include <iostream>

using namespace std;

struct Node {
  int v;
  int count;
  Node* left;
  Node* right;
  Node(int _v) : v(_v), count(1), left(0), right(0) { }
};

void insert(Node*& root, int v, int& c){
  if (root == 0){
    root = new Node(v);
    return;
  }

  root->count++;
  if (root->v == v) {
    if (root->right)
      c = c + root->right->count;
  }
  else if (v < root->v) {
    insert(root->left, v, c);
    c = c + root->count - root->left->count;
  }
  else
    insert(root->right, v, c);
}

int find(int* a, int n){
  Node * root = 0;
  int c = 0;
  for (int i = 0; i < n; i++) 
    insert( root, a[i], c);
  
  return c;
}

struct Node_dhu {
  Node_dhu(int val) { data = val; count_right = 0; left = 0; right = 0; }

  Node_dhu* left;
  Node_dhu* right;
  int data;
  int count_right;  // Number of nodes on right subtree
};

void insert_dhu(Node_dhu*& root, int val, int& c) {
  if (!root) {
    root = new Node_dhu(val);
    return;
  }

  if (root->data > val) {
    c++;
    c = c + root->count_right;
    insert_dhu(root->left, val, c);
  }
  else {
    root->count_right++;
    insert_dhu(root->right, val, c);
  }
}

int find_dhu(int* a, int n){
   Node_dhu* root = 0;
   int c = 0;
   for (int i = 0; i < n; i++) 
     insert_dhu(root, a[i], c);
   
   return c;
}

int main() {
  int a[] = { 8, 3, 3, 6, 1, 10, 5 };
  cout << "(1) " << find(a, sizeof(a) / sizeof(int)) << endl;
  cout << "(2) " << find_dhu(a, sizeof(a) / sizeof(int)) << endl;

}
