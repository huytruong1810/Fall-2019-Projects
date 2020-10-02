program.exe: main.o queueFunctions.o functions.o
	gcc -o program.exe main.o queueFunctions.o functions.o
main.o: main.c header.h
	gcc -c main.c
queueFunctions.o: queueFunctions.c header.h
	gcc -c queueFunctions.c
functions.o: functions.c header.h
	gcc -c functions.c