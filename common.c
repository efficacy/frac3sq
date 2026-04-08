#include "extern.h"

#define RANDFUDGE 10501

float gprand() {
    return ((rand() % RANDFUDGE) / (float) RANDFUDGE);
}

int min(int a,int b)
{
    return (a>b?b:a);
}

int diff(int a,int b)
{
    return (a>b?a-b:b-a);
}

int interp(int a, int b, float delta)
{
    return ((int)(delta * diff(a,b) + min(a,b)));
}

void output(map sheet,position point)
{
    sheet[point.x][point.y] += point.z;
}

map allocate(int size)
{
    int i, **res;

    res = (map) malloc((unsigned) ((size+1) * sizeof(int*)));
    for (i = 0; i < size; i++)
        res[i] = (int*) malloc((unsigned)((size+1) * sizeof(int)));
    return (res);
}

rect* mkrect(rect *res, position tl, position tr,position bl,position br)
{
    res->tl = tl;
    res->tr = tr;
    res->bl = bl;
    res->br = br;
    return (res);
}

void init(map sheet,int size)
{
    int x,y;

    for (y = 0; y < size; y++) {
	    for (x = 0; x < size; x++) {
	        sheet[x][y] = 0;
		}
    }
}

void finaldump(map sheet,int size)
{
    int x,y;
    printf("%5d%5d\n",size,size);
    for (y=0; y < size; y++) {
        for (x = 0; x < size; x++)
            printf("%4d",sheet[x][y]);
        putchar('\n');
    }
}

void setup(map sheet,rect* st,int size)
{
    init(sheet,size);
    st->tl.x = 1; st->tl.y = 1; st->tl.z = 1;
    st->tr.x = size-1; st->tr.y = 1; st->tr.z = 1;
    st->bl.x = 1; st->bl.y = size-1; st->bl.z = 1;
    st->br.x = size-1; st->br.y = size-1; st->br.z = 1;
}
