# reading a csv file into r[Machines][unites] -> values of reward
M = []
with open('sorted.csv', 'r') as f:
    f.readline()
    for line in f:
        M.append(   list(  map( int, line.strip().split(',') )  )   )

N = len(M)
R = len(M[0]) - 1 

F=[[0]*(R+1) for _ in range(N-1)]
F.append(M[-1])

RA=[[0]*(R+1) for _ in range(N-1)]
RA.append([ [i] for i in range(0, R+1)])


for i in range(N-2, -1, -1):
    for j in range(0, R+1):
        k = 0
        mx = -1
        ra = []
        while(k <= j):
            n = M[i][k] + F[i+1][j-k]
            if n > mx :
                mx = n
                ra.clear()
                ra.append(k)
            elif n == mx:
                ra.append(k)

            k += 1
        F[i][j] = mx
        RA[i][j] = ra

print('F', '\n'.join(map(repr, F)) , sep='\n', end ='\n\n')
print('R', '\n'.join(map(repr, RA)), sep='\n', end ='\n\n')


def f(ressources, step=1, s=[]):
    if ressources == 0:
        print(s + [0]*(N-step+1))
        return
    ra_list = RA[step-1][ressources]
    for ra in ra_list:
        f(ressources-ra ,step+1   ,s+[ra])
    
f(R)