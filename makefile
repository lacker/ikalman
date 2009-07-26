CC = gcc
CFLAGS = -g -O2 -std=c99
OBJECTS = matrix.o kalman.o gps.o

%_test : %_test.o $(OBJECTS)
	$(CC) $(CFLAGS) $< $(OBJECTS) -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm *.o *_test