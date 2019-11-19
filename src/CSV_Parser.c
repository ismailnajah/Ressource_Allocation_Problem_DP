#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "Headers/CSV_Parser.h"


void extendMatrix(Matrix *M){
    (*M)->activities=(*M)->activities+1;
    (*M)->values=(int**)realloc((*M)->values,((*M)->activities+1)*sizeof(int*));
    (*M)->values[(*M)->activities-1]=(int*)calloc((*M)->ressource+1,sizeof(int));
}

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


void error(char* msg){
    printf("Error!#%s\n",msg);
    exit(EXIT_FAILURE);
}

char *getLine(FILE *file){
    char *line = NULL;
    int c,buffer_size=0;
    while(true){
        c = fgetc(file);
        if(c==EOF || c=='\n')
            break;

        line = realloc(line,++buffer_size);
        line[buffer_size-1]=c;
    }
    if(buffer_size>0){
        line = realloc(line,++buffer_size);
        line[buffer_size-1]='\0';
    }
    return line;
}

Matrix getMatrix(FILE *file){
    Matrix m = (Matrix)malloc(sizeof(struct Matrix));
    if(m==NULL){
        perror("Matrix");
        exit(EXIT_FAILURE);
    }
    m->activities = 0;
    m->ressource = 0;
    m->values = NULL;

    char *line,*p;
    while( (line=getLine(file) ) != NULL){
        m->values = (int**)realloc(m->values,(++m->activities)*sizeof(int*));
        if(m->values==NULL){
            perror("getMatrix");
            exit(EXIT_FAILURE);
        }
        m->values[m->activities-1] = NULL;
        m->ressource = 0;
        p=strtok(line,CSV_SEP);
        while( p != NULL){
            m->values[m->activities-1] = (int*)realloc(m->values[m->activities-1],(++m->ressource)*sizeof(int));
            if(m->values[m->activities-1]==NULL){
                perror("getMatrix");
                exit(EXIT_FAILURE);
            }
            m->values[m->activities-1][m->ressource-1] = atoi(p);
            p=strtok(NULL,CSV_SEP);
        }

        free(line);
    }
    m->ressource--;

    if(m->values==NULL)
        error("getMatrix: Empty file");

    return m;
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