/**
* Rectangle union
* Input: N (number of rectangles), and then N rectangles (x1 y1 x2 y2)
* Output: area of union of all rectangles
* 
* Author: Erel Segal
* Created: 2010-10-07
*
* TODO: Use an Interval Tree: http://en.wikipedia.org/wiki/Interval_tree 
*   to make RectangleCollection::contains() more efficient.
*/
 
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <time.h>
#include <assert.h>
using namespace std;
 
typedef unsigned long long ulonglong;
 
 
 
template <class Iterator> void print (ostream& out, Iterator iFrom, Iterator iTo) {
        for (; iFrom<iTo; ++iFrom) {
                out << *iFrom << " ";
        }
        out << endl;
}


template <class Iterator> void shuffle (Iterator iFrom, Iterator iTo) {
	int size = iTo-iFrom;
	for (int i=1; i<size; ++i) {
		Iterator iCurrent = iFrom+i;
		Iterator iNew = iFrom+(rand()%(i+1));
		swap(*iCurrent, *iNew);
	}
}

template <class T> void unique_vector (vector<T>& v) {
	typename vector<T>::iterator new_end = ::unique (v.begin(), v.end());
	v.resize(new_end-v.begin());
}


struct Rectangle {
        int x1, y1, x2, y2;
        Rectangle() {}
        Rectangle(int _x1, int _y1, int _x2, int _y2) { x1=_x1; x2=_x2; y1=_y1; y2=_y2; }
        friend istream& operator>> (istream& in, Rectangle& r) { in >> r.x1 >> r.y1 >> r.x2 >> r.y2; return in; }
        friend ostream& operator<< (ostream& out, const Rectangle& r) { out << r.x1 << " " << r.y1 << " " << r.x2 << " " << r.y2; return out; }
        friend ostream& operator<< (ostream& out, const Rectangle* r) { return (out << *r); }
 
        int midx() const { return (x1+x2)/2; }
        int midy() const { return (y1+y2)/2; }
 
        bool contains(int x, int y) const { return x1<=x && x<x2 && y1<=y && y<y2; }
        bool containsX (int x) const { return x1<=x && x<x2; }
        bool containsY (int y) const { return y1<=y && y<y2; }
        
        bool entirelyLefter(int x) const { return x2<=x; }
        bool entirelyRighter(int x) const { return x<x1; }
};
 
 
bool lefter(const Rectangle* A, const Rectangle* B) {
        return A->x1 < B->x1;
}
 
bool righter(const Rectangle* A, const Rectangle* B) {
        return A->x2 > B->x2;
}
 
typedef vector<Rectangle*> PRectangleVector; 
/**
 An interval tree for sorting Rectangles by their x value
 @see: http://en.wikipedia.org/wiki/Interval_tree
 */
class RectangleTree {
        int myThreshold;
        RectangleTree* lefterRectangles;
        RectangleTree* righterRectangles;
        PRectangleVector containingRectanglesSortedByLeft;
        PRectangleVector containingRectanglesSortedByRight;
        
        // INVARIANT 1: a tree-node has children if and only if it has rectangles.
        //   (when we create a tree, we first insert a rectangle, only then we create children).
 
public:
        RectangleTree(): lefterRectangles(NULL), righterRectangles(NULL), containingRectanglesSortedByLeft(), containingRectanglesSortedByRight() {}
 
        bool isEmpty() const { return containingRectanglesSortedByLeft.empty(); }
 
