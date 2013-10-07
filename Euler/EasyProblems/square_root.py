#!/usr/bin/env python

import sys
import math

def square_root(number):
    """Returns integer square root of number"""
    sq_root = 0
    for idx in range(2, number/2):
        #print "test {0}".format(idx)
        prod = idx*idx
        if prod >= number:
            if prod == number:
                return idx
            break
        sq_root = idx

    return sq_root

#try square root with a bin_search
def bin_square_root(number):
    """Search the integer square root using bin_search"""

    #current start
    cstart = 0
    #current_end
    cend = number/2 - 2

    found = 0

    no_op = 0

    while cstart <= cend:
        #take the middle of the list
        middle = (cstart + cend)/2

        #current number
        celem = middle + 2
        prod = celem * celem

        if prod == number:
            return celem

        no_op += 1

        #move to right
        if prod < number:
            cstart = middle+1
            found = celem
        else:
            #move to left
            cend = middle-1

    print "no op: ",no_op

    return found

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print "usage : ./square_root <no>"
        sys.exit(1)

    number = long (sys.argv[1])
    if number <= 0:
        print "no. must be positive integer"
        sys.exit(2)

#    res = square_root(number)
    res = bin_square_root(number)

    print "integer sq_root({0}) = {1}".format(number, res)
    assert (res == int(math.sqrt(number)))
