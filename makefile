crypt: crypt.c
	gcc -Wall -o onetimepad crypt.c

clean:
	rm -f onetimepad
	rm -f *.o
