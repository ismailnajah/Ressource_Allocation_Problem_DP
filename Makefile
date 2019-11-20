all: bin/ bin/main.o bin/CSV_Parser.o bin/dyn_max_iterative.o bin/dyn_max_recurcive.o bin/bruteforce.o
	gcc -o "bin/main" "bin/main.o" "bin/CSV_Parser.o" "bin/dyn_max_iterative.o" "bin/dyn_max_recurcive.o" "bin/bruteforce.o"

bin/ :
	[ -d bin ] || mkdir -p bin

bin/main.o: src/main.c
	gcc -c "src/main.c" -o bin/main.o 

bin/CSV_Parser.o: src/CSV_Parser.c
	gcc -c "src/CSV_Parser.c" -o bin/CSV_Parser.o 

bin/dyn_max_iterative.o : src/dyn_max_iterative.c
	gcc -c "src/dyn_max_iterative.c" -o bin/dyn_max_iterative.o 
	
bin/dyn_max_recurcive.o : src/dyn_max_recurcive.c
	gcc -c "src/dyn_max_recurcive.c" -o bin/dyn_max_recurcive.o 

bin/bruteforce.o : src/bruteforce.c
	gcc -c "src/bruteforce.c" -o bin/bruteforce.o 