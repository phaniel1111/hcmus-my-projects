from Space import *
from Constants import *
import math

#python main.py --algo DFS --start 143 --goal 291
def DFS(g:Graph, sc:pygame.Surface):
    print('Implement DFS algorithm')
    path =[]
    open_set = [g.start.value]
    closed_set = []
    father = [-1]*g.get_len()
    while True:
        currentNode = open_set.pop()
        if g.grid_cells[currentNode] != g.start and g.grid_cells[currentNode] != g.goal:
            g.grid_cells[currentNode].set_color(yellow)
            g.draw(sc)
        # Check if node is goal
        if currentNode == g.goal.value:
            father[g.start.value] = g.start.value
            while father[currentNode] != currentNode:
                path.append(currentNode)
                currentNode = father[currentNode]
            break
        # expanding nodes
        for i in g.get_neighbors(g.grid_cells[currentNode]):
            if i.value not in closed_set:
                open_set.append(i.value)
                closed_set.append(i.value)
                father[i.value]= currentNode
                if i.value != g.start.value and i.value != g.goal.value:
                    i.set_color(red)
                    g.draw(sc)
        if currentNode != g.start.value and currentNode != g.goal.value:
            g.grid_cells[currentNode].set_color(blue)
            g.draw(sc)
    #draw final path
    for h in path:
        if h != g.start.value and h != g.goal.value:
            g.grid_cells[h].set_color(grey)
            g.draw(sc)

#python main.py --algo BFS --start 97 --goal 123
def BFS(g:Graph, sc:pygame.Surface):
    print('Implement BFS algorithm')

    open_set = [g.start.value]
    closed_set = []
    father = [-1]*g.get_len()
    path = []
    while True:
        currentNode = open_set.pop(0)
        if g.grid_cells[currentNode] != g.start and g.grid_cells[currentNode] != g.goal:
            g.grid_cells[currentNode].set_color(yellow)
            g.draw(sc)
        #closed_set.append(currentNode)
        # Check if node is goal
        if currentNode == g.goal.value:
            father[g.start.value] = g.start.value
            while father[currentNode] != currentNode:
                path.append(currentNode)
                currentNode = father[currentNode]
            break
        #expanding nodes
        for i in g.get_neighbors(g.grid_cells[currentNode]):
            if i.value not in closed_set:
                father[i.value]= currentNode
                open_set.append(i.value)
                closed_set.append(i.value)
                if i.value != g.start.value and i.value != g.goal.value:
                    i.set_color(red)
                    g.draw(sc)
        if currentNode != g.start.value and currentNode != g.goal.value:
            g.grid_cells[currentNode].set_color(blue)
            g.draw(sc)
    #draw final path
    for h in path:
        if h != g.start.value and h != g.goal.value:
            g.grid_cells[h].set_color(grey)
            g.draw(sc)

#python main.py --algo UCS --start 120 --goal 169
def UCS(g:Graph, sc:pygame.Surface):
    print('Implement UCS algorithm')
    open_set = {}
    open_set[g.start.value] = 0
    closed_set:list[int] = []
    father = [-1]*g.get_len()
    cost = [100_000]*g.get_len()
    cost[g.start.value] = 0
    path = []

    while len(open_set) > 0:
        currentNode = None
        for i in open_set:
            if currentNode == None or cost[i] < cost[currentNode]:
                currentNode = i
        if g.grid_cells[currentNode] != g.start and g.grid_cells[currentNode] != g.goal:
            g.grid_cells[currentNode].set_color(yellow)
            g.draw(sc)
        #check if is goal 
        if currentNode == g.goal.value:
            while father[currentNode] != currentNode:
                path.append(currentNode)
                currentNode = father[currentNode]
            break
        #expanding nodes
        for j in g.get_neighbors(g.grid_cells[currentNode]):
            if j.value not in open_set and j.value not in closed_set:
                open_set[j.value] =  cost[currentNode]/100_000
                father[j.value] = currentNode
                cost[j.value] = cost[currentNode] + 100_000
                if j != g.start and j != g.goal:
                    j.set_color(red)
                    g.draw(sc)
            else:
                if cost[j.value] > cost[currentNode] + 100_000:
                    cost[j.value] = cost[currentNode] + 100_000
                    father[j.value] = currentNode
                    if j.value in closed_set:
                        closed_set.remove(j.value)
                        open_set[j.value] = cost[currentNode]/100_000
        del open_set[currentNode]
        closed_set.append(currentNode)
        if g.grid_cells[currentNode] != g.start and g.grid_cells[currentNode] != g.goal:
            g.grid_cells[currentNode].set_color(blue)
            g.draw(sc)
    #draw final path
    for h in path:
        if h != g.start.value and h != g.goal.value:
            g.grid_cells[h].set_color(grey)
            g.draw(sc)

