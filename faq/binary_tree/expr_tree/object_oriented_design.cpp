/* Object oriented design of Expression tree, based on GoogleTechTalk on Youtube.
 * Node::in_order2() is written to print out the expression without 
 * redundant "()" pairs. See the following link on discussions of in_order2():
 * http://www.mitbbs.com/article_t/JobHunting/32091379.html
 */

#include <iostream>

using namespace std;

// Pure abstract class for generic node
struct Node {
  virtual ~Node() { }

  // Return the char value of node
  virtual char id() const = 0;

  // Return the numeric value of the (sub)tree that is rooted at current node
  virtual int eval() const = 0;

  // In-order traversal that prints out all "()".
  virtual void in_order() const = 0;

  // In-order traversal that only prints out "()" that are necessary.
  virtual void in_order2(const Node* parent) const = 0;
  
};

// Concrete class defined for leaf node (operand, aka. numeric value)
struct LeafNode : public Node {
  int dat;

  LeafNode(int i) { dat = i; }

  char id() const { return dat; }

  int eval() const {
    return dat;
  }

  void in_order() const {
    cout << dat;
  }

  void in_order2(const Node*) const {
    cout << dat;
  }

};

// Derived pure abstract class for operator node
struct OperatorNode : public Node {
  Node* left;
  Node* right;

  // "Tempalte method" design pattern
  void in_order() const {
    cout << "(";
    left->in_order();
    cout << " " << id() << " " ;
    right->in_order();
    cout << ")";
  }

  // "Tempalte method" design pattern again
  void in_order2(const Node* parent) const {
    if (!parent) {
      left->in_order2(this);
      cout << " " << id() << " " ;
      right->in_order2(this);
      return;
    }

    char pid = parent->id();
    bool flag = needParentheses(pid);
    if (flag)
      cout << "(";

    left->in_order2(this);
    cout << " " << id() << " " ;
    right->in_order2(this);

    if (flag)
      cout << ")";
  }

  /* Pure virtual function: when previous operator is pid, 
   * does this operator need "()"? */
  virtual bool needParentheses(char pid) const = 0;
};

// "+" operator
struct Plus : public OperatorNode {
  char id() const { return '+'; }

  int eval() const {
    return left->eval() + right->eval();
  }

  bool needParentheses(char p) const {
    if (p == '*' || p == '/' || p == '-')
      return true;
    return false;
  }

};

// "-" operator
struct Minus : public OperatorNode {
  char id() const { return '-'; }

  int eval() const {
    return left->eval() - right->eval();
  }

  bool needParentheses(char p) const {
    if (p == '*' || p == '/' || p == '-')
      return true;
    return false;
  }

};

// "*" operator
struct Multiply : public OperatorNode {
  char id() const { return '*'; }

  int eval() const {
    return left->eval() * right->eval();
  }

  bool needParentheses(char p) const {
    if (p == '/')
      return true;
    return false;
  }

};

// "/" operator
struct Divide : public OperatorNode {
  char id() const { return '/'; }

  int eval() const {
    return left->eval() / right->eval();
  }

  bool needParentheses(char p) {
    if (p == '/')
      return true;
    return false;
  }

};

// Wrapper of Node::in_order()
void in_order(const Node* root) 
{
  root->in_order();
  cout << endl;
}

// Wrapper of Node::in_order2()
void in_order2(const Node* root) 
{
  root->in_order2(NULL);
  cout << endl;
}


// Test harness
int main()
{
  // (1+ (2*3) ) + (4*5)
  Plus* plus1 = new Plus;
  Plus* plus2 = new Plus;
  Multiply* mult1 = new Multiply;
  Multiply* mult2 = new Multiply;

  LeafNode* leaf1 = new LeafNode(1);
  LeafNode* leaf2 = new LeafNode(2);
  LeafNode* leaf3 = new LeafNode(3);
  LeafNode* leaf4 = new LeafNode(4);
  LeafNode* leaf5 = new LeafNode(5);

  plus1->left = plus2;
  plus1->right = mult1;

  plus2->left = leaf1;
  plus2->right = mult2;

  mult2->left = leaf2;
  mult2->right = leaf3;

  mult1->left = leaf4;
  mult1->right = leaf5;

  in_order(plus1);
  in_order2(plus1);
  cout << "result: " << plus1->eval() << endl;
  
  /*
  // 3 - (5 - 4)
  Minus* minus1 = new Minus;
  Minus* minus2 = new Minus;
  LeafNode* leaf3 = new LeafNode(3);
  LeafNode* leaf4 = new LeafNode(4);
  LeafNode* leaf5 = new LeafNode(5);
  minus1->left = leaf3;
  minus1->right = minus2;
  minus2->left = leaf5;
  minus2->right = leaf4;

  in_order(minus1);
  in_order2(minus1);
  cout << "result: " << minus1->eval() << endl;
  */

  return 0;
}
  
