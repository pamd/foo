/* Google: Given an array of random numbers. Find the longest consecutive sequence.
http://www.mitbbs.com/article_t1/JobHunting/31911013_0_1.html
http://www.mitbbs.com/article_t/JobHunting/31970781.html
*/

// (Java code)
public class LongestRange {
	public int[] longest(int[] a) {
    	int start = 0;
    	int maxLen = 0;
        
    	HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();
    	for (int i=0; i<a.length; i++) {
        	int left = map.containsKey(a[i]-1)? map.get(a[i]-1) : 0;
        	int right = map.containsKey(a[i]+1)? map.get(a[i]+1) : 0;
        	int len = left + 1 + right;
        	map.put(a[i]-left, len);
        	map.put(a[i]+right, len);
            
        	if (len > maxLen) {
            	maxLen = len;
            	start = a[i] - left;
        	}
    	}
        
    	int[] b = new int[maxLen];
    	for (int i=0; i<maxLen; i++) b[i] = start + i;
    	return b;
	}
}

// C++ implementation by fantasist
#include <map>
#include <iostream>

using namespace std;

int main()
{
    map<int, int> hashmap;
    
    int arr[] = { 100, 3, 200, 3, 1, 2, 4, 101, 6, 99, 7, 102, 105, 104, 
103
};
    
    int maxLen = 0;
    int maxStart = -1;
    for(int i = 0; i < sizeof(arr) / sizeof(int); i++) {
        map<int, int>::iterator it = hashmap.find(arr[i]);
        if(it == hashmap.end()) {
            map<int, int>::iterator left = hashmap.find(arr[i] - 1);
            map<int, int>::iterator right = hashmap.find(arr[i] + 1);
            int leftoffset = (left == hashmap.end() ? 0 : hashmap[arr[i] 
- 1
]);
            int rightoffset = (right == hashmap.end() ? 0 : 
hashmap[arr[i] +
1]);
            int newMax = leftoffset + rightoffset + 1;
            if(newMax > maxLen) {
                maxLen = newMax;
                maxStart = arr[i] - leftoffset;
            }
            
            // Update left end and right end
            hashmap[arr[i] - leftoffset] = newMax;
            hashmap[arr[i] + rightoffset] = newMax;
        }
        else    // Ignore duplicate numbers
            continue;
    }
    
    printf("Start from %d, length = %d\n", maxStart, maxLen);
    
    return 0;
}
