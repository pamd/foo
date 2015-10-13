//
// Because the leaf nodes on T reaches level 5, we now have to rebalance the tree rooted at 15.
//
// The AVL trees are more balanced compared to Red Black Trees, but they may cause more rotations
// during insertion and deletion. So if your application involves many frequent insertions and
// deletions, then Red Black trees should be preferred. And if the insertions and deletions are
// less frequent, and search is more frequent, then AVL tree should be preferred over Red Black
// Tree.

#include <iostream>

using namespace std;

// An AVL tree node
struct Node
{
   int key;
   Node* left;
   Node* right;
   int height; // Height of the subtree whose root is current node.
};

// A utility function to get height of the tree
int get_height(Node* root) {
   if (!root) {
      return 0;
   }

   return root->height;
}

// Helper function: allocate a new node with the given key,
// and set left and right children to NULL.
Node* create_node(int key) {
   Node* node = new Node;
   node->key = key;
   node->left = NULL;
   node->right = NULL;
   node->height = 1;  // new node is initially added at leaf

   return node;
}

// Right rotate subtree rooted with "root".
Node* right_rotate(Node* root) {
   Node* x = root->left;
   Node* T2 = x->right;

   // Perform rotation
   x->right = root;
   root->left = T2;

   // Update heights
   root->height = max(get_height(root->left), get_height(root->right)) + 1;
   x->height = max(get_height(x->left), get_height(x->right)) + 1;

   // Return new root
   return x;
}

// Left rotate subtree rooted with node x.
Node* left_rotate(Node* x) {
   Node* y = x->right;
   Node *T2 = y->left;

   // Perform rotation
   y->left = x;
   x->right = T2;

   //  Update heights
   x->height = max(get_height(x->left), get_height(x->right)) + 1;
   y->height = max(get_height(y->left), get_height(y->right)) + 1;

   // Return new root
   return y;
}

// Get Balance factor of node N
int get_balance_factor(Node* root) {
   if (!root) {
      return 0;
   }

   return get_height(root->left) - get_height(root->right);
}

// Return the root of BST (which may have been rebalanced).
Node* insert(Node* root, int key) {
   // 1) Perform the normal BST rotation.
   if (!root) {
      return create_node(key);
   }

   if (key < root->key) {
      root->left = insert(root->left, key);   // Recursive call on left subtree.
   }
   else {
      root->right = insert(root->right, key); // Recursive call on right subtree.
   }

   // 2) Update height of current root
   root->height = max(get_height(root->left), get_height(root->right)) + 1;

   // 3) Check whether the subtree from root becomes unbalanced or not.
   int balance = get_balance_factor(root);

   // If the subtree from root is still balance, do nothing, return root immediately.
   if (balance >= -1 && balance <= 1) {
      return root;
   }

   // If this node becomes unbalanced, then there are 4 cases:
   // 4a) Left Left Case
   if (balance > 1 && key < root->left->key) {
      return right_rotate(root);
   }

   // 4b) Left Right Case
   if (balance > 1 && key > root->left->key) {
      root->left = left_rotate(root->left);
      return right_rotate(root);
   }

   // 5a) Right Right Case
   if (balance < -1 && key > root->right->key) {
      return left_rotate(root);
   }

   // 5b) Right Left Case
   if (balance < -1 && key < root->right->key) {
      root->right = right_rotate(root->right);
      return left_rotate(root);
   }
}

// Utitlity function used by delete().
// It returns the node whose key value is minimum in the tree.
Node* get_min_node(Node* root)
{
   Node* current = root;
   // Find the left-most leaf node.
   while (current->left) {
      current = current->left;
   }
   return current;
}

