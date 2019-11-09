all: bin/ bin/main.o bin/CSV_Parser.o bin/dyn_max_withOP.o
	gcc -o "bin/main" "bin/main.o" "bin/CSV_Parser.o" "bin/dyn_max_withOP.o" -Wall

bin/ :
	[ -d bin ] || mkdir -p bin

bin/main.o: src/main.c
	gcc -c "src/main.c" -o bin/main.o -Wall -g

bin/CSV_Parser.o: src/CSV_Parser.c
	gcc -c "src/CSV_Parser.c" -o bin/CSV_Parser.o -Wall -g

bin/dyn_max_withOP.o : src/dyn_max_withOP.c
	gcc -c "src/dyn_max_withOP.c" -o bin/dyn_max_withOP.o -Wall -g
