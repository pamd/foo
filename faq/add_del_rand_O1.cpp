/* Data structure that allows add(), delete() and getRandom() operations all in O(1).  
 * http://www.mitbbs.com/article_t1/JobHunting/31719465_0_3.html
 * Pseudo code is based on:
 * http://www.sureinterview.com/shwqst/1019005/91011
 * The end of this webpage also talks about how to deal with duplicate elements.

 ************************************************************************
 * THE FOLLOWING 3 LINES OF COMMENTS ARE NOT VALID ANY MORE !!!!!!!!!!!!!!!!!!!!!!!!
 *-----------------------------------------------------------------------
 * This implementation is not really what fzblg said in post #43, 
 * in which the data value is in randomArr, and the value in hash table 
 * records the index of that value in randomArr.
 ************************************************************************
 *
 * Another simpler implementation: mitbbs link post #5
 * (which can not deal with duplicate elements either)
 * A hash table is used to support O(1)-time insertions and deletions and 
 * use the array for getRandom. Basically we maintain an array (or more precisely, 
 * a dynamic array) of pointers for the integers in the set and a counter k for how 
 * many integers the hash table currently contains. 
 * We also store the index of an element in the array in the hash table of that 
 * element. When an integer is inserted, we add a new entry to the end of the array 
 * and increment the counter; when deleting an entry, we use hash table to retrieve 
 * its index in the array, move the entry at the end of the array to this vacant one and 
 * update the hash table accordingly. To get a random element, simply generate a random 
 * integer and get its modulo k. 
 *
 // dataArr stores real data, new element will be always put at the end
 T dataArr[];    

 // hashArr's index is hash value of data, value is the index of the data in dataArr
 int hashArr[];
  
 // size keeps track of the number of elements 
 int size = 0;   

 void add(T data) {
   dataArr[size++] = data;
   int key = hashFunction(data);
   hashArr[key] = size - 1;
 }

 void delete(T data) {
   int key = hashFunction(data);
   int index = hashArr[key];
   hashArr[key] = NULL;
   dataArr[index] = dataArr[--size];
 }

 T getRandom() {
   int rand_val = rand() % size;
   return dataArr[rand_val];
 }
 
 */

template <typename T> 
class Foo {
  // Nested class
  class Data {
    T val;
    int idx;
  };
  
  // array that holds the data, index is the hash value of Data::val
  Data dataArr[];   
  // Arbitrary hash table size
  int HASH_SIZE = 0x100000 - 1;
  // array that records the hash value of each data item, index will enable getRandom() in O(1).
  int randomArr[]; 
  // number of elements in randomArr
  int size;        

public:
  // Initialize size to 0
  Foo() { size = 0; }  

  // Return the number of elements in randomArr
  int getSize() {
    return size;
  }
 
  // Hash function implementation
  int hashFunction(T data) {
    int pos = Math.abs(data.hashCode()) % HASH_SIZE;
    // handle conflict, size, etc.
    return pos;
  }
 
  // Add() in O(1) 
  void add(T data) {
    // Get the insert position
    int pos = hashFunction(data); 
    dataArr[pos].data = data;
    // Append to the tail of the index array, and hook two structures together.
    dataArr[pos].idx = size; 
    randomArr[size] = pos;
    size++;
  }

  // Delete() in O(1)
  void delete(T data) {
    if (isEmpty())
      return;

    int pos = hashFunction(data);
    int currIndex = dataArr[pos].idx;
    dataArr[pos].data = null;  // remove the data at pos
 
    /* To avoid moving large data block left, the data at the tail is moved to 
     * the position where the element is deleted, so the pointers in randomArr 
     * should be updated. */
    size--;
    int newHashVal = randomArr[size];
    randomArr[currIndex] = newHashVal;    // move pointer to middle
    dataArr[newHashVal].idx = currIndex;  // adjust the pointer in data array.
  } 

  // getRandom() in O(1)
  T getRandom() {
    // get a random number between 0 and size - 1
    int random = getAValidRandomNumber(); 
    return dataArr[randomArr[random]].data;
  }
 
};
