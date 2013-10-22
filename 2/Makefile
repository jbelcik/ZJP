all:	sekwencyjny wspolbiezny

sekwencyjny:
	gcc -Wall s.c -o s.o -lrt

wspolbiezny:
	mpicc -Wall w.c -o w.o -lrt

clean:
	rm -f *.o

test:
	./s.o 1000 t
	mpirun -np 2 ./w.o 1000 t
	mpirun -np 4 ./w.o 1000 t
	mpirun -np 8 ./w.o 1000 t
	./s.o 10000 t
	mpirun -np 2 ./w.o 10000 t
	mpirun -np 4 ./w.o 10000 t
	mpirun -np 8 ./w.o 10000 t
	./s.o 1000000 t
	mpirun -np 2 ./w.o 100000 t
	mpirun -np 4 ./w.o 100000 t
	mpirun -np 8 ./w.o 100000 t
