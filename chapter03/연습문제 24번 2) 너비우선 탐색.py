from collections import deque

def bfs(vertex, adjMat, start):
    visited = [False] * len(vertex)
    queue = deque()

    queue.append(start)
    visited[start] = True

    while queue:
        current = queue.popleft()
        print(vertex[current])

        for i in range(len(vertex)):
            if adjMat[current][i] == 1 and not visited[i]:
                queue.append(i)
                visited[i] = True

vertex = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H']
adjMat = [[0, 1, 1, 0, 0, 0, 0, 0],
          [1, 0, 0, 1, 0, 0, 0, 0],
          [1, 0, 0, 1, 1, 0, 0, 0],
          [0, 1, 1, 0, 0, 1, 0, 0],
          [0, 0, 1, 0, 0, 0, 1, 1],
          [0, 0, 0, 1, 0, 0, 0, 0],
          [0, 0, 0, 0, 1, 0, 0, 1],
          [0, 0, 0, 0, 1, 0, 1, 0]]

print("Breadth First Traversal:")
bfs(vertex, adjMat, 0)
