/* 193. Google: Find or determine non existence of a number in a sorted list of N numbers 
 * where the numbers range over M, M >> N. require O(lgn)
 * http://www.mitbbs.com/article_t1/JobHunting/31916065_0_1.html
 */

// getback: binary search
low = 0;
high = N-1;
start = 0;
end = M-1;

while (low <= high) {
  mid = low + (high - low)/2;
  if (A[mid]==mid) {
	low = mid + 1;
	start = low;
  }
  else {
	high = mid - 1;
	end = A[mid] - 1;
  }
}
//[start, end] are missing numbers, you can always return the first one.
return start;
