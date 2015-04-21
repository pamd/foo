/* Given a string having 2n charecters as c1 c3 c5 c7...c2n-1 c2 c4 c6 .....c2n,
 * write an algorithm to rearrange the charecters so that the string will 
 * become:
 * c1 c2 c3 c4 c5 ......c2n
 * Max complexity of algo should be O(n). Do it without using extra storage
 *
 * References:
 * http://www.mitbbs.com/article_t1/JobHunting/31948557_0_1.html
 * (post #11 by doubleplay)
 * and:
 * http://fayaa.com/code/view/612/
 * by shyx
 */

// Code based on DoublePlay's algorithm

#include <iostream>
#include <vector>

using namespace std;

void swap(int& v1, int& v2) 
{
  int tmp = v1;
  v1 = v2;
  v2 = tmp;
}

int target(int i, int len) {
  if (i % 2 == 1)
    return len / 2 + i / 2;

  return i / 2;
}

void interleave(int arr[], int len) {
  for (int i = 1; i < len - 2; i++) {
    int idx = target(i, len);
    while (idx < i) {
      idx = target(idx, len);
    }
    if (i != idx)
      swap(arr[i], arr[idx]);
  }
}

// Test DoublePlay's algorithm
// int main() 
// {
//   int arr[] = { 2, 5, 3, 7, 15, 4 };
//   int len = sizeof(arr) / sizeof(int);
//   interleave(arr, len);
//   for (int i = 0; i < len; i++)
//     cout << arr[i] << " ";
//   cout << endl;
// }
  
/****************************************************************
 * http://fayaa.com/code/view/612/raw/
 * C implementation of the in-place perfect shuffle permutation

http://spellscroll.com/viewquestions/?tag=shuffle
http://fayaa.com/code/view/612/

This C code was slightly modified by spellscroll@gmail.com from the original C code posted by 
'shyx' in the following post: 

(Originaly copied from the url 
http://www.mitbbs.com/article_t1/JobHunting/31168039_0_1.html  
which is now invalid!)

ansonyy (ansonyy):
Suppose we have an array
a1,a2,... ,an, b1,b2,..., bn

How to change this array to
a1,b1,a2,b2, ..., an,bn in O(n) time and in O(1) space.


shyx (shyx):

Here's a more detailed explanation of my code. I am not sure if it is the
simplest or the most elegant way to solve the problem, but it is the best
result I am aware of. I hope it helps.

For convenience I'll denote the input as a 1D array of 2n numbers: "a[2*n]"
Here a[0] is the "a1" and a[2*n-1] is the "bn" in Ansonyy's original post.

First you will notice that among the 2*n numbers in the array, the 2 numbers
a[0] and a[2*n-1] are never moved. The rest 2*n-2 numbers are moved in an
interleaving pattern:

a[1] --> entry n
a[2] --> entry 1
a[3] --> entry n+1
a[4] --> entry 2
...
a[2*n-3] --> entry 2*n-2
a[2*n-2] --> entry n-1

To summarize, here's a formula for where each a[i] is moved to:

a[i] --> entry ((i*n) % (2*n-1))

For example, let n=6. Here's how each entries are moved (I'm omitting
entries 0 and 11 because they're not moved)

1->6, 2->1, 3->7, 4->2, 5->8, 6->3, 7->9, 8->4, 9->10, 10->5

To achieve O(1) space, you can't have a temp buffer to hold numbers,
so you can only swap a pair of numbers at a time, or shift them in
a circle. Here's how you can reorder the numbers in a circle:

1->6->3->7->9->10->5->8->4->2->1

Easy, right? You just start at a[1] and move the numbers around the
circle. It will be O(n) time.

Unfortunately not all values of n results in such easy patterns. For
example let's try n=23. Here's the circles you'll have to deal with:

1->23->34->17->31->38->19->32->16->8->4->2->1 (12 numbers)
3->24->12->6->3 (4 numbers)
5->25->35->40->20->10->5 (6 numbers)
7->26->13->29->37->41->43->44->22->11->28->14->7 (12 numbers)
9->27->36->18->9 (4 numbers)
15->30->15 (2 numbers)
21->33->39->42->21 (4 numbers)

You can try some larger n but you'll realize that things can get messy.
The reason behind the mess is: 2*n-1 = 45 is not a prime number. It is
divisible by 3 and 5, which means if you start a circle with a number
that is also divisible by 3 or 5, the circle will be "short" because
there aren't that many numbers divisible by 3 or 5 between 1 and 44!

But wait. Even if 2*n-1 is a prime number, there's no guarantee that
you only have 1 big circle to deal with. For example let n=16, then
2*n-1 = 31 is a prime number. But here's the circles:

1->16->8->4->2->1 (4 numbers)
3->17->24->12->6->3 (4 numbers)
5->18->9->20->10->5 (4 numbers)
7->19->25->28->14->7 (4 numbers)
11->21->26->13->22->11 (4 numbers)
15->23->27->29->30->15 (4 numbers)

In general, for values of n such that 2*n-1 is a prime number, you'll
expect to deal with x circles where each circle contains (2*n-2)/x
numbers, but x can be a fairly large value. However, notice that value
(2*n-2) must be divisible by x. Therefore if (n-1) is also a prime
number, then x can only be either 1 or 2. (Note that x will never be
(n-1) or (2*n-2) because that would mean each circle only has 1 or 2
numbers, which is impossible unless n <= 2). When that is the case,
you just need to start a circle from a[1] and shift the numbers while
keeping counting until you're back to a[1]. If you have moved all the
numbers, then you're done; otherwise you'll need to start another circle
from a[2*n-2] and do it again, then you'll be done.

There are plenty of n such that both (n-1) and (2*n-1) are prime numbers.
It is estimated that the reciprocal of their density is O(log(n)^2). Thus
if n doesn't satisfy the requirement, we can always search for a value m
that is almost as large as n and do the reordering on the 2*m numbers
first: a[0], a[1], ..., a[m-1]; a[n], a[n+1], ..., a[n+m-1]. After that
we'll move the 2*m numbers to the front of the array, and reorder the rest
2*(n-m) numbers.

Note:
The same question has been asked again in MITBBS
http://www.unknownspace.org/article_t/Programming/31162946.html
http://www.mitbbs.com/article_t/JobHunting/31339410.html

More discussions can be found in
http://www.cpper.com/c/t4838.html
http://groups.google.com/group/pongba/browse_thread/thread/464c3dc44f644b4e/836800c7fc666a49
http://arxiv.org/PS_cache/arxiv/pdf/0805/0805.1598v1.pdf
http://www.cs.uvic.ca/~jellis/Publications/shuffle.ps
http://hi.baidu.com/bestcpp/blog/item/ce02bd4409a26d4a510ffef7.html 

*/


