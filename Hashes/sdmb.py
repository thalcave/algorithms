#!/usr/bin/env python

import sys
from ctypes import c_ulong

def ulong(i): return c_ulong(i).value  # numpy would be better if available

def sdbm(to_hash):
    """transforms a string into a hash(long)"""

    # hash to return
    hash = 0

    for x in to_hash:
        hash = ulong(ord(x) + ulong(hash << 6) + ulong(hash << 16) - hash)
        print "hash: {0}".format(hash)

    return hash

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print "Usage: ./sdbm.py <str>"
        sys.exit(1)

    print "sdbm({0}) = {1}".format(sys.argv[1], sdbm(sys.argv[1]))
