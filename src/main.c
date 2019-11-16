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
    if(op == 1){
        char url[100];
        printf("file URL : ");
        scanf("%s",url); 
        file = fopen(url, "r");

    }else{
        generateFile();
        file = fopen(URL_DEFAULT, "r");
    }
    printf("\n**************************************************\n");
    if ( file == NULL){
        perror("File");
        exit(EXIT_FAILURE);

    }//~ 
    // Loading the input table into the r(i, j) matrix
    Matrix r = getMatrix(file);  fclose(file);
    printf("## DATA Loaded ##\n");

    clock_t begin = clock();
    double time = 0.0;
    
    dyn_max_recurcive(r) ; 
    //dyn_max_iterative(r);

    clock_t end = clock();
    time += (double)(end-begin)/CLOCKS_PER_SEC;


    printf("Temps d'execution est %f seconds\n",time);
    freeMatrix(r);

    return 0;
}//~ main()


int Menu(){
    printf("##### Ce programme resoudre les problemes d'allocation de ressources ###### \n");
    printf("il utilise comme input un fichier csv contient les valeurs necessaire pour le calcule\n");
    printf("  1- Saisire l'URL d'un fichier CSV.\n");
    printf("  2- Generer un Exemple.\n");

    int op;
    printf("Votre option : ");
    scanf("%i",&op);
    while(op<1 || op>2){
        printf("ERROR!! choisire 1 ou 2: ");
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