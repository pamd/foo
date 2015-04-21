/* Insert a new node into a complete binary tree without using extra space.
 * A complete binary tree is a binary tree in which every level, except 
 * possibly the last, is completely filled, and all nodes are as far left as 
 * possible.
 * Refer to:
 * http://www.mitbbs.com/article_t/JobHunting/32120985.html
 */

#include <iostream>
#include <climits>
using namespace std;

// Helper structure
struct Node {
  Node(int v) { 
    left = right = 0; 
    dat =v; 
  }

  Node* left;
  Node* right;
  int dat;
};

/* dhu approach. This O(n) algorithm is buggy. For a binary tree like this:
 *
 *         1
 *        / \
 *       2   3
 *      / \
 *     4   5
 *
 * It will return null, and the new node will be inserted as left child
 * of node 4, but it should be inserted as left child of node 3. 
 * 
 */
Node* get_first_incomplete(Node* root) {
  if (!root->left)
    return 0;

  if (!root->right)
    return root;

  Node* left = get_first_incomplete(root->left);
  if (left)
    return left;

  return get_first_incomplete(root->right);
}

// Helper function that returns the left-most node in binary tree
Node* get_left_most(Node* root) {
  while (root->left)
    root = root->left;
  return root;
}

// Wrapper function that does insertion
void insert(Node* root, int v) {
  if (!root)
    return;

  Node* parent = get_first_incomplete(root);
  if (!parent) 
    parent = get_left_most(root);

  if (!parent->left)
    parent->left = new Node(v);
  else 
    parent->right = new Node(v);
}

/* Code by innerCool.
 * Update: fix some boundary condition checks. Recursively call a function 
 * Node* cc(Node* root) to find out where to insert an extra node, where 
 * cc checks left subtree first and then right subtree to find a non-full 
 * subtree. It returns 0 if both subtrees are full.
 *
 * dhu note: This approach is almost identical to my algorithm. 
 * So it shares the same bug.
 */
Node* cc(Node* root) {  
  // make sure that leaf node return 0
  if (root == 0) 
    return 0;
  // first check if root has both children, if not return root
  if (root->left != 0 && root->right == 0)
    return root;
  Node* tmp = cc(root->left);
  // left subtree has priority
  if (tmp != 0)
    return tmp;
  tmp = cc(root->right);
  // if right subtree is also full, then return 0
  return tmp ? tmp : 0;
}

// claxton: AMAZING simple O(n) solution.
// target will be set to the node that is closest to the root and 
// whose subtree is not complete.
// minLevel keeps track of the distance from root to target. 
void claxton_getNode(Node* root, int level, int& minLevel, Node*& target){
  if (root == NULL) 
    return;
  if (root->left == NULL || root->right == NULL) {
    if (level < minLevel) {
      target = root;
      minLevel = level;
    }
  }
  claxton_getNode(root->left, level + 1, minLevel, target);
  claxton_getNode(root->right, level + 1, minLevel, target);
}

// Wrapper for claxton_getNode()
void claxton_insert(Node* root, int v) {
  Node *target = NULL;
  int minLevel = INT_MAX;
  claxton_getNode(root, 0, minLevel, target);

  // For debugging only
  /*
  if (!target) 
    cout << "null target" << endl;
  else
    cout << target->dat << endl;
  */

  // added by dhu
  if (!target->left)
    target->left = new Node(v);
  else
    target->right = new Node(v);
}

/*
// tallcuterich
Node result = null;
boolean setResult = true;
int check(Node node){
  if(node == null){
    return 0;
  }
    
  int left = check(node.left);
  int right = check(node.right);
  
  if(left != right && setResult){
    result = node;
    setResult = false;
  }
    
  return left + right + 1;
}

// jingoshine
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>

using namespace std;

class Node {
private:
  Node *left;
  Node *right;
  int value;
    
public:
  Node() {
    left = right = NULL;
    value = 0;
  }
  
  Node(int v) {
    left = right = NULL;
    value = v;
  }
  
  int Height(Node *node) {
    int h = 0;
    if(node == NULL)
      return 0;
    while(node) {
      h++;
      node = node->left;
    }
    return h;
  }

  int HeightRight(Node *node) {
    int h = 0;
    if(node == NULL)
      return 0;
    while(node) {
      h++;
      node = node->right;
    }
    return h;
  }

  bool Insert(Node *root, Node *newNode) {
    if(root == NULL)
      return false;

    int height = Height(root);
    int checkLevel = 1;

    // First check if last level is full
    if(height == HeightRight(root)) {
      Node *node = root;
      while (node) {        
        if (node->left == NULL) {
          node->left = newNode;
          return true;
        }
        node = node->left;
      } 
    }

    Node *lastMoveLeftNode = root;
    Node *tmp = root;
    while(true) {
      if (tmp->right) {
        int h = Height(tmp->right) + checkLevel;        
        if(h == height) {
          tmp = tmp->right;
          checkLevel ++;
        }
        else {
          lastMoveLeftNode = tmp;
          tmp = tmp->left;
          checkLevel ++;
        }
      }
      else if (tmp->left) {
        // tmp->left is the last node in the complete tree.
        tmp->right = newNode;
        return true;
      }
      else {
        // tmp is the last node in the complete tree.
        // So go back to lastMoveLeftNode to inert newNode
        if(!lastMoveLeftNode->right) {
                lastMoveLeftNode->right = newNode;
                return true;
        }
        else {
          tmp = lastMoveLeftNode->right;
          while(tmp->left)
            tmp = tmp->left;
          tmp->left = newNode;
          return true;
        }
      }
    }
    return false;
  }

  void Print() {
    list<Node *> queue;  
    queue.push_back(this);
 
    while(queue.size()>0) {
      Node *node = queue.front();
      queue.pop_front();
      printf("%d ", node->value);
      
      // if(node->left) {
      //   printf("(%d, ", node->left->value);             
      // }
      // else
      //   printf("(NULL, ");
      // if(node->right) {
      //   printf("%d)  ", node->right->value);            
      // }
      // else
      //   printf("NULL)  ");
       
      if(node->left) {
        queue.push_back(node->left);
        if(node->right) {
          queue.push_back(node->right);
        }
      }
    }
    printf("\n\n");
  }
};

// jingoshine main()
int main(int argc, char *argv[]) {
  int n = 10;
  
  if(argc >= 2) {
    n = atoi(argv[1]);  
  }
  
  Node *root = new Node(0);
  for(int i=1; i<n; i++) {
    //printf("\nInsert %d\n", i);
        root->Insert(root, new Node(i));
  }
  
  root->Print();
  return 0;
}
*/



// dhu test harness
int main() {
  Node* n1 = new Node(1);
  Node* n2 = new Node(2);
  Node* n3 = new Node(3);
  Node* n4 = new Node(4);
  Node* n5 = new Node(5);

  n1->left = n2;
  n1->right = n3;
  //n2->left = n4;
  //n2->right = n5;

  claxton_insert(n1, 6);

}

