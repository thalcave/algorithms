#!/usr/bin/env python

"""
Starting in the top left corner of a 2x2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.
How many such routes are there through a 20x20 grid?

Answer: 40!/(20! * 20!).
"""

import sys

from collections import deque

def find_routes(values, size, level):
    """Recursive function to find no. of routes in a grid"""
    if (size * 2) == level:
        return values[size]

    #add 1 at beginning and 1 at end
    new_values = deque()
    new_values.appendleft(1)

    for idx in range(0, len(values)-1):
        new_values.append(values[idx] + values[idx+1])

    new_values.append(1)
    values = deque(new_values)

    level += 1
    return find_routes(values, size, level)

def no_routes(size):
    """Get number of routes for a size x size grid"""
    #algorithm:
    # 1st level: 1,1
    # 2nd level: 1, (1+1), 1
    # 3rd level: 1, (1+(1+1)), ((1+1)+1), 1
    # etc.

    values = deque()
    values.appendleft(1)
    values.appendleft(1)
    return find_routes(values, size, 1)

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print "usage : ./lattice_paths <no>"
        sys.exit(1)

    print "No. of routes: {0}".format(no_routes(int(sys.argv[1])))
