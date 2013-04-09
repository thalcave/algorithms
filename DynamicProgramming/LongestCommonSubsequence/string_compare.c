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
 * ***
 *
 * USAGE INFORMATION (SAMPLE APPLICATION):
 * Usage:
 *   string_compare [String1] [String2]
 *
 * ***
 *
 * EXTENSIBILITY ETC.:
 * This implementation can be used to calculate the LCS for basically every
 * kind of data. For demonstration purposes calculating the LCS of two
 * wchar_t strings (->unicode capable) is shown below. Compiling it with 
 * -DDEBUG activates various status and progress reports.
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


// sample printing function
static void printLCS(int m, int n,wchar_t *X, wchar_t *Y, LCSMarker* b, unsigned int* c, int i, int j) {
  if (0 == i || 0 == j) {
    return;
  }

  if (ARROW_UP_LEFT == b[calcArrayPos(m,n,i,j)]) {
    printLCS(m, n, X, Y, b, c, i-1, j-1);
    fprintf(stdout, "%lc", X[i]);
    return;
  }
  else if (ARROW_UP == b[calcArrayPos(m,n,i,j)]) {
    printLCS(m, n, X, Y, b, c, i-1, j);
    return;    
  }
  else {
    printLCS(m, n, X, Y, b, c, i, j-1);
    return;    
  }
}



// sample helper function to compare two wchar_ts
static int compWCHAR_T (const void* a, const void* b) {
  wchar_t *el1 = (wchar_t*) a;
  wchar_t *el2 = (wchar_t*) b;

  return *el1 == *el2;
}




