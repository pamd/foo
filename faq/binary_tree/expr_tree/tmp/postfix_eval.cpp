/* Given a postfix expression, calculate the result.
 * This problem is easy to solve by stacks. See "Algorithms in C++" book.
 * The following solution does not use explicit stack, refer to:
 * http://www.mitbbs.com/article_t/JobHunting/32113255.html
 */

/* Original Java code 
   static class IntWrapper {
   public int val;
   public IntWrapper(int val) {
   this.val = val;
   }
   }
   static double rpn(List<String> ops) {
   if (ops == null || ops.size() == 0) {
   throw new IllegalArgumentException();
   }
        
   IntWrapper idx = new IntWrapper(ops.size() - 1);
   return rpnInternal(ops, idx);
   }
   static boolean isOperator(String s) {
   return s.equals("+") || s.equals("-") || s.equals("*") || s.equals("/");
   }
   static double calculate(double op1, double op2, String operator) {
   if (operator == null || operator.length() != 1) {
   throw new IllegalArgumentException();
   }
   switch (operator.charAt(0)) {
   case '+':
   return op1 + op2;
   case '-':
   return op1 - op2;
   case '*':
   return op1 * op2;
   case '/':
   return op1 / op2;
   default:
   throw new IllegalArgumentException();
   }
   }
   static double rpnInternal(List<String> ops, IntWrapper idx) {
   if (idx.val < 0) {
   throw new IllegalStateException();
   }
        
   if (isOperator(ops.get(idx.val))) {
   String operator = ops.get(idx.val);
   idx.val --;
   double op2 = rpnInternal(ops, idx);
   double op1 = rpnInternal(ops, idx);
   return calculate(op1, op2, operator);
   } else {
   double ret = Double.parseDouble(ops.get(idx.val));
   idx.val --;
   return ret;
   }
   }
    
   static void testRpn() {
   List<String> ops = Arrays.asList("4", "1", "+", "2", "*");
   System.out.println(rpn(ops));
        
   ops = Arrays.asList("2", "4", "1", "+", "*");
   System.out.println(rpn(ops));
        
   // (3/4 + 1) * 8 = 14
   // 3 4 / 1 + 8 *
   ops = Arrays.asList("3", "4", "/", "1", "+", "8", "*");
   System.out.println(rpn(ops));
   }

*/

// dhu C++ code
struct IntWrapper {
  IntWrapper(int i) { val = i; }

  int val;
};

// rpn: Reverse Poland Notation
double rpn(List<String> ops) {
  if (ops == null || ops.size() == 0) {
    throw Exception("Invalid input");
  }
        
  IntWrapper idx(ops.size() - 1);
  return rpnInternal(ops, idx);
}

bool isOperator(const string& s) {
  return s == "+" || s == "-" || s == "*" || s == "/";
}

double calculate(double op1, double op2, char operator_in) {
  switch (operator_in) {
  case '+':
    return op1 + op2;
  case '-':
    return op1 - op2;
  case '*':
    return op1 * op2;
  case '/':
    return op1 / op2;
  }
}

double rpnInternal(const string& expr, size_t idx) {
  if (isOperator(expr[idx])) {
    String operator = ops.get(idx.val);
    idx.val --;
    double op2 = rpnInternal(ops, idx);
    double op1 = rpnInternal(ops, idx);
    return calculate(op1, op2, operator);
  } 
  else {
    double ret = Double.parseDouble(ops.get(idx.val));
    idx.val--;
    return ret;
  }
}
    
static void testRpn() {
  List<String> ops = Arrays.asList("4", "1", "+", "2", "*");
  System.out.println(rpn(ops));
        
  ops = Arrays.asList("2", "4", "1", "+", "*");
  System.out.println(rpn(ops));
        
  // (3/4 + 1) * 8 = 14
  // 3 4 / 1 + 8 *
  ops = Arrays.asList("3", "4", "/", "1", "+", "8", "*");
  System.out.println(rpn(ops));
}

