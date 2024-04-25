def proper_subset(A, B):
    if set(A).issubset(set(B)) and set(A) != set(B):
        return True
    else:
        return False

A = [1, 2]
B = [1, 2, 3, 4, 5]
print("A가 B의 진부분집합?", proper_subset(A, B))
