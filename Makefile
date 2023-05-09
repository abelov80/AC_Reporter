MYFILES = main.o my_func.o

main.exe: $(MYFILES)
	gcc -o main.exe $(MYFILES)

main.o: main.c my_func.c my_func.h
	gcc -g -std=c99 -Wall -E main.c -o main.i 
	gcc -g -std=c99 -Wall -S main.i -o main.s
	gcc -g -std=c99 -Wall -g3 -c main.c

my_func.o: my_func.c my_func.h
	gcc -g -std=c99 -Wall -E my_func.c -o my_func.i
	gcc -g -std=c99 -Wall -S my_func.i -o my_func.s
	gcc -g -std=c99 -Wall -g3 -c my_func.c

clean:
	del -rf *.i *.s *.o *.exe