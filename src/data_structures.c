#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

/*
 *  Creates a (Nx(M+1) matrix ) of pointers to 
 */
CACHE* create_cache(int N,int M){
    // Allocating the space for the cache
    CACHE*  cache = NULL;
    if(  ( cache = (CACHE*)malloc( sizeof(CACHE) )  )==NULL){
        perror("Cache");
        exit(EXIT_FAILURE);
    }

    cache->activities = N ;
    cache->ressources = M ;

    // Allocating the space for N row of the matrix
    cache->optimals = (OPTIMAL***) malloc(N* sizeof(OPTIMAL**));
    if(cache->optimals==NULL){
        perror("Cache optimal **");
        exit(EXIT_FAILURE);
    }

    // Allocating the space for M+1 colomns of the matrix
    for(int i=0;i<N;i++){
        cache->optimals[i] = (OPTIMAL**) calloc((M+1),  sizeof(OPTIMAL*));
        if(cache->optimals[i]==NULL){
            perror("Cache optimal *");
            exit(EXIT_FAILURE);
        }
    }
    return cache;
}

/*
 * Frees the cache and every other memory that it is pointing at 
 */
void free_cache(CACHE* cache) {
    for(int i=cache->activities - 1; i >= 0 ;i--){
        for(int j=0; j <= cache->ressources; j++) {
            if (cache->optimals[i][j] != NULL) {
                clear_added_optimal_policies(cache->optimals[i][j]);
                free(cache->optimals[i][j]);
                cache->optimals[i][j] = NULL;  // TODEL
            }
        }
        free(cache->optimals[i]);
    }
    free(cache->optimals);
    free(cache);
}

/*
 * This function creates an struct OPTIMAL element initialized to 0
 * and return a pointer to it.
 */
OPTIMAL* create_optimal(void) {
    OPTIMAL* optimal = (OPTIMAL*) malloc( sizeof(*optimal) );
    if ( optimal==NULL ) {
        perror("Make OPTIMAL");
        exit(EXIT_FAILURE);
    }
    optimal->optimal_value=0; optimal->optimal_policies_head=NULL;
    return optimal;
}

/*
 * This function frees the allocated memory for the optimal and its 
 * cascading memory/children
 */
// TODO DELETE THIS 
// void free_optimal(OPTIMAL* optimal){
    //free_optimal_policies(optimal);
//    free(optimal);
//}


void free_optimal_policies(OPTIMAL* optimal) {
    if (optimal == NULL) return ;
    else if (optimal->optimal_policies_head == NULL ) return;

    OPTIMAL_POLICY* pt = optimal->optimal_policies_head;
    OPTIMAL_POLICY* temp = NULL;
    OPTIMAL_DECISION* pt2=NULL, *temp2 = NULL;
    while(pt != NULL) {
        pt2 = pt->optimal_decisions_head;
        while (pt2 != NULL) {
            temp2 = pt2;
            pt2 = pt2->next;
            free(temp2);
            temp2 = NULL;
        }
        temp = pt;
        pt = pt->next;
        free(temp);
    }
    optimal->optimal_policies_head= NULL;
}

/*
 * Reverts the added (now is decision ) from the inherited desitions and resets the head of 
 * the OPTIMAL->optimalpolicies.head to NULL 
 */
void clear_added_optimal_policies(OPTIMAL* optimal) {
    OPTIMAL_POLICY* pt = optimal->optimal_policies_head;
    OPTIMAL_POLICY* temp = NULL;
    while(pt != NULL) {
        temp = pt;
        pt = pt->next;
        free(temp->optimal_decisions_head); temp->optimal_decisions_head = NULL;
        free(temp); temp = NULL;
    }
    optimal->optimal_policies_head = NULL;
}

/* 
 * Extend the temp optimals of the past activities/machine with the decision d to its left 
 * by creating OPTIMAL_ELEMENT decision d and appending it before each list we have so far
 * and extending the whole thing to tge OPTIMAL::optimal_policies we have so far
 */
void extend_optimal_policies(OPTIMAL* optimal /*to extend to*/, int d /*decision*/ , OPTIMAL* temp /*optimal paths to extend from*/) {
    if(optimal == NULL ) { // Nothing to do here
        perror("reverence to the optimals list is Null");
        return;
    }

    if(temp == NULL || temp->optimal_policies_head == NULL ) {
        // temp is empty ==> append the decision node d to the head of the optimal list 
        // Creating the decision "OPTIMAL_DECISION" node for the linked list
        OPTIMAL_DECISION* decision_node = (OPTIMAL_DECISION*) malloc(sizeof(OPTIMAL_DECISION));
        if(decision_node == NULL) {
            perror("Malloc decision_node"); 
            exit(EXIT_FAILURE);
        }
        decision_node->ressource = d;   decision_node->next = NULL;

        // Making the optimal_policy node 
        OPTIMAL_POLICY* OP = (OPTIMAL_POLICY*) malloc(sizeof(OPTIMAL_POLICY));
        if(OP == NULL) {
            perror("Malloc Optimal_policy"); 
            exit(EXIT_FAILURE);
        }
        OP->optimal_decisions_head     = decision_node;
        OP->next                       = optimal->optimal_policies_head;
        optimal->optimal_policies_head = OP;

    } else { // optimal list is empty or not and temp has a number of optimal decisions
        OPTIMAL_POLICY* pt_policy_temp = temp->optimal_policies_head;
        while(pt_policy_temp != NULL) {
        
            // Creating the decision "OPTIMAL_DECISION" node for the linked list
            OPTIMAL_DECISION* decision_node = (OPTIMAL_DECISION*) malloc(sizeof(OPTIMAL_DECISION));
            if(decision_node == NULL) {
                perror("Malloc decision_node"); 
                exit(EXIT_FAILURE);
            }
            decision_node->ressource = d;   decision_node->next = pt_policy_temp->optimal_decisions_head ;

            // Making the optimal_policy node 
            OPTIMAL_POLICY* OP = (OPTIMAL_POLICY*) malloc(sizeof(OPTIMAL_POLICY));
            if(OP == NULL) {
                perror("Malloc Optimal_policy"); 
                exit(EXIT_FAILURE);
            }
            OP->optimal_decisions_head = decision_node;
            OP->next = optimal->optimal_policies_head;    // insert at the optimal policy at the beginning of the optimal policies list
            optimal->optimal_policies_head = OP;        // make the optimal policies list point to the new element

            pt_policy_temp = pt_policy_temp->next;
        }
    }
}

/*
 * Print all found optimal policies
 */
void print_optimals_policies(OPTIMAL* opt) {
    if(opt == NULL) return ;
    OPTIMAL_POLICY* op = opt->optimal_policies_head;
    while (op != NULL) {
        OPTIMAL_DECISION* od = op->optimal_decisions_head;
        while(od != NULL) {
            printf("%d ", od->ressource);
            od = od->next;
        } printf("\n");
        op = op->next;
    }
}