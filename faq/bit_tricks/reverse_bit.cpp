/* Reverse bits of an input integer. Code is copied from:
 * http://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious
 */

#include <iostream>
#include <iomanip>

using namespace std;

const int CHAR_BIT = 8;

template <typename T>
void print_binary(T v)
{
  int s = sizeof(v) * CHAR_BIT - 1;
  T mask = 1 << s;
  for (int i = 0; i <= s; i++) {
    if (v & mask)
      cout << 1;
    else
      cout << 0;
    mask >>= 1;

    if (i % CHAR_BIT == CHAR_BIT - 1)
      cout << " ";
  }
  cout << endl;
}

// Reverse bits in the obvious way. Code is based on: 
// http://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious
unsigned int reverse(unsigned int x) {
  // ret will be the returned value that has reversed bits of v; 
  // By setting ret to x, the LSB of x is set in ret.
  unsigned int ret = x; 

  int sz = sizeof(x) * CHAR_BIT - 1; // extra shift needed at end

  // By left shifting ret, all bits in ret that are 
  // on the left side of LSB will be eventually removed.

  for (x >>= 1; x != 0; x >>= 1) {   
    ret <<= 1;
    ret |= x & 1;
    sz--;
  }

  ret <<= sz; // shift when x's highest bits are zero

  return ret;
}

// dhu version: traditional idea, which is easier to understand.
unsigned int reverse_dhu(unsigned int x) {
  int sz = sizeof(v) * CHAR_BIT - 1;
  unsigned ret = 0;
  unsigned mask = 1;
  while (x) {
    if (x & mask)
      ret |= (1 << sz);

    sz--;
    x >>= 1;
  }

  return ret;
}

// Helper function that builds the bit reverse table
static const unsigned char BitReverseTable256[256] = {
#   define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
#   define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#   define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )
    R6(0), R6(2), R6(1), R6(3)
};

// Reverse bits in word by lookup table, option #1
unsigned reverse_table1(unsigned v) {
  unsigned int c; // c will get v reversed

  // Option 1:
  c = (BitReverseTable256[v & 0xff] << 24) | 
    (BitReverseTable256[(v >> 8) & 0xff] << 16) | 
    (BitReverseTable256[(v >> 16) & 0xff] << 8) |
    (BitReverseTable256[(v >> 24) & 0xff]);

  return c;
}

// Reverse bits in word by lookup table, option #2
unsigned reverse_table2(unsigned v) {
  unsigned int c; // c will get v reversed

  unsigned char * p = (unsigned char *) &v;
  unsigned char * q = (unsigned char *) &c;
  q[3] = BitReverseTable256[p[0]]; 
  q[2] = BitReverseTable256[p[1]]; 
  q[1] = BitReverseTable256[p[2]]; 
  q[0] = BitReverseTable256[p[3]];

  return c;
}

// Reverse bits in a single byte
unsigned char reverse_char(unsigned char c) {
  unsigned char r = (c * 0x0202020202ULL & 0x010884422010ULL) % 1023;
  return r;
}

// Test harness
int main() {
  //  unsigned int a = 12345;
  // print_binary(a);
  
  //unsigned int ra = reverse_table2(a);
  //print_binary(ra);

  //   for (int i = 0; i < 256; i++) {
  //     cout << i << ": " << (int) BitReverseTable256[i] << " ";
  //     print_binary(BitReverseTable256[i]);
  //   }
  
  //unsigned char c = 123;
  //print_binary(c);

  //print_binary(0x0202020202ULL);
  //print_binary(0x010884422010ULL);
  
  //print_binary<unsigned>(5);
   
  print_binary<unsigned>(reverse(5));
  print_binary<unsigned>(reverse_dhu(5));

  //cout << sizeof(0x0202020202ULL) << endl;
  
  //cout << 0x0202020202ULL << endl;
  //cout << 0x010884422010ULL << endl;
  //print_binary(reverse_char(c));
  

  return 0;
}
