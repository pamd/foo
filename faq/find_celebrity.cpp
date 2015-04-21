/* Find a celebrity who knows nobody but everybody else knows him. 
 * http://www.mitbbs.com/article_t/JobHunting/32090725.html
 * http://stackoverflow.com/questions/8704829/find-the-best-element-from-the-given-list
 */

/* Code from longway2008. know is a bool matrix that tells whether person[row] 
 * knows person[col] or not.
 * This approch is not correct. Suppose person #0 knows person #1, and person #1 
 * knows only person #0, this approach will return person #1 as celebrity. 
 * But actually in this case, the celebrity does not exist.
 * To fix thi problem, we need a second pass to confirm that the result is correct.  
 */
int FindCelibrity(bool ** know, int n) { 
  if (know == NULL || n<1) 
    return -1;

  int cel=0;
  for (int i=1; i<n; i++)
    if (know[cel][i])
      cel = i;

  // dhu: error, second pass is needed to confirm the result!
  return cel;
}
