#!/bin/bash -x

ifndef $(MSPGCCDIR)
	MSPGCCDIR=$(HOME)/ti/msp430-gcc
endif

SUPPORT_FILE_DIRECTORY = $(MSPGCCDIR)/include
OTHER_INCLUDE = include

DDEVICE_ID = 1

DEVICE  = msp430fr5994
CC      = $(MSPGCCDIR)/bin/msp430-elf-g++
GDB     = msp430-elf-gdb

CSTD_FLAGS = -std=c++11 -funsigned-char
DEBUG_FLAGS = -g -g3 -ggdb -gdwarf-2
ERROR_FLAGS = -Wall -Wextra -Wshadow -Wfatal-errors
NO_ERROR_FLAGS = -Wno-unused-parameter -Wno-unknown-pragmas -Wno-unused-variable -Wno-type-limits -Wno-comment
MSP430_FLAGS = -mmcu=$(DEVICE) -mhwmult=f5series
REDUCE_SIZE_FLAGS = -O0

CXXFLAGS = -I $(SUPPORT_FILE_DIRECTORY) $(CSTD_FLAGS) $(DEBUG_FLAGS) $(ERROR_FLAGS) $(NO_ERROR_FLAGS) $(MSP430_FLAGS) $(REDUCE_SIZE_FLAGS)
LFLAGS = -L $(SUPPORT_FILE_DIRECTORY)
VPATH = $(OTHER_INCLUDE)

OBJ = cc1101.o serialmonitor.o

all: $(OBJ) basestation_receive.c
	$(CC) $(CXXFLAGS) -DDEVICE_ID=$(DDEVICE_ID) $(LFLAGS) $^ -o basestation_receive.elf

cc1101.o : cc1101.c
	$(CC) -c $(CXXFLAGS) $(LFLAGS) $< -o $@

serialmonitor.o : serialmonitor.c
	$(CC) -c $(CXXFLAGS) $(LFLAGS) $< -o $@


install: all
	mspdebug tilib "prog basestation_receive.elf" --allow-fw-update

debug: all
	gdb_agent_console /opt/ti/gcc/msp430.dat

gdb:
	$(GDB) basestation_receive.elf

clean:
	rm -f *.elf *.asm *.o
