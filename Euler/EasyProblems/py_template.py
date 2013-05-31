#!/usr/bin/env python

import sys

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print "usage : ./replace <filename>"
        sys.exit(1)

        replace(sys.argv[1])
