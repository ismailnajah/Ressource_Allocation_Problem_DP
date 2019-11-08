# reading a csv file into r[Machines][unites] -> values of reward
r = []
with open('inpt.csv', 'r') as f:
    f.readline()
    for i in f:
        r.append(   list(  map( int, i.split(',') )  )   )

# cache is a dictionary for memorizing optimal solutions
cache = {}
total_f = total_cached = 0
def dyn_max(n: int, machine:int=1) -> int: 
    global total_f
    global total_cached
    total_f += 1
    print("__"*machine + ">","machine: {}, ressource : {}".format( machine, n))
    if machine == len(r):
        cache[(machine, n)] = r[machine - 1][n]
        return r[machine - 1][n]

    listToMaximaze = []
    unite = 0; 
    temp = 0
    while unite <= n:
        if cache.get( (machine+1, n-unite), False ) is not False  :
            temp = cache[(machine+1, n-unite)] 
            total_cached += 1
        else :
            temp = dyn_max(n - unite, machine + 1) 

        listToMaximaze.append( r[machine - 1][unite] + temp ) 
        unite += 1

    cache[(machine, n)] = max(listToMaximaze)
    return cache[(machine, n)]

print('Optimal value :', dyn_max( len(r[0]) - 1 ))
#print('len_cache :', len(cache))
print('times f was called :', total_f)
print('times the value was recovered from the cache :', total_cached)