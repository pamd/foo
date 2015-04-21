// Brute-force substring search method, based on java code
// in Robert Sedgewick "Algorithms" 4th edition.

// Approach #1
int bf1(const string& text, const string& pat) {
  int N = text.size();
  int M = pat.size();

  // Compare text[i+j] with pat[j]
  for (int i = 0; i < N; i++) {
    int j  = 0;
    for (; j < M; j++) {
      if (text[i + j] != pat[j])
	break;
    }
    if (j == M)
      return i;
  }

  return -1;
}

// Alternative approach
int bf2(const string& text, const string& pat) {
  int N = text.size();
  int M = pat.size();
  int i = 0; 
  int j = 0;
  
  // Compare text[i] with pat[j]
  for (; i < N && j < M; i++) {
    if (text[i] == pat[j])
      j++;
    else {
      i -= j; // Backup text pointer
      j = 0;
    }
  }

  if (j == M)
    return i;

  return -1;
}

// dhu implementation of bf2(): change "for" loop into 
// "while" loop, which makes the code easier to understand. 
int bf2_dhu(const string& text, const string& pat) {
  int N = text.size();
  int M = pat.size();
  int i = 0; 
  int j = 0;

  while (i < N && j < M) {
    if (text[i] == pat[j]) {
      i++;
      j++;
    }
    else {
      i -= j - 1;
      j = 0;
    }
  }

  if (j == M)
    return i - j;

  return -1;
}

// Leetcode OJ strstr() solution: 20ms for large dataset 
char* bf2_leetcode_oj(char* haystack, char* needle) {
  // Optional
  if (!needle)
    return haystack;

  // Optional
  if (!haystack)
    return 0;

  int i = 0;
  int j = 0;
  while (haystack[i] && needle[j]) {
    if (haystack[i] == needle[j]) {
      i++;
      j++;
    }
    else {
      i -= j - 1;
      j = 0;
    }
  }

  if (needle[j] == 0)
    return haystack + i - j;

  return 0;
}
