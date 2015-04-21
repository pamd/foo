/* 
Insert bounding box (merge rectangles)
http://www.mitbbs.com/article_t/JobHunting/32104365.html
A 2-D bounding box can represented as (Xmin, Xmax, Ymin, Ymax).  We have a set of bounding boxes. There is no intersection between any two of the bounding boxes. 
    
Now we want to insert one bounding box into the bounding boxes set and merge the intersected bounding boxes if necessary. Two intersected boxes can be merged into a big box like this:
  	Xmin = min(Xmin1, Xmin2);  Xmax = max(Xmax1, Xmax2);  
      	Ymin = min(Ymin1, Ymin2);  Ymax = max(Ymax1, Ymax2);
Design an algorithm to do the insertion.

Example:
Exising bounding boxes set is { (1,4,0,2),  (0,2,3,6) }, bounding box to be inserted:  (3,5,1,4)
Result:  { (0, 5, 0, 6) }
*/

// Recursive solution in Java from bajiezhu, O(n^2). Is there a better solution
// (such as sort the X or Y coordinates first, then scan the line)?
public static List<BoundBox> Insert(List<BoundBox> boundBoxs, BoundBox boundBox)
{
  List<BoundBox> result = new List<BoundBox>();
  
  BoundBox bb = null;
  int i;
  for (i = 0; i < boundBoxs.Count(); i++) {
    // Merge() is not defined here. What it does should be: 
    // if boundBoxs[i] intersects with boundBox, return a new merged bounding box;
    // if null otherwise. 
    bb = Merge(boundBoxs[i], boundBox);
    if (bb != null) {
      break;
    }
  }
  // Copy all input bound boxes into results
  result.AddRange(boundBoxs);
  
  // if boundBox does not intersect with any elements in boundBoxes, add boundBox, we are done.
  if (bb == null) {
    result.Add(boundBox);
  }
  // Otherwise, remove the first bounding box that intersects with input box, 
  // then call insert recursively. So total time is O(n^2).
  else {
    result.RemoveAt(i);
    result = Insert(result, bb);
  }
  
  return result;
}
