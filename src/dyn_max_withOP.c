#include "dyn_max_withOP.h"


Result maximize_profite_withOP(Matrix r){
    //A 2D array that memorized optimal values, cache[activity][ressource] = f*(activity, ressource)
    Result **cache = createCache(r);
    Result profit = (Result)malloc(sizeof(struct  Result));
    Result result = dyn_max_with_optimalPolicies(r,cache,1,r->ressource);
    copyResult(result, profit);

    clearPoliciesTable(result);
    free(result);
    freeCache(cache,r->activities,r->ressource);

    return profit;
}

Result dyn_max_with_optimalPolicies(Matrix r,Result **cache,int activity,int ressource){

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

        }else{
            // calculate the value 
            temp = dyn_max_with_optimalPolicies(r, cache, activity+1, ressource-i);
           
        }

        int gain = r->values[activity-1][i] + temp->optimalValue;


        if(optimal->optimalValue < gain){
            if(optimal->nPolicies > 0 )
                clearPoliciesTable(optimal);
            
            optimal->nPolicies = temp->nPolicies;
            optimal->optimalPolicies = (Policy*)malloc(optimal->nPolicies*sizeof(Policy));
            for(int j=0;j<optimal->nPolicies;j++){
                optimal->optimalPolicies[j] = (Policy)malloc(sizeof(struct Policy));
                optimal->optimalPolicies[j]->value = i;
                optimal->optimalPolicies[j]->next = temp->optimalPolicies[j];
            }
            optimal->optimalValue = gain;
        }else if(optimal->optimalValue == gain){
            int start = optimal->nPolicies;
            optimal->nPolicies += temp->nPolicies;
            optimal->optimalPolicies = (Policy*)realloc(optimal->optimalPolicies,optimal->nPolicies*sizeof(Policy));
            for(int j=start;j<optimal->nPolicies;j++){

                optimal->optimalPolicies[j] = (Policy)malloc(sizeof(struct Policy));
                optimal->optimalPolicies[j]->value = i;
                optimal->optimalPolicies[j]->next = temp->optimalPolicies[j-start];

            }
        }
    }
    
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
    if(r->nPolicies > 0){
        r->nPolicies = 0;
        for(int i=0;i<r->nPolicies;i++){
            Policy p = r->optimalPolicies[i];
            while(p!=NULL){
                Policy q = p->next;
                free(p);
                p = q;
            }
        }
        free(r->optimalPolicies);
        r->optimalPolicies=NULL;
    }
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

Policy copyPolicy(Policy pol){
    Policy p = pol;
    Policy head = (Policy)malloc(sizeof(struct Policy));
    Policy q = head;

    head->value = p->value;
    while(p->next!=NULL){
        q->next = (Policy)malloc(sizeof(struct Policy));
        q->next->value = p->next->value;
        q=q->next;
        p=p->next;
    }
    q->next = NULL;

    return head;
}

void copyResult(Result src,Result dist){
    dist->nPolicies = src->nPolicies;
    dist->optimalPolicies = (Policy*)malloc(dist->nPolicies*sizeof(Policy));
    dist->optimalValue = src->optimalValue;
    for(int i=0;i<src->nPolicies;i++){
        dist->optimalPolicies[i] = copyPolicy(src->optimalPolicies[i]);
    }
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

    