        void insert (Rectangle* newRectangle) {
                //cout << "insert " << newRectangle << "(size=" << containingRectanglesSortedByLeft.size() << ")" << endl;
                if (isEmpty()) {
                        //cout << "insert to empty" << endl;
                        myThreshold = newRectangle->midx();
                        containingRectanglesSortedByLeft.push_back(newRectangle);
                        containingRectanglesSortedByRight.push_back(newRectangle);
                } else if (newRectangle->containsX(myThreshold)) {
                        //cout << "insert to containing" << endl;
                        containingRectanglesSortedByLeft.push_back(newRectangle);
                        containingRectanglesSortedByRight.push_back(newRectangle);
                } else if (newRectangle->entirelyLefter(myThreshold)) {
                        //cout << "insert to left" << endl;
                        if (!lefterRectangles)
                                lefterRectangles = new RectangleTree();
                        lefterRectangles->insert(newRectangle);
                } else if (newRectangle->entirelyRighter(myThreshold)) {
                        //cout << "insert to right" << endl;
                        if (!righterRectangles)
                                righterRectangles = new RectangleTree();
                        righterRectangles->insert(newRectangle);
                } else {
                        throw string("Impossible case");
                }
        }
        
        void sort() {
                std::sort(containingRectanglesSortedByLeft.begin(), containingRectanglesSortedByLeft.end(), &lefter);
                std::sort(containingRectanglesSortedByRight.begin(), containingRectanglesSortedByRight.end(), &righter);
                if (lefterRectangles) lefterRectangles->sort();
                if (righterRectangles) righterRectangles->sort();
        }
        
        bool contains(int x, int y) const {
                bool result = false;
                if (isEmpty()) { 
                        result = false;  // no rectangles -> no children (by invariant 1)
                } else if (x<myThreshold) {
                        // search for containing rectangles that start lefter than x
                        for (PRectangleVector::const_iterator it=containingRectanglesSortedByLeft.begin(); it!=containingRectanglesSortedByLeft.end(); ++it) {
                                const Rectangle& rect = **it;
                                if (rect.contains(x,y)) 
                                        result = true;
                                if (rect.entirelyRighter(x))
                                        break; // since the rectangles are sorted
                        }
                        if (!result)
                        // search for lefter rectangles that start lefter than x
                                result = (lefterRectangles? lefterRectangles->contains(x,y): false);
                } else {// (x>=myThreshold) 
                        // search for containing rectangles that end righter than x
                        for (PRectangleVector::const_iterator it=containingRectanglesSortedByRight.begin(); it!=containingRectanglesSortedByRight.end(); ++it) {
                                const Rectangle& rect = **it;
                                if (rect.contains(x,y)) 
                                        result = true;
                                if (rect.entirelyLefter(x))
                                        break; // since the rectangles are sorted
                        }
                        // search for righter rectangles that start righter than x
                        if (!result)
                                result = (righterRectangles? righterRectangles->contains(x,y): false);
                }
                //cout << "contains("<< x << "," << y << ")=" << result << endl;
                return result;
        }
        
        void print(ostream& out, string prefix="") const {
                out << prefix << "LEFTER THAN " << myThreshold << ":" << endl;
                if (lefterRectangles) lefterRectangles->print(out, prefix+"  ");
                out << prefix << "CONTAINING " << myThreshold << " SORTED BY LEFT: " << endl;
                out << prefix; ::print(out, containingRectanglesSortedByLeft.begin(), containingRectanglesSortedByLeft.end());
                out << prefix << "CONTAINING " << myThreshold << " SORTED BY RIGHT: " << endl;
                out << prefix; ::print(out, containingRectanglesSortedByRight.begin(), containingRectanglesSortedByRight.end());
                out << prefix << "RIGHTER THAN " << myThreshold << ":" << endl;
                if (righterRectangles) righterRectangles->print(out, prefix+"  ");
        }
 
};
 
class RectangleCollection {
        vector<Rectangle> myRectangles;
        RectangleTree myRectangleTree;
 
        vector<int> xs; // a sorted array of all x coordinates.
        vector<int> ys; // a sorted array of all y coordinates.
        
        int myCount;
        bool isSorted;
 
public:
        RectangleCollection(int newCount): 
                myRectangles(newCount), 
                myRectangleTree(),
                xs(2*newCount), ys(2*newCount), myCount(0), isSorted(false) {}
 
        void add(const Rectangle& rect) {
                //cout << "add " << rect << endl;
                assert(!isSorted);
                myRectangles[myCount] = rect;
 
                xs[2*myCount] = rect.x1;
                xs[2*myCount+1] = rect.x2;
                ys[2*myCount] = rect.y1;
                ys[2*myCount+1] = rect.y2;
 
                ++myCount;
        }
 
