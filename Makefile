1xor:
	gcc -Wall -o 1xor 1xor.c
	strip 1xor

clean:
	rm -rf *~ core 1xor ??
