targets = vector_test vector_test.o vector.o

vector_test: vector.o vector_test.o 
	gcc -o vector_test vector.o vector_test.o

vector_test.o: vector_test.c 
	gcc -c vector_test.c

vector.o: vector.c 
	gcc -c vector.c

.PHONY: test 

test: vector_test
	./vector_test

MEMCHECK=valgrind --tool=memcheck --leak-check=full --track-origins=yes
VECTOR_PROG=vector_test

vector-memcheck: $(VECTOR_PROG)
	$(MEMCHECK) ./$(VECTOR_PROG)


clean: 
	-rm $(targets)
