#!/usr/bin/env python

import sys

def set_prime(num, limit, is_prime):
    """num is a prime; set all of its multiples in is_prime to zero"""
    for x in xrange(num*2, limit, num):
        is_prime[x] = 0


def eratostene_sieve(limit):
    """Find prime numbers until limit"""

    # initialize an array of flags
    is_prime = [1 for num in xrange(limit)]
    is_prime[0] = 0 # this is because indexing starts at zero
    is_prime[1] = 0 # one is not a prime, but don't mark all of its multiples!

    # iterate over all integers up to N and update the is_prime array accordingly
    for num in xrange(limit):
        if is_prime[num] == 1:
            set_prime(num, limit, is_prime)

    primes = [num for num in xrange(limit) if is_prime[num]]
    print "No. of primes until {0}: {1}".format(limit, len(primes))

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print "usage : ./eratostene_sieve <limit>"
        sys.exit(1)

    eratostene_sieve(int(sys.argv[1]))
