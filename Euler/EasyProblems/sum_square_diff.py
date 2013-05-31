#!/usr/bin/env python

"""
The sum of the squares of the first ten natural numbers is,
1^2 + 2^2 + ... + 10^2 = 385
The square of the sum of the first ten natural numbers is,
(1 + 2 + ... + 10)^2 = 55^2 = 3025
Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is:
3025-385 = 2640.

Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
"""

import sys

def get_diff(limit):
    """Get diff between ..."""
    sum_squares = limit * (limit+1)*(2*limit+1)/6

    square_sum = limit * (limit+1)/2
    square_sum *= square_sum

#    print square_sum

    return square_sum - sum_squares

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print "usage : ./sum_square_diff <limit>"
        sys.exit(1)

    print "sum square diff: {0}".format(get_diff(int(sys.argv[1])))
