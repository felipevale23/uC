PHONY. = all proj clean build

CC = xc8

SRCS := $(wildcard src/*.c)
INCLUDES := $(wildcard src/*.h)
OBJS := $(patsubst %.c, %.obj, ${SRCS})

CHIP = --chip=16f887

all: main

main: ${SRCS} ${INCLUDES}
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

build:
	@echo Building 
	bash ./build.sh
