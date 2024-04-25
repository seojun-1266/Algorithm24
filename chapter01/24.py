import heapq

def r(n):
    sorted_nums = []
    heapq.heapify(n)
    while n:
        sorted_nums.append(heapq.heappop(n))
    return sorted_nums

n = list(map(int, input("숫자 리스트를 입력하세요 (공백으로 구분): ").split()))
sorted_nums = r(n)
print("정렬된 숫자:", sorted_nums)
