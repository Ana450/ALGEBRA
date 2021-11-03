
p=100049

for g in range(2, p):
    for x in range(1, p-1):
        if pow(g,x)%p==1:
            break
    if x == p-2:
        break

for x in range(1, p):
    y = pow(g,x)%p
    print(g,"^",x,"mod",p,"=",y)
print(g)
