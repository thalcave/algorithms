#!/usr/bin/env python

"""
Find the sum of all the primes below two million.
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
    # step over even numbers (because division by 2 is already tested)
#    for i in range(3, sqr_root, 2):
#    print "len primes:{0} n {1}".format(len(primes), n)
    for prime_no in primes:
        if prime_no > sqr_root:
            break
        if not n % prime_no:
            return False

    return True

def sum_primes_until(limit):
    """returns sum of all the primes below 2 millions"""

    psum = 2
    primes = [2]

    #a) without range
    cnum = 3
    while cnum < limit:
        if isprime(cnum, primes):
            psum += cnum
            primes.append(cnum)
        cnum += 2

    print "First sum: {0}".format(psum)

    #b) with range
#    psum = 2
#    psum += sum(filter(isprime, range(3, limit, 2)))

#    print "Second sum: {0}".format(psum)


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print "usage : ./primes_until.py <limit>"
        sys.exit(1)

    limit = int(sys.argv[1])
    sum_primes_until(limit)



