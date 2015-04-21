/* Divide a string that consists of digits into groups. Each group includes 2 or 3 chars.
 * If a group has identical chars, its socre is 2; if a group has 3 chars and any two of them
 * are identical, its score is 1; otherwise the score is 0. How to maximize the score?
 * Refer to:
 * http://www.mitbbs.com/article_t/JobHunting/32078073.html
 */

// Java code copied from peking2 (not checked yet)
import java.io.*;
import java.util.*;

public class test
{

    public static void main(String[] args)
  {
    new test().run();
  }

  PrintWriter out = null;

  int score(String str, int start, int len)
  {
    if (len == 2)
      {
	if (str.charAt(start) == str.charAt(start + 1))
	  return 2;
      }
    else if (len == 3)
      {
	char[] a = str.substring(start, start + 3).toCharArray();
	if (a[0] == a[1] && a[1] == a[2])
	  return 2;
	else if (a[0] == a[1] || a[0] == a[2] || a[1] == a[2])
	  return 1;
      }
    return 0;
  }

  void run()
  {
    Scanner in = new Scanner(System.in);
    out = new PrintWriter(System.out);

    String str = in.next();

    int n = str.length();
    int[] dp = new int[3];

    for (int i = 2; i <= n; i++)
      {
	int max = 0;
	if (i >= 3 && i - 3 != 1)
	  max = Math.max(max, score(str, n - i, 3) + dp[(i - 3) % 3]);

	if (i >= 2 && i - 2 != 1)
	  max = Math.max(max, score(str, n - i, 2) + dp[(i - 2) % 3]);

	dp[i % 3] = max;
      }

    out.println(dp[n % 3]);
    out.close();
  }
}

// longway2008
int bestGrouping(char c[], int n) {
   if (n < 2) 
      return 0;

   if (n < 4)
      return groupScore(c, n);

   int * scores = new int[n];
   a[0] = 0; 
   a[1] = groupScore(c, 2)
   a[2] = groupScore(c, 3)
   a[3] = groupScore(c, 2) + groupScore(c + 2, 2); 

   for (int i = 4; i < n; i++) {
     a[i] = groupScore(c + i - 2, 3) + a[i-3];
     a[i] = max(a[i], groupScore(c + i - 1, 2) + a[i-2]);
   }   

   int result = scores[n-1];
   delete [] scores;
   return result;
} 
// longway2008
int groupScore(char c[], int n) {
  if (n < 2 || n > 3)
    return 0;
  
  if (n == 2) {
    if (c[0] == c[1])
      return 2;
     
    return 0;
  }

  if (n == 3) {
    int score = (c[0] == c[1]);
    score += (c[1] == c[2]);
    score += (c[0] == c[2]);

    if (score >= 2)
      score = 2;
    
    return score;         
  }
}
