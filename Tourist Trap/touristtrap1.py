from collections import deque

f = open('touristtrap-sub1-attempt0.txt', 'r')
f_output = open('task4_1.txt', 'w')

testcases = int(f.readline())

def get_possible_nodes(city, x, y):
    children = set()
    if x-1 >= 0 and city[y][x-1] == '_':
        children.add((x-1,y))
    if x+1<len(city[0]) and city[y][x+1] == '_':
        children.add((x+1, y))
    if y-1>=0 and city[y-1][x] == '_':
        children.add((x, y-1))
    if y+1<len(city) and city[y+1][x] == '_':
        children.add((x, y+1))
    return children

def bfs(city, edge_nodes, stoffl_x, stoffl_y):
    unvisited = deque()
    visited = set()
    if (stoffl_x, stoffl_y) in edge_nodes:
        return True
    visited.add((stoffl_x, stoffl_y))
    for child in get_possible_nodes(city, stoffl_x, stoffl_y):
        unvisited.append(child)

    while len(unvisited) != 0:
        node = unvisited.popleft()
        if node in visited:
            continue
        if node in edge_nodes:
            return True
        visited.add(node)
        for child in get_possible_nodes(city, node[0], node[1]):
            if child in visited:
                continue
            if child in edge_nodes:
                return True
            unvisited.append(child)
    return False


for i in range(testcases):
    width, height, stoffl_x, stoffl_y = map(int, f.readline().split())

    city = []
    edge_nodes = set()
    for y in range(height):
        line = f.readline()
        city.append([char for char in line])
        if city[-1][-1] == '\n':
            city[-1].remove('\n')
        if y == height-1 or y == 0:
            [edge_nodes.add((x, y)) if city[-1][x] == '_' else '' for x in range(len(city[-1]))]
        else:
            if city[-1][0] == '_':
                edge_nodes.add((0, y))
            if city[-1][width-1] == '_':
                edge_nodes.add((width-1, y))

    if len(edge_nodes)==0 or not bfs(city, edge_nodes, stoffl_x, stoffl_y):
        print('Case #%d: %s' %(i, "IMPOSSIBLE"))
        f_output.write('Case #%d: %s\n' %(i, "IMPOSSIBLE"))
    else:
        print('Case #%d: %s' %(i, "POSSIBLE"))
        f_output.write('Case #%d: %s\n' %(i, "POSSIBLE"))
