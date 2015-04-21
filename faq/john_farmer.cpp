/* This program is based on:
* http://poj.org/problem?id=3273
* http://poj.org/bbs?problem_id=327
*/

#include <iostream>
using namespace std;

int count(int* arr, int len, int target)
{
 int counter = 0;
 int sum = 0;
 int i = 0;
 while (i < len) {
   sum += arr[i];
   if (sum > target) {
     counter++;
     sum = 0;
     continue;
   }
   else if (sum == target) {
     counter++;
     sum = 0;
     i++;
     continue;
   }
   else if (i == len - 1) {
     counter++;
     break;
   }
   else
     i++;
 }

 return counter;
}

int main()
{
 int n = 7;
 int m = 5;
 int arr[7] = { 100, 400, 300, 100, 500, 101, 200 };
 //int arr[7] = { 100, 200, 300, 100, 240, 101, 200 };
 int lower = arr[0];
 int upper = arr[0];
 for (int i = 1; i < n; i++) {
   if (lower < arr[i])
     lower = arr[i];
   upper += arr[i];
 }

 //cout << count(arr, 7, 320) << endl;

 int mid = 0;
 while (lower < upper) {
   mid = (lower + upper) / 2;
   cout << lower << endl;
   cout << upper << endl;
   cout << "mid: "  << mid << endl;

   int counter = count(arr, n, mid);
   cout << "counter: " << counter << endl;
   if (counter > m)
     lower = mid + 1;
   else
     upper = mid - 1;
   cout << endl;
 }

 cout << "lower: "  << lower << endl;
 cout << "upper: "  << upper << endl;
 cout << "mid: "  << mid << endl;

 return lower;
}
   
