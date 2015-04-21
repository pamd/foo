/* Copied from:
 * http://ideone.com/MpLqp
 *
 * Rectangle union
 * Input: N (number of rectangles), and then N rectangles (x1, y1, x2, y2)
 * Output: area of union of all rectangles.
 * 
 * Author: Erel Segal
 * Created: 2010-10-07
 *
 * TODO: 
 * Use an Interval Tree
 * http://en.wikipedia.org/wiki/Interval_tree 
 * to make RectSet::contains() more efficient.
 *
 * dhu note: Although this approach uses interval tree, 
 * the time complexity seems to be O(n^2 * logn).
 */
 
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <time.h>
#include <assert.h>

using namespace std;
 
// Print out elements in an input range 
template <class Iterator> 
void print_range(ostream& out, Iterator from, Iterator to) {
  for (; from < to; ++from) 
    out << *from << " ";
  
  out << endl;
}

// Randomly shuffle elements in an input range 
template <class Iterator> 
void shuffle(Iterator from, Iterator to) {
  int size = to - from;
  for (int i = 1; i < size; ++i) {
    Iterator current = from + i;
    Iterator tmp = from  + (rand() % (i + 1));
    swap(*current, *tmp);
  }
}

// Remove consecutive duplicate elements
template <class T> 
void unique_vector(vector<T>& v) {
  typename vector<T>::iterator new_end = unique(v.begin(), v.end());
  v.resize(new_end - v.begin());
}

// Rectangle class def
struct Rect {
  int x1, y1, x2, y2;

  // Default ctor
  Rect() { }

  // Another ctor
  Rect(int _x1, int _y1, int _x2, int _y2) { 
    x1 = _x1; 
    x2 = _x2; 
    y1 = _y1; 
    y2 = _y2; 
  }

  // Input operator
  friend istream& operator>>(istream& in, Rect& r) { 
    in >> r.x1 >> r.y1 >> r.x2 >> r.y2; 
    return in; 
  }

  // Output operator
  friend ostream& operator<<(ostream& out, const Rect& r) { 
    out << r.x1 << " " << r.y1 << " " << r.x2 << " " << r.y2; 
    return out; 
  }

  // Another output operator
  friend ostream& operator<<(ostream& out, const Rect* r) { 
    return (out << *r); 
  }
 
  // Midpoint of x
  int midx() const { return (x1 + x2) / 2; }

  // Midpoint of y
  int midy() const { return (y1 + y2) / 2; }
 
  // Is input x in [x1, x2) AND input y in [y1, y2)?
  bool contains(int x, int y) const { 
    return x1 <= x && x < x2 && y1 <= y && y < y2; 
  }

  // Is input x in [x1, x2)?
  bool containsX (int x) const { 
    return x1 <= x && x < x2; 
  }

  // Is input y in [y1, y2)?
  bool containsY (int y) const { 
    return y1 <= y && y < y2; 
  }
        
  // Is current rectangle on left side of x?
  bool onLeft(int x) const { 
    return x2 <= x; 
  }

  // Is current rectangle on right side of x?
  bool onRight(int x) const { 
    return x < x1; 
  }

};
 
// Is rectangle A on left side of B? (A and B may overlap.) 
bool cmp_left(const Rect* A, const Rect* B) {
  return A->x1 < B->x1;
}

// Is rectangle A on right side of B? (A and B may overlap.) 
bool cmp_right(const Rect* A, const Rect* B) {
  return A->x2 > B->x2;
}
 
//typedef vector<Rect*> PRectangleVector; 
/**
 *  An interval tree for sorting Rectangles by their x value
 * @see: http://en.wikipedia.org/wiki/Interval_tree
 */
class RectTree {
  int threshold;
  RectTree* left;
  RectTree* right;
  vector<Rect*> left_sorted;
  vector<Rect*> right_sorted;
        
  // INVARIANT 1: a tree-node has children if and only if it has rectangles.
  // (when we create a tree, we first insert a rectangle, only then we create children).
 
public:
  RectTree(): left(NULL), right(NULL) { }
 
