/* stl::lower_bound() returns the first element in a sorted array that is 
 * >= input value.
 *
 * stl::upper_bound() returns the first element in a sorted array that is
 * strictly > input value.
 * 
 * For example, suppose input array is { 10, 20, 20, 20, 30 }, and input value
 * is 20, then lower_bound() returns the iterator that points to index 1 
 * (the first "20", which is the second element), and upper_bound() returns 
 * an iterator that points to index 4 (element "30").
 * 
 * So if lower_bound() is equal to upper_bound(), then input value does not exist 
 * in input array. In another word, upper_bound() - lower_bound() is equal to
 * the number of occurrences of input value. 
 */ 

/* lower_bound() implementation, copied from:
 * http://www.cplusplus.com/reference/algorithm/lower_bound/
 * This is a variant of binary search, but the code is not easy to follow. 
 */
template <class ForwardIterator, class T>
ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last, const T& value) {
  iterator_traits<ForwardIterator>::difference_type count, step;
  count = distance(first, last); // # of elements in search range

  while (count > 0) {
    ForwardIterator it = first; 
    step = count / 2; 
    advance (it, step);

    /* If current value "*it" is less than input value, increase left search 
     * border ("first") by 1, and decrease search range by step + 1. */
    if (*it < value) {  // or: if (comp(*it,value)), for the comp version
      first = ++it; 
      count -= step + 1;  
    }
    // If current value >= input value, decrease search range by one half.
    else 
      count = step;
  }

  return first;
}

/* upper_bound() implementation, copied from:
 * http://www.cplusplus.com/reference/algorithm/upper_bound/
 */
template <class ForwardIterator, class T>
ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last, const T& value) {
  ForwardIterator it;
  iterator_traits<ForwardIterator>::difference_type count, step;
  count = distance(first, last); // # of elements in search range

  while (count > 0) {
    it = first; 
    step = count / 2; 
    advance(it, step);

    /* If current value "*it" <= input value, increase left search 
     * border ("first") by 1, and decrease search range by step + 1. */  
    if (!(value < *it)) {  // or: if (!comp(value,*it)), for the comp version
      first = ++it; 
      count -= step + 1;  
    }
    // If current value > input value, decrease search range by one half.
    else 
      count = step;
  }

  return first;
}

/* equal_range() implementation, copied from:
 * http://www.cplusplus.com/reference/algorithm/equal_range/
 * It calls lower_bound() and upper_bound(), then returns them as a pair. 
 */
template <class ForwardIterator, class T>
pair<ForwardIterator, ForwardIterator>
equal_range (ForwardIterator first, ForwardIterator last, const T& value) {
  ForwardIterator it = lower_bound (first, last, value);
  return make_pair(it, upper_bound(it, last, value));
}
