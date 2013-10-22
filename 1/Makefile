all:	sekwencyjny wspolbiezny

sekwencyjny:
	gcc -Wall s.c -o s.o -lrt

wspolbiezny:
	mpicc -Wall w.c -o w.o -lrt

clean:
	rm -f *.o

test:
	./s.o 16 t
	mpirun -np 2 ./w.o 16 t
	mpirun -np 4 ./w.o 16 t
	mpirun -np 8 ./w.o 16 t
	./s.o 64 t
	mpirun -np 2 ./w.o 64 t
	mpirun -np 4 ./w.o 64 t
	mpirun -np 8 ./w.o 64 t
	./s.o 256 t
	mpirun -np 2 ./w.o 256 t
	mpirun -np 4 ./w.o 256 t
	mpirun -np 8 ./w.o 256 t
	./s.o 1024 t
	mpirun -np 2 ./w.o 1024 t
	mpirun -np 4 ./w.o 1024 t
	mpirun -np 8 ./w.o 1024 t
