#!/usr/bin/env python

"""
Generates N number between [0, 2^x]
"""

import random
import sys
import math

def generateData(number, bits, ofile):
    """generate N numbers"""

    #set the limit
    limit = math.pow(2, bits)
    #open file to write results
    with open(ofile, 'w') as mfile:
        for idx in range(0, number):
            mfile.write("%s\n"%random.randint(0, limit))

if __name__ == '__main__':
    if len(sys.argv) != 4:
        print "usage: ./generate_data.py <N> <no_of_bits> <ofile>"
        sys.exit(1)

    #how many
    number = int(sys.argv[1])
    bits = int(sys.argv[2])
    ofile = sys.argv[3]
    generateData(number, bits, ofile)


