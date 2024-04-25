def selection_sort(A, n):                   
    for i in range(n-1):                    
        least = i                           
        for j in range(i+1, n):             
            if A[j] < A[least]:            
                least = j                  
        A[i], A[least] = A[least], A[i]     

A = [3, 7, 9, 4, 2, 8, 1, 5]
selection_sort(A, len(A))
print(A)