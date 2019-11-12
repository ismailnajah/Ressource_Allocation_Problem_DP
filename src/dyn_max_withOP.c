#include "dyn_max_withOP.h"


void maximize_profite_withOP(Matrix r){
    //A 2D array that memorized optimal values, cache[activity][ressource] = f*(activity, ressource)
    Result **cache = createCache(r);
    
    Result result = dyn_max_with_optimalPolicies(r,cache,1,r->ressource);
    
    printf("Optimal value :  %d \n",result->optimalValue);
    showPolicies(result,r->activities);

    freeCache(cache,r->activities,r->ressource);
}

Result dyn_max_with_optimalPolicies(Matrix r,Result **cache,int activity,int ressource){
    static int f= 1,c = 0;
    if(activity == r->activities){
        Result result = (Result)malloc(sizeof(struct Result));
        result->optimalValue = r->values[activity-1][ressource];
        result->nPolicies = 1;

        result->optimalPolicies = (Policy*)malloc(sizeof(Policy));
        result->optimalPolicies[0] = (Policy)malloc(sizeof(struct Policy));

        result->optimalPolicies[0]->value = ressource;
        result->optimalPolicies[0]->next = NULL;


        cache[activity-1][ressource] = result;
        return result;
    }
    
    Result optimal=(Result)malloc(sizeof(struct Result));
    optimal->optimalValue=0;
    optimal->nPolicies = 0;
    optimal->optimalPolicies = NULL;

    Result temp;
   
    for(int i=0 ; i<=ressource ; i++) {
        
        if ( cache[activity][ressource-i] != NULL ){
            // the value already calculated
            temp = cache[activity][ressource-i];
            c++;
        }else{
            // calculate the value 
            temp = dyn_max_with_optimalPolicies(r, cache, activity+1, ressource-i);
            f++;
        }

        int gain = r->values[activity-1][i] + temp->optimalValue;


        if(optimal->optimalValue <= gain){
            int newSize,start;
            if (optimal->optimalValue == gain){
                newSize = optimal->nPolicies + temp->nPolicies;
                start = optimal->nPolicies;
            }else{
                if(optimal->nPolicies > 0 )
                    clearPoliciesTable(optimal);
                start = 0;
                newSize = temp->nPolicies;
            }
            optimal->nPolicies = newSize;
            optimal->optimalPolicies = (Policy*)realloc(optimal->optimalPolicies,optimal->nPolicies*sizeof(Policy));
            optimal->optimalValue = gain;
            for(int j=start;j<optimal->nPolicies;j++){
                optimal->optimalPolicies[j] = (Policy)malloc(sizeof(struct Policy));
                optimal->optimalPolicies[j]->value = i;
                optimal->optimalPolicies[j]->next = temp->optimalPolicies[j-start];
            }
        }
    }
    if(activity==1)
        printf("recover from Cache  = %d\ncall function dyn_max() = %d\n",c,f);

    cache[activity-1][ressource] = optimal;
    return optimal;
}

Result **createCache(Matrix r){
    Result** cache = (Result**)malloc(r->activities*sizeof(Result));
    for(int i=0;i<r->activities;i++){
        cache[i] = (Result*)calloc(r->ressource+1,sizeof(Result));
    }
    return cache;
}

void clearPoliciesTable(Result r){
    for(int i=0;i<r->nPolicies;i++)
        free(r->optimalPolicies[i]);
    free(r->optimalPolicies);
    r->optimalPolicies = NULL;
}

void freeCache(Result **cache,int rows,int columns){
    for(int i=0;i<rows;i++){
        for(int j=0;j<=columns;j++){
            if(cache[i][j]!=NULL){
                clearPoliciesTable(cache[i][j]);
                free(cache[i][j]);
            }
        }
        free(cache[i]);
    }
    free(cache);
}

void showPolicies(Result r,int activities){
    printf("__> Optimal policies (%d): \n",r->nPolicies);
    printf("Activitie |");
    
    for(int i=0;i<activities;i++){
        printf("%3d|",i+1);
    }
    printf("\n");
    for(int i=0;i<r->nPolicies;i++){
        Policy  p = r->optimalPolicies[i];
        printf("          |");
        while(p != NULL){
            printf("%3d|",p->value);
            p = p->next;
        }
        printf("\n");
    }
}

    