all:	sekwencyjny wspolbiezny

sekwencyjny:
	gcc -Wall s.c -o s.o -lrt

wspolbiezny:
	mpicc -Wall w.c -o w.o -lrt

clean:
	rm -f *.o

test:
	./s.o 4000 t
	mpirun -np 2 ./w.o 2000 t
	mpirun -np 4 ./w.o 1000 t
	mpirun -np 8 ./w.o 500 t
	./s.o 20000 t
	mpirun -np 2 ./w.o 10000 t
	mpirun -np 4 ./w.o 5000 t
	mpirun -np 8 ./w.o 2500 t
	./s.o 100000000 t
	mpirun -np 2 ./w.o 25000000 t
	mpirun -np 4 ./w.o 12500000 t
	mpirun -np 8 ./w.o 6250000 t
