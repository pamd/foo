#include <string>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <cassert>
#include <chrono>

using namespace std;

// Brute force method: O(m*n) time.
int brute(const string& haystack, const string& needle) {
  unsigned long n = haystack.size();
  unsigned long m = needle.size();
  unsigned long i = 0; 
  unsigned long j = 0;
  while (i < n && j < m) {
    if (haystack[i] == needle[j]) {
      i++;
      j++;
    }
    else {
      i -= j - 1;
      j = 0;
    }
  }

  if (j == m)
    return i - j;

  return -1;
}

// KMP: build table
void build_kmp_table(const string& needle, long overlap[]) {
  unsigned long len = needle.size();
  overlap[0] = -1;
  if (len > 1)
    overlap[1] = 0;

  int candidate = 0;
  size_t index = 2;
  while (index < len) {
    if (needle[index - 1] == needle[candidate]) {
      candidate++;
      overlap[index] = candidate;
      index++;
    }
    else if (candidate) { // aka. else if (candidate > 0)
      candidate = overlap[candidate];
    }
    else {
      overlap[index] = 0;
      index++;
    }
  } // end of "while" loop
}

// KMP algorithm
int kmp(const string& haystack, const string& needle) {
  unsigned long m = needle.size();
  if (m == 0)
    return 0;

  unsigned long n = haystack.size(); 
  long overlap[m];
  build_kmp_table(needle, overlap);

  unsigned long i = 0; // Starting index of a possible needle match in haystack string
  unsigned long j = 0; // Index of current char that is being compared in needle string 
  while (i + j < n) {
    if (haystack[i + j] == needle[j]) {
      j++;
      if (j == m) // We found it!
	return i;
    }
    else {
      i = i + j - overlap[i];
      if (j)
	i = overlap[i];
    }
  }

  return -1;
}

// Boyer-Moore helper: set up bad character shift table.
void get_bad_char(const string& needle, vector<int>& bad_char) {
  unsigned long m = needle.size();
  for (unsigned long j = 0; j < m; j++) { // Can be optimized to "j < m - 1"
    int idx = needle[j];
    bad_char[idx] = j;
  }
}

// Boyer-Moore algorithm that uses only bad character jumping table.
int boyer_moore_bad_char(const string& haystack, const string& needle) {
  vector<int> bad_char(1 << 8, -1);
  get_bad_char(needle, bad_char);

  unsigned long n = haystack.size();
  unsigned long m = needle.size();
  unsigned long i = 0;     // index of haystack string
  unsigned j = m - 1; // index of needle string
  while (i <= n - m) {
    if (haystack[i + j] == needle[j]) {  // Compare haystack[i + j] with needle[j]
      --j;
      if (j < 0)
	return i;
    }
    else {
      int idx = haystack[i + j];
      int skip = j - bad_char[idx];
      if (skip <= 0) 
	skip = 1;
      i += skip;
      j = m - 1;
    }
  }

  return -1; // not found.
}

// Boyer-Moore helper: build good suffix jumping table
void make_good_suffix_table(const string & needle, vector<unsigned long>& table) {
  unsigned long m = needle.length();
  table.resize(m+1);
  vector<unsigned long> z(m+1);
  unsigned long i = m;
  unsigned long j = m + 1;

  z[i] = j;
  while (i > 0) {
    while (j <= m && needle[i - 1] != needle[j - 1]) {
      if (table[j] == 0) {
	table[j] = j - i;
      }
      j = z[j]; // DP idea that is also used when building KMP table.
    }
    i--, j--;
    z[i] = j;
  }

  j = z[0];
  for (i = 0; i <= m; ++i) {
    if (table[i] == 0) {
      table[i] = j;
    }
    if (i == j)
      j = z[j];
  }
}

