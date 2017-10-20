
C := gcc
PROGRAM = camacusb
SRC := main.c

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

CFLAGS := -I./include -Wall -Wno-write-strings  -g -ggdb 
LDFLAG := $(GTKLIB) -l usb-1.0

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(C) $(CFLAGS) $(SRC) $(LDFLAG) -o $(PROGRAM)

clean:
	rm -fr $(PROGRAM) $(PROGRAM).o

