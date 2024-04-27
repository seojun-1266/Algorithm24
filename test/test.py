def quick_sort(A, left, right):
    if left <right : 
        mid = partition(A, left, right)
        quick_sort(A, left, mid-1)
        quick_sort(A, mid + 1, right)