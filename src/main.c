#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "CSV_Parser.h"
#include "data_structures.h"

#define URL_DEFAULT "inpt.csv"


/*
 *  Small container that sets up the cashe buffer for dyn_max() -> returns the optimal f*
 */
int maximize_profite(Matrix r);
/*
 *  dyn_max() takes activity + ressource + global variable Matrix matrix 
 *  and returns the optimal value for activity machine given a part of the ressource
 */
OPTIMAL* dyn_max(Matrix r, CACHE* cache, int activity, int ressource);


/*
** TODO DELETE HADCHI
*/
int total_f = 0;
int total_cache_check = 0;

int main(int argc, char* argv[]){
    // Configuring the input file
    char *url = (argc==2)?argv[1] : URL_DEFAULT ;

    // Opening The input file
    FILE *file ;
    if ( (file = fopen(url, "r") ) == NULL){
        perror("File");
        exit(EXIT_FAILURE);

    }//~ 
    
    // Loading the input table into the r(i, j) matrix
    Matrix r = getMatrix(file);  fclose(file);
    printf("## DATA Loaded ##\n");
    
    // Find the optimal f* for r 
    int optimal = maximize_profite(r);    freeMatrix(r);
    printf("Optimal value :  %d \n",optimal);
    printf("recursivity :  %d \n",total_f);
    printf("cache check :  %d \n",total_cache_check);

    return 0;
}//~ main()


int maximize_profite(Matrix r){
    //A 2D array that memorized optimal values, cache[activity][ressource] = f*(activity, ressource)
    CACHE* cache = create_cache(r->activities,r->ressource);
    OPTIMAL* profit = dyn_max(r,cache, 1, r->ressource);
    print_optimals_policies(profit);
    int x = profit->optimal_value;
    free_cache(cache);
    return x;
}

OPTIMAL* dyn_max(Matrix r,CACHE* cache,int activity,int ressource){
    // TODO to delete this global variable counter  
    total_f++;
    if(activity == r->activities){
        OPTIMAL* temp = create_optimal();
        extend_optimal_policies(temp, ressource, NULL);
        temp->optimal_value = r->values[activity-1][ressource];
        cache->optimals[activity-1][ressource] = temp;
        return temp;
    }
    
    OPTIMAL* optimal=create_optimal();
    OPTIMAL* temp=NULL;
    for(int i=0 ; i<=ressource ; i++) {
        if ( cache->optimals[activity][ressource-i] != NULL  ){
            // TODO DELETE THIS 
            total_cache_check++;
            // the value already calculated
            temp = cache->optimals[activity][ressource-i]; 
        }else{
            // calculate the value 
            temp = dyn_max(r, cache, activity+1, ressource-i);
        }
        int gain = r->values[activity-1][i] + temp->optimal_value;
        if(optimal->optimal_value < gain){
            optimal->optimal_value = gain;
            clear_added_optimal_policies(optimal);
            extend_optimal_policies(optimal, i, temp);
        } else if (optimal->optimal_value == gain) {
            extend_optimal_policies(optimal, i, temp);
        }
    }
    cache->optimals[activity-1][ressource] = optimal;
    return optimal;
}