PHONY. = all proj clean

CC = xc8

SRCS := $(wildcard src/*.c)

CHIP = --chip=16f887

all: proj

proj: ${SRCS}
	${CC} ${CHIP} $<

clean:
	rm *.as
	rm *.cmf
	rm *.d
	rm *.lst
	rm *.obj
	rm *.p1
	rm *.pre
	rm *.rlf
	rm *.sdb
	rm *.sym