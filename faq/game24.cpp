/* Calculate a taget integer value based on input integers. 
 * Based on the algorithm on "Beauty of Programming" (Chinese).
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <set>

using namespace std;

const double epsilon = 1e-6;
set<string> results;

// Expression definition
struct Expr {
  Expr(const string& s, double d) : str(s), val(d) { }

  string str;
  double val;
};

// Are two input double values equal within epsilon?
bool equal(double d1, double d2) {
  return fabs(d1 - d2) < epsilon;
}

// Recursively calculate the values: divide and conquer
void calc(vector<Expr>& v, size_t len, double target) {
  if (len == 1) { 
    if (equal(v[0].val, target) && results.find(v[0].str) == results.end()) {
      results.insert(v[0].str);
      string s = v[0].str;
      cout << s.substr(1, s.size() - 2)  << endl;  // Do not print the outer "()"
    }
    return;
  }

  for (size_t i = 0; i < len; i++) {
    Expr vi = v[i]; // Save original v[i]
    for (size_t j = i + 1; j < len; j++) {
      Expr vj = v[j];    // Save original v[j]
      v[j] = v[len - 1]; // Move v[len - 1] to v[j]

      // Use v[i] to hold the newly created value based on vi and vj 
      // vi + vj (vj + vi is skipped)
      v[i].str = "(" + vi.str + " + " + vj.str + ")";
      v[i].val = vi.val + vj.val;
      calc(v, len - 1, target);

      // vi - vj
      v[i].str = "(" + vi.str + " - " + vj.str + ")";
      v[i].val = vi.val - vj.val;
      calc(v, len - 1, target);
      // vj - vi
      v[i].str = "(" + vj.str + " - " + vi.str + ")";
      v[i].val = vj.val - vi.val;
      calc(v, len - 1, target);

      //  vi * vj (vj * vi is skipped)
      v[i].str = "(" + vi.str + " * " + vj.str + ")";
      v[i].val = vi.val * vj.val;
      calc(v, len - 1, target);

      // vi / vj
      if (!equal(v[j].val, 0)) {
	v[i].str = "(" + vi.str + " / " + vj.str + ")";
	v[i].val = vi.val / vj.val;
	calc(v, len - 1, target);
      }
      // vj / vi
      if (!equal(v[i].val, 0)) {
	v[i].str = "(" + vj.str + " / " + vi.str + ")";
	v[i].val = vj.val / vi.val;
	calc(v, len - 1, target);
      }

      v[j] = vj; // recover v[j]
    }
    v[i] = vi; // recover v[i]
  }

}

// Test harness
int main(int argc, char* argv[]) {
  if (argc < 3) {
    cout << "Usage: ./game24 <target_value> <input1> <input<2> ..." << endl;
    exit(1);
  }

  double target = atoi(argv[1]);
  vector<Expr> v;
  for (int i = 2; i < argc; i++) 
    v.push_back(Expr(argv[i], atoi(argv[i])));

  calc(v, v.size(), target);
}

