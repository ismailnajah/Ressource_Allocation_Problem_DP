#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CSV_Parser.h"


int main(){
    srand(time(NULL));

    int n,m;
    printf(" Activities : ");
    scanf("%d",&n);
    printf(" Ressources : ");
    scanf("%d",&m);

    FILE *file = fopen("g_test.csv","w+");
    fprintf(file,"%d%s%d\n",n,CSV_SEP,m);

    int i=1,j=0,x=4;
    while(i<=n){
        j=0;
        while(j<=m){
            int r = j==0?j:(r+rand()%x);
            fprintf(file,"%d",r);
            if(j!=m)
                fprintf(file,CSV_SEP);
            j++;
        }
        fprintf(file,"\n");
        i++;
    }
    fclose(file);
    return 0;
}