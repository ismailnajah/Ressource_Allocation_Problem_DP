#include <stdio.h>

#ifndef H_CSV_PARSER
#define H_CSV_PARSER


#define CSV_SEP ","

struct Matrix{
    int ressource;
    int activities;
    int **values;
};

typedef struct Matrix* Matrix;

Matrix createMatrix(int,int);
Matrix getMatrix(FILE*);
void showMatrix(Matrix);
char *getLine(FILE*);

void freeMatrix(Matrix);
void showMatrix(Matrix);

#endif