CFLAGS= -g -Wall -pedantic -std=c99
LDFLAGS= -g
LDLIBS= -lpthread -lm

all: test-p1

test-p1.o p1.o: p1.h
test-p1.o: test-p1.c
	gcc -g -c -Wall -std=gnu99 test-p1.c

test-p1: test-p1.o p1.o
test-p1-g:
	make clean
	make test-p1
	./test-p1

test-p2.o p2.o: p2.h
test-p2: test-p2.o p2.o
test-p2-g:
	make clean
	make test-p2
	./test-p2

test-p2-vg:
	make clean
	make test-p2
	valgrind --leak-check=full --track-origins=yes ./test-p2

test-p2-vg-ddd:
	make clean
	make test-p2
	valgrind --leak-check=full --track-origins=yes --vgdb=yes --vgdb-error=0 ./test-p2

test-p3.o p3.o: p3.h
test-p3: test-p3.o p3.o
test-p3-g:
	make clean
	make test-p3
	./test-p3

test-p3-vg:
	make clean
	make test-p3
	valgrind --leak-check=full --track-origins=yes ./test-p3

test-p3-vg-ddd:
	make clean
	make test-p3
	valgrind --leak-check=full --track-origins=yes --vgdb=yes --vgdb-error=0 ./test-p3

rotar: rotar.c

test-rotar-g:
	make clean
	make rotar
	cp noms-orig.txt noms.txt
	./rotar noms.txt 2 5 0 4
	@echo diff noms.txt noms-ref.txt
	@diff noms.txt noms-ref.txt && echo "Felicitaciones: test aprobado"

test-rotar-vg:
	make clean
	make rotar
	cp noms-orig.txt noms.txt
	valgrind --leak-check=full --track-origins=yes ./rotar noms.txt 2 5 0 4
	@echo diff noms.txt noms-ref.txt
	@diff noms.txt noms-ref.txt && echo "Felicitaciones: test aprobado"

test-rotar-vg-ddd:
	make clean
	make rotar
	cp noms-orig.txt noms.txt
	valgrind --leak-check=full --track-origins=yes --vgdb=yes --vgdb-error=0 ./rotar noms.txt 2 5 0 4
	@echo diff noms.txt noms-ref.txt
	@diff noms.txt noms-ref.txt && echo "Felicitaciones: test aprobado"

test-p5.o p5.o: p5.h
test-p5: test-p5.o p5.o
test-p5-g:
	make clean
	make test-p5
	./test-p5

test-p5-O:
	make clean
	make "CFLAGS=-O -std=c99 -Wall -pedantic" test-p5
	./test-p5

test-p5-vg:
	make clean
	make "CFLAGS=${CFLAGS} -DVALGRIND" test-p5
	valgrind --leak-check=full --track-origins=yes ./test-p5

test-p5-vg-ddd:
	make clean
	make "CFLAGS=${CFLAGS} -DVALGRIND" test-p5
	valgrind --leak-check=full --track-origins=yes --vgdb=yes --vgdb-error=0 ./test-p5

clean:
	rm -f *.o test-p1 test-p2 test-p3 rotar test-p5
