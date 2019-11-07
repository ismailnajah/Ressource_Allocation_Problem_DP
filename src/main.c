#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "CSV_Parser.h"


#define URL_DEFAULT "test.csv"


/*
**  Small container that sets up the cashe buffer for dyn_max() -> returns the optimal f*
*/
int maximize_profite(Matrix r);
/*
**  dyn_max() takes activity + ressource + global variable Matrix matrix 
**  and returns the optimal value for activity machine given a part of the ressource
*/
int dyn_max(Matrix r,Matrix cache,int activity,int ressource);


int main(int argc, char* argv[]){
    // Configuring the input file
    char *url=(argc==2)? argv[1] : URL_DEFAULT ;

    // Opening The input file
    FILE *file ;
    if ( (file = fopen(url, "r") ) == NULL){
        perror("File");
        exit(EXIT_FAILURE);

    }//~ 
    
    // Loading the input table into the r(i, j) matrix
    Matrix r = getMatrix(file);  fclose(file);
    printf("## DATA Loaded ##\n");

    // Find the optimal f* for r 
    int optimal = maximize_profite(r);    freeMatrix(r);
    printf("Optimal value :  %d \n",optimal);

    return 0;
}//~ main()


int maximize_profite(Matrix r){
    //A 2D array that memorized optimal values, cache[activity][ressource] = f*(activity, ressource)
    Matrix cache = createMatrix(r->activities,r->ressource+1);
    int profit = dyn_max(r,cache,r->activities, r->ressource);
    freeMatrix(cache);
    return profit;
}

int dyn_max(Matrix r,Matrix cache,int activity,int ressource){
    if(activity==1){
        return r->values[activity-1][ressource];
    }
    
    int optimal=0, value;
    for(int i=0 ; i<=ressource ; i++) {
        if ( cache->values[activity-1][i] ){
            // the value already calculated
            value = cache->values[activity-1][i]; 
        }else{
            // calculate the value 
            value =  r->values[activity-1][i] + dyn_max(r,cache,activity-1,ressource-i);
        }
        if(optimal < value){
            optimal = value;
        }
    }
    cache->values[activity-1][ressource] = optimal;
    return optimal;
}