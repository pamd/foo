/* This program reads an input expression string that includes 
 * numbers, operators (+, -, *, /) and valid parentheses, then
 * remove the redundant parentheses based on operator priorities. 
 * For example, "1 + (2 * 3)" will be changed into: 1 + 2 * 3 
 *
 * An intuitive approach is to convert the expression first to 
 * expression tree, then do a modified in-order traversal to remove 
 * the unnecessary (). Note that unless each operation is enclosed by 
 * (), the conversion from expression string to expression tree is not 
 * unique. But any valid conversion will be good enough to remove the 
 * redundant (). See Node::in_order2() in expression_tree_design.cpp.
 *
 * Instead of building the expression tree, the algorithm in this program 
 * uses two stacks. One keeps track of the positions of '(' chars, the other
 * keeps track of operator characters. We then scan the input string from 
 * the very beginning. If the current char is '(', push it into the first stack;
 * if the current char is an operator, push it into the second stack;
 * if the current char is ')', then we have met one () block. To determine
 * whether this () pair is necessary or not, we try to find the previous and
 * next operator in the outer layer () block. If the operator that is closest 
 * to the current () pair has higher priority, we will have to keep the current
 * () pair. If it is redundant, we record indexes of '(' and ')', then pop the 
 * top elements in both stacks.
 *
 * When the scan is done, we have to sort the vector that records redundant 
 * () indexes, because when adding the indexes of '(', the indexes may not be 
 * in acending order. 
 * For example: (1+(2*3)), the vector of redundant () indexes will be: { 3, 7, 0, 8}.
 * 
 * Then we compare input string and the vector, and print out the necessary () pairs 
 * with all the other characters in the expression.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/* Get the operator that is before current '(', whose index is idx.
 * If currnet '(' is the leading char, or the char 
 * before current '(' is another '(', return 0.
 */
char getPrevOpr(const string& str, size_t idx)
{
  if (idx == 0 || str[idx - 1] == '(')
    return 0;

  return str[idx - 1];
}

/* Get the operator that is after current ')', whose index is idx. 
 * If currnet ')' is the ending char, or the char 
 * after current ')' is another ')', return 0.
 */
char getNextOpr(const string& str, size_t idx)
{
  if (idx == str.size() - 1 || str[idx + 1] == ')')
    return 0;

  return str[idx + 1];
}

// Remove redundant parenthes
void rmRedundant(const string& str)
{
  // Use vector to simulate the stack that keeps track of index of each '(' 
  vector<size_t> left_stack;
  // Another stack that keeps track of operator that have been read so far
  vector<char> operators;  
  // Indexes of '(' and ')' that are redundant due to operator priority
  vector<size_t> redundant;
  //char curr_op;
  for (size_t i = 0; i < str.size(); i++) {
    if (str[i] == '(') 
      left_stack.push_back(i);
    else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
      operators.push_back(str[i]);
    else if (str[i] == ')') {
      char curr_op = operators.back();
      char prev_op = getPrevOpr(str, left_stack.back());
      char next_op = getNextOpr(str, i);
      if (prev_op == 0 && next_op == 0) {
	redundant.push_back(left_stack.back());
	redundant.push_back(i);
      }
      else if ((prev_op == '+' && curr_op == '+') || // a+(b+c) 
	       (prev_op == '+' && curr_op == '-') || // a+(b-c)
	       (prev_op == '+' && curr_op == '*') || // a+(b*c)
	       (prev_op == '+' && curr_op == '/') || // a+(b/c)
	       (prev_op == '-' && curr_op == '*') || // a-(b*c)
	       (prev_op == '-' && curr_op == '/') || // a-(b/c)
	       (prev_op == '*' && curr_op == '*') || // a*(b*c)
	       (prev_op == '*' && curr_op == '/')) { // a*(b/c)
	redundant.push_back(left_stack.back());
	redundant.push_back(i);
      }
      else if (prev_op == 0) {
	if ((curr_op == '+' && next_op == '+') || // (b+c)+d
	    (curr_op == '+' && next_op == '-') || // (b+c)-d
	    (curr_op == '-' && next_op == '+') || // (b-c)+d
	    (curr_op == '-' && next_op == '-') || // (b-c)-d
	    curr_op == '*' || curr_op == '/') {   // (b*c)/d
	  redundant.push_back(left_stack.back());
	  redundant.push_back(i);

	}
      }
      left_stack.pop_back();
      operators.pop_back();	
    }
  }

  if (redundant.size() == 0) {
    cout << str << endl;
    return;
  }

  sort(redundant.begin(), redundant.end());
  size_t p = 0;
  for (size_t i = 0; i < str.size(); i++) {
    if (i == redundant[p]) {
      p++;
      continue;
    }
    cout << str[i];
  }
  cout << endl;
}

