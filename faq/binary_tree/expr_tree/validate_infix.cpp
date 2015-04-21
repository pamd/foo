/* Facebook: Write code to do arithmetic expression validation: 
 * digits: 0..9
 * operators: +, -, (, )
 * e.g.
 * 1+2-3: valid
 * 1+(2-(3+4)): valid
 * -2: not valid
 *
 * Ref:
 * http://www.mitbbs.com/article_t/JobHunting/32364859.html
 *
 * dhu: This is a variant of "infix evaluation", but it is simpler. 
 * We can certainly use the same idea of "infix evaluation" to solve this problem.
 * But since we do not care the value of any operations in input expression, we can
 * simply check whether "()" matches, and whether it is a numerical value when we expect
 * an operand. This is what the solution by redarm does.
 */

// Based on Java code by redarm
bool validate(const string& expression){
  string expr = expression.trim();
  bool expectNum = true;
  int numOfParentheses = 0;
  int i = 0;
  while (i < expr.length()){
    if (expr.at(i) == '('){
      if (!expectNum) 
	return false;
      numOfParentheses++;
      i++;
    } else if (expr.charAt(i) == ')'){
      if(expectNum || numOfParentheses < 1) return false;
      numOfParentheses--;
      i++;
    } else if(expectNum){
      if(!isDigit(expr.charAt(i))){
	return false;
      }
      i++;
      while (i < expr.length() && isDigit(expr.charAt(i))){
	i++;
      }
      expectNum = false;
    } else {
      
      if(!isOperator(expr.charAt(i))){
	return false;
      }
      
      i++;
      expectNum = true;
    }
  }

  return expectNum == false && numOfParentheses == 0;
}

boolean isDigit(char c){
  return c <= '9' && c >= '0';
}
    
boolean isOperator(char c){
  return c == '+' || c == '-' || c == '*' || c == '/';
}
