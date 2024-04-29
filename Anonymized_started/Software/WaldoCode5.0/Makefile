ifndef $(MSPGCCDIR)
	MSPGCCDIR=$(HOME)/ti/msp430-gcc
endif

NAME		=  main2
SOURCES 	=  $(wildcard *.c)
OBJECTS 	=  $(patsubst %.c,%.o,$(SOURCES))
EXE 		=  $(NAME).out
CC          = msp430-elf-gcc
DEVICE  	= msp430fr5994
GDB     	= msp430-elf-gdb

#paths
SUPPORT_FILE_DIRECTORY = $(MSPGCCDIR)/include

# GCC flags
CSTD_FLAGS 			= -funsigned-char -std=c99
DEBUG_FLAGS 		= -g3 -ggdb -gdwarf-2
ERROR_FLAGS 		= -Wall -Wextra -Wshadow -fmax-errors=5
NO_ERROR_FLAGS 		= -Wno-unused-parameter -Wno-unknown-pragmas -Wno-unused-variable -Wno-type-limits -Wno-comment
LIB_INCLUDES 		= -I $(MSPGCC_ROOT)/../include/ -I. -I $(SUPPORT_FILE_DIRECTORY) -I /Users/hsdesai/persist-msplib/msplib/src/ -I /Users/hsdesai/persist-msplib/msplib/src/hw/ -I /Users/hsdesai/persist-msplib/msplib/src/hw/chips/
MSP430_FLAGS 		= -mmcu=$(DEVICE) -mhwmult=none -D__$(DEVICE)__ -DDEPRECATED -mlarge
REDUCE_SIZE_FLAGS	= -fdata-sections -ffunction-sections -finline-small-functions -O2
#MSPSIM			= -D__MSPSIM__
CFLAGS 			= $(CSTD_FLAGS) $(DEBUG_FLAGS) $(ERROR_FLAGS) $(NO_ERROR_FLAGS) $(LIB_INCLUDES) $(MSP430_FLAGS) $(REDUCE_SIZE_FLAGS) $(MSPSIM)

LFLAGS 			= -Wl,--gc-sections -Wl,--reduce-memory-overheads -Wl,--stats -Wl,--relax
LIBS 			= -L $(MSPGCC_ROOT)/../include/ -L $(SUPPORT_FILE_DIRECTORY)

ID = 0

all: compile

$(NAME).o: $(NAME).c
	$(CC) $(CFLAGS) -c $(LFLAGS) $< -o $@

%.asm: %.c
	$(CC) $(CFLAGS) -S -fverbose-asm -c $< -o $@

# Change -o to $(DEVICE) when we need multiple devices
compile: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LFLAGS) -DDEVICEID=$(ID) -o $(EXE) $(LIBS)

install: all
	mspdebug tilib "prog $(EXE)" --allow-fw-update

debug: all
	mspdebug tilib gdb &

gdb:
	rm -f gdb.cmd
	printf "file main.out\ntarget remote localhost:2000\nbreak main\nload main.out\nc\n" >> gdb.cmd
	$(GDB) -x gdb.cmd

mem-dump:
	mspdebug tilib "md 0x10000 100" --allow-fw-update

clear:
	mspdebug tilib "mw 0x10000 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00" --allow-fw-update

clean:
	rm -rf $(OBJECTS) *.asm
	rm -f $(EXE)
	rm -f gdb.cmd
