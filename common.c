#include "extern.h"

#define RANDFUDGE 10501

int height(map sheet, position point) {
	return sheet[point.x][point.y];
}

float gprand() {
    return ((rand() % RANDFUDGE) / (float) RANDFUDGE);
}

int min(int a,int b) {
    return (a>b?b:a);
}

int diff(int a,int b) {
    return (a>b?a-b:b-a);
}

int interp(int a, int b, float delta) {
    return ((int)(delta * diff(a,b) + min(a,b)));
}

void output(map sheet, position point, int z) {
    sheet[point.x][point.y] += z;
}

map allocate(int size) {
    int i, **res;

    res = (map) malloc((unsigned) ((size+1) * sizeof(int*)));
    for (i = 0; i < size; i++)
        res[i] = (int*) malloc((unsigned)((size+1) * sizeof(int)));
    return (res);
}

void init(map sheet,int size) {
    int x,y;

    for (y = 0; y < size; y++) {
	    for (x = 0; x < size; x++) {
	        sheet[x][y] = 0;
		}
    }
}

rect setup(map sheet,int size) {
    init(sheet,size);
    return (rect){
    	.tl = (position){.x=0,.y=0},
     	.br = (position){.x=size-1,.y=size-1}
    };
}

void dump(map sheet,rect sq,char* note) {
    fprintf(stderr,"=====%s\n",note);
    for (int y=sq.tl.y; y <= sq.br.y; ++y) {
        for (int x = sq.tl.x; x <= sq.br.x-1; ++x) {
            printf("%3d,",sheet[x][y]);
        }
        printf("%3d",sheet[sq.br.x][y]);
        putchar('\n');
    }
}
