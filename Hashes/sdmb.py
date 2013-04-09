#!/usr/bin/env python

"""sdbm (database manager) hashing implementation"""

import sys
from ctypes import c_ulong

def ulong(i):
    """gets the value from c_ulong"""

    return c_ulong(i).value  # numpy would be better if available

def sdbm(to_hash):
    """transforms a string into a hash(long)"""

    # hash to return
    ret_hash = 0

    for mchar in to_hash:
        ret_hash = ulong(ord(mchar) + ulong(ret_hash << 6) + 
                         ulong(ret_hash << 16) - ret_hash)
 

    return ret_hash

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print "Usage: ./sdbm.py <str>"
        sys.exit(1)

    print "sdbm({0}) = {1}".format(sys.argv[1], sdbm(sys.argv[1]))
