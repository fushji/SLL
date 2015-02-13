sll_example: sll.h sll.c
sll_example: sll.c sll_example.c
	$(CC) -Wall -W -Os -g -o sll_example sll.c sll_example.c
	@echo ">>> Type ./sll_example to run the sll.c example. File sll_example.log will be created"
clean:
	rm -f sll_example sll_example.log
