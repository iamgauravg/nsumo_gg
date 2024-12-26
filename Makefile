######################################################################
# Toolchain
######################################################################
CC = msp430-elf-gcc
RM = rm
DEBUG = LD_LIBRARY_PATH=/home/gauravgupta/ti/ccs1281/ccs/ccs_base/DebugServer/drivers /home/gauravgupta/ti/ccs1281/ccs/ccs_base/DebugServer/bin/mspdebug

######################################################################
# Flags
######################################################################
CFLAGS = -mmcu=msp430fr2355 $(addprefix -I ,$(INCLUDE_DIRS)) -g3 -ggdb -gdwarf-2
LDFLAGS = -mmcu=msp430fr2355 $(addprefix -L ,$(LIB_DIRS))

######################################################################
# Directories
######################################################################
INCLUDE_GCC_DIR = /home/gauravgupta/ti/ccs1281/ccs/ccs_base/msp430/include_gcc/
INCLUDE_DIRS = $(INCLUDE_GCC_DIR)
LIB_DIRS = $(INCLUDE_GCC_DIR)
ROOT = .
BIN_DIR = $(ROOT)/bin
OBJ_DIR = $(ROOT)/obj
SRC_DIR = $(ROOT)/src


######################################################################
# Files
######################################################################
TARGET = blink
OBJECTS = blink.o
SOURCES = blink.c

######################################################################
# Build
######################################################################


$(TARGET): $(OBJECTS)
	@echo "Linking $^"
	$(CC) $(LDFLAGS) -o $@ $^

%.o: $(SRC_DIR)/%.c	
	@echo "Compilinging $^"
	$(CC) $(CFLAGS) -c -o $@ $^


######################################################################
# Phony targes
######################################################################

.PHONY: clean flash

clean:
	$(RM) $(TARGET) $(OBJECTS)

flash: $(TARGET)
	$(DEBUG) tilib "prog $(TARGET)"

