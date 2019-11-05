#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "CSV_Parser.h"

void showPath(int *path);
int maximizeProfit(int activity,int ressource);

Matrix matrix;

//this matrix memorizes the optimal value\
 foreach (activity,ressource) to avoid repetitive calculation 
Matrix cache;

//this variable will store the value of optimal path

int main(){
    //char *url = (char*)malloc(1000);
    //printf("file URL : ");
    //scanf("%s",url);
    char url[] = "test.csv";
    
    //------------ Parse CSV File ---------------
    FILE *file ;
    if ( (file = fopen(url,"r") ) == NULL){
        perror("File");
        exit(EXIT_FAILURE);
    }
    printf("## DATA Loaded ##\n");
    matrix = getMatrix(file);
    fclose(file);


    cache = createMatrix(matrix->activities,matrix->ressource+1);
    int optimal = maximizeProfit(matrix->activities, matrix->ressource);

    printf("Optimal value :  %d \n",optimal);
    freeMatrix(matrix);
    freeMatrix(cache);
    //free(url);
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
