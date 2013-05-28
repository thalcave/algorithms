#!/usr/bin/env python

"""
If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
Find the sum of all the multiples of 3 or 5 below 1000.
"""

import sys

def get_sum(number, limit):
    """Get sum of all multiples of number below limit"""
    #first, obtain the quotient
    quotient = int(limit/number)
    #get sum 1+2+..+quotient
    tmp = quotient * (quotient+1) * 0.5
    return int(number * tmp)

def find_sum(limit):
    """Find the sum of all the multiples of 3 or 5 below limit"""
    #for multiples of 3
    result = get_sum(3, limit-1)
    #for multiples of 5
    result += get_sum(5, limit-1)
    #get multiple of 15
    sum_15 = get_sum(15, limit-1)
    return result-sum_15

def inefficient_sum(limit):
    result = 0
    for i in range(3, limit):
        if i%3 == 0 or i%5 ==0:
            result += i
    return result

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print "Usage: ./multiples_3_5.py <number>"
        sys.exit(1)
    number = int(sys.argv[1])
    if number < 3:
        print "Sum({0}): 0".format(number)
    result = find_sum(number)
    print "Sum({0}): {1}".format(number, result)
    print "Sum({0}): {1}".format(number, inefficient_sum(number))

