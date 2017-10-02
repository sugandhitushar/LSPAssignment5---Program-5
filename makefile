messageQueue: program.c program.h
	gcc -o messageQueue program.c

.PHONY: clean run
run:
	./messageQueue
clean:
	rm messageQueue
usage:
	@echo make
	@echo make run
