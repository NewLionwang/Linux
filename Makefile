test:test.o
	gcc test.o -o test
test.o:test.s
	gcc -c test.s -o test.o
test.s:test.i
	gcc -S test.i -o test.s
test.i:test.c
	gcc -E test.c -o test.i
.PHONY:clean
clean:
	rm test.i test.o test.s test
