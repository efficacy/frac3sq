#include "extern.h"

#define HEIGHTFACTOR (float)0.5

int findscale(rect* st) {
	int w = st->tr.x - st->tl.x;
	int h = st->bl.y - st->tl.y;
	return min(w,h);
}

void tweakheight(map sheet, position p, int scale) {
	float dz = gprand();
	// debug("tweakheight: x=%d y=%d scale=%d orig=%d ", p.x, p.y, scale, height(sheet,p));
	int change = (int)((float)scale * HEIGHTFACTOR * (dz - 0.5));
	// debug("dz=%f change=%d\n", dz, change);
	output(sheet,p,height(sheet,p) + change);
}

void stripex(map sheet, position from, position to) {
	int startz = height(sheet,from);
	int endz = height(sheet,to);
	int xrange = to.x - from.x;
	int zrange = endz - startz;
	float step = (float)zrange / (float)xrange;

	// debug("stripex: from=%d,%d to=%d,%d startz=%d endz=%d step=%f\n", from.x, from.y, to.x, to.y, startz, endz, step);

	for (int i = 1; i < xrange; ++i) {
		float change = ((float)i) * step;
		output(sheet, (position){.x=from.x + i,.y=from.y}, (int) ((float)startz + change));
	}
}

void stripey(map sheet, position from, position to) {
	float startz = height(sheet,from);
	float endz = height(sheet,to);
	int yrange = to.y - from.y;
	int zrange = endz - startz;

	float step = (float)zrange / (float)yrange;
	for (int i = 1; i < yrange; ++i) {
		output(sheet, (position){.x=from.x,.y=from.y + i}, (int) (startz + ((float)i) * step));
	}
}

// 'level' a rectangle to form a smooth (albeit curved) plane between the dour corners
void align_rect(map sheet,rect* st) {
	// fill in side edges
	stripey(sheet, st->tl, st->bl);
	stripey(sheet, st->tr, st->br);

	// sweep down filling in rows
	for (int i = st->tl.y; i < st->bl.y; ++i) {
		position from = (position){.x=st->tl.x,.y=i};
		position to = (position){.x=st->tr.x,.y=i};
		stripex(sheet, from, to);
	}
}

// find the middle point and adjust its height by a proportionate random amount
position adjust_middle(map sheet,rect* st) {
	position middle;
	int scale = findscale(st);
	int w = st->tr.x - st->tl.x;
	int h = st->bl.y - st->tl.y;

	middle.x = st->tl.x + w / 2;
	middle.y = st->tl.y + h / 2;

	tweakheight(sheet, middle, scale);

	return middle;
}

// given a 'levelled' rectangle and an adjusted midddle point,
// split it into four quadrants and repeat the process
void recur(map sheet,rect* start)
{
// 	float dy = gprand(); float dx = gprand(); float dz = gprand();
	align_rect(sheet,start);
// 	position middle = adjust_middle(worksheet,start,size);

// 	// split into four sub-rects
// 	// if any are too small, special case them, otherwise
// 	// pass each sub-rect to recur

//     position tm,bm,lm,rm;
//     rect *temp = (rect*) malloc(sizeof(rect)+1);
//     int xrange,yrange,zrange,x,y,z;

//     // debug("recur zr=%d\n", zr);
//     // debug("tl: x=%d y=%d\n", st->tl.x, st->tl.y);
//     // debug("tr: x=%d y=%d\n", st->tr.x, st->tr.y);
//     // debug("bl: x=%d y=%d\n", st->bl.x, st->bl.y);
//     // debug("br: x=%d y=%d\n", st->br.x, st->br.y);

//     xrange = diff(st->tl.x,st->tr.x);
//     yrange = diff(st->tl.y,st->bl.y);
//     zrange = (xrange * yrange) / 2;

//     // debug("new ranges: x=%d y=%d z=%d\n", xrange, yrange, zrange);

//     x = (int) xrange * dx;
//     y = (int) yrange * dy;
//     z = (int) zr * (dz - 0.5);

//     tm.x = min(st->tl.x,st->tr.x) + x;
//     tm.y = st->tl.y;
//     tm.z = interp(st->tl.z,st->tr.z,dx);
//     bm.x = tm.x;
//     bm.y = st->bl.y;
//     bm.z = interp(st->bl.z,st->br.z,dx);
//     lm.x = st->tl.x;
//     lm.y = min(st->tl.y,st->bl.y) + y;
//     lm.z = interp(st->tl.z,st->bl.z,dy);
//     rm.x = st->tr.x;
//     rm.y = lm.y;
//     rm.z = interp(st->tr.z,st->br.z,dy);

//     middle.x = tm.x;
//     middle.y = lm.y;
//     middle.z = z + (interp(lm.z,rm.z,dx) + interp(tm.z,bm.z,dy)) / 2;

//     if ((xrange <= 1) || (yrange <=1 )) {
//         output(sheet,middle);
//         return;
//     }

//     recur(sheet, mkrect(temp,st->tl,tm,lm,middle),zrange);
//     recur(sheet, mkrect(temp,tm,st->tr,middle,rm),zrange);
//     recur(sheet, mkrect(temp,lm,middle,st->bl,bm),zrange);
//     recur(sheet, mkrect(temp,middle,rm,bm,st->br),zrange);

//     free((char*)temp);
}

void init_corners(map sheet,rect* start,int size) {
	tweakheight(sheet,start->tl,size);
	tweakheight(sheet,start->tr,size);
	tweakheight(sheet,start->bl,size);
	tweakheight(sheet,start->br,size);
}

void create(map sheet,rect* start,int size) {
	init_corners(sheet,start,size);
	recur(sheet,start);
}
