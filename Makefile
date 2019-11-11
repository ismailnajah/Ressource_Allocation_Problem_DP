all: bin/ bin/main.o bin/CSV_Parser.o bin/data_structures.o
	gcc -o "bin/main" "bin/main.o" "bin/CSV_Parser.o" bin/data_structures.o -Wall -Werror

bin/ :
	[ -d bin ] || mkdir -p bin

bin/main.o: src/main.c
	gcc -c "src/main.c" -o bin/main.o -Wall -g -Werror

bin/CSV_Parser.o: src/CSV_Parser.c
	gcc -c "src/CSV_Parser.c" -o bin/CSV_Parser.o -Wall -g -Werror

# TODO this is added for testing puposes :
test : bin/CSV_Parser.o bin/data_structures.o bin/maintest.o 
	gcc -o bin/maintest bin/maintest.o bin/CSV_Parser.o bin/data_structures.o -Wall 

bin/data_structures.o : src/data_structures.c
	gcc -c src/data_structures.c -o bin/data_structures.o -Wall -g -Werror

bin/maintest.o : src/maintest.c
	gcc -c src/maintest.c -o bin/maintest.o -Wall -g -Werror