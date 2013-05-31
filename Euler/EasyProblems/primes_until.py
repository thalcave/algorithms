#!/usr/bin/env python

"""
Primes until limit
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

def primes_until(end):
    """returns the prime numbers smaller than n"""

#    for x in range(2,n):
#        if isprime(x):
#            primes.append(x)
    #list comprehension
    primes = filter(isprime, range(2, end))
    print_primes(primes, 25)
    print "no: {0}".format(len(primes))

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print "usage : ./smallest_multiple.py <limit>"
        sys.exit(1)

    limit = int(sys.argv[1])
    primes_until(limit)



