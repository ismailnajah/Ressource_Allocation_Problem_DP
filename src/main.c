#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "CSV_Parser.h"

Matrix matrix;

/*
**  this matrix memorizes the optimal value
**  foreach (activity,ressource) to avoid repetitive calculation 
*/
//  A 2D matrix that memorized optimal values, cache[machine][unity] = f*(machine, unity) 
Matrix cache;               
//this variable will store the value of the optimal path
int *path;


/*
**  TODO
*/
void showPath(int *path);
/*
**  just like dyn_max() in python, takes activity + ressource + global variable Matrix matrix 
**  and returns the optimal value for activity machine given a part of the ressource
*/
int maximizeProfit(int activity,int ressource);


int main(){
    //char *url = (char*)malloc(1000);
    //printf("file URL : ");
    //scanf("%s",url);
    char url[] = "test.csv";
    //free(url);
    //------------ Parse CSV File ---------------
    FILE *file ;
    if ( (file = fopen(url,"r") ) == NULL){
        perror("File");
        exit(EXIT_FAILURE);
    }
    matrix = getMatrix(file);
    fclose(file);

    printf("## DATA Loaded ##\n");

    cache = createMatrix(matrix->activities,matrix->ressource+1);
    path = (int*)calloc(matrix->activities,sizeof(int));

    int optimal = maximizeProfit(matrix->activities, matrix->ressource);

    printf("Optimal value :  %d \n",optimal);
    showPath(path);
    freeMatrix(matrix);
    freeMatrix(cache);
    free(path);
    //---------------------------------------
    return 0;
}

int maximizeProfit(int activity,int ressource){
    if(activity==1){
        return matrix->values[activity-1][ressource];
    }
    
    int optimal=0;
    for(int i=0;i<=ressource;i++){
        int value;
        if ( cache->values[activity-1][i] ){
            // the value alredy calculated
            value = cache->values[activity-1][i]; 
        }else{
            // calculate the value 
            value =  matrix->values[activity-1][i] + maximizeProfit(activity-1,ressource-i);
        }
        if(optimal<value){
            optimal = value;
        }
    }
    cache->values[activity-1][ressource] = optimal;
    return optimal;
}

void showPath(int *path){
    for(int i=0;i<matrix->activities;i++){
        printf(" %d ",path[i]);
    }
    printf("\n");
}
