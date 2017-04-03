xor:
	gcc -o xor xor.c
	strip xor

clean:
	rm -rf *~ core xor ??
