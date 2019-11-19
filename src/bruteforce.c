#include "Headers/dyn_max.h"



int factorial(int ressource)
{
    if (ressource == 0)
        return 1;
    else
        return ressource * factorial(ressource - 1);
}
void echanger(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/* Fonction pour imprimer des permutations d'un tableau d'entiers
    Cette fonction prend trois paramÃ¨tres:
    1. tableau d'entiers
    2. Index de dÃ©part du tableau
    3. Index de fin du tableau. */

bool shouldSwap(int str[], int start, int curr)
{
    for (int i = start; i < curr; i++)
        if (str[i] == str[curr])
            return 0;
    return 1;
}
void permuter(int *a, int l, int r, int activite, Matrix gain, Matrix *path, int *solution_opt)
{
    int i;
    int somme;
    if (l == r)
    {
        
        somme = 0;
        for (int j = 0; j < activite; j++)
        {
            somme = somme + gain->values[j][a[j]];
          //  temp[j] = a[j];
        }
        // cherchons le solution optimale
        if (somme > *solution_opt)
        {
            freeMatrix(*path);
            *path = createMatrix(1, activite);
            *solution_opt = somme;
            for (int k = 0; k < activite; k++)
            {
                (*path)->values[(*path)->activities - 1][k] = a[k];
            }
        }
        else if (somme == *solution_opt)
        {
            extendMatrix(path);
            for (int k = 0; k < activite; k++)
            {
                (*path)->values[(*path)->activities - 1][k] = a[k];
            }
        }
    }
    else
    {
        for (i = l; i <= r; i++)
        {
            bool check = shouldSwap(a, l, i);
            if (check)
            {
                echanger((a + l), (a + i));
                permuter(a, l + 1, r, activite, gain, path, solution_opt);
                echanger((a + l), (a + i));
            }
        }
    }
}

// Fonction rÃ©cursive pour gÃ©nÃ©rer toutes les combinaisons de nombres
// ayant la somme ressource. index indique le prochain emplacement libre dans le tableau de sortie
void Generer_Combinaisons(int i, int ressource, int out[], int index, int activite, Matrix gain, Matrix *path, int *solution_opt)
{
    int temp[activite];
    // si la somme devient ressource, ajouter la combinaison
    if (ressource == 0 && index <= activite)
    {
        int p;

        for (p = 0; p < index; p++)
            temp[p] = out[p];
        for (int q = index; q < activite; q++)
            temp[q] = 0;
        permuter(temp, 0, activite - 1, activite, gain, path, solution_opt);
    }
    int j;
    // commencer Ã  partir de l'Ã©lÃ©ment prÃ©cÃ©dent dans la combinaison jusqu'Ã  ressource
    for (j = i; j <= ressource; j++)
    {
        // place l'Ã©lÃ©ment en cours Ã  l'index en cours
        out[index] = j;
        // recurence avec somme rÃ©duite
        Generer_Combinaisons(j, ressource - j, out, index + 1, activite, gain, path, solution_opt);
    }
}

void Bruteforce(Matrix r){
    Matrix *path_optimal=(Matrix*)malloc(sizeof(struct Matrix));
    *path_optimal = createMatrix(1, r->activities+1);
    int solution_optimal = 0;
    int temp[r->activities];
    
    Generer_Combinaisons(1, r->ressource, temp, 0, r->activities,r,path_optimal,&solution_optimal);

    printf("+++++++++++++++++Solution optimale : %d et le(s) sequence(s) de decision sont: \n",solution_optimal);
    showMatrix(*path_optimal);
    freeMatrix(*path_optimal);
    free(path_optimal);
}