
C := gcc
PROGRAM = camacusb
SRC := main.c
CFLAGS := -I./include -Wall -Wno-write-strings  -g -ggdb #-DANNIYING_DEBUG
LDFLAG := -l usb-1.0

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(C) $(CFLAGS) $(SRC) $(LDFLAG) -o $(PROGRAM)

clean:
	rm -fr $(PROGRAM) $(PROGRAM).o

