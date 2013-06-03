#!/usr/bin/env python

"""
A Pythagorean triplet is a set of three natural numbers, a  b  c, for which,
a2 + b2 = c2
For example, 32 + 42 = 9 + 16 = 25 = 52.
There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
"""

import math

def is_whole(nr):
    """See if a number is integer"""
    return nr == math.floor(nr)

def pyta_triplet(a, b):
    """Check if a + b + sqrt(a^2 + b ^2) = 1000"""
     tmp_sqr = math.sqrt(a*a+b*b)

    #check if we have integer
    if not is_whole(tmp_sqr):
        return False

#    print "Integer result: sqrt({0}^2+{1}^2 = {2}".format(a, b, tmp_sqr)
    msum = a + b + tmp_sqr
    if msum == 1000:
        return (a, b, tmp_sqr)

#    print "Computed sum: {0}".format(msum)


def get_triplet():
    """Get Pyta triplet for 1000"""
    #find a and b for which a + b + sqrt(a^2 + b ^2) = 1000
    for idxa in range(1,500):
        for idxb in range (idxa, 500):
            if pyta_triplet(idxa, idxb):
                return (idxa, idxb, math.sqrt(idxa*idxa + idxb*idxb))

    return (None, None, None)

if __name__ == '__main__':
    triplet = get_triplet()
    print "Pythagorean triplet for a + b + c = 1000 is [{0}, {1}, {2}]".format(triplet[0], triplet[1], triplet[2])
