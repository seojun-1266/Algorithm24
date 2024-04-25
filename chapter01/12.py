import collections

Q = collections.deque()        
Q.append(0)                     
Q.append(1)                    

print("F(0) = 0")
print("F(1) = 1")

for i in range(2, 11):          
    first = Q.popleft()        
    second = Q.popleft()     
    val = first + second        
    Q.appendleft(second)        
    Q.append(val)              
    print("F(%d) ="%i, val)     