        void sort() {
                //cout << "xs: "; ::print (cout, xs.begin(), xs.end());
                //cout << "ys: "; ::print (cout, ys.begin(), ys.end());
                ::sort (xs.begin(), xs.end());
                ::sort (ys.begin(), ys.end());
                //cout << "xs: "; ::print (cout, xs.begin(), xs.end());
                //cout << "ys: "; ::print (cout, ys.begin(), ys.end());
                ::unique_vector (xs);
                ::unique_vector (ys);
                //cout << "xs: "; ::print (cout, xs.begin(), xs.end());
                //cout << "ys: "; ::print (cout, ys.begin(), ys.end());
                //exit(1);
                shuffle(myRectangles.begin(), myRectangles.end());
                for (size_t i=0; i<myRectangles.size(); ++i) {
                        myRectangleTree.insert(&myRectangles[i]);
                }
                myRectangleTree.sort();
 
                //myRectangleTree.print(cout); cout << "sort end!" << endl;
 
                isSorted=true;
        }
 
        bool contains (int x, int y) const {
                return myRectangleTree.contains(x,y);
                
                for (vector<Rectangle>::const_iterator i=myRectangles.begin(); i<myRectangles.end(); ++i) {
                        if (i->contains(x,y))
                                return true;
                }
                return false;
        }
 
        // calculate the total area
        ulonglong area() const {
                assert(isSorted);
                ulonglong a = 0;
                for (int x=0; x<xs.size()-1; ++x) {
                        for (int y=0; y<ys.size()-1; ++y) {
                                if (this->contains(xs[x],ys[y])) {
                                        int pixelArea = (xs[x+1]-xs[x]) * (ys[y+1]-ys[y]);
                                        a += pixelArea;
                                }
                        }
                }
                return a;
        }
        
        void assertArea(ulonglong expected) const {
                time_t before = time(NULL);
                
                size_t a = area();
                if (a!=expected) {
                        cerr << "ERROR: Area should be " << expected << " but was " << a << endl;
                } else {
                        time_t after = time(NULL);
                        cout << "calculated area of " << myCount << " rects in " << (after-before) << " seconds" << endl;
                }
        }
 
};  // RectangleCollection
 
 
 
void testDiagonal0(int N) {
        RectangleCollection rects(N);
        
        for (int i=0; i<N; ++i) {
                rects.add(Rectangle(2*i,2*i,2*i+1,2*i+1));
        }
        rects.sort();
        rects.assertArea(N);
}
 
 
void testDiagonal1(int N) {
        RectangleCollection rects(N);
        
        for (int i=0; i<N; ++i) {
                rects.add(Rectangle(i,i,i+1,i+1));
        }
        rects.sort();
        rects.assertArea(N);
}
 
void testDiagonal2(int N) {
        RectangleCollection rects(N);
        for (int i=0; i<N; ++i) {
                rects.add(Rectangle(i,i,i+2,i+2));
        }
        rects.sort();
        rects.assertArea(4*N-(N-1));
}
 
void testEqual(int N) {
        RectangleCollection rects(N);
        for (int i=0; i<N; ++i) {
                rects.add(Rectangle(0,0,1,1));
        }
        rects.sort();
        rects.assertArea(1);
}
 
int main() {
        int N; // number of rectangles in input
        cin >> N;
/*
        time_t before = time(NULL);
        testDiagonal0(N);
        testDiagonal1(N);
        testDiagonal2(N);
        testEqual(N);
        time_t after = time(NULL);
        cout << "calculated areas of " << N << " rects in " << (after-before) << " seconds" << endl;
        exit(1);
*/
        RectangleCollection rects(N);
        Rectangle rect;
        for (int i=0; i<N; ++i) {
                cin >> rect;  // input
                rects.add(rect);
        }
        rects.sort();
 
        cout << rects.area() << endl;
}
