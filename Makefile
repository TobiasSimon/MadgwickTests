CC=gcc
CFLAGS=-O3
LIBS=-lm

DEPS = MadgwickAHRS.h
OBJ = test.o MadgwickAHRS.o

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o test