  bool isEmpty() const { return left_sorted.empty(); }
 
  // Recursive insertion
  void insert (Rect* rect_in) {
    //cout << "insert " << rect_in << "(size=" << left_sorted.size() << ")" << endl;
    if (isEmpty()) {
      //cout << "insert to empty" << endl;
      threshold = rect_in->midx();
      left_sorted.push_back(rect_in);
      right_sorted.push_back(rect_in);
    } 
    else if (rect_in->containsX(threshold)) {
      //cout << "insert to containing" << endl;
      left_sorted.push_back(rect_in);
      right_sorted.push_back(rect_in);
    } 
    else if (rect_in->onLeft(threshold)) {
      //cout << "insert to left" << endl;
      if (!left)
	left = new RectTree();
      left->insert(rect_in);
    } 
    else if (rect_in->onRight(threshold)) {
      //cout << "insert to right" << endl;
      if (!right)
	right = new RectTree();
      right->insert(rect_in);
    } 
    else { // This should never happen
      throw string("Impossible case");
    }
  }
        
  // Recursive sort
  void sort() {
    std::sort(left_sorted.begin(), left_sorted.end(), &cmp_left);
    std::sort(right_sorted.begin(), right_sorted.end(), &cmp_right);

    if (left) 
      left->sort();

    if (right) 
      right->sort();
  }
    
  // Recursive search: does current RectTree contain range [x, y]?  
  bool contains(int x, int y) const {
    bool result = false;
    if (isEmpty()) 
      return false;  // no rectangles -> no children (by invariant 1)

    if (x < threshold) {
      // search for containing rectangles that start lefter than x
      for (vector<Rect*>::const_iterator it = left_sorted.begin(); it != left_sorted.end(); ++it) {
	const Rect& rect = **it;
	if (rect.contains(x, y)) 
	  result = true;
	if (rect.onRight(x))
	  break; // since the rectangles are sorted
      }
      if (!result)
	// search for left rectangles that start lefter than x
	result = (left ? left->contains(x, y): false);
    } 
    else { // (x >= threshold) 
      // search for containing rectangles that end righter than x
      for (vector<Rect*>::const_iterator it = right_sorted.begin(); 
	   it != right_sorted.end(); ++it) {
	const Rect& rect = **it;
	if (rect.contains(x, y)) 
	  result = true;
	if (rect.onLeft(x))
	  break; // since the rectangles are sorted
      }

      // search for righter rectangles that start righter than x
      if (!result)
	result = (right ? right->contains(x, y) : false);
    }

    //cout << "contains("<< x << "," << y << ")=" << result << endl;
    return result;
  }
   
  // Print out all nodes (in-order traversal)
  void print(ostream& out, string prefix = "") const {
    out << prefix << "LEFTER THAN " << threshold << ":" << endl;
    if (left) 
      left->print(out, prefix+"  ");

    out << prefix << "CONTAINING " << threshold << " SORTED BY LEFT: " << endl;
    out << prefix; 
    print_range(out, left_sorted.begin(), left_sorted.end());
    out << prefix << "CONTAINING " << threshold << " SORTED BY RIGHT: " << endl;
    out << prefix; 
    print_range(out, right_sorted.begin(), right_sorted.end());
    out << prefix << "RIGHTER THAN " << threshold << ":" << endl;

    if (right) 
      right->print(out, prefix + "  ");
  }
 
};  // RectTree
 
// Rectangle set def
class RectSet {
  vector<Rect> rects;
  RectTree r_tree;
 
  vector<int> xs; // a sorted array of all x coordinates.
  vector<int> ys; // a sorted array of all y coordinates.
        
  int count;
  bool isSorted;
 
public:
  RectSet(int count_in): rects(count_in), xs(2 * count_in), ys(2 * count_in) { 
    count = 0;
    isSorted = false; 
  }
 
  void add(const Rect& rect) {
    //cout << "add " << rect << endl;
    assert(!isSorted);
    rects[count] = rect;
 
    xs[2 * count] = rect.x1;
    xs[2 * count + 1] = rect.x2;
    ys[2 * count] = rect.y1;
    ys[2 * count + 1] = rect.y2;
 
    ++count;
  }
 
