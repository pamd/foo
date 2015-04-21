/* Given the order of a tree (the maximum number of children a node can have),
 * and pre-order and post-order traversal strings, how many uniques can be 
 * constructed?
 * Copied from a problem in ACM 2002.
 */

#include <iostream>
#include <string>

using namespace std;

/* order: maximum number of child that a parent node can have;
 * pre_order: input preorder traversal string;
 * post_order: input post-order traversal string. */
long count(int order, string pre_order, string post_order) {
  /* Make sure the first char in pre_order is equal to 
   * the last char in post_order. If not, return 0. */
  if (pre_order.substr(0, 1) != post_order.substr(post_order.length() - 1, 1))
    return 0;

  // Return 1 if pre_order has only one char.
  if (pre_order.length() == 1)
    return 1;

  // Remove the first char in pre_order string
  pre_order = pre_order.substr(1, pre_order.length());

  // Remove the last char in post_order string
  post_order = post_order.substr(0, post_order.length() - 1);

  long answer = 1;
  int num_child = 0;
  long combination = 1;
  while (pre_order.length() > 0) {
    num_child++;
    // cout << "num_child: " << num_child << endl;

    int index = post_order.find(pre_order[0]);
    /* Make sure the first char in pre_order is available in post_order.
     * If not, return 0. (This should never happen.) */
    if (index == -1) 
      return 0;

    // Preorder string that will be used for next recursion.
    string new_pre_order = pre_order.substr(0, index + 1);
    // Preorder string that will be used for next iteration in current "while" loop
    pre_order = pre_order.substr(index + 1, pre_order.length());

    // Postorder string that will be used for next recursion.
    string new_post_order = post_order.substr(0, index + 1);
    // Postorder string that will be used for next iteration in current "while" loop
    post_order = post_order.substr(index + 1, post_order.length());

    // Recursive calculation
    answer *= count(order, new_pre_order, new_post_order);

    // This should never happen.
    if (answer == 0)
      return 0;

    /* Suppose the number of iterations in current "while" loop is k, 
     * at the end of loop, the following line calculates the value of 
     * C(order, k), aka, the number of choices to select k children
     * out of all children (whose value is "order"). This calculation
     * is necessary because in first iteration, the program actually 
     * assigns new_pre_order and new_post_order as the left-most possible
     * child of root node. We have "order" choices in this iteration. 
     * In second iteration, the new_pre_order and new_post_order have to
     * be put on the right side of nodes that we have put in first iteration,
     * and so on. So the total number of possible assignments is C(order, k).  
     */
    combination *= (order - num_child + 1) / num_child;
  }

  return answer * combination;
}

// Test harness
int main() {
  string pre_order("abc");
  string post_order("cba");
  int m = 2;
  cout << count(m, pre_order, post_order) << endl;

  /*
  cin >> m;
  while (m != 0) {
    cin >> pre_order >> post_order;
    if (pre_order.length() != post_order.length())
      cout << 0 << endl;
    else
      cout << count(m, pre_order, post_order) << endl;
    cin >> m;
  }
  */

}
