
# makfile configuration
COMMON_OBJECTS  = main.o 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: button.elf 

#additional rules for files
button.elf: ${COMMON_OBJECTS} ../11-buzzer-change-tone/buzzer.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ../../demos/lib/libTimer.a
load: button.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

buzzer.o: buzer.h