/* determine if an odd number is prime or not */
int isprime(int n)
{
    int x;
    for (x = 3; x * x <= n; x += 2)
        if (n % x == 0)
            return 0;
    return 1;
}


#define next(x) (x*m)%(2*m-1)
#define prev(x) (x%m+x/m*n)
int cycle(int a[], int n, int m, int i)
{
    int x, y, z, c;
    for (x = i, y = next(x), z = a[prev(x)], c = 1;
        y != i; x = y, y = next(x), ++c){
            a[prev(x)] = a[prev(y)];
    }
    a[prev(x)] = z;
    return c;
}

void rotate(int a[], int n, int m)
{
    int s, t;
    for (s = m + n, t = m; m < n; m++, n++,(t >= m) || (t += n - m), (n < s) || (n = t))
        a[m] ^= a[n] ^= a[m] ^= a[n];
}

// in-place transposition of matrix a[2][n]
void shuffle(int a[], int n)
{
    int m;
    for (; n > 1; n -= m, a += 2 * m)
    {
        for (m = n & ~1; m >= 2; m -= 2){
            if (isprime(m * 2 - 1) && isprime(m - 1)) break;
        }
        if (cycle(a, n, m, 1) != 2 * m - 2)
            cycle(a, n, m, m - 1);
        if (n>m)
            rotate(a, n, m);
    }
}

#include <stdlib.h>
#include <assert.h>
int main()
{
    const int MAX_N = 1000;
    int i, n;
    int *a;
    for (n=1;n<MAX_N;++n){
        a = (int *)malloc(2*n*sizeof(int));
        for (i=0;i<2*n;++i) a[i] = i;
        shuffle(a,n);
        for (i=0;i<n;++i){
            assert(a[2*i]==i);
            assert(a[2*i+1]==n+i);
        }
        free(a);
    }
    return 0;
}





