#!/usr/bin/env python

"""
The prime factors of 13195 are 5, 7, 13 and 29.
What is the largest prime factor of the number 600851475143 ?
"""

import math
import sys

def isprime(n):
    """returns True if n is prime, False otherwise"""

    # 1 is not a prime number
    if n<=1:
        return False

    sqr_root =int(math.sqrt(n))+1
    #print "sqr_root: ",sqr_root

    for i in range(2, sqr_root):
        if n % i == 0:
            return False

    return True



def largest_prime_factor(number):
    """Largest prime factor
    prime factor = prime number which divides an integer exactly
    """
    limit = int(number/2)
    idx = 2
    while idx <= limit:
        a, b = divmod(number, idx)
        #if division was exact and quotient is prime
        if not b and isprime(a):
            return a
        idx += 1
#        print idx


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print "Usage: ./largest_prime_factor.py <number>"
        sys.exit(1)
    number = int(sys.argv[1])

    print "largest prime factor: {0}".format(largest_prime_factor(number))

