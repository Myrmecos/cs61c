ll_cycle.o: ll_cycle.c 
	gcc -c ll_cycle.c 
test_ll_cycle.o: test_ll_cycle.c 
	gcc -c test_ll_cycle.c 
test_ll_cycle: test_ll_cycle.o ll_cycle.o
	gcc -o test_ll_cycle test_ll_cycle.o ll_cycle.o

.PHONY: test clean
target = ll_cycle.o test_ll_cycle.o test_ll_cycle
test: test_ll_cycle
	./test_ll_cycle
clean:
	rm -f $(target)
