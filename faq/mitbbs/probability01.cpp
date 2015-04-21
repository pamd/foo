/* Use a fair coin to generate a double value that is between 0 and 1.0.
 * See discussions on Google Drive "MITBBS Pearls" Q318.
 */

#include <stdio.h>  
#include <stdlib.h> 
#include <time.h>   
#include <iostream>

using namespace std;

int r_calls = 0;
int rand01() {
  ++r_calls;
  return rand() % 2;
}

/* Return true with the probability of p;
 * Return false with the probability of 1-p.
 *
 * dhu solution that uses binary search. 
 * This solution is NOT efficient. 
 * The average number of calls of rand01() is more than 10.
 */ 
bool dhu_bsearch(double p) {
  double left = 0;
  double right = 1.0;
  while (left < right) {
    double mid = (left + right) / 2.0;
    int r = rand01();
    if (r == 1) {
      if (p > mid) 
	return true;
      left = mid;
    }
    else {  // r == 0
      if (p > mid)
	left = mid;
      else
	right = mid;
    }
  }

  return false;
}
 
// dhu improved binary search approach:
// The idea is almost identical to dhu_double_format().
// The average number of rand01() calls is 2.
bool dhu_bsearch2(double p) {
  double left = 0;
  double right = 1.0;
  while (left < right) {
    double mid = (left + right) / 2.0;
    int r = rand01();
    if (p > mid && r == 0) 
      return true;
    if (p < mid && r == 1)
      return false;

    if (p > mid && r == 1) 
      left = mid;
    else if (p < mid && r == 0)
      right = mid;
    else // if (p == mid), return r
      return r;
  }

  return rand01();
}

/* dhu solution that uses binary expression of double value.
 * The average number of rand01() calls is 2.
 * Imagine each value between 0 and 1 is expressed in binary format:
 * a * (1/2) + b * (1/4) + c * (1/8) + ...
 * in which a, b, c, ... are either 0 or 1. 
 * Calling rand01() is like generating a, b, c, ... for a double value.
 * If this double value is less than p, we will return true;
 * If this double value is larger than p, we will return false;
 * If this double value is equal to p, we will return a random true or false.
 * This will guarantee that the probability of returning true is p,
 * and the the probability of returning false is 1-p.
 *
 * Let's examine the procedure step by step:
 * The first call of rand01() generates a. 
 * 1) If a is 0 and p > 1/2, then no matter what values b, c, ... are, 
 * the double value will be always less than p, so we return true;
 *
 * 2) If a is 1 and p < 1/2, then no matter what values b, c, ... are, 
 * the double value will be always larger than p, so we return false;
 *
 * 3) If a is 1 and p > 1/2, then depending on b, c, ..., the double value
 * could be >, ==, or < p, so we keep going. 
 * 
 * 4) If a is 0 and p < 1/2, then once again, depending on b, c, ..., 
 * the double value could be >, ==, or < p, so we keep going. 
 * 
 * In dhu_double_format(), we modified "p" and/or "curr". To better understand
 * the internal algorithm, refer to dhu_double_format2().
 */ 
bool dhu_double_format(double p) {
  double curr = 0.5;
  while (p != curr) {
    int r = rand01();  
    if (p > curr) {
      if (r == 0)
	return true;
      else { // r == 1
	p = p - curr;
	curr /= 2.0;
      }
    }
    else { // p < curr
      if (r == 1) 
	return false;
      else
	curr /= 2.0;
    }
  }

  return rand01();
}

// Another approach that uses double format
bool dhu_double_format2(double p) {
  if (p == 1.0)
    return true;
  if ( p == 0)
    return false;

  double curr = 0.5;
  double range = 0.25;
  while (p != curr) {
    int r = rand01();  
    //curr += r * range;
    if (p > curr && r == 0)
      return true;
    if (p < curr && r == 1)
      return false;

    if (p > curr && r == 1) {
      curr = curr + range; // modify curr
    }
    else if (p < curr && r == 0) {
      curr = curr - range; // modify curr
    }

    range /= 2.0; // modify range
  }

  return rand01();
} 

// peking2: average number of rand01() is 2.
// The average number of rand01() calls is 2.
bool peking2(double p, bool expected = true) {
  if (p < 0.5) {
    expected = !expected;
    p = 1 - p;
  }
 
  if (rand01() == 1) 
    return expected;

  return peking2((p - 0.5) / 0.5, expected);
}

// chump: compact but hard to understand
bool chump(double p) {
  int q;
 
  while ((q = rand01()) == (int)(p *= 2)) {
    p -= (int)p;
  }

  return (q < (int)p);
}

// Based on Java code by DataMining: alittle too tedious
bool DataMining(double p) {
  double EPS = 1e-8;
  if (p >= 1.0) {
    return true;
  }

  if (p <= 0.0) {
    return false;
  }

  int bitPos = 0;
  while (p > EPS) {
    bitPos++;
    p = p * 2;
    if (p >= 1.0) {
      // We need to return true with prob 2^(-bitPos), 
      // this can be achieved by calling prob() with bitPos times 
      // and return true if all true.

      // All false is the prerequesite state for checking next 1's.

      bool allTrue = true, allFalse = true;
      for (int i = 0; i < bitPos; ++i) {
	bool flip = rand01();
	allTrue = allTrue && flip;
	allFalse = allFalse && !flip;
	EPS = EPS * 2;
      } // end of "for" loop

      if (allTrue) {
	return true;
      }

      if (!allFalse) {
	return false;
      }

      bitPos = 0;
      p = p - 1.0;
    }
  } // end of "while" loop

  return false;
}

// Based on code by lanti, with two bugs fixed.
// The idea is almost identical to dhu_double_format().
bool lanti(double p) {
  p *= 2;
  bool b = rand01();
  while (p != 0 && p != 1) {
    if (b == 0 && p > 1)
      return true;  // buf fixed: return false;
    else if (b == 1 && p < 1)
      return false; // buf fixed: return true;
    else if (p > 1)
      p = (p - 1) * 2;
    else 
      p *= 2;

    b = rand01();
  }

  return b;
}

// Based on Java code by swanswan.
// Same idea as dhu_double_format, but code is more compact.
bool swanswan(double p) {
  while (p) {
    int bit = (p > 0.5) ? 1 : 0;
    int r = rand01();
    if (r < bit) 
      return true;

    if (r > bit) 
      return false;

    // r == bit
    p = p * 2.0;
    if (bit) 
      p = p - 1.0;
  }

  return false;
}

// Test harness
int main() {
  srand (time(NULL));
  double p = 1.0;
  int iter = 1000000; // 1 million
  int count = 0;
  for (int i = 0; i < iter; i++) {
    //count += dhu_double_format2(p);
    //count += dhu_bsearch2(p);
    count += swanswan(p);
  }

  cout << count << endl;
  cout << "rand01() calls: " << r_calls << endl;

  return 0;
}
