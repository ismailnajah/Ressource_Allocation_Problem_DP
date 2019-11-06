#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "CSV_Parser.h"
 
/*
**  dyn_max() takes activity + ressource + global variable Matrix matrix 
**  and returns the optimal value for activity machine given a part of the ressource
*/
int dyn_max(Matrix r,Matrix cache,int activity,int ressource);
int maximize_profite(Matrix r);

int main(){
    
    char url[] = "test.csv";
    
    //------------ Parse CSV File ---------------
    FILE *file ;
    if ( (file = fopen(url,"r") ) == NULL){
        perror("File");
        exit(EXIT_FAILURE);
    }
    Matrix r = getMatrix(file);
    fclose(file);
    printf("## DATA Loaded ##\n");
    //---------------------------------------
    
    int optimal = maximize_profite(r);


    printf("Optimal value :  %d \n",optimal);
    freeMatrix(r);

    return 0;
}





int dyn_max(Matrix r,Matrix cache,int activity,int ressource){
    if(activity==1){
        return r->values[activity-1][ressource];
    }
    
    int optimal=0;
    for(int i=0;i<=ressource;i++){
        int value;
        if ( cache->values[activity-1][i] ){
            // the value alredy calculated
            value = cache->values[activity-1][i]; 
        }else{
            // calculate the value 
            value =  r->values[activity-1][i] + dyn_max(r,cache,activity-1,ressource-i);
        }
        if(optimal<value){
            optimal = value;
        }
    }
    cache->values[activity-1][ressource] = optimal;
    return optimal;
}


int maximize_profite(Matrix r){
    //A 2D array that memorized optimal values, cache[activity][ressource] = f*(activity, ressource)
    Matrix cache = createMatrix(r->activities,r->ressource+1);
    int profit = dyn_max(r,cache,r->activities, r->ressource);
    freeMatrix(cache);
    return profit;
}

