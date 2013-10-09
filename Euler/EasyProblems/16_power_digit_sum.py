#!/usr/bin/env python

import sys
import math

"""
2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
What is the sum of the digits of the number 2^1000?
"""

def power_digit_sum(number):
    """computes 2^number and the sum of all digits"""
    return sum(map(int, str(2 ** number)))

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print "usage : ./16_power_digit_sum <power>"
        sys.exit(1)

    pdg = power_digit_sum(int(sys.argv[1]))
    print "pdg: {0}".format(pdg)
