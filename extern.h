#include "frac.h"

extern float gprand();
extern int min(int a,int b);
extern int diff(int a,int b);
extern int interp(int a,int b,float delta);
extern void output(map sheet,position point);
extern void init(map sheet,int size);
extern void setup(map sheet,rect *st,int size);
extern void finaldump(map sheet,int size);
extern map allocate(int size);
extern rect * mkrect(rect* res,position tl,position tr,position bl,position br);
extern void recur(map sheet,rect* st,int zr);
