/* Convert an input prefix string into postfix string.
 * Refer to:
 * http://www.mitbbs.com/article_t/JobHunting/31982445.html
 *
 * The idea from darksteel is also used to convert postfix to prefix. 
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

// xieyi
string pre2post(string pre)
{
  string temp, tmp_pos;
  size_t i = 0;
  stack<string> ops;
  while (i < pre.size()) {
    temp = pre.substr(i, 1);
    // If current char is an operator, push it into the stack
    if (pre[i] =='-' || pre[i] =='+' || pre[i] =='*' || pre[i] =='/')     
      ops.push(temp);
    // If current char is an operand
    else {
      /* If the stack is not empty and its top element is NOT an operator,
       * merge the current number with the top two elements in the stack.*/
      while (!ops.empty() && !((tmp_pos = ops.top()).size() == 1 &&
			       (tmp_pos[0] == '-' || tmp_pos[0] == '+' ||
				tmp_pos[0] == '*' || tmp_pos[0] == '/'))) {
	string t = tmp_pos;
	ops.pop();
	t.append(temp);
	t.append(ops.top());
	ops.pop();
	temp = t;
      }  // end of inner while loop
      ops.push(temp);
    } // end of else

    i++;
  }

  /* At the end, the stack will have only one element, 
   * which is the postfix string. */
  if (!ops.empty())
    return ops.top();

  return "";
}

/*
int main()
{
    string pre1="-+1*23/-456";
    cout<<pre1<<endl;
    cout<<pre2post(pre1)<<endl;
    return 0;
}
*/

/*
output:
-+1*23/-456
123*+45-6/-
*/


// Rustywind: build expression tree first, then do post-order traversal
struct BNode {
  char c;
  BNode* left;
  BNode* right;
  BNode():c(0){}; //avoid uninitialized value for c
  BNode(char _c):c(_c),left(NULL),right(NULL){};
};

// Rustywind approch
void pre2bst_rusty(string pre, size_t& start, size_t len, BNode* &p) {
  if(start<len) {
    p=new BNode(pre[start]);
    size_t curr=start;
    start++;
    if(pre[curr]=='+'||pre[curr]=='-'||pre[curr]=='*'||pre[curr]=='/') {
      pre2bst_rusty(pre,start,len,p->left);
      pre2bst_rusty(pre,start,len,p->right);
    }
    else
      return;
  }
}

// Rustywind approch
void post_order_rusty(BNode* p) {
  if(!p)
    return;
  if(!p->c)//handle empty tree
    return;
  
  post_order_rusty(p->left);
  post_order_rusty(p->right);
  cout<<p->c;
}

// Rustywind approch
void pre2post_rusty(string pre) {
  size_t len=pre.size();
  BNode* bst= new BNode();
  size_t begin=0;
  pre2bst_rusty(pre, begin, len, bst);
  post_order_rusty(bst);
}

void test_pre2post() {
  string tst[]={"*+123", "++*321/23", ""};
  size_t len = sizeof(tst)/sizeof(tst[0]);
  for(size_t i=0; i<len;i++) {
    cout<<"preorder expression is: "<<tst[i]<<endl;
    cout<<"postorder expression is: ";
    pre2post_rusty(tst[i]);
    cout<<endl;
  }
}

// Code by darksteel, comments added by dhu
void pre2post_darksteel() {
  char c;
  // Read input until the next operand or operator
  while ((c = cin.get()) == ' ');
  
  // If an operator is found, recursively read left subtree 
  // and right subtree; do nothing for operand string.
  if(c < '0' || c > '9') {
    pre2post_darksteel(); 
    pre2post_darksteel();
  }
  // Print out the operand or operator
  cout << c;
}

/* dhu code, based on pre2post() by darksteel 
 * ------------------------------------------ 
 */
// Recursive helper function, which will be called by pre2post_dhu() 
void pre2post_dhu(const vector<string>& prefix, vector<string>& result, size_t& level) {
  if (level == prefix.size())
    return;

  string str = prefix[level];
  if (prefix[level] == "+" || prefix[level] == "-" ||
      prefix[level] == "*" || prefix[level] == "/") {
    pre2post_dhu(prefix, result, ++level);
    pre2post_dhu(prefix, result, ++level);
  }

  result.push_back(str);

}

// dhu wrapper function 
vector<string> pre2post_dhu(const vector<string>& prefix) {
  vector<string> result;
  size_t level = 0;
  pre2post_dhu(prefix, result, level);
  return result;
}

// Helper function that converts postfix to prefix
string post2pre_dhu(const string& str, int& level) {
  string ret;
  if (level < 0)
    return ret;

  char c = str[level];
  ret.push_back(c);
  if (c == '+' || c == '-' || c == '*' || c == '/') {
    string right = post2pre_dhu(str, --level);
    string left = post2pre_dhu(str, --level);
    ret += left + right;
  }
  return ret;
}

// Driver function that converts an input postfix string into prefix 
string post2pre(const string& str) {
  int level = str.size() - 1;
  return post2pre_dhu(str, level);
}

// dhu test harness
int main() {
  /*
  vector<string> prefix;
  prefix.push_back("+");
  prefix.push_back("+");
  prefix.push_back("*");
  prefix.push_back("3");
  prefix.push_back("2");
  prefix.push_back("1");
  prefix.push_back("/");
  prefix.push_back("2");
  prefix.push_back("3");

  vector<string> postfix = pre2post_dhu(prefix);  
  for (size_t i = 0; i < postfix.size(); i++) 
    cout << postfix[i] << " ";
  cout << endl;
  */

  //test_pre2post();

  string postfix("123*+45-6/-");
  cout << post2pre(postfix) << endl;

  return 0;  
}
