#!/usr/bin/env python

"""
Problem: Find and maintain the median value as new values are generated
Solution: use 2 heaps: a Max and a Min one, with following restraints:
1. numbers from Max-heap are smaller than numbers from Min-heaps
2. size(Max-heap) is equal to or 1 more than size(Min-heap):
	if N is even --> size(Max-heap) = size(Min-heap) = N/2
	if N is odd --> size(Max-heap) = N/2 + 1 size(Min-heap) = N/2
"""

import heapq
import random

class streamMedian:
    def __init__(self):
        self.minHeap, self.maxHeap = [], []
        self.N=0

    def insert(self, num):
        #if N is even before insertion, OK
        if self.N%2==0:
            heapq.heappush(self.maxHeap, -1*num)
            self.N+=1
            if len(self.minHeap)==0:
                return
            # check if restraint 1 is OK
            if -1*self.maxHeap[0]>self.minHeap[0]:
                #if not, swap root of maxHeap with root of minHeap
                toMin=-1*heapq.heappop(self.maxHeap)
                toMax=heapq.heappop(self.minHeap)
                heapq.heappush(self.maxHeap, -1*toMax)
                heapq.heappush(self.minHeap, toMin)
        else:
            toMin=-1*heapq.heappushpop(self.maxHeap, -1*num)
            #maxHeap has N+2 elements, minHeap has N --> Restraint 2 is violated
            #pop from MaxHeap and push it on minHeap
            heapq.heappush(self.minHeap, toMin)
            self.N+=1

    def getMedian(self):
        if self.N%2==0:
            return (-1*self.maxHeap[0]+self.minHeap[0])/2.0
        else:
            return -1*self.maxHeap[0]

def get_random():
    return random.randint(0, 100)

if __name__ == '__main__':
    smed = streamMedian()

    numbers = list()

    random.seed()
    for i in range(10):
        rand_elem = get_random()

        numbers.append(rand_elem)
        smed.insert(rand_elem)
        print numbers
        print smed.getMedian()
        print "----------------------"
