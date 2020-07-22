gcc -c linklist.c -o linklist.o

ar rcs linklist.a linklist.o

gcc main.c linklist.a -o linklist.out

./linklist.out

