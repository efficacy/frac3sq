#include "extern.h"

#define BUFLEN 30

int main(int argc, char** argv) {
    int seed, size, times;
    char buf[BUFLEN];

    tellme("--------frac3 v3.0 (2026)--------\n");

    if (argc > 1) {
    	size = atoi(argv[1]);
    } else {
#ifdef DEBUG
		size = 20;
#else
        do tellme("size: "); while (fgets(buf,BUFLEN,stdin) == NULL);
        size = atoi(buf);
#endif
    }

    if (argc > 2) {
    	size = atoi(argv[2]);
    } else {
#ifdef DEBUG
		times = 1;
#else
        do tellme("times: "); while (fgets(buf,BUFLEN,stdin) == NULL);
        times = atoi(buf);
#endif
    }

    if (argc > 3) {
    	size = atoi(argv[3]);
    } else {
#ifdef DEBUG
		seed = 123;
#else
	    do tellme("seed: "); while (fgets(buf,BUFLEN,stdin) == NULL);
	    seed = atoi(buf);
#endif
    }

    srand(seed);
    map sheet = allocate(size);

// debug("main: seed=%d, size=%d, times=%d\n", seed, size, times);
    rect st = setup(sheet,size);
// debug("after setup: st=%d,%d-%d,%d\n", st.tl.x,st.tl.y, st.br.x,st.br.y);

    while (times--) {
        create(sheet,st,size);
        dump(sheet,st,"final");
    }

    return 0;
}
