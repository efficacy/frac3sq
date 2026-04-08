#include <stdio.h>
#include <stdlib.h>

typedef struct { int x, y, z; } position;
typedef struct { position tl, tr, bl, br; } rect;
typedef int** map;

#ifdef DEBUG
#define debug printf
#else
#define DEBUG (void)
#endif

#define tellme(something) fprintf(stderr, something)

extern float gprand();