# python main.py --algo AStar --start 71 --goal 318
def AStar(g:Graph, sc:pygame.Surface):
    print('Implement A* algorithm')
    open_set = {}
    open_set[g.start.value] = 0
    closed_set:list[int] = []
    father = [-1]*g.get_len()
    cost = [100_000]*g.get_len()
    cost[g.start.value] = 0
    path = []

    while len(open_set) > 0:
        currentNode = None
        for i in open_set:
            if currentNode == None or open_set[i] + math.sqrt((g.grid_cells[i].x -  g.goal.x)**2 + (g.grid_cells[i].y -  g.goal.y)**2) < open_set[currentNode] + math.sqrt((g.grid_cells[currentNode].x -  g.goal.x)**2 + (g.grid_cells[currentNode].y -  g.goal.y)**2):
                currentNode = i  
        if g.grid_cells[currentNode] != g.start and g.grid_cells[currentNode] != g.goal:
            g.grid_cells[currentNode].set_color(yellow)
            g.draw(sc)
        #check if node is goal
        if currentNode == g.goal.value:
            while father[currentNode] != currentNode:
                path.append(currentNode)
                currentNode = father[currentNode]
            break
        #expanding node
        for j in g.get_neighbors(g.grid_cells[currentNode]):
            if j.value not in open_set and j.value not in closed_set:
                open_set[j.value] =  cost[currentNode]/100_000
                father[j.value] = currentNode
                cost[j.value] = cost[currentNode] + 100_000
                if j != g.start and j != g.goal:
                    j.set_color(red)
                    g.draw(sc)
            else:
                if cost[j.value] > cost[currentNode] + 100_000:
                    cost[j.value] = cost[currentNode] + 100_000
                    father[j.value] = currentNode
                    if j.value in closed_set:
                        closed_set.remove(j.value)
                        open_set[j.value] = cost[currentNode]/100_000
        del open_set[currentNode]
        closed_set.append(currentNode)
        if g.grid_cells[currentNode] != g.start and g.grid_cells[currentNode] != g.goal:
            g.grid_cells[currentNode].set_color(blue)
            g.draw(sc)
    #draw final path
    for h in path:
        if h != g.start.value and h != g.goal.value:
            g.grid_cells[h].set_color(grey)
            g.draw(sc)

# python main.py --algo Greedy --start 67 --goal 210
def Greedy(g:Graph, sc:pygame.Surface):
    print('Implement A* algorithm')
    open_set = {}
    open_set[g.start.value] = 0
    closed_set:list[int] = []
    father = [-1]*g.get_len()
    cost = [100_000]*g.get_len()
    cost[g.start.value] = 0
    path = []

    while len(open_set) > 0:
        currentNode = None
        for i in open_set:
            if currentNode == None or math.sqrt((g.grid_cells[i].x -  g.goal.x)**2 + (g.grid_cells[i].y -  g.goal.y)**2) < math.sqrt((g.grid_cells[currentNode].x -  g.goal.x)**2 + (g.grid_cells[currentNode].y -  g.goal.y)**2):
                currentNode = i  
        if g.grid_cells[currentNode] != g.start and g.grid_cells[currentNode] != g.goal:
            g.grid_cells[currentNode].set_color(yellow)
            g.draw(sc)
        #check if node is goal
        if currentNode == g.goal.value:
            while father[currentNode] != currentNode:
                path.append(currentNode)
                currentNode = father[currentNode]
            break
        #expanding node
        for j in g.get_neighbors(g.grid_cells[currentNode]):
            if j.value not in open_set and j.value not in closed_set:
                open_set[j.value] =  cost[currentNode]/100_000
                father[j.value] = currentNode
                cost[j.value] = cost[currentNode] + 100_000
                if j != g.start and j != g.goal:
                    j.set_color(red)
                    g.draw(sc)
            else:
                if cost[j.value] > cost[currentNode] + 100_000:
                    cost[j.value] = cost[currentNode] + 100_000
                    father[j.value] = currentNode
                    if j.value in closed_set:
                        closed_set.remove(j.value)
                        open_set[j.value] = cost[currentNode]/100_000
        del open_set[currentNode]
        closed_set.append(currentNode)
        if g.grid_cells[currentNode] != g.start and g.grid_cells[currentNode] != g.goal:
            g.grid_cells[currentNode].set_color(blue)
            g.draw(sc)
    #draw final path
    for h in path:
        if h != g.start.value and h != g.goal.value:
            g.grid_cells[h].set_color(grey)
            g.draw(sc)

