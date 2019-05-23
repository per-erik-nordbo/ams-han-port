PROGS=test_rx gen-fcs conv hex aes-test tst tst2 tst3 sender receiver tm tm2 tm3 sizeof
CFLAGS=-Wall -Wextra -O2
LIBS=-lm

# /dev/ttyAMA0 - RPi3 UART
# /dev/ttyS0 - ??
# /dev/ttyUSB0 - Raspian USB UART ADAPTER

all: $(PROGS)

test_rx: read.c rs232.c fcs.c
	gcc -o test_rx -D SERIAL_PORT='"/dev/ttyUSB0"' $(CFLAGS) read.c rs232.c fcs.c aes.c $(LIBS)

sender: sender.c
	gcc -o sender $(CFLAGS) sender.c

receiver: receiver.c
	gcc -o receiver $(CFLAGS) receiver.c

gen-fcs: gen-fcs.c
	gcc -o gen-fcs $(CFLAGS) gen-fcs.c

tst: tst.c fcs.c
	gcc -o tst $(CFLAGS) tst.c fcs.c

tst2: tst2.c
	gcc -o tst2 $(CFLAGS) tst2.c

tst3: tst3.c rs232.c
	gcc -o tst3 $(CFLAGS) tst3.c rs232.c

conv: conv.c
	gcc -o conv $(CFLAGS) conv.c

hex: hex.c
	gcc -o hex $(CFLAGS) hex.c

aes-test: aes-test.c aes.c
	gcc -o aes-test $(CFLAGS) aes-test.c aes.c

tm: tm.c
	gcc -o tm tm.c
	gcc -o aes-test $(CFLAGS) aes-test.c aes.c $(LIBS)

tm2: tm2.c
	gcc -o tm2 $(CFLAGS) tm2.c $(LIBS)

tm3: tm3.c
	gcc -o tm3 $(CFLAGS) tm3.c $(LIBS)

sizeof: sizeof.c
	gcc -o sizeof $(CFLAGS) sizeof.c

clean:
	rm -f *.o $(PROGS) *.exe

CLEAN: clean
	rm -f *~ \#*

