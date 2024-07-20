.PHONY: run

run: ./bin/test.exe
	./bin/test.exe

./bin/test.exe: ./obj/os_terminal.o ./obj/main.o ./obj/ansi_codes.o
	gcc $^ -o ./bin/test.exe

./obj/main.o: ./src/main.c
	gcc -I ./include -c ./src/main.c -o ./obj/main.o

./obj/os_terminal.o: ./src/os_terminal.c
	gcc -I ./include -c ./src/os_terminal.c -o ./obj/os_terminal.o

./obj/ansi_codes.o: ./src/ansi_codes.c
	gcc -I ./include -c ./src/ansi_codes.c -o ./obj/ansi_codes.o
