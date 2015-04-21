/* Build a BST based on its representation of by-level printout. For example:
 *
 * 5 
 * 4 8 
 * 2 7 9 
 * 3 10 
 *
 * The corresponding BST will be:
 *     5
 *    / \
 *   4   8
 *  /   / \
 * 2   7   9
 *  \       \
 *   3      10
 *
 * Refer to:
 * http://www.mitbbs.com/article_t/JobHunting/32128319.html
 */

#include <iostream>
#include <vector>
#include <deque>
#include <climits>

using namespace std;

// Generic binary search tree node
struct Node {
  Node(int i) : dat(i), left(0), right(0) { }

  int dat;
  Node* left;
  Node* right;

};

// hackie: recusive function, it is also easy to write an iterative function.
// dhu: root may be created, so it is passed in as Node*&.
void insert_node(Node*& root, int v) {
  if (!root) {
    root = new Node(v);
    return;
  }

  if (root->dat > v) 
    insert_node(root->left, v);
  else 
    insert_node(root->right, v);    
}       

// hackie: wrapper
Node* hackie(const vector<vector<int> >& values) {       
  Node* root = 0;
  // dhu: each node is inserted from root, total time is O(NlgN), 
  // may not be efficient enough.
  for (size_t i = 0; i < values.size(); i++) {
    const vector<int>& numbers = values[i];
    for (size_t j = 0; j < numbers.size(); j++) {
      insert_node(root, numbers[j]);
    }
  }

  return root;  
}

/* dhu implementation using a queue, run time complexity is O(N).
 * Initially the queue has only one range: { INT_MIN, INT_MAX, NULL }.
 * When root node is built, the matching range will be dequeued,
 * then two new ranges will be enqueued. 
 * Suppose root node is 5, the two elements will be: 
 *
 * e1: { INT_MIN, 5, root, true } (it is left child of root) 
 * and:
 * e2: { 5, INT_MAX, root, false } (it is NOT right child of root)
 *
 * The next input value is 4, we start from the head of queue, find that 
 * e1 is the first range that covers 4, so we know that 4 will be 
 * the left child of root node (5); then we enqueue two more elements:
 *
 * e3: { INT_MIN, 4, node4 } and:
 * e4: {       4, 5, node4 }
 *
 * Now we can also dequeue e1 out of the queue, because it won't bee needed 
 * any more. 
 * Then check the next input value 8, which is covered by e2... 
 * Repeat this process until all input values have been scanned.
 */

// Data structure of Range
struct Range {
  // Ctor
  //Range(int min_in, int max_in, Node* p_in, bool l_flag) : 
  //  min(min_in), max(max_in), parent(p_in), left(l_flag) { }

  Range(int min_in, int max_in, Node* p_in) 
    : min(min_in), max(max_in), parent(p_in) { }

  // Is x covered by Range?
  bool cover(int x) const { return x > min && x < max; }

  int min, max; // valid interval that the current queue element will cover.
  Node* parent; // parent node in previous level.
  //bool left;
};

/* dhu algorithm #1: input integers are vector of vectors, ordered by level.
 * In each level, the number is ranked from left to right. */
Node* dhu(const vector<vector<int> >& values) {
  Node* root = 0;
  deque<Range> ranges;
  ranges.push_back(Range(INT_MIN, INT_MAX, NULL));
  for (size_t i = 0; i < values.size(); i++) {
    for (size_t j = 0; j < values[i].size(); j++) {
      int val = values[i][j];
      Range curr_range = ranges.front();
      while (!curr_range.cover(val)) {
	ranges.pop_front();
	curr_range = ranges.front();
      }
      ranges.pop_front();
      Node* tmp = new Node(val);
      if (!curr_range.parent)
	root = tmp;
      else if (val < curr_range.parent->dat)
	curr_range.parent->left = tmp;
      else
	curr_range.parent->right = tmp;

      ranges.push_back(Range(curr_range.min, val, tmp));
      ranges.push_back(Range(val, curr_range.max, tmp));
    }
  }

  return root;
}
 
/* dhu algorithm #2: input integers are in one vector, ordered by level, 
 * and in each level, the numbers are ordered from left to right. */
Node* dhu(const vector<int>& values) {
  Node* root = 0;
  deque<Range> ranges;
  ranges.push_back(Range(INT_MIN, INT_MAX, NULL));
  for (size_t i = 0; i < values.size(); i++) {
    int val = values[i];
    Range curr_range = ranges.front();
    while (!curr_range.cover(val)) {
      ranges.pop_front();
      curr_range = ranges.front();
    }
    ranges.pop_front();
    Node* tmp = new Node(val);
    if (!curr_range.parent)
      root = tmp;
    else if (val < curr_range.parent->dat)
      curr_range.parent->left = tmp;
    else
      curr_range.parent->right = tmp;
    
    ranges.push_back(Range(curr_range.min, val, tmp));
    ranges.push_back(Range(val, curr_range.max, tmp));
  }

  return root;
}

