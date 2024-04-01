#include <stdio.h>
#include "bit_ops.h"

// Return the nth bit of x.
// Assume 0 <= n <= 31
unsigned get_bit(unsigned x,
                 unsigned n) {
    // YOUR CODE HERE
    // Returning -1 is a placeholder (it makes
    // no sense, because get_bit only returns
    // 0 or 1)
    unsigned mask = 1;
    mask = mask << n;
    return (x&mask)>>n;
}
// Set the nth bit of the value of x to v.
// Assume 0 <= n <= 31, and v is 0 or 1
void set_bit(unsigned * x,
             unsigned n,
             unsigned v) {
    // YOUR CODE HERE
    unsigned mask = 0;
    unsigned mask1 = 1;
    mask1 = mask1 << n;
    v = v << n;
    mask = ~mask;
    mask = mask^mask1;
    *x = (*x & mask) | v;
    
    

}
// Flip the nth bit of the value of x.
// Assume 0 <= n <= 31
void flip_bit(unsigned * x,
              unsigned n) {
    // YOUR CODE HERE
    unsigned mask = 1;
    mask = mask << n;
    *x = *x^mask;
}

