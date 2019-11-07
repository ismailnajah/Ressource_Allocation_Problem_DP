# reading a csv file into r[Machines][unites] -> values of reward
r = []
with open('small.csv', 'r') as f:
    for i in f:
        r.append(   list(  map( int, i.split(',') )  )   )

# cache is a dictionary for memorizing optimal solutions and policies 
# cache is of the form : cache = {(machine, resources): {'optimalValue': 0, 'optimalPolicies':[]}}
cache = {}
total_f = total_cached = 0
def dyn_max(n: int, machine:int=1) -> int: 
    global total_f, total_cached
    total_f += 1
    if machine == len(r):
        return {
                                'optimalValue'    : r[machine - 1][n], 
                                'optimalPolicies' : [[n]],
                               } 

    listOfOptimals = {
                        'optimalValue'    : 0, 
                        'optimalPolicies' : []
                     } 
    i = 0; 
    while i <= n:
        
        temp = None 
        if cache.get( (machine+1, n-i), False ) :
            temp = cache[(machine+1, n-i)]
            total_cached += 1
        else :
            temp = dyn_max(n - i, machine + 1) 

        gain = r[machine - 1][i] + temp['optimalValue']
        if listOfOptimals['optimalValue'] < gain:
            listOfOptimals['optimalPolicies'].clear()
            listOfOptimals['optimalPolicies'].extend( [ [i] + optPolicy for optPolicy in temp['optimalPolicies'] ] ) 
            listOfOptimals['optimalValue'] = gain
        elif listOfOptimals['optimalValue'] == gain:
            listOfOptimals['optimalPolicies'].extend( [ [i] + optPolicy for optPolicy in temp['optimalPolicies'] ] ) 

        i += 1

    cache[(machine, n)] = listOfOptimals
    return cache[(machine, n)]

d = dyn_max(len(r[0]) - 1)
print('Optimal value :', d['optimalValue'], '\n' ,
      '__> Optimal policies :\n', '\n'.join(map(repr, d['optimalPolicies']))
)
print('len_cache :', len(cache))
print('times f was called :', total_f)
print('times the value was recovered from the cache :', total_cached)