#!/usr/bin/env python

import sys

def get_no_divisors(cnum):
    """Returns the number of divisors of cnum"""
    #every number can be divided with 1
    no_divisors = 1

#    middle = int(cnum/2)
    divisor_list = [1, cnum]

    for idx in range(2, cnum):
        a, b = divmod(cnum, idx)

        #stop when quotient is smaller than divisor (e.g 28/7 --> 4 is smaller than 7)
        if not b:
            if a < idx:
                divisor_list.sort()
                print divisor_list
                return no_divisors * 2
            if a == idx:
                divisor_list.sort()
                print divisor_list
                return (no_divisors*2 + 1)
            no_divisors += 1
            divisor_list.append(idx)
            divisor_list.append(a)

def test_divisors(number):
    """Get the number of divisors"""
    print "for {0} : {1} divisors".format(number, get_no_divisors(number))

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print "usage : ./test_divisors.py <no>"
        sys.exit(1)

    test_divisors(int(sys.argv[1]))
