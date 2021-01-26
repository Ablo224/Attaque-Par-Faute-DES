NOM=ABDOULAYE_BALDE
CFLAGS=-c -g -Wall


main:main.o solovayStrassen.o mesFonctions.o
	gcc main.o solovayStrassen.o mesFonctions.o -o run -lgmp

main.o: main.c solovayStrassen.h
	gcc $(CFLAGS) main.c -lgmp

solovayStrassen.o: solovayStrassen.c 
	gcc $(CFLAGS) solovayStrassen.c -lgmp

mesFonctions.o: mesFonctions.c 
	gcc $(CFLAGS) mesFonctions.c -lgmp


clean:
	rm -rf *.o
	rm -rf run
