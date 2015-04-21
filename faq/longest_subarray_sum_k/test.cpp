// Test various implementations.

#include <iostream>
#include <numeric>
#include <cassert>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

// All functions defined in various cpp files
pair<int, int> epi_less_equal(const vector<int>&, int);
void epi_check_less_equal(const vector<int>&, const pair<int, int>&, int);

pair<int, int> less_equal_nlgn_2(const vector<int>&, int);
pair<int, int> mitbbs_less_equal(const vector<int>&, int);
pair<int, int> less_equal_n_1(const vector<int>&, int);
pair<int, int> less_equal_n_2(const vector<int>&, int);
pair<int, int> less_equal_n_3(const vector<int>&, int);
pair<int, int> less_equal_n_4(const vector<int>&, int);

int bsearch_last_larger_equal(const vector<int>&, int);
pair<int, int> larger_equal_nlgn_1(const vector<int>&, int);

int bsearch_first_less_equal(const vector<int>&, int);
pair<int, int> larger_equal_nlgn_2(const vector<int>&, int);

pair<int, int> larger_equal_n_1(const vector<int>&, int);
pair<int, int> larger_equal_n_2(const vector<int>&, int);
pair<int, int> larger_equal_n_3(const vector<int>&, int);
pair<int, int> larger_equal_n_4(const vector<int>&, int);

pair<int, int> brute_less_equal(const vector<int>&, int);
pair<int, int> brute_larger_equal(const vector<int>&, int);

bool check_less_equal(const vector<int>&, int max_len, int k, pair<int, int> ans); 
bool check_larger_equal(const vector<int>&, int max_len, int k, pair<int, int> ans);

// Test harness
int main(int argc, char *argv[]) {
  /*
  // dhu individual test cases
  // int a[] = { 0, 0, 1, 3, 6 };
  // int k = 4;

  //int a[] = { 3, -4, -6, 7, 2 }; 
  // k = 5;

  int a[] = { 6, 1, -5, -6, 9 };
  int k = 11;

  vector<int> A(a, a + sizeof(a) / sizeof(int));
  pair<int, int> foo = dhu_less_equal_O_n(A, k);
  pair<int, int> brute = brute_less_equal(A, k);

  if (foo != brute) {
    cout << "foo: " << foo.first << ' ' << foo.second << endl;
    cout << "ans: " << brute.first << ' ' << brute.second << endl;
  }
  */

  // Random test cases
  srand(time(nullptr));
  // All elements in input vector will be in this range: [-(range-1), range-1]
  int range = 200; 
  int iteration = 100;  // Number of random test cases
  int n = 100;          // Number of elements in input vector

  for (int times = 0; times < iteration; ++times) {
    int k = rand() % 20;
    vector<int> A;
    for (int i = 0; i < n; ++i) 
      A.emplace_back(((rand() & 1) ? -1 : 1) * rand() % range);

    pair<int, int> foo = larger_equal_n_4(A, k);
    pair<int, int> brute = brute_larger_equal(A, k);
    int max_len = brute.second - brute.first;
    assert(check_larger_equal(A, max_len, k, foo));

    if (foo == brute) {
      //cout << "Check passed: " << brute.first << " " << brute.second << endl << endl;
    }
    else {
      /*
      cout << "Check failed" << endl;
      cout << "A: ";
      for (size_t i = 0; i < A.size(); i++) 
	cout << A[i] << ' ';
      cout << endl;

      cout << "k: " << k << endl;
      cout << "foo: " << foo.first << ' ' << foo.second << endl;
      cout << "ans: " << brute.first << ' ' << brute.second << endl;
      cout << endl;
      */
    }
  }
  
  return 0;
}
