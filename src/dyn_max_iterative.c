#include "Headers/dyn_max.h"



void print_optimal_paths(List **RA,int a,int r,int step,int *s){
    if(r==0){
        for(int i=0;i<a;i++)
            printf(" %i ",s[i]);
        printf("\n");
        return;
    }

    for(int i=0 ;i < RA[step-1][r]->size ;i++){
        s[step-1] = RA[step-1][r]->values[i];
        print_optimal_paths(RA ,a ,r - RA[step-1][r]->values[i] ,step+1 ,s);
    }
}

void free3D(List **t,int R,int A){
    for(int i=0;i<A;i++){
        for(int j=0;j<R;j++){
            if(t[i][j]!=NULL){
                free(t[i][j]->values);
                free(t[i][j]);
            }
        }
        free(t[i]);
    }
    free(t);
}

void dyn_max_iterative(Matrix r){
    int A,R;
    A = r->activities;
    R = r->ressource+1;

    //Cache
    Matrix F = createMatrix(A,R);
    for(int i=0;i<R;i++){
       F->values[A-1][i] = r->values[A-1][i];
    }

    //RA : Ressource Affecter
    List** RA = (List**)malloc(A*sizeof(List*));
    for(int i=0;i<A;i++){
        RA[i] = (List*)calloc(R,sizeof(List));
    }

    for(int i=0;i<R;i++){
        RA[A-1][i] = (List)malloc(sizeof(struct List));
        RA[A-1][i]->size = 1;
        RA[A-1][i]->values = (int*)malloc(RA[A-1][i]->size*sizeof(int));
        RA[A-1][i]->values[RA[A-1][i]->size-1]=i;
    }

    for(int i=A-2;i>-1;i--){
        for(int j=0;j<R;j++){
            int k=0;
            int optimal=-1;

            List ra = (List)malloc(sizeof(struct List));
            ra->size=0;
            ra->values=NULL;

            while(k<=j){
                int temp = r->values[i][k] + F->values[i+1][j-k];
                if( temp > optimal){
                    optimal=temp;
                    ra->size = 1;
                    ra->values=(int*)realloc(ra->values,sizeof(int));
                    ra->values[0] = k;
                }else if(temp==optimal){
                    ra->size++;
                    ra->values=(int*)realloc(ra->values,ra->size*sizeof(int));
                    ra->values[ra->size-1] = k;
                }
                k++;
            }
            F->values[i][j] = optimal;
            RA[i][j] = ra;
        }
    }
    printf("Optimal value :  %d \n",F->values[0][R-1]);


    int *s = (int*)calloc(A,sizeof(int));
    print_optimal_paths(RA,A,R-1,1,s);

    //free Memoire allouee par F,RA et s
    freeMatrix(F);
    free3D(RA,R,A);
    free(s);
}