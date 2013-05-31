#!/usr/bin/env python

"""
By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
What is the 10 001st prime number?
"""

import math
import sys
import operator

def isprime(n):
    """returns True if n is prime, False otherwise"""

    # 1 is not a prime number
    if n<=1:
        return False

    sqr_root =int(math.sqrt(n))+1

    for i in range(2, sqr_root):
        if n % i == 0:
            return False

    return True

def print_primes(primes, no_elem):
    """Print no_elem from primes on each line"""
    for idx in range(0, len(primes), no_elem):
        print primes[idx:idx+no_elem]

def nth_prime(n):
    """returns the n-th prime number"""

    found_prime = None
    counter = 1
    idx = 3
    tested = 0
    while (1):
        tested += 1
        if isprime(idx):
            counter += 1
            if counter == n:
                found_prime = idx
                print "Found prime: {0} after testing {1} numbers".format(found_prime, tested)
                break
        idx += 2

    if not found_prime:
        print "Prime not found  testing {0} numbers".format(tested)

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print "usage : ./smallest_multiple.py <limit>"
        sys.exit(1)

    limit = int(sys.argv[1])
    nth_prime(limit)