// ------------ PROGRAM START --------------
int main(const int argc, const char *argv[]) {
#ifdef DEBUG
	int               i, j;
#endif
	int               mX, nY, nT, mT, mXc, nYc, Xels, Yels;
	unsigned int      xaddr, yaddr;
	size_t            size, readChars;
	wchar_t           *X = NULL;
	wchar_t           *Y = NULL;
	LCSMarker         *b = NULL;
	unsigned int      *c = NULL;


	// set locale so unicode etc. works
	if (NULL == setlocale(LC_ALL,"")) {
	  fprintf(stderr, "Couldn't set locale.\n");
	  abort();
	}


	// check for parameter validity
	if (3 != argc) {
	  fprintf(stderr,"Longest Common Subsequence (LCS) - (c) 2005 Markus Stengel\n\n");
	  
	  fprintf(stderr,"Error: This program requires exactly two string parameters.\n");
	  fprintf(stderr,"Example:\n");
	  fprintf(stderr," %s \"To you this is just a test string ... A.\" \"And this is just another test string B.\"\n\n", argv[0]);
	  return -1;
	}

	// determine the string lengths
	// first: the total byte count of each parameter
	mXc = strlen(argv[1]);
	nYc = strlen(argv[2]);
	// second: now figure out the amount of wide characters
	mX = mbsrtowcs(NULL, &(argv[1]), mXc, NULL);
	nY = mbsrtowcs(NULL, &(argv[2]), nYc, NULL);

	// "mbsrtowcs" returns not only the number of characters, but includes the
        // trailing \NUL in the figure as well
	Xels = mX - 1;
	Yels = nY - 1;

	// allocate memory to store the strings
	// add 2 chars storage space for the leading and trailing 0
	size = sizeof(wchar_t)*(mX+1+1);
#ifdef DEBUG
	fprintf(stderr,"Allocating %u bytes for X\n", size);
#endif
	X = (wchar_t*)malloc(size);
	if (NULL == X) {
	  fprintf(stderr,"Couldn't allocate memory!");
	  return -1;
	}
	size = sizeof(wchar_t)*(nY+1+1);
#ifdef DEBUG
	fprintf(stderr,"Allocating %u bytes for Y\n", size);
#endif
	Y = (wchar_t*)malloc(size);
	if (NULL == Y) {
	  fprintf(stderr,"Couldn't allocate memory!");
	  free (X);
	  return -1;
	}

	// copy the strings and insert leading and trailing 0s
	X[0] = '\0';
	Y[0] = '\0';
	xaddr = ((unsigned int) X) + sizeof(wchar_t)*1;
	yaddr = ((unsigned int) Y) + sizeof(wchar_t)*1;
	readChars = mbsrtowcs((wchar_t*) xaddr, &(argv[1]), mX, NULL);
	if (((size_t) -1) == readChars) {
	  fprintf(stderr, "Error occurred while converting the characters!\n");
	  free(Y);
	  free(X);
	  return -1;
	}
	if (readChars != mX) {
	  fprintf(stderr, "An unexpected amount of characters was converted: %u\n", readChars);
	  free(Y);
	  free(X);
	  return -1;
	}
	X[mX+1] = '\0';	// theoretically unnecessary, but it's easier to understand the workflow this way

	readChars = mbsrtowcs((wchar_t*) yaddr, &(argv[2]), nY, NULL);
	if (((size_t) -1) == readChars) {
	  fprintf(stderr, "Error occurred while converting the characters!\n");
	  free(Y);
	  free(X);
	  return -1;
	}
	if (readChars != nY) {
	  fprintf(stderr, "An unexpected amount of characters was converted: %u\n", readChars);
	  free(Y);
	  free(X);
	  return -1;
	}
	Y[nY+1] = '\0'; // theoretically unnecessary, but it's easier to understand the workflow this way


	// allocate storage space for the c and b tables
	// add storage space for the leading 0
	// -> 1 unit extra space
	mT = mX +1;
	nT = nY +1;
	size = sizeof(LCSMarker)*((mT+1)*(nT+1));
#ifdef DEBUG
	fprintf(stderr,"Allocating %u bytes for b\n", size);
#endif
	b = (LCSMarker*)malloc(size);
	if (NULL == b) {
	  fprintf(stderr,"Couldn't allocate memory!");
	  free (X);
	  free (Y);	  
	  return -1;
	}

	size = sizeof(unsigned int)*((mT+1)*(nT+1));
#ifdef DEBUG
	fprintf(stderr,"Allocating %u bytes for c\n", size);
#endif
	c = (unsigned int*)malloc(size);
	if (NULL == c) {
	  fprintf(stderr,"Couldn't allocate memory!");
	  free (X);
	  free (Y);
	  free (b);
	  return -1;
	}



	// status report
#ifdef DEBUG
	fprintf(stderr, "Addresses: X@%u, Y@%u, xaddr=%u, yaddr=%u, b@%u, c@%u\n", (unsigned int) X, (unsigned int) Y,xaddr, yaddr, (unsigned int) b, (unsigned int) c);
	fprintf(stderr,"Given strings:\nX[1..%d]=%ls\nY[1..%d]=%ls\n", mX, (wchar_t*) xaddr, nY, (wchar_t*) yaddr);
#endif
	
	// initialize the b and c fields
#ifdef DEBUG
	fprintf(stderr, "Initializing...");
#endif
	
	memset(c, 0, mT*nT*sizeof(unsigned int));
	memset(b, 0, mT*nT*sizeof(LCSMarker));
	b[0] = FINAL;

#ifdef DEBUG
	fprintf(stderr, "done.\n");
#endif


	// ----- this is the central part -----
	// -        calculate the LCS         -
	// ------                        ------
	calcLCS(   Xels, Yels,
		   X, Y, 
		   b, c, 
		   sizeof(wchar_t), compWCHAR_T);
	// ------------------------------------



	// print the various tables
#ifdef DEBUG
	// print the b table
	fprintf(stderr,"b:\n");
	for (i=0; i<=mT; i++) {
	  for (j=0; j<nT; j++) {
	    int pos = calcArrayPos(mT,nT,i,j);
	    fprintf(stderr,"%2d.",(int) b[pos]);
	  }
	  int pos = calcArrayPos(mT,nT,i,j);
	  fprintf(stderr,"%2d\n",(int) b[pos]);
	}
	fprintf(stderr,"\n");

	// print the c table
	fprintf(stderr,"c:\n");
	for (i=0; i<=mT; i++) {
	  for (j=0; j<nT; j++) {
	    int pos = calcArrayPos(mT,nT,i,j);
	    fprintf(stderr,"%2d.",(int) c[pos]);
	  }
	  int pos = calcArrayPos(mT,nT,i,j);
	  fprintf(stderr,"%2d\n",(int) c[pos]);
	}
	fprintf(stderr,"\n");


	// print the matching text parts
	fprintf(stderr,"graphical representation: ('-' ARROW_LEFT, '|' ARROW_UP, [glyph] ARROW_UP_LEFT)\n");
	for (i=0; i<=mT; i++) {
	  for (j=0; j<nT; j++) {
	    int pos = calcArrayPos(mT,nT,i,j);
	    if (ARROW_UP_LEFT == b[pos]) {
	      fprintf(stderr,"%lc", X[i]);
	    }
	    else if (ARROW_UP == b[pos]) {
	      fprintf(stderr,"|");
	    }
	    else if (FINAL != b[pos]) {
	      fprintf(stderr,"-");
	    }
	    else {
	      fprintf(stderr,"!");
	    }
	  }
	  fprintf(stderr,"\n");
	}
	fprintf(stderr,"\n");
#endif

	// print the resulting LCS
#ifdef DEBUG
	fprintf(stderr, "LCS:\n");
#endif
	printLCS(mT,nT,X,Y,b,c,mX,nY);
	fprintf(stdout, "\n");

	// clean up before exiting
#ifdef DEBUG
	fprintf(stderr, "Cleaning up...");
	fprintf(stderr, "Freeing: c@%u\n",(unsigned int) c);
#endif
	free (c);
#ifdef DEBUG
	fprintf(stderr, "Freeing: b@%u\n",(unsigned int) b);
#endif
	free (b);
#ifdef DEBUG
	fprintf(stderr, "Freeing: Y@%u\n",(unsigned int) Y);
#endif
	free (Y);
#ifdef DEBUG
	fprintf(stderr, "Freeing: X@%u\n",(unsigned int) X);
#endif
	free (X);	
#ifdef DEBUG
	fprintf(stderr, "done.\n");
#endif

	return 0;
}
