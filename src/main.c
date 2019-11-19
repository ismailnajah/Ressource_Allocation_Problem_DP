#include "Headers/dyn_max.h"
#include <time.h>

#define URL_DEFAULT "g_test.csv"

//--------------------------------------------------------
int Menu();
void generateFile();

int main(){
    // Configuring the input file
    // Opening The input file
    int op = Menu();
    FILE *file ;
    if(op == 1 || op==2 || op==3){
        char url[100];
        printf("file URL : ");
        scanf("%s",url); 
        file = fopen(url, "r");

    }else{
        generateFile();
        file = fopen(URL_DEFAULT, "r");
    }
    Matrix r = getMatrix(file);  fclose(file);
    printf("\n**************************************************\n");
    if ( file == NULL){
        perror("File");
        exit(EXIT_FAILURE);

    }//~ 
    printf("## DATA Loaded ##\n");
    clock_t begin = clock();
    double time = 0.0;
    if(op==1){
        dyn_max_iterative(r);
    }
    if(op==2){
        dyn_max_recurcive(r);
    }
    if(op==3){
        Bruteforce(r);
    }
    clock_t end = clock();
    time += (double)(end-begin)/CLOCKS_PER_SEC;

    printf("Execution time : %f seconds\n",time);
    freeMatrix(r);

    return 0;
}//~ main()


int Menu(){
    printf("##### This program solves resources allocation problems ###### \n");
    printf(" it uses as input a csv file contains the gains values\n");
    printf(" there are three approaches :\n");
    printf("  1- Dynamic programming : forward approach\n");
    printf("  2- Dynamic programming : backward approach\n");
    printf("  3- Brute Force Algorithm\n");
    printf("  4- Generer un Exemple.\n");

    int op;
    printf("Votre option : ");
    scanf("%i",&op);
    while(op<1 || op>4){
        printf("ERROR!! choisire 1,2,3 ou 4:");
        scanf("%i",&op);
    }
    return op;
}

void generateFile(){
    srand(time(NULL));
    int n,m;
    printf(" Activities : ");
    scanf("%d",&n);
    printf(" Ressources : ");
    scanf("%d",&m);

    FILE *file = fopen(URL_DEFAULT,"w+");
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
}