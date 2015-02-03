#!/usr/bin/env python

"""
Problem: function to return a big amount (one million --> one billion) of unique random numbers,
		having only getRandom() which returns 0 <= n <=1
Solution: implement Durstenfeld solution:
* initialize array with n elements
* max = n
* while max:
    generate number between 0,max
    swap a[number], a[max]
    --max
"""

import random

class GetRandom(object):
    """Class to get random numbers between 0 and 1"""
    def __init__(self):
        random.seed()

    def get_number(self):
        return random.random()

if __name__ == '__main__':

    # initialise Random object
    mrand = GetRandom()
    # init array with values 0..100
    nums = [x for x in range(0, 10)]
    #current max is end of array
    cmax = len(nums) - 1
    while cmax:
        num = int(mrand.get_number() * cmax)
        nums[num], nums[cmax] = nums[cmax], nums[num]
        cmax -= 1
        print nums

    print "Final:"
    print nums

