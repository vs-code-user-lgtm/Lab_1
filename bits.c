/* 
 * CS:APP Data Lab 
 * 
 * <郑依桐 25300180083>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ make clean& ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(~x & ~y) & ~(x & y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int sign = x >> 31;
  return (~x + 1) & sign;
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int src_shift = src << 3;
  int dst_shift = dst << 3;
  int mask = 0xFF;
  int src_byte = (x >> src_shift) & mask;
  int clear_mask = ~(mask << dst_shift); 
  return (x & clear_mask) | (src_byte << dst_shift);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  return (x >> n) & ~(((1 << 31) >> n) << 1);
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int m = 0x0f;
  m = m | (m << 8);
  m = m | (m << 16);
  m = m | (m << 24);
  return ((x & m) << 4) | ((x >> 4) & m);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int z = ~x;
  int first = z & (~z + 1);
  int rest = z ^ first;
  return rest & (~rest + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  return (x & 1) ^ 1;
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int k = n & 31; 
  int l = (~k + 1) & 31;
  int low = x >> k;
  int mask = ~((~0) << l);
  return ((low & mask) | (x << l));
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int mask = ~(~0 << n);
  int half = 1 << (n + ~0);
  int base = x & ~mask;
  int r = x & mask;
  int s = r + (~half + 1);
  int q = x >> n;
  int nonneg = !(s >> 31);
  int isZero = !s;
  int qOdd = q & 1;
  int roundup = nonneg & (qOdd | !isZero);
  return base + (roundup << n);
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int a = x & y;
  int b = x ^ y;
  int floor = a + (b >> 1);
  int odd = b & 1;
  int sign = b >> 31;
  int xnonneg = !(x >> 31);
  int diff = x + (~y + 1);
  int dn = diff >> 31;
  int diffgt = (!!diff) & !dn;
  int s1 = (~sign) & diffgt;
  int s2 = sign & xnonneg;
  int truth = s1 | s2;
  int adjust = truth & odd;
  return floor + adjust;
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int sx = x >> 31;
  int sa = a >> 31;
  int sb = b >> 31;
  int sd1 = sx ^ sa;
  int sd3 = sx ^ sb;
  int d1 = x + (~a + 1);
  int d2 = a + (~x + 1);
  int d3 = x + (~b + 1);
  int d4 = b + (~x + 1);
  int same1 = !(d1 >> 31);
  int same2 = !(d2 >> 31);
  int same3 = !(d3 >> 31);
  int same4 = !(d4 >> 31);
  int nxx = !sx;
  int nax = !sa;
  int nbx = !sb;
  int g1 = ((~sd1) & same1) | (sd1 & nxx);
  int g2 = ((~sd1) & same2) | (sd1 & nax);
  int g3 = ((~sd3) & same3) | (sd3 & nxx);
  int g4 = ((~sd3) & same4) | (sd3 & nbx);
  int term1 = g1 & g4;
  int term2 = g3 & g2;
  return term1 | term2;
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int T = (0x9a) | (0x99 << 8) | (0x99 << 16) | (0x19 << 24);
  int s  = x >> 31;
  int xp = ~s;
  int t  = (x << 2) + x;
  int d  = x + (~T + 1);
  int op = xp & ~(d >> 31);
  int e  = x + T;
  int en = s & ((e + ~0) >> 31);
  int lo = 0x80 << 24;
  int hi = ~lo;
  int sat = (op & hi) | (en & lo);
  int over = op | en;
  return ((over & (sat ^ t)) ^ t);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int a = x + y;
  int b = a + z;
  int hx = x >> 31;
  int hy = y >> 31;
  int hz = z >> 31;
  int ha = a >> 31;
  int hb = b >> 31;
  int xneg = hx & 1;
  int yneg = hy & 1;
  int zneg = hz & 1;
  int aneg = ha & 1;
  int bneg = hb & 1;
  int xpos = !hx;
  int ypos = !hy;
  int zpos = !hz;
  int apos = !ha;
  int bpos = !hb;
  int c1p = xpos & ypos & aneg;
  int c1n = xneg & yneg & apos;
  int c1 = c1p + (~c1n + 1);
  int c2p = apos & zpos & bneg;
  int c2n = aneg & zneg & bpos;
  int c2 = c2p + (~c2n + 1);
  int C = c1 + c2;
  int ch = C >> 31;
  int cneg = ch & 1;
  int cis0 = !C;
  int cpos = (!ch) & (!cis0);
  return cpos + (~cneg + 1);
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned sign = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 0xff;
  unsigned frac = uf & 0x7fffff;
  if (exp == 0xff) return uf;
  if (exp == 0) {
    unsigned t = 3 * frac;
    unsigned q = t >> 1;
    unsigned r = t & 1;
    unsigned N = q + (r & (q & 1));
    if (N >= 0x800000) {
      return sign | (1u << 23) | (N & 0x7fffff);
    } else {
      return sign | N;
    }
  }
  unsigned M = frac | 0x800000;
  unsigned P = 3 * M;
  unsigned ph = P;
  int sh = 0;
  while (ph >> 24) { ph = ph >> 1; sh = sh + 1; }
  unsigned dropped = P & ((1u << sh) - 1);
  unsigned half = 1u << (sh - 1);
  int roundUp;
  if (dropped > half) roundUp = 1;
  else roundUp = (dropped == half) & (ph & 1);
  ph = ph + roundUp;
  if (ph >= 0x1000000) { ph = ph >> 1; sh = sh + 1; }
  int field = exp + sh - 1;
  if (field >= 255) return sign | 0x7f800000;
  return sign | (field << 23) | (ph & 0x7fffff);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned sign = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 0xff;
  unsigned frac = uf & 0x7fffff;
  if (exp == 0xff) return uf;
  if (exp == 0) return sign;
  int e = exp - 127;
  if (e >= 23) return uf;
  if (e < 0) {
    if (e == -1 && frac) return sign | 0x3f800000;
    return sign;
  }
  unsigned n = (1u << 23) | frac;
  int shift = 23 - e;
  unsigned ip = n >> shift;
  unsigned fbits = n & ((1u << shift) - 1);
  unsigned h = 1u << (shift - 1);
  unsigned rounded = ip;
  if (fbits > h) rounded = rounded + 1;
  else if (fbits == h && (ip & 1)) rounded = rounded + 1;
  if (rounded == 0) return sign;
  unsigned v = rounded;
  int pent = 0;
  while (v < 0x800000) { v = v << 1; pent = pent + 1; }
  unsigned fexp = 127 + (23 - pent);
  unsigned m = v & 0x7fffff;
  return sign | (fexp << 23) | m;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  unsigned sign = 0;
  unsigned absd;
  unsigned frac;
  int exp;
  int n, shift;
  if (x == 0) return 0;
  if (x < 0) { sign = 0x80000000; absd = (~x) + 1; }
  else absd = x;
  for (n = 31; n >= 0; n = n - 1) {
    if (absd & (1u << n)) break;
  }
  exp = n + 127;
  if (n > 23) {
    shift = n - 23;
    frac = absd >> shift;
    int rest = absd & ((1u << shift) - 1);
    int h = 1u << (shift - 1);
    int roundUp;
    if (rest > h) roundUp = 1;
    else roundUp = (rest == h) && (frac & 1);
    frac = frac + roundUp;
    if (frac >= (1u << 24)) { frac = frac >> 1; exp = exp + 1; }
    frac = frac & 0x7fffff;
  } else {
    frac = (absd & ((1u << n) - 1)) << (23 - n);
  }
  return sign | (exp << 23) | frac;
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int mask1 = 0x55 | (0x55 << 8);
  mask1 = mask1 + (mask1 << 16);
  int mask2 = 0x33 | (0x33 << 8);
  mask2 = mask2 + (mask2 << 16);
  int mask4 = 0x0F | (0x0F << 8);
  mask4 = mask4 + (mask4 << 16);
  int mask8 = 0xFF + (0xFF << 16);
  int mask16 = 0xFF + (0xFF << 8);
  int count = (x & mask1) + ((x >> 1) & mask1);
  count = (count & mask2) + ((count >> 2) & mask2);
  count = (count & mask4) + ((count >> 4) & mask4);
  count = (count & mask8) + ((count >> 8) & mask8);
  count = (count & mask16) + ((count >> 16) & mask16);
  return count;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  int mask1 = 0x55 | (0x55 << 8);
  mask1 = mask1 | (mask1 << 16);
  int mask2 = 0x33 | (0x33 << 8);
  mask2 = mask2 | (mask2 << 16);
  int mask4 = 0x0F | (0x0F << 8);
  mask4 = mask4 | (mask4 << 16);
  int mask8 = 0xFF | (0xFF << 16);

  x = ((x >> 1) & mask1) | ((x & mask1) << 1);
  x = ((x >> 2) & mask2) | ((x & mask2) << 2);
  x = ((x >> 4) & mask4) | ((x & mask4) << 4);
  x = ((x >> 8) & mask8) | ((x & mask8) << 8);
  x = ((x >> 16) & (0xFF | (0xFF << 8))) | (x << 16);
  return x;
}
