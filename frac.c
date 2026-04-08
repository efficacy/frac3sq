#include "extern.h"

#define BUFLEN 30

int main() {
    int seed, size, times;
    char buf[BUFLEN];
    map worksheet;
    rect* start = (rect*) malloc(sizeof(rect) + 1);

    tellme("--------frac3 v3.0 (rect)--------\n");

#ifdef DEBUG
	seed = 123;
#else
    do tellme("seed: "); while (fgets(buf,BUFLEN,stdin) == NULL);
    seed = atoi(buf);
#endif
    srand(seed);

#ifdef DEBUG
	size = 20;
#else
    do tellme("size: "); while (fgets(buf,BUFLEN,stdin) == NULL);
    size = atoi(buf);
#endif
	worksheet = allocate(size);

#ifdef DEBUG
	times = 1;
#else
    do tellme("times: "); while (fgets(buf,BUFLEN,stdin) == NULL);
    times = atoi(buf);
#endif

// debug("seed=%d, size=%d, times=%d\n", seed, size, times);
    setup(worksheet,start,size);
    while (times--) {
        recur(worksheet,start,size);
        finaldump(worksheet,size);
    }

    return 0;
}
