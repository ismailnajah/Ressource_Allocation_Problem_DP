#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "CSV_Parser.h"


#define URL_DEFAULT "test.csv"

//  r[m][n], contains the gains r(i,j)>=0 for each machine 'm' for each ressources 'n' 
Matrix r;
//  A 2D matrix that memorized optimal values, cache[machine][unity] = f*(machine, unity) 
Matrix cache;               


/*
**  TODO
*/
void showPath(int *path);
/*
**  just like dyn_max() in python, takes activity + ressource + global variable Matrix matrix 
**  and returns the optimal value for activity machine given a part of the ressource
*/
int maximizeProfit(int activity,int ressource);


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
    r = getMatrix(file);    fclose(file);
    
    cache = createMatrix(r->activities,r->ressource+1);
    int optimal = maximizeProfit(r->activities, r->ressource);

    printf("Optimal value :  %d \n",optimal);
    freeMatrix(r);
    freeMatrix(cache);
    return 0;
}//~ main()

int maximizeProfit(int activity,int ressource){
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
            value =  r->values[activity-1][i] + maximizeProfit(activity-1,ressource-i);
        }
        if(optimal<value){
            optimal = value;
        }
    }
    cache->values[activity-1][ressource] = optimal;
    return optimal;
}

void showPath(int *path){
    for(int i=0;i<r->activities;i++){
        printf(" %d ",path[i]);
    }
    printf("\n");

}
