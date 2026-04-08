#include "extern.h"

void recur(map sheet,rect* st,int zr)
{
    position middle;
    position tm,bm,lm,rm;
    rect *temp = (rect*) malloc(sizeof(rect)+1);
    int xrange,yrange,zrange,x,y,z;
    float dy = gprand(); float dx = gprand(); float dz = gprand();

    debug("recur zr=%d\n", zr);
    debug("tl: x=%d y=%d\n", st->tl.x, st->tl.y);
    debug("tr: x=%d y=%d\n", st->tr.x, st->tr.y);
    debug("bl: x=%d y=%d\n", st->bl.x, st->bl.y);
    debug("br: x=%d y=%d\n", st->br.x, st->br.y);

    xrange = diff(st->tl.x,st->tr.x);
    yrange = diff(st->tl.y,st->bl.y);
    zrange = (xrange * yrange) / 2;

    debug("new ranges: x=%d y=%d z=%d\n", xrange, yrange, zrange);

    x = (int) xrange * dx;
    y = (int) yrange * dy;
    z = (int) zr * (dz - 0.5);

    tm.x = min(st->tl.x,st->tr.x) + x;
    tm.y = st->tl.y;
    tm.z = interp(st->tl.z,st->tr.z,dx);
    bm.x = tm.x;
    bm.y = st->bl.y;
    bm.z = interp(st->bl.z,st->br.z,dx);
    lm.x = st->tl.x;
    lm.y = min(st->tl.y,st->bl.y) + y;
    lm.z = interp(st->tl.z,st->bl.z,dy);
    rm.x = st->tr.x;
    rm.y = lm.y;
    rm.z = interp(st->tr.z,st->br.z,dy);

    middle.x = tm.x;
    middle.y = lm.y;
    middle.z = z + (interp(lm.z,rm.z,dx) + interp(tm.z,bm.z,dy)) / 2;

    if ((xrange <= 1) || (yrange <=1 )) {
        output(sheet,middle);
        return;
    }

    recur(sheet, mkrect(temp,st->tl,tm,lm,middle),zrange);
    recur(sheet, mkrect(temp,tm,st->tr,middle,rm),zrange);
    recur(sheet, mkrect(temp,lm,middle,st->bl,bm),zrange);
    recur(sheet, mkrect(temp,middle,rm,bm,st->br),zrange);

    free((char*)temp);
}
