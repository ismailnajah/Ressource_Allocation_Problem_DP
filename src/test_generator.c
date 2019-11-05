#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(){
    srand(time(NULL));

    int n,m;
    printf(" Activities : ");
    scanf("%d",&n);
    printf(" Ressources : ");
    scanf("%d",&m);

    FILE *file = fopen("g_test.csv","w+");
    fprintf(file,"%d;%d\n",n,m);

    int i=1,j=0;
    while(i<=n){
        j=0;
        while(j<=m){
            int r = j==0?j:rand()%100;
            fprintf(file,"%d",r);
            if(j!=m)
                fprintf(file,";");
            j++;
        }
        fprintf(file,"\n");
        i++;
    }
    fclose(file);
    return 0;
}