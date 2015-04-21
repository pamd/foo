/* Test code that converts skip list to BST and vice versa.
 * We can always convert a binary search tree into skip list, but if a skip list 
 * has links between node that have same number of links, then it can only be converted 
 * into a 2-3-4 tree, in which the nodes that have same number of links and are linked 
 * will be put in one node. 
 * Note that the first node in skip list is a dummy node that has same number of links as 
 * the node that has maximum number of links.

 * Algorithms in C++ page 582: To build the skip list corresponding to a tree, 
 * we give each node a number of links equal to its height in the tree, and then 
 * link the nodes horizontally. To build the tree corresponding to a skip list, 
 * we group skipped nodes, and recursively link them to nodes at the next level.
 *
 * dhu notes: 
 * From skip list to binary search tree (suppose the skip list can be converted into 
 * a valid BST): the first node that dummy head node links to is the root. The left child
 * of root can be built recursively by the partial skip list from dummy head node to the 
 * root (exclusive), the right child of root can be built recursively by the partial skip 
 * list from root (exclusive) to the end. 
 *
 * To build skip list based from a balanced binary search tree, we first do 
 * in-order traversal of the tree, create skip list nodes during traversal and
 * put them into a vector (or array). The number of links in each node of skip list 
 * is equal to the height of each binary tree node. We then create the dummy head node 
 * in skip list, then scan the vector and connect the nodes horirontally. 
 *
 * --------------------------------------------------------------------------
 * The following code has NOT been tested yet. So it is more like pseudocode.
 * --------------------------------------------------------------------------
 */

// Skip list node, based on Program 13.8 on "Algorithms in C++" page 578.
struct SL_Node {
  // Ctor
  SL_Node(int v, int link_sz = 0) {
    dat = v;
    sz = 0;
    setSize(link_sz);
  }
 
  // Set # of links in the node
  void setSize(int link_sz) {
    if (link_sz < = 0)
      return;

    sz = link_sz;
    links = new SL_Node*[link_sz];
    for (int i = 0; i < sz; i++)
      links[i] = 0;
  }

  int dat;
  SL_Node** links;
  int sz; // Number of links
};

// Skip list, based on Program 13.8 on "Algorithms in C++" page 578.
struct SkipList {
  SL_Node* head;  // dummy head node

  /* maximum number of links in each node, the node that 
   * connects the dummy head and root node will be head[max_links - 1]. */
  int max_links;  
  // ...
};

// Binary search tree node
struct BST_Node {
  BST_Node(int v) { dat = v; left = right = 0; }

  int dat;
  BST_Node* left;
  BST_Node* right;
};

/* Build binary search tree starting from start-node.
 * We do not need the end node because the level parameter 
 * can detect when we have reached the ending point. 
 * Code NOT tested yet. */
BST_Node* sl2bst_helper(SL_Node* start_node, int level) 
{
  if (level < 0 || !start_node)
    return 0;

  SL_Node* current = start_node->links[level];
  if (!current)
    return 0;

  BST_Node* root = new BST_Node(current->dat);
  root->left = sl2bst(start_node, level - 1); 
  root->right = sl2bst(current, level - 1);

  return root;
}

// Wrapper function 
BST_Node* sl2bst(const SkipList& list)
{
  return sl2bst_helper(list.head, list.max_links - 1);
}

/* Functions to build skip list based from a balanced binary search tree. 
 * (NOT test yet)
 */

/* Traverse binary search tree, create skip list nodes and put them 
 * into a vector. (NOT tested yet.)
 */
int traverse(BST_Node* root, vector<SL_Node>& nodes) 
{
  if (!root)
    return 0;

  int left = traverse(root->left, nodes);
  SL_Node* tmp = new SL_Node(root->dat);
  nodes.push_back(tmp);
  size_t idx = nodes.size() - 1;
  int right = traverse(root->right, nodes);
  int ret = 1 + max(left, right);
  nodes[idx]->setSize(ret);

  return ret;
}

// Build skip list from binary search tree (NOT tested yet)
SkipList* bst2sl(BST_Node* root)
{
  if (!root)
    return 0;

  vector<SL_Node*> nodes;
  traverse(root, nodes);
  // Get the maximum number of links in nodes
  int max_links = 0;
  for (size_t i = 0; i < nodes.size(); i++) {
    if (max_links < nodes[i]->sz)
      max_links = nodes[i]->sz;
  }

  SkipList* ret = new SkipList;
  // The dummy head node should have same number of links as the maximum height
  ret->head = new SL_Node(INT_MIN, max_links);
  ret->max_links = max_links;

  /* Now scan each node in nodes vector. If the number of links in a node
   * is equal to or less than the previous node, connect the two nodes together.
   * This takes O(max_links * N) time. Not sure whether it can be faster.
   */
  for (int i = max_links; i > 0; i--) {
    SL_Node* current = ret->head;
    for (size_t j = 0; j < nodes.size(); j++) {
      if (nodes[j]->sz >= i) {
	current->links[i - 1] = nodes[j];
	current = nodes[j];
      }
    }
  }

  return ret;
}