// Java code by yishan, refer to:
// http://www.mitbbs.com/article_t/JobHunting/32089951.html
/*
public class BracketInfo
    {
        public char OperatorBefore = '\0'; // Low-Pri
        public char OperatorInner = '$'; // Hi-Pri
        public char OperatorAfter = '\0'; // Low-Pri
        public int BracketStart = -1;
        public int BracketEnd = -1;
    }

    public class BracketChecker
    {
        private Dictionary<char, int> operatorPriority = null;
        public Dictionary<char, int> OperatorPriority
        {
            get
            {
                if (this.operatorPriority == null)
                {
                    // Init operator priorites
                    this.operatorPriority = new Dictionary<char, int>();
                    this.operatorPriority['$'] = 8;
                    this.operatorPriority['/'] = 4;
                    this.operatorPriority['*'] = 4;
                    this.operatorPriority['-'] = 2;
                    this.operatorPriority['+'] = 2;
                    this.operatorPriority['\0'] = 0;
                }

                return this.operatorPriority;
            }
        }

        public bool IsRemovable(BracketInfo bracket)
        {
            int beforePriority = this.OperatorPriority[bracket.
OperatorBefore];
            if ((bracket.OperatorBefore == '/') || (bracket.OperatorBefore =
= '-'))
                beforePriority++;

            // Compare inner operator with before and end operators
            if ((this.OperatorPriority[bracket.OperatorInner] >= this.
OperatorPriority[bracket.OperatorAfter])
                && (this.OperatorPriority[bracket.OperatorInner] >= 
beforePriority))
                return true;
            else
                return false;
        }

        public string RemoveBrackets(string expression)
        {
            char[] buffer = expression.ToCharArray();
            List<BracketInfo> brackets = new List<BracketInfo>();
            int bracketDepth = 0;
            char lastOperator = '\0';

            for (int i = 0; i < buffer.Length; i++)
            {
                char ch = buffer[i];
                switch (ch)
                {
                    case '(':
                        brackets.Add(new BracketInfo());
                        bracketDepth++;
                        brackets[bracketDepth - 1].OperatorBefore = 
lastOperator;
                        brackets[bracketDepth - 1].BracketStart = i;
                        lastOperator = '\0';
                        break;
                    case ')':
                        brackets[bracketDepth - 1].BracketEnd = i;
                        bracketDepth--;
                        break;
                    case '+':
                    case '-':
                    case '*':
                    case '/':
                        lastOperator = ch;

                        // Update inner operator if in a bracket
                        if ((bracketDepth > 0) 
                            && (this.OperatorPriority[brackets[bracketDepth 
- 1].OperatorInner] > this.OperatorPriority[ch]))
                            brackets[bracketDepth - 1].OperatorInner = ch;

                        if (bracketDepth < brackets.Count)
                        {
                            // Check finished bracket
                            BracketInfo bracket = brackets[bracketDepth];
                            bracket.OperatorAfter = ch;
                            if (this.IsRemovable(bracket))
                            {
                                buffer[bracket.BracketStart] = ' ';
                                buffer[bracket.BracketEnd] = ' ';
                                brackets.RemoveAt(bracketDepth);
                            }
                        }
                        break;
                }
            }

            if (bracketDepth < brackets.Count)
            {
                BracketInfo bracket = brackets[bracketDepth];
                if (this.IsRemovable(bracket))
                {
                    buffer[bracket.BracketStart] = ' ';
                    buffer[bracket.BracketEnd] = ' ';
                    brackets.RemoveAt(bracketDepth);
                }
            }

            return new String(buffer);
        }

    }
*/




int main(int argc, char** argv) {
  if (argc != 2) {
    cout << "Input string needed" << endl;
    return 0;
  }

  string expr = argv[1];
  rmRedundant(expr);
}
