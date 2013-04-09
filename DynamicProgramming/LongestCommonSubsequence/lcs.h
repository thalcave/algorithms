#ifndef _LCS_
#define _LCS_

// --- INCLUDES ---
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <wchar.h>
#include <locale.h>


// --- TYPEDEFS, CONSTS ETC. ---

typedef enum {
  NOTHING       = 0,
  ARROW_UP      = 1,
  ARROW_LEFT    = 2,
  ARROW_UP_LEFT = 3,
  FINAL         = 4
} LCSMarker;



// --- PROTOTYPES ---
void calcLCS( int mX, int nY, void* X, void* Y, LCSMarker* b, unsigned int* c, int elSize, int (*compareFunc)(const void*, const void*));


#endif
