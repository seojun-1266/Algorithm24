def dfs(vertex, adjMat, start, visited):
    visited[start] = True
    print(vertex[start])

    for i in range(len(vertex)):
        if adjMat[start][i] == 1 and not visited[i]:
            dfs(vertex, adjMat, i, visited)

vertex = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H']
adjMat = [[0, 1, 1, 0, 0, 0, 0, 0],
          [1, 0, 0, 1, 0, 0, 0, 0],
          [1, 0, 0, 1, 1, 0, 0, 0],
          [0, 1, 1, 0, 0, 1, 0, 0],
          [0, 0, 1, 0, 0, 0, 1, 1],
          [0, 0, 0, 1, 0, 0, 0, 0],
          [0, 0, 0, 0, 1, 0, 0, 1],
          [0, 0, 0, 0, 1, 0, 1, 0]]

visited = [False] * len(vertex)

print("Depth First Traversal:")
dfs(vertex, adjMat, 0, visited)
