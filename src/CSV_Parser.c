#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "CSV_Parser.h"


Matrix createMatrix(int N,int M){
    Matrix matrix = (Matrix)malloc(sizeof(struct Matrix));
    if(matrix==NULL){
        perror("Matrix");
        exit(EXIT_FAILURE);
    }
    matrix->ressource = M-1;
    matrix->activities = N;
    matrix->values = (int**)malloc(N*sizeof(int*));
    if(matrix->values==NULL){
        perror("Matrix");
        exit(EXIT_FAILURE);
    }
    
    for(int i=0;i<N;i++){
        matrix->values[i] =(int*)calloc(M,sizeof(int));
        if(matrix->values[i]==NULL){
            perror("Matrix");
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}

Matrix getMatrix(FILE *file){
    // get N(Rows) and M(Columns) from CSV file 
    int N,M;
    char *line,*p;
    if( (line=getLine(file) ) != NULL){
        p = strtok(line,CSV_SEP);
        N = atoi(p);
        p = strtok(NULL,CSV_SEP);
        M = atoi(p);
    }
    free(line);
    //----------------------------------------- 
    //Allocate 2D table with N Rows and M Columns
    Matrix matrix = createMatrix(N,M);
    //-----------------------------------------
    //Get Matrix values from CSV file
    int i=0,j;
    while( (line=getLine(file) ) != NULL){
        j=0;
        p=strtok(line,CSV_SEP);
        while( p != NULL){
            matrix->values[i][j++] = atoi(p);
            p=strtok(NULL,CSV_SEP);
        }
        free(line);
        i++;
    }
    //--------------------------------
    return matrix;
}

char *getLine(FILE *file){
    char *line = NULL;
    int c,buffer_size=0;
    while(true){
        c = fgetc(file);
        if(c==EOF || c=='\n')
            break;
        buffer_size++;
        line = realloc(line,buffer_size);
        line[buffer_size-1]=c;
    }
    return line;
}

void freeMatrix(Matrix matrix){
    int i;
    for(i=0;i<matrix->activities;i++){
        free(matrix->values[i]);
    }
    free(matrix->values);
    free(matrix);
}

// debug
void showMatrix(Matrix matrix){
    printf("\n-----------Matrix(%d,%d)------------\n",matrix->activities,matrix->ressource);
    for(int i=0; i<matrix->activities; i++){
        for(int j=0; j<matrix->ressource; j++){
            printf(" %d",matrix->values[i][j]);
        }
        printf("\n");
    }
}