#!/usr/bin/env python

import random

"""
Bucket sort:
- initialise empty buckets
- scatter: fill buckets with values from array
- sort buckets
- gather: fill array from buckets
"""

BUCKETS = 10

def get_random(number):
    random.seed()
    return [random.random() for i in range(number)]

def get_bucket_no(num):
    return int(num*10)

if __name__ == '__main__':
    num = 20
    mlist = get_random(num)
    print "Unsorted list: {0}".format(mlist)

    # copy the list
    # a = b --> b is a reference to the same list
    # b = a[:] --> a slice of a from beginning to end
    # more explicit
    copy = list(mlist)

    #initialise BUCKETS buckets
    bucket_list = list()
    for _ in range(BUCKETS):
        bucket_list.append(list())

    #scatter
    for x in mlist:
        bucket_list[get_bucket_no(x)].append(x)
    print "Buckets list:{0}".format(bucket_list)

    #sort buckets
    for bucket in bucket_list:
        bucket.sort()
    print "Sorted buckets: {0}".format(bucket_list)

    #gather
    mlist[:] = [] #clear list

    for bucket in bucket_list:
        for x in bucket:
            mlist.append(x)

    print "Sorted list: {0}".format(mlist)

    copy.sort()
    assert(mlist == copy)