/* An alternative question is: how can we construct the tree 
 * given its in-order and by-level traversals (assume that the
 * input values are all distinct). 
 * The solution is more complex. Every time we build a new node, 
 * we have to search that value in in-order traversal and mark it.
 * When searching the in-order array and mark that element,
 * we do not search the whole array. Instead, we memorize the boundary
 * of its parent index, and search the current node either from left 
 * to right (for right child), or from right to left (for left child).
 * So on average, each search will cost O(n/2), and the total run time 
 * complexity is O(nlgn). In the worst case (when the binary tree has 
 * only one branch like a linked list), it will be O(n^2).
 *
 * The program can be simplified by searching the whole in-order list 
 * for the element, but that will cost O(n).
 */

/* Data structure that memorizes parent node, an index which is the search 
 * boundary in in-order array, and a flag that tells whether search should 
 * be from left to right, or from right to left. */
struct NodeInfo {
  NodeInfo(Node* p_in, size_t i, bool b_in) {
    p = p_in;
    idx = i;
    isMaxIdx = b_in;
  }

  Node* p;
  size_t idx;
  bool isMaxIdx;
};

/* Helper function that returns index of the input node in in-order vector. */
size_t search_in_order(const vector<int>& in_order, const NodeInfo& node) {
  size_t idx = node.idx;
  int x = node.p->dat;
  if (node.isMaxIdx) {
    for (int i = idx - 1; i >= 0; i--) {
      if (in_order[i] == x)
	return i;
    }
  }
  else {
    for (size_t i = idx + 1; i < in_order.size(); i++) {
      if (in_order[i] == x)
	return i;
    }
  }

  // The program should never reach here!
  return 0;
}

// Algorithm function
Node* dhu3(const vector<int>& in_order, const vector<int>& by_level) {
  if (in_order.size() == 0)
    return 0;

  vector<bool> visited(in_order.size(), false);
  Node* root = new Node(by_level[0]);
  NodeInfo ni(root, 0, false);
  deque<NodeInfo> prev_nodes;
  prev_nodes.push_back(ni);

  Node* parent = root;
  size_t in_order_idx = search_in_order(in_order, ni);
  visited[in_order_idx] = true;
  size_t by_level_idx = 1;
  while (by_level_idx < by_level.size()) {
    int val = by_level[by_level_idx];
    /* If the left neighbor of parent node value in in-order traversal
     * exists and has not been visited yet, val must be parent's left child. */
    if (in_order_idx > 0 && visited[in_order_idx - 1] == false) {
      Node* tmp = new Node(val);
      parent->left = tmp;
      prev_nodes.push_back(NodeInfo(tmp, in_order_idx, true));
      by_level_idx++;
    }

    val = by_level[by_level_idx];
    /* If the right neighbor of parent node value in in-order traversal
     * exists and has not been visited yet, val must be parent's right child. */
    if (in_order_idx + 1 < by_level.size() && visited[in_order_idx + 1] == false) {
      Node* tmp = new Node(val);
      parent->right = tmp;
      prev_nodes.push_back(NodeInfo(tmp, in_order_idx, false));
      by_level_idx++;
    }

    prev_nodes.pop_front();
    parent = prev_nodes.front().p;
    in_order_idx = search_in_order(in_order, prev_nodes.front());
    visited[in_order_idx] = true;
  }

  return root;
}

// Helper function: in-order traversal of bninary tree
void in_order(const Node* root) {
  if (!root)
    return;

  in_order(root->left);
  cout << root->dat << " ";
  in_order(root->right);
}

// Helper function: traverse binary tree by level
void by_level(Node* root) {
  deque<Node*> queue;
  queue.push_back(root);
  while (queue.size()) {
    Node* curr = queue.front();
    cout << curr->dat << " ";
    if (curr->left)
      queue.push_back(curr->left);
    if (curr->right)
      queue.push_back(curr->right);
    queue.pop_front();
  }
}

// Test harness
int main() {
  
  // Test input vector of vector
  vector<vector<int> > values(4);
  values[0].push_back(5);

  values[1].push_back(4);
  values[1].push_back(8);

  values[2].push_back(2);
  values[2].push_back(7);
  values[2].push_back(9);

  values[3].push_back(3);
  values[3].push_back(10);
  

  /*
  // Test hackie solution
  Node* root = hackie(values);
  print(root->left->left); 
  print(root->left->right);
  */

  
  /*
  // Test one input array
  int a[] = { 5, 4, 8, 2, 7, 9, 3, 10 };
  vector<int> values(a, a + sizeof(a) / sizeof(int));
  */

  Node* root = dhu(values);
  in_order(root);
  cout << endl;
  by_level(root);
  cout << endl;
  

  /*
  // Test by level and in-order
  int a1[] = { 1, 2, 3, 4, 5, 6, 7, 8 }; 
  vector<int> v_by_level(a1, a1 + sizeof(a1) / sizeof(int));

  int a2[] = { 4, 7, 2, 1, 5, 3, 8, 6 };
  vector<int> v_in_order(a2, a2 + sizeof(a2) / sizeof(int));

  Node* root = dhu3(v_in_order, v_by_level);
  cout << "In order: " << endl;
  in_order(root);
  cout << endl;

  cout << "By level: " << endl;
  by_level(root);
  cout << endl;
  */
}

  
