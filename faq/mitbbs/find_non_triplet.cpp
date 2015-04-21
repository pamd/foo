/* Given an array in which one element shows up only once,
 * the other elements show up three times. 
 * Find the one that shows up only once in O(n).
 *
 * Refer to dhu Reserved Discussions #89 and:
 * http://www.mitbbs.com/article_t/JobHunting/31995025.html
 * http://blog.renren.com/share/171828317/11349726763
 * 
 * Extension: In the input array, if only one element shows up once, 
 * another element shows up twice, and all the other elements show up 
 * three times, then at the end of this program, ones will be the one 
 * that shows up once and twos will be the value that shows up twice. 
 */

#include <iostream>

using namespace std;

int main() {
  int B[] = { 1, 1, 4, 1, 2, 3, 2, 2, 3 };
  int len = sizeof(B) / sizeof(int); 
  // Value that shows up once
  int ones = 0; 
  // Value that shows up twice
  int twos = 0; 

  // When a certain bit shows up three times, set that bit to 0
  int not_threes = 0; 

  for (int i = 0; i < len; i++ ) {
    /* If a certain bit in elements { B[0] ... B[i] } has been set
     * 3 * x + 2 times, set that bit to 1 in twos. */
    twos |= ones & B[i];

    /* If a certain bit in elements { B[0] ... B[i] } has been set
     * 3 * x + 1 times, set that bit to 1 in ones. */
    ones ^= B[i];

    /* The bits that have been set in both ones and twos must have
     * shown up three times. Set these bits to 0 in not_threes,
     * the rest of bits in not_threes are set to 1. */ 
    not_threes = ~(ones & twos);

    // Now, in ones and twos, set the bits that are 0 in not_threes to 0 too.  
    ones &= not_threes;
    twos &= not_threes;

    // Debug purpose
    cout << i << ": " << endl;
    cout << "ones: " << ones << endl;
    cout << "twos: " << twos << endl;
    cout << "not_threes: " << not_threes << endl << endl;
  }

  // Print out final result
  cout << "ones: " << ones << endl;
  cout << "twos: " << twos << endl;

  return 0;
}
