lly the triangle's area * 2,
// thus the function is called area2().
//
int area2(const Point& A, const Point& B, const Point& C) {
   int tmp = (B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y);
   return tmp;
}

// Return square of distance between p1 and p2
int distance_sq(const Point& p1, const Point& p2) {
   return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

// Main algorithm
void get_longest_distance(const vector<Point>& hull) {
   int M = hull.size() - 1;
   int best1 = 0;
   int best2 = 0;
   int best_distance = 0;

   int k = 2;

   // BUGGY LINE:
   // Reverse the order of the last two arguments of area2() so that it returns positive value.
   // while (area(hull[M], hull[k+1], hull[1]) > area(hull[M], hull[k], hull[1])) {
   while (area2(hull[M], hull[1], hull[k+1]) > area2(hull[M], hull[1], hull[k])) {
      k++;
   }

   int j = k;
   for (int i = 1; i <= k; i++) {
      // hull[i] and hull[j] are antipodal.
      if (distance_sq(hull[i], hull[j]) > best_distance) {
         best1 = i;
         best2 = j;
         best_distance = distance_sq(hull[i], hull[j]);
      }

      // Now i is fixed, j is incrementing.

      // BUGGY LINE:
      // Reverse the order of the last two arguments of area2() so that it returns positive value.
      // while (j < M && area(hull[i], hull[j+1], hull[i+1]) > area(hull[i], hull[j], hull[i+1])) {
      while (j < M && area2(hull[i], hull[i+1], hull[j+1]) > area2(hull[i], hull[i+1], hull[j])) {
         j++;
         // hull[i] and hull[j] are antipodal.
         double curr_distance = distance_sq(hull[i], hull[j]);
         if (curr_distance > best_distance) {
            best1 = i;
            best2 = j;
            best_distance = curr_distance;
         }
      } // end of "while" loop

   } // end of "for" loop

   cout << "Longest distance square: " << best_distance
        << " (between points " << best1 << " and " << best2 << ")" << endl;
}

// Test harness
int main() {
   vector<Point> points;
   points.push_back(Point(0, 0)); // dummy point, not used.

   points.push_back(Point(2, 2)); // Point #1
   points.push_back(Point(3, 1)); // Point #2
   points.push_back(Point(4, 1)); // Point #3
   points.push_back(Point(5, 2)); // Point #4
   points.push_back(Point(4, 3)); // Point #5
   points.push_back(Point(3, 3)); // Point #6

   get_longest_distance(points);

   return 0;
}

// Incorrect output from ALGS4 implementation:
//      Longest distance square: 2 (between points 1 and 2)
//
// Correct output:
//      Longest distance square: 9 (between points 1 and 4)

