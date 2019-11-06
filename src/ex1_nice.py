with open('inpt.csv', 'r') as f:
    # reading a csv file into r[Machines][unites] -> values of reward
    r = []
    for i in f:
        r.append(   list(  map( int, i.split(',') )  )   )

    # cache is a dictionary for memorizing optimal solutions
    cache = {}
    optimalPolicies = []
    def dyn_max(n: int, machine:int=1, path=[], optimal=False) -> int: 
        if machine == len(r):
            if optimal:
                path += [n]
                if sum ( [r[m][i] for m, i in enumerate(path) ]) == optimal:
                    optimalPolicies.append( path )
            return r[machine - 1][n]

        listToMaximaze = []
        for unite in range(n+1):
            if cache.get( (machine, unite), False ):
                listToMaximaze.append(cache[(machine, unite)])
            else :
                listToMaximaze.append(  r[machine - 1][unite] + dyn_max(n-unite, machine + 1
                                        , path+[unite], optimal=optimal) 
                                     )

        cache[(machine, unite)] = max(listToMaximaze)
        return cache[(machine, unite)]

    print(dyn_max(len(r[0]) - 1, optimal=128))
    print(optimalPolicies)
    print('\n'.join(map(repr, optimalPolicies)))

#optimal solution (machine, unite) ((1, 3), (2, 3), (3, 0), (4, 4))

