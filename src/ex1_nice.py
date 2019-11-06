with open('test_p.csv', 'r') as f:
    r = []
    for i in f:
        r.append(   list(  map( int, i.split(',') )  )   )

    cache = {}
    total = 0
    def dyn_max(n, machine=1):
        global total
        total+=1
        if machine == len(r):
            return r[machine - 1][n]

        l = []
        for i in range(n+1):
            if cache.get( (machine, i), False ):
                l.append(cache[(machine, i)])
            else :
                l.append( r[machine - 1][i] + dyn_max(n-i, machine + 1) )

        cache[(machine, i)] = max(l)
        return cache[(machine, i)]

    print(dyn_max(10))
    print(total)
