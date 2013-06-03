#!/usr/bin/env python

"""
2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
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

def primesuntil(n):
    """returns the prime numbers smaller than n"""

#    for x in range(2,n):
#        if isprime(x):
#            primes.append(x)
    #list comprehension
    primes = filter(isprime, range(2,n))
    return primes

def check_division(number, limit):
    """Checks if number is evenly divisible with range(2,limit)"""
    #all() returns True if all elements from list are true
    return all(number%idx == 0 for idx in range(2,limit))

def get_smallest_multiple(limit):
    """Smallest positive number ..."""
    prime_nos = primesuntil(limit)
    print "Primes until {0}: {1}".format(limit, prime_nos)

    #product of a list
    prime_product = reduce(operator.mul, prime_nos, 1)
    print "Prime product: {0}".format(prime_product)

    idx = 2
    while (1):
        tmp_prod = prime_product * idx
        if check_division(tmp_prod, limit):
            return tmp_prod
        idx += 1

    #reduce(lambda x,y: x*y, prime_nos, 1)
    return None

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print "usage : ./smallest_multiple.py <limit>"
        sys.exit(1)

    limit = int(sys.argv[1])
    print "Smallest multiple: {0}".format(get_smallest_multiple(limit))



