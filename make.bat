IF NOT EXIST bin mkdir bin
gcc -c "src/main.c" -o bin/main.o 
gcc -c "src/CSV_Parser.c" -o bin/CSV_Parser.o 
gcc -c "src/dyn_max_iterative.c" -o bin/dyn_max_iterative.o 
gcc -c "src/dyn_max_recurcive.c" -o bin/dyn_max_recurcive.o 
gcc -c "src/bruteforce.c" -o bin/bruteforce.o 
gcc -o "bin/main" "bin/main.o" "bin/CSV_Parser.o" "bin/dyn_max_iterative.o" "bin/dyn_max_recurcive.o" "bin/bruteforce.o"