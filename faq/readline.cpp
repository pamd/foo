/* Facebook: Implement a function char* readLine() which returns single lines from a buffer. 
 * To read the buffer, you can make use of a function int read(char* buf, int len) which 
 * fills buf with upto len chars and returns the actual number of chars filled in. 
 * Function readLine can be called as many times as desired. If there is no valid data or 
 * newline terminated string available, it must block. In order to block, it can use read 
 * function which in turn will block whenit doesn't have anything to fill the buf.
 * Refer to: 
 * http://www.mitbbs.com/article_t/JobHunting/32042617.html
 * (see code from claxton)
 * http://www.mitbbs.com/article_t/JobHunting/32101029.html
 * (revisit)
 */

// Code by claxton
char* readLine() {
  static char[BUFSIZE] buf;
  static char* ptr = buf;
  static int bufSize = 0;
  int outputSize = 0;
  char *output = NULL;
   
  while (1) {
    int pos = getNewLinePos(ptr, bufSize);
    if (pos > 0){
      // found new line char in the buffer
      output = realloc(output, outputSize+pos+1); // one extra char for '\0'
      // TODO: check realloc return value
      memcpy (output + outputSize, ptr, pos);
      output[outputSize + pos]  = '\0';
      ptr += pos;
      bufsize -= pos;
      return output;
    }
    else { 
      // no new line char in the buffer, push all data in buffer
      // to the output and read from underneath buffer
      // TODO: check if bufSize == 0 (?) 
      output = realloc(output, outputSize + bufSize);
      memcpy(output+outputSize, ptr, bufSize);
      outputSize += bufSize;
      ptr = buf;
      bufSize = 0;
      bufSize = read(ptr, BUF_SIZE);
    }
  }
}

// Code by claxton
int getNewLinePos(char *p, int len) {
  int i = 0;
  while (i < len){
    if (*(p+i) == '\n')
      return (i+1);
    i++;
  }
  
  return 0;
}
