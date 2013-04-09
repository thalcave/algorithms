/*
 * Copyright 2005 Markus Stengel, Tuebingen, Germany.
 * All Rights Reserved.
 *
 * ***
 *
 * LICENSE:
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * ***
 *
 * ALGORITHM:
 * This is an implementation of the LCS-Delta algorithm as it is described
 * in "Introduction to Algorithms", MIT Press, 2001, Second Edition, written
 * by Thomas H. Cormen et. al. It uses dynamic programming to solve the
 * Longest Common Subsequence (LCS) problem.
 *
 *
 * EXTENSIBILITY ETC.:
 * This implementation can be used to calculate the LCS for basically every
 * kind of data.  Compiling it with -DDEBUG activates various status and 
 * progress reports.
 *
 */

#include "lcs.h"

// this function makes calculating the corresponding array indexes easier
// m = len(X), n = len(Y)
static int calcArrayPos(int m, int n, int i, int j) {
  if (1>m || 1>n || i>m || j>n) {
    fprintf(stderr, "Error: illegal dimensions provided! <- m=%d, n=%d, i=%d, j=%d\n",m,n,i,j);
    abort();
  }
  return n*i+j;
}


// ----------------------------------------------------
// -        implementation of the LCS algorithm       -
// ----------------------------------------------------
void calcLCS( int m,                                           // number of elements in X
	      int n,                                           // number of elements in Y
	      void* X,                                         // the first array
	      void* Y,                                         // the second array
	      LCSMarker* b,                                    // array for the "arrows"
	      unsigned int* c,                                 // array for the weights
	      int elSize,                                      // size of an element of X and Y
	      int (*compareFunc)(const void*, const void*))    // the compare function, returns
                                                               // 1 if two elements match
{
	unsigned int xaddr, yaddr;
	int     i, j, mX, nY;

	// the leading zeroes need to be taken care of
	mX = m + 1;
	nY = n + 1;

        // calculate the LCS
#ifdef DEBUG
	fprintf(stderr, "Calculating LCS...");
#endif
	for (i=1; i<=mX; i++) {
	  for (j=1; j<=nY; j++) {
	    xaddr = ((unsigned int) X) + elSize*i;
	    yaddr = ((unsigned int) Y) + elSize*j;
	    if (compareFunc((void*) xaddr, (void*) yaddr)) {
	      c[calcArrayPos(mX+1,nY+1,i,j)] = c[calcArrayPos(mX+1,nY+1,i-1,j-1)] + 1;
	      b[calcArrayPos(mX+1,nY+1,i,j)] = ARROW_UP_LEFT;
	    }
	    else if (c[calcArrayPos(mX+1,nY+1,i-1,j)] >= c[calcArrayPos(mX+1,nY+1,i,j-1)]) {
	      c[calcArrayPos(mX+1,nY+1,i,j)] = c[calcArrayPos(mX+1,nY+1,i-1,j)];
	      b[calcArrayPos(mX+1,nY+1,i,j)] = ARROW_UP;	      
	    }
	    else {
	      c[calcArrayPos(mX+1,nY+1,i,j)] = c[calcArrayPos(mX+1,nY+1,i,j-1)];
	      b[calcArrayPos(mX+1,nY+1,i,j)] = ARROW_LEFT;	      
	    }
	  }
	}
#ifdef DEBUG
	fprintf(stderr, "done.\n");
#endif
}
// ----------------------------------------------------