// Deletion in AVL tree:
// Let w be the node to be deleted,
// 1) Perform standard BST delete for w.
// 2) Starting from w, travel up and find the first unbalanced node. Let:
//       z be the first unbalanced node,
//       y be the larger height child of z,
//       x be the larger height child of y.
//    Note that the definitions of x and y are different from insertion here.
// 3) Re-balance the tree by performing appropriate rotations on the subtree rooted with z.
//    There can be 4 possible cases that needs to be handled as x, y and z can be arranged
//    in 4 ways. Following are the possible 4 arrangements:
//       a) y is left child of z and x is left child of y (Left Left Case)
//       b) y is left child of z and x is right child of y (Left Right Case)
//       c) y is right child of z and x is right child of y (Right Right Case)
//       d) y is right child of z and x is left child of y (Right Left Case)
//
//    Note that, unlike insertion, fixing the node z may not fix the complete AVL tree.
//    After fixing z, we may have to fix ancestors of z as well. Thus, we must continue
//    to trace the path until we reach the root.
// ---------------------------------------------------------------------------------------------
// The following C++ implementation uses the recursive BST delete as basis. In the recursive
// BST delete, after deletion, we get pointers to all ancestors one by one in bottom up manner.
// So we don't need parent pointer to travel up. The recursive code itself travels up and visits
// all the ancestors of the deleted node.
// 1) Perform the normal BST deletion.
// 2) The current node must be one of the ancestors of the deleted node. Update the height of
//    the current node.
// 3) Get the balance factor (left_subtree_height - right_subtree_height) of the current node.
// 4) If balance factor is greater than 1, then the current node is unbalanced, and we are
//    either in Left Left case or Left Right case. To check whether it is Left Left case or
//    Left Right case, get the balance factor of left subtree. If balance factor of the left
//    subtree >= 0, then it is Left Left case, else Left Right case.
// 5) If balance factor is less than -1, then the current node is unbalanced, and we are either
//    in Right Right case or Right Left case. To check whether it is Right Right case or Right
//    Left case, get the balance factor of right subtree. If the balance factor of the right
//    subtree <= 0, then it is Right Right case, else Right Left case.
//
Node* delete_key(Node* root, int key)
{
   // STEP 1: Perform standard BST deletion.
   if (!root) {
      return root;
   }

   // If the key to be deleted is less than the root's key, recurse on the left subtree.
   if (key < root->key) {
      root->left = delete_key(root->left, key);
   }
   // If the key to be deleted is greater than the root's key, recurse on the right subtree.
   else if (key > root->key) {
      root->right = delete_key(root->right, key);
   }
   else { // Root is the node that should be deleted.
      // Root is a leaf node, or it has only one child.
      if (!root->left || !root->right) {
         Node* temp = root->left ? root->left : root->right;
         // Root is a leaf node.
         if (!temp) {
            temp = root;
            root = NULL;
         }
         // Root has only one child.
         else {
            *root = *temp; // Copy the contents of non-empty child to root node.
         }
         delete temp;   // Delete "temp", which is a clone of root node.
      }
      // Root has both left and right children, so we will get root's in-order
      // successor (the node whose kkey is the least in the right subtree).
      else {
         Node* temp = get_min_node(root->right);
         root->key = temp->key; // Copy the successor's data to root node.
         root->right = delete_key(root->right, temp->key); // Use recursion to delete the successor node.
      }
   }

   // If the tree had only one node, return immediately.
   if (!root) {
      return root;
   }

   // STEP 2: Update current node's height.
   root->height = max(get_height(root->left), get_height(root->right)) + 1;

   // STEP 3: Check whether root node became unbalanced or not.
   int balance = get_balance_factor(root);

   // If it is still balanced, return immediately.
   if (balance >= -1 && balance <= 1) {
      return root;
   }

   // If root node becomes unbalanced, then there are 4 cases:
   // 1) Left Left Case
   if (balance > 1 && get_balance_factor(root->left) >= 0) {
      return right_rotate(root);
   }

   // 2) Left Right Case
   if (balance > 1 && get_balance_factor(root->left) < 0) {
      root->left = left_rotate(root->left);
      return right_rotate(root);
   }

   // 3) Right Right Case
   if (balance < -1 && get_balance_factor(root->right) <= 0) {
      return left_rotate(root);
   }

   // 4) Right Left Case
   if (balance < -1 && get_balance_factor(root->right) > 0) {
      root->right = right_rotate(root->right);
      return left_rotate(root);
   }
}

// Utility function: print pre-order traversal of the tree and the height of each node.
void pre_order(Node* root)
{
   if (root) {
      cout << "Key: " << root->key << ", height: " << root->height << endl;
      pre_order(root->left);
      pre_order(root->right);
   }
}

// Test insertion. main() in:
// http://www.geeksforgeeks.org/avl-tree-set-1-insertion/
void test_insertion() {
   Node* root = NULL;

   // Constructing tree.
   root = insert(root, 10);
   root = insert(root, 20);
   root = insert(root, 30);
   root = insert(root, 40);
   root = insert(root, 50);
   root = insert(root, 25);

   // The constructed AVL Tree should be:
   //
   //         30
   //        /  \
   //       20  40
   //      /  \   \
   //     10  25  50
   //

   cout << "Pre-order traversal of the constructed AVL tree is: " << endl;;
   pre_order(root);
}

// Test insertion and deletion, main() in:
// http://www.geeksforgeeks.org/avl-tree-set-2-deletion/
void test_deletion() {
   Node* root = NULL;

   // Constructing tree given in the above figure.
   root = insert(root, 9);
   root = insert(root, 5);
   root = insert(root, 10);
   root = insert(root, 0);
   root = insert(root, 6);
   root = insert(root, 11);
   root = insert(root, -1);
   root = insert(root, 1);
   root = insert(root, 2);

   // The constructed AVL Tree would be:
   //        9
   //       / \
   //      1   10
   //     / \   \
   //    0   5   11
   //   /   / \
   //  -1  2   6
   //

   cout << "Pre order traversal of the constructed AVL tree is:" << endl;
   pre_order(root);

   // Delete "10" from the tree.
   root = delete_key(root, 10);

   // The AVL Tree becomes:
   //       1
   //      / \
   //     0   9
   //    /   / \
   //   -1  5  11
   //      / \
   //     2   6
   //

   printf("\nPre order traversal after deletion of 10 \n");
   pre_order(root);
}

// Test harness:
int main()
{
   // test_insiertion();

   test_deletion();

   return 0;
}
