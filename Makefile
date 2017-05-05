TARGETS = rng_c_example
DEPS    = pcg-c-0.94/extras/pcg_spinlock.h pcg-c-0.94/extras/entropy.h
OBJ     = rng_c_example.o pcg-c-0.94/extras/entropy.o

LDFLAGS = -L pcg-c-0.94/src/
LDLIBS  = -lpcg_random -lm
CC      = mpicc
INCLUDE = -I pcg-c-0.94/include -I pcg-c-0.94/extras
CFLAGS  = -std=c99

all: $(TARGETS)

clean:
	rm -f *.o $(TARGETS)

rng_c_example.o: rng_c_example.c $(DEPS)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $< 

rng_c_example: $(OBJ)
	$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@ 

run: $(TARGETS)
	mpirun -np 4 $(TARGETS)
