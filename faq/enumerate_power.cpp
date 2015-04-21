/* Enumerate powers in ascending order. 
 * Code is based on Listing 5.8 on page 62 of B. Green's book.
 */

#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/* numbers is input list of numbers that are bases of output powers.
 * It does not have to be sorted, so I am using vector instead of 
 * std::set (which was used in the book). 
 * num_powers is input number of powers the program should generate. 
 * out will hold the output powers.
 */
void enumerate_powers(const vector<unsigned>& numbers, size_t num_powers, 
		      vector<int>& out) {
  /* ValueTerm.first will be the value of the power, 
   * ValueTerm.second will be the base of power. It is used 
   * to calculate the next power with same base. */
  typedef pair<unsigned, unsigned> ValueTerm;
  vector<ValueTerm> heap;

  for (size_t i = 0; i < numbers.size(); i++) 
    heap.push_back(ValueTerm(1, numbers[i]));

  make_heap(heap.begin(), heap.end(), greater<ValueTerm>());
  
  size_t value = 0;
  while (num_powers && heap.size()) {
    ValueTerm entry = heap.front();
    /* cplusplus.com: pop_heap() moves the value at heap.begin() to (heap.end() - 1), 
     * and adjusts the values of the elements in the range [first, last-1) so that 
     * this part of the range retains the heap property (with its first element being 
     * the new highest value).
     * dhu: note that this function will NOT change the size of heap. */
    pop_heap(heap.begin(), heap.end(), greater<ValueTerm>());

    // This "if" condition is required to avoid duplicate values in output
    if (value != entry.first) {
      value = entry.first;
      out.push_back(value);
      --num_powers;
    }

    // Put a new power value into the end of heap
    heap.back() = ValueTerm(entry.first * entry.second, entry.second);
    /* cplusplus.com: Given a heap range [first,last-1), push_heap extends the range 
     * considered a heap to [first, last) by placing the value in (last-1) into its 
     * corresponding location in it. */
    push_heap(heap.begin(), heap.end(), greater<ValueTerm>());
  }
}

int main() {
  vector<unsigned> numbers;
  numbers.push_back(3);
  numbers.push_back(2);
  numbers.push_back(4);

  size_t num_powers = 10;
  vector<int> out;

  enumerate_powers(numbers, num_powers, out);
  for (size_t i = 0; i < out.size(); i++) {
    cout << out[i] << endl;
  }

}
 
 
