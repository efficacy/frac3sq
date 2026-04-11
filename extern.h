#include "frac.h"

extern float gprand();
extern void init(map sheet,int size);
extern rect setup(map sheet,int size);
extern void create(map sheet,rect start,int size);
extern void output(map sheet,position point,int z);
extern void dump(map sheet,rect sq,char* note);

extern int height(map sheet, position point);

extern int min(int a,int b);
extern int diff(int a,int b);
extern int interp(int a,int b,float delta);
extern map allocate(int size);
extern rect * mkrect(rect* res,position tl,position tr,position bl,position br);
extern void recur(map sheet,rect st);
