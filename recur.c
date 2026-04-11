#include "extern.h"
#include <math.h>

#define HEIGHTFACTOR (float)0.2
#define MINSCALE 5

int findscale(rect st) {
	int w = st.br.x - st.tl.x;
	int h = st.br.y - st.tl.y;
	return min(w,h);
}

void tweakheight(map sheet, position p, int scale) {
	float dz = gprand();
	debug("#tweakheight: x=%d y=%d scale=%d orig=%d ", p.x, p.y, scale, height(sheet,p));
	int change = round((float)scale * HEIGHTFACTOR * (dz - 0.5));
	debug("dz=%f change=%d\n", dz, change);
	output(sheet,p,height(sheet,p) + change);
}

void stripex(map sheet, position from, position to) {
	int quadz = height(sheet,from);
	int endz = height(sheet,to);
	int xrange = to.x - from.x;
	int zrange = endz - quadz;
	float step = (float)zrange / (float)xrange;

	debug("#stripex: from=%d,%d to=%d,%d quadz=%d endz=%d step=%f\n", from.x, from.y, to.x, to.y, quadz, endz, step);

	for (int i = 1; i < xrange-1; ++i) {
		position spot = (position){.x=from.x + i,.y=from.y};
		int h = height(sheet,spot);
		float change = ((float)i) * step;
		int newz = quadz + round(change);
		debug("#stripex: spot=%d,%d old=%d change=%f new=%d\n", spot.x, spot.y, h, change, newz);
		output(sheet, spot, newz);
	}
}

void stripey(map sheet, position from, position to) {
	int quadz = height(sheet,from);
	int endz = height(sheet,to);
	int yrange = to.y - from.y;
	int zrange = endz - quadz;
	float step = (float)zrange / (float)yrange;

	debug("#stripey: from=%d,%d to=%d,%d quadz=%d endz=%d step=%f\n", from.x, from.y, to.x, to.y, quadz, endz, step);

	for (int i = 1; i < yrange-1; ++i) {
		position spot = (position){.x=from.x,.y=from.y + i};
		int h = height(sheet,spot);
		float change = ((float)i) * step;
		int newz = quadz + round(change);
		debug("#stripey: spot=%d,%d old=%d change=%f new=%d\n", spot.x, spot.y, h, change, newz);
		output(sheet, spot, newz);
	}
}

// 'level' a rectangle to form a smooth (albeit curved) plane between the dour corners
void align_rect(map sheet,rect st) {
	debug("#align: st=%d,%d - %d,%d\n", st.tl.x,st.tl.y,st.br.x,st.br.y);

	// fill in side edges
	stripey(sheet, st.tl, (position){.x=st.tl.x,.y=st.br.y});
	stripey(sheet, (position){.x=st.br.x,.y=st.tl.y}, st.br);
	// dump(sheet,st,"stripey");

	// sweep down filling in rows
	for (int i = st.tl.y; i <= st.br.y; ++i) {
		position from = (position){.x=st.tl.x,.y=i};
		position to = (position){.x=st.br.x,.y=i};
		stripex(sheet, from, to);
	}

// char buf[32];
// sprintf(buf,"align=%d,%d-%d,%d",st.tl.x, st.tl.y, st.br.x, st.br.y);
// dump(sheet,st,buf);
}

position findmiddle(rect st) {
	int w = st.br.x - st.tl.x;
	int h = st.br.y - st.tl.y;

	return (position){.x = st.tl.x + w / 2, .y = st.tl.y + h / 2};
}

// find the middle point and adjust its height by a proportionate random amount
position adjust_middle(map sheet,rect st) {
	position middle = findmiddle(st);
	int scale = findscale(st);
	tweakheight(sheet, middle, scale);

	return middle;
}

void subrect(map sheet,rect quad) {
	align_rect(sheet,quad);
	recur(sheet, quad);

// char buf[32];
// sprintf(buf,"quad=%d,%d-%d,%d",quad.tl.x, quad.tl.y, quad.br.x, quad.br.y);
// dump(sheet,quad,buf);
}

// given a 'levelled' rectangle and an adjusted midddle point,
// split it into four quadrants and repeat the process
void recur(map sheet,rect quad) {
	// debug("#recur: from=%d,%d to=%d,%d\n", quad.tl.x, quad.tl.y, quad.br.x, quad.br.y);

	int scale = findscale(quad);
	if (scale > MINSCALE) {
		position middle = adjust_middle(sheet,quad);
		// debug("#recur: middle=%d,%d\n", middle.x, middle.y);

		subrect(sheet, (rect){.tl=quad.tl,.br=middle});
		subrect(sheet, (rect){.tl=(position){.x=middle.x+1,.y=quad.tl.y},.br=(position){.x=quad.br.x,.y=middle.y}});
		subrect(sheet, (rect){.tl=(position){.x=quad.tl.x,.y=middle.y+1},.br=(position){.x=middle.x,.y=quad.br.y}});
		subrect(sheet, (rect){.tl=(position){.x=middle.x+1,.y=middle.y+1},.br=quad.br});
	} else {
		// debug("#recur: quad %d,%d-%d,%d too small, stopping here\n", quad.tl.x, quad.tl.y, quad.br.x, quad.br.y);
	}
}

void init_corners(map sheet,rect quad,int size) {
	int scale = size * 5;
	tweakheight(sheet,quad.tl,scale);
	tweakheight(sheet,(position){.x=quad.br.x,.y=quad.tl.y},scale);
	tweakheight(sheet,(position){.x=quad.tl.x,.y=quad.br.y},scale);
	tweakheight(sheet,quad.br,scale);
}

void create(map sheet,rect quad,int size) {
	init_corners(sheet,quad,size);
 // dump(sheet,quad,"corners");
 	align_rect(sheet,quad);
	recur(sheet,quad);
}
