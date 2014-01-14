#!/usr/bin/env python

"""
sort an array of 0's and 1's in a most efficient way.
"""

import random

def sortArray(data):
    """sort an array containing (0,1) in order 0,1"""

    #keep an index to where 1 ends
    last = len(data)

    #start from 0
    idx = 0

    while idx < last:
        if data[idx]:
            #1 encountered, move it to end
            data[idx], data[last - 1] = data[last - 1], data[idx]
            last -= 1
        else:
            #0 encountered, leave it there
            idx += 1

def generateData():
    """generate an array of random length, containing 0 and 1 in random order"""

    # max length = 30
    while True:
        length = random.randrange(5, 300)
        if length:
            break

    print "length: ",length

    data = []

    values = [0, 1]

    data = [random.choice(values) for x in range(0, length)]
    return data


if __name__ == '__main__':
    data = generateData()

    print "initial data: ",data
    sortArray(data)
    print "sorted  data: ",data



