import functions as ft
import sys

if __name__ == '__main__':
    INPUT = []
    OUTPUT = []
    for i in range(int(sys.argv[1])):
        INPUT.append('input'+str(i)+'.txt')
        OUTPUT.append('output'+str(i)+'.txt')
    pairs = list(zip(INPUT, OUTPUT))
    for (i,j) in pairs:
        alpha, n, KB = ft.readInput("INPUT/"+i)
        n=int(n[0])
        output,c = ft.PLResolution(alpha,KB)
        ft.writeOutput( output,c, "OUTPUT/"+j)

