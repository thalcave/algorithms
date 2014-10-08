#!/usr/bin/env python

"""
Primes until limit
"""

import math
import sys
import operator

def isprime(n, primes):
    """returns True if n is prime, False otherwise"""

    # 1 is not a prime number
    if n<=1:
        return False

    sqr_root =int(math.sqrt(n)) + 1
    # user already computed prime numbers
    for idx in primes:
        if idx > sqr_root:
            break
        if not n % idx:
            return False

    return True

def print_primes(primes, no_elem):
    """Print no_elem from primes on each line"""
    for idx in range(0, len(primes), no_elem):
        print primes[idx:idx+no_elem]

def primes_until(end):
    """returns the prime numbers smaller than n"""

    #list comprehension
    primes = [2]
#    primes.extend(filter(isprime, range(3, end, 2)))
    cnum = 3
    while cnum < end:
        if isprime(cnum, primes):
            primes.append(cnum)
        cnum += 2


    print_primes(primes, 25)
    print "no: {0}".format(len(primes))

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print "usage : ./primes_until.py <limit>"
        sys.exit(1)

    limit = int(sys.argv[1])
    primes_until(limit)



