/*
 * Element of a Linked list that forms an optimal policy
 * Optimal d* decision to pay at a k decision to get the optimal value
 */ 
typedef struct OPTIMAL_DECISION
{
    int ressource;
    struct OPTIMAL_DECISION* next;
} OPTIMAL_DECISION;

/*
 * A Linked list structure pointing at the Optimal decisions' list
 * and linked with other possible optimal policies
 */ 
typedef struct OPTIMAL_POLICY
{
    OPTIMAL_DECISION* optimal_decisions_head;
    struct OPTIMAL_POLICY* next;
} OPTIMAL_POLICY;

/*
 * A Data structure that is supposed to hold the optimal Value and the optimal policies
 * to be stored in the cache (each element of the cache matrix is supposed to point at 
 * this structure) 
 */
typedef struct OPTIMAL
{
    int optimal_value;
    OPTIMAL_POLICY* optimal_policies_head;
} OPTIMAL;

/*
 * Data Structure CACHE. Caches/Memorizes the (struct OPTIMAL - optimal value and policies -
 */
typedef struct CACHE
{
    int activities ;
    int ressources ;
    OPTIMAL* (** optimals);
} CACHE;




/*
 *  Creates a (CACHE*) - 2D array of NULL ELEMENTS OF TYPE OPTIMAL * that are initialized to NULL 
 */
CACHE* create_cache(int N,int M);
/*
 *  Frees the (CACHE*) - 2D array matrix ELEMENTS OF TYPE OPTIMAL * and the memory it is pointing to
 */
void free_cache(CACHE* cache);
/*
 * Create an OPTIMAL element which the cache matrix's elements point to
 */
OPTIMAL* create_optimal(void);
/*
 * Free the OPTIMAL element to which the cache matrix's elements points
 */
// TODO DELETE THIS 
//void free_optimal(OPTIMAL* optimal);
/*
 * This is supposed to clear/free every node of the list OPTIMAL::optimal_policies.head
 * and reset the head = NULL
 * (similar to what list.clear() does to a list in python)
 */
void free_optimal_policies(OPTIMAL* optimal);

/*
 * Reverts the added (now is decision ) from the inherited desitions and resets the head of 
 * the OPTIMAL->optimalpolicies.head to NULL 
 */
void clear_added_optimal_policies(OPTIMAL* optimal);

/* 
 * Extend the temp optimals of the past activities/machine with the decision d 
 * by creating OPTIMAL_ELEMENT decision d and appending it before each list we have so far
 * and extending the whole thing to tge OPTIMAL::optimal_policies we have so far
 */
void extend_optimal_policies(OPTIMAL* optimal, int d, OPTIMAL* temp);

/*
 * Print all found optimal policies
 */
void print_optimals_policies(OPTIMAL* opt);