// Boyer-Moore algorithm that uses both bad character 
// jumping table and good suffix jumping table.
int boyer_moore(const string& haystack, const string& needle) {
  if (needle.empty())
    return 0;

  vector<int> bad_char(1 << 8, -1); 
  get_bad_char(needle, bad_char);

  unsigned long m = needle.size();
  unsigned long n = haystack.size();
  vector<unsigned long> good_suffix(m + 1);
  make_good_suffix_table(needle, good_suffix);

  unsigned long i = 0;
  unsigned long j = m - 1;
  while (i <= n - m) {
    if (haystack[i + j] == needle[j]) {
      --j;
      if (j < 0)
	return i;
    }
    else {
      i += max(j - bad_char[haystack[i+j]], good_suffix[j+1]);
      j = m - 1;
    }
  }

  return -1;
}

// Rabin-Karp helper: Compute hash for key[0..M-1]. 
long rk_hash(const string& key, unsigned long M, int R, int Q) { 
  long h = 0; 
  for (unsigned long j = 0; j < M; j++) 
    h = (R * h + key[j]) % Q; 
  return h; 
} 

// Rabin-Karp helper: Preprocess input needle string and return the hash value.
long processNeedle(const string& needle, int& RM, int R, int Q) {
  unsigned long M = needle.size();
  // precompute R^(M-1) % Q for use in removing leading digit
  for (unsigned long i = 1; i <= M - 1; i++)
    RM = (R * RM) % Q;
  
  return rk_hash(needle, M, R, Q);    
} 

// Rabin-Karp helper: confirm whether needle[] really matches haystack[i..i-M+1] ?
bool check(const string& haystack, const string& needle, unsigned long i) {
  unsigned long M = needle.size();
  for (unsigned long j = 0; j < M; j++) { 
    if (needle[j] != haystack[i + j]) 
      return false; 
  }

  return true;
}

// Rabin-Karp algorithm
unsigned long rabin_karp(const string& haystack, const string& needle) { 
  unsigned long N = haystack.size(); 
  unsigned long M = needle.size();
  if (N < M) 
    return -1;

  int R = 256;
  long Q = 997; // Arbitrary prime number, selected by dhu
  
  int RM = 1;
  long needleHash = processNeedle(needle, RM, R, Q);
  long haystackHash = rk_hash(haystack, M, R, Q); 
  // Check for match at offset 0
  if ((needleHash == haystackHash) && check(haystack, needle, 0))
    return 0;
  
  // Check for hash match; if hash match, check for exact match
  for (unsigned long i = M; i < N; i++) {
    // Remove leading digit, add trailing digit, check for match. 
    haystackHash = (haystackHash + Q - RM * haystack[i-M] % Q) % Q; 
    haystackHash = (haystackHash * R + haystack[i]) % Q; 
    
    // match
    unsigned long offset = i - M + 1;
    if ((needleHash == haystackHash) && check(haystack, needle, offset))
      return offset;
  }

  // no match
  return -1;
}


// Generate a random haystack string that includes only A/G/C/T
string rand_str_gen(size_t len) {
  string str(len, 0);
  for (size_t i = 0; i < len; i++) {
    str[i] = rand() % 4 + 'A';
  }

  return str;
}

// Make sure input string includes only A/B/C/D
bool chk_str(const string& str) {
  for (size_t i = 0; i < str.size(); i++) {
    if (str[i] != 'A' && str[i] != 'B' && str[i] != 'C' && str[i] != 'D')
      return false;
  }

  return true;
}

