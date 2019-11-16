#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "CSV_Parser.h"

#ifndef H_dyn_max_withOP
#define H_dyn_max_withOP

/*
 * Policy structure contains 2 variables :
 *        value : the ressource allocated
 *        next : pointer points on the next element in the policy
 */
struct Policy{
    int value;
    struct Policy *next;
};
typedef struct Policy* Policy;


/*
 * Result structure contains 3 variables :
 *        optimalValue : the optimal value found in dyn_max
 *        nPolicies : keeps track of number of policies found
 *        optimalPolicies : list of heads of policies (each policy is a linkedList)
 */
struct Result{
    int optimalValue;
    int nPolicies;
    Policy *optimalPolicies;
};
typedef struct Result* Result;

struct List{
    int size;
    int *values;
};
typedef struct List* List;


/*
 *  Small container that sets up the cashe buffer for dyn_max() ,it outputs
 *  the optimal value and the Optimal policies
 */
void dyn_max_recurcive(Matrix r);


/*
 *  Same as dyn_max_recurcive the difference is that this one is more efficient and faster
 */
void dyn_max_iterative(Matrix r);


/*
 *  dyn_max_recurcive() takes activity + ressource + Matrix matrix 
 *  and returns the optimal value and the Optimal policies for activity machine given a part of the ressource
 */
Result dyn_max(Matrix r,Result** cache,int activity,int ressource);


/*
 *  this function create a matrix of Result structure to store pointers of calculated results
 */ 
Result **createCache(Matrix r);

//   #  Memory management functions
/*
 *  clearPoliciesTable(Result) : 
 *      policies table is a list of heads of linkedlists (each policy is a linkedlist)
 *      and this function clears this table of a particulare result
 */
void clearPoliciesTable(Result r);
/* freeCache(Result**,int,int):
 *      it frees the memory allocated by each Result in the Cache
 */
void freeCache(Result **cache,int rows,int colums);




/*
 * Print policies on the screen in a fancy way :)
 */
void showPolicies(Result r,int activities);

#endif