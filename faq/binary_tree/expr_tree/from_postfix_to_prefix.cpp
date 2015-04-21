/* Convert an input postfix string into prefix notation. 
 * The idea is similar to converting prefix to postfix. 
 * We can either scan left to right, or from right to left. 
 * We can either use an explicit stack, or use recursion. */

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

/* Use explicit stack, scan from left to right. */
string iteration(const string& postfix) {
  if (postfix.size() == 0)
    return string();

  stack<string> stk;
  for (size_t i = 0; i < postfix.size(); i++) {
    string tmp = postfix.substr(i, 1);
    if (tmp == "+" || tmp == "-" || tmp == "*" || tmp == "/") {
      string right = stk.top();
      stk.pop();
      string left = stk.top();
      stk.pop();
      stk.push(tmp + left + right);
    }
    else
      stk.push(tmp);
  }

  return stk.top();
}

/***********************************************************
 * Recursive solution: scan input string from right to left.
 ***********************************************************/

// Helper function that converts postfix to prefix
string recursion_helper(const string& str, int& level) {
  string ret;
  if (level < 0)
    return ret;

  char c = str[level];
  ret.push_back(c);
  if (c == '+' || c == '-' || c == '*' || c == '/') {
    string right = recursion_helper(str, --level);
    string left = recursion_helper(str, --level);
    ret += left + right;
  }

  return ret;
}

// Driver function that converts an input postfix string into prefix 
string recursion(const string& str) {
  int level = str.size() - 1;
  return recursion_helper(str, level);
}

/* Recursive solution: scan from left to right
 * http://www.daniweb.com/software-development/cpp/threads/178746/need-help-with-a-recursive-postfix-expression-evaluator
 */

//stringify just converts a int to string
inline string stringify(double x)
{
    ostringstream o;
    if (!(o << x))
        cout<<"Stringify::Bad Conversion";
    return o.str();
}
int postfix(string s)
{
    cout<<"New Postfix:"<<s<<endl; // for debug
    int a, b;
    if ( !isdigit(s[2]) && isdigit(s[0]))//check if the first three charactrs can be evaluated
    {
        //now if the length is greater than three, replace the first three with the value
        if (s.length() > 3 )
            return postfix(s.replace(0,3,stringify(postfix(s.substr(0,3)))));
        else if (s.length()==3)//elseif the length is 3
        {
            
            cout<<"Inside If:"<<endl; // for debug
            a = s[0]-48;
            b = s[1]-48;
            cout<<"eval "<<a<<" "<<s[2]<<" "<<b<<endl;
            switch (s[2])
            {
            case '+':
                return a + b;
            case '-':
                return a - b;
            case '*':
                return a * b;
            case '/':
                return a / b;
            default :
                cout<<"bad input\n";
            }
        }
        else //just a error check in case ;)
            cout<<"Too short to evaluate(min is 3)";
    }
    else
    {
        cout<<"theElsepart:"<<s.substr(1,3)<<endl;//ForDebugging
        //This needs explaination:
        //Lets say the the expression was "262/3*+"
        //Now, I am replacing the "62/" to its value by
        //calling postfix() again on "62/"
        return postfix(s.replace(1,3,stringify(postfix(s.substr(1,3)))));
    }
    return 0; // This return is for debug
}

/*
int main() {
    cout<<postfix("22/2+1+");
}
*/


// Test harness
int main() {
  string postfix("12-345/*+");
  string prefix = recursion(postfix);
  cout << prefix << endl;
}