  void sort() {
    //cout << "xs: "; ::print (cout, xs.begin(), xs.end());
    //cout << "ys: "; ::print (cout, ys.begin(), ys.end());

    std::sort(xs.begin(), xs.end());
    std::sort(ys.begin(), ys.end());

    //cout << "xs: "; ::print (cout, xs.begin(), xs.end());
    //cout << "ys: "; ::print (cout, ys.begin(), ys.end());

    // Remove duplicate elements in xs and ys
    unique_vector(xs);
    unique_vector(ys);

    //cout << "xs: "; ::print (cout, xs.begin(), xs.end());
    //cout << "ys: "; ::print (cout, ys.begin(), ys.end());
    //exit(1);

    shuffle(rects.begin(), rects.end());
    for (size_t i = 0; i < rects.size(); ++i) 
      r_tree.insert(&rects[i]);
    
    r_tree.sort();
 
    //r_tree.print(cout); cout << "sort end!" << endl;
 
    isSorted = true;
  }
 
  // Does RectTree contain input range [x, y)?
  bool contains(int x, int y) const {
    return r_tree.contains(x, y);
    
    // Brute force check
    // for (vector<Rect>::const_iterator i = rects.begin(); i < rects.end(); ++i) {
    //   if (i->contains(x, y))
    // 	return true;
    // }

    // return false;
  }
 
  // Calculate the total area: O(n^2 * logn) time
  unsigned get_area() const {
    assert(isSorted);
    unsigned a = 0;
    for (size_t x = 0; x < xs.size() - 1; ++x) { // O(n) 
      for (size_t y = 0; y < ys.size() - 1; ++y) { // O(n)
	if (!contains(xs[x], ys[y])) // O(logn)
	  continue;

	a += (xs[x+1] - xs[x]) * (ys[y+1] - ys[y]);
      }
    }

    return a;
  }
       
  // Does get_area() return expected value (the input value)?  
  void assertArea(unsigned expected) const {
    time_t before = time(NULL);   
    size_t a = get_area();
    if (a != expected) 
      cerr << "ERROR: Area should be " << expected << " but was " << a << endl;
    else {
      time_t after = time(NULL);
      cout << "Calculated area of " << count << " rects in " 
	   << (after - before) << " seconds" << endl;
    }
  }
 
};  // RectSet
 
// Test case #1: Input rectangles do not have any overlap.
void test1(int N) {
  RectSet rects(N);
  for (int i = 0; i < N; ++i) 
    rects.add(Rect(2 * i, 2 * i, 2 * i + 1, 2 * i + 1));
  
  rects.sort();
  rects.assertArea(N);
}
 
// Test case #2: Input rectangles only overlap on corner vertexes.
void test2(int N) {
  RectSet rects(N);      
  for (int i = 0; i < N; ++i) 
    rects.add(Rect(i, i, i + 1, i + 1));
  
  rects.sort();
  rects.assertArea(N);
}
 
// Test case #3: Each input rectangle overlaps with its left and right neighbors.  
void test3(int N) {
  RectSet rects(N);
  for (int i = 0; i < N; ++i) 
    rects.add(Rect(i, i, i + 2, i + 2));

  rects.sort();
  rects.assertArea(4 * N - ( N - 1)); // Total area: 3 * N + 1
}
 
// Test case #4: All input rectangles are identical.
void test4(int N) {
  RectSet rects(N);
  for (int i = 0; i < N; ++i) 
    rects.add(Rect(0, 0, 1, 1));
  
  rects.sort();
  rects.assertArea(1);
}
 
// Test harness
int main() {
  /*
  int N; // number of rectangles in input
  cin >> N;

  RectSet rects(N);
  Rect rect;
  for (int i=0; i<N; ++i) {
    cin >> rect;  // input
    rects.add(rect);
  }

  rects.sort();
  cout << rects.area() << endl;
  */

  int N = 10;
  test1(N);
  test2(N);
  test3(N);
  test4(N);

  return 0;
}
