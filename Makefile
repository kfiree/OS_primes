all:
	gcc -c primeSlow.c
	gcc primeSlow.c -o solution -pthread -lm

clean:
	rm *.o sol2
