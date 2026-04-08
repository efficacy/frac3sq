## Generic Makefile -- v1.0
## NAME:			   frac3 - 3d terrain generator
## AUTHOR:			 F K Carver
## VERSION:			3.0
## DATE:			   19 Feb 1985

COMPILE=cc
# OPTIMISE=-O
DEBUGGING=-g -DDEBUG
CFLAGS=${OPTIMISE} ${DEBUGGING}

PROG=frac3
HEADERS=frac.h extern.h
SOURCEFILES=frac.c common.c recur.c

OFILES=${SOURCEFILES:.c=.o}
ALLFILES=${HEADERS} ${SOURCEFILES}

## Standard actions

${PROG} : ${OFILES} ${HEADERS} ${SOURCEFILES}
	${COMPILE} -o ${PROG} ${OFILES}

tidy:
	rm ${OFILES}
again:
	touch ${HEADERS} ${SOURCEFILES}
	make
lint:
	${SOURCEFILES} ${HEADERS}
	lint ${SOURCEFILES} |tee linterrs |more

## User actions

frac.o : frac.c ${HEADERS}
common.o : common.c ${HEADERS}
recur.o : recur.c ${HEADERS}
