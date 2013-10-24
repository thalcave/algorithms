#!/usr/bin/env python

"""
Problem: replace every occurence of ' ' with '%20'
Solution:
- first scan of string: count no. of spaces
- second scan of string: replace ' ' with '%20'
"""


import sys

def replace_char(mstr):
    """Replace chars in str"""
    print "str: [{0}] with size {1}".format(mstr, len(mstr))
    #first scan
    count = 0
    for ch in mstr:
        if ch == ' ':
            count += 1
    print "no. of spaces: {0}".format(count)

    old_len = len(mstr)
    #in C we would have resized the string with new_len
    new_len = old_len + count * 2
    #for _ in range(count*2):
    #mstr += ' '

    old_str = mstr

    for x in range(old_len-1, 0, -1):
        if mstr[x] == ' ':
            #mstr[new_len-1] = '0'
            #mstr[new_len-2] = '2'
            #mstr[new_len-3] = '%'
            #idx = new_len - 3
            mstr = mstr[:x] + '%20' + mstr[x+1:]
            new_len -= 3
        else:
            #idx = new_len-1
            mstr = mstr[:x] + mstr[x] + mstr[x+1:]
            new_len -= 1
    print "str: [{0}] with size {1}".format(mstr, len(mstr))

    assert(mstr == old_str.replace(' ', '%20'))

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print "usage : ./replace '<string>'"
        sys.exit(1)

    replace_char(sys.argv[1])
