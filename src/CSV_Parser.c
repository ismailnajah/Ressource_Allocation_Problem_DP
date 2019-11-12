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
    Matrix matrix = createMatrix(N,M+1);
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
        if(c==EOF || c=='\n'){
            c = '\0';
            //line[buffer_size-1]=c;
            break;
        }
        line = realloc(line,++buffer_size);
        line[buffer_size-1]=c;
    }
    if(buffer_size>0){
        line = realloc(line,++buffer_size);
        line[buffer_size-1]='\0';
    }
    return line;
}

void freeMatrix(Matrix matrix){
    
    for(int i=0;i<matrix->activities;i++){
        free(matrix->values[i]);
    }
    free(matrix->values);
    free(matrix);
}

// debug
void showMatrix(Matrix matrix){
    char s[] = "___|";
    printf("a\\r|");

    for(int k=0;k<= matrix->ressource;k++)
        printf("%3d|",k);
    printf("\n");
    for(int k=0;k<= matrix->ressource+1;k++)
        printf("%s",s);
    printf("\n");
    for(int i=0; i<matrix->activities; i++){
        printf("%3d|",i+1);
        for(int j=0; j<=matrix->ressource; j++){
            printf("%3d|",matrix->values[i][j]);
        }
        printf("\n");
        for(int k=0;k<= matrix->ressource+1;k++)
            printf("%s",s);
        printf("\n");
    }
    printf("\n");
}