// Test harness
int main() {
  typedef chrono::high_resolution_clock Clock;
  typedef chrono::milliseconds milliseconds;

  srand(time(NULL));

  // n could be as large as 3 billion, which is the  
  // total number of base pairs in human whole genome.
  unsigned long n = 3000000000;  
  unsigned long m = 10000; // 10^4
  string haystack = rand_str_gen(n);
  string needle = rand_str_gen(m);

  /*
  for (size_t i = 0; i < 100; ++i) {
    cout << haystack[i];
  }
  cout << endl;
  for (size_t i = 0; i < 100; ++i) {
    cout << needle[i];
  }
  cout << endl;
  assert(chk_str(haystack) && chk_str(needle));
  */

  long s1;
  Clock::time_point t0 = Clock::now();
  size_t tmp = haystack.find(needle);
  Clock::time_point t1 = Clock::now();
  milliseconds ms = chrono::duration_cast<milliseconds>(t1 - t0);
  cout << "string::find():\t" << ms.count() / 1000.0 << " second" << endl;
  if (tmp == string::npos)
    s1 = -1;
  else
    s1 = tmp;

  t0 = Clock::now();
  long s2 = brute(haystack, needle);
  t1 = Clock::now();
  ms = chrono::duration_cast<milliseconds>(t1 - t0);
  cout << "brute method:\t" << ms.count() / 1000.0 << " second" << endl;

  long s3 = -1;
  /*
  t0 = Clock::now();
  long s3 = kmp(haystack, needle);
  t1 = Clock::now();
  ms = chrono::duration_cast<milliseconds>(t1 - t0);
  cout << "kmp method:\t" << ms.count() / 1000.0 << " second" << endl;
  */

  t0 = Clock::now();
  long s4 = boyer_moore_bad_char(haystack, needle);
  t1 = Clock::now();
  ms = chrono::duration_cast<milliseconds>(t1 - t0);
  cout << "bm bad char:\t" << ms.count() / 1000.0 << " second" << endl;

  t0 = Clock::now();
  long s5 = boyer_moore(haystack, needle);
  t1 = Clock::now();
  ms = chrono::duration_cast<milliseconds>(t1 - t0);
  cout << "bm combo:\t" << ms.count() / 1000.0 << " second" << endl;

  const char* hc = haystack.c_str();
  const char* nc = needle.c_str();
  t0 = Clock::now();
  const char* strstr_ret = strstr(hc, nc);
  t1 = Clock::now();
  ms = chrono::duration_cast<milliseconds>(t1 - t0);
  cout << "strstr():\t" << ms.count() / 1000.0 << " second" << endl;

  long s6;
  if (strstr_ret == 0)
    s6 = -1;
  else
    s6 = strstr_ret - hc;

  t0 = Clock::now();
  long s7 = rabin_karp(haystack, needle);
  t1 = Clock::now();
  ms = chrono::duration_cast<milliseconds>(t1 - t0);
  cout << "Rabin Karp:\t" << ms.count() / 1000.0 << " second" << endl;

  assert(s1 == s2 && s3 == s2 && s4 == s2 && s5 == s2 && s6 == s2 && s7 == s2);
  cout << "Result: " << s2 << endl;

  return 0;
}

/*
  m = 5,000, n = 100,000,000, mismatch:
  --------------------------------------
  bm combo:	0.17 second
  strstr():	0.306 second
  find():       0.556 second
  bm bad char:	0.761 second
  brute method:	1.335 second
  kmp method:	1.398 second

  m = 5,000, n = 100,000,000, match in the middle of haystack
  ------------------------------------------------------------
  bm combo:	0.064 second
  strstr():	0.165 second
  find():	0.278 second
  bm bad char:	0.406 second
  brute method:	0.633 second
  kmp method:	0.709 second

  m = 10,000, n = 1,000,000,000, mismatch:
  ----------------------------------------
  bm combo:	 1.857 second
  strstr():	 2.051 second
  bm bad char:	 4.607 second
  find():	 5.093 second
  brute method:	13.071 second
  kmp method:	13.452 second
  Rabin Karp:	51.980 second

  m = 10,000, n = 3,000,000,000, mismatch:
  -------------------------------------------
  string::find(): 16.686 second
  brute method:	  39.171 second
  bm bad char:	  24.019 second


  Conclusion: The time taken can be ranked from fastest to lowest as:
  -------------------------------------------------------------------
  1. Boyer Moore
  2. strstr()
  3. string::find()
  4. Boyer-Moore, bad_char only
  5. Brute force 
  6. KMP (Knuth-Morris-Pratt)
  7. Rabin Karp

  bm_combo is about 4 times faster than string::find();
  strstr() is about 2 times faster than string::find();
  Brute force and KMP are very close, 
  Rabin-Karp is disappointingly slow, not even in the same magnitude.

*/
