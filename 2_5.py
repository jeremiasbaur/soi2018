def binaryDeleteSmallerThan(n, currentList):
    lenList = len(currentList)
    l = 0
    r = lenList - 1
    i = r//2

    if lenList==1:
        if n < currentList[-1]:
            return currentList
        else:
            return list()
    if n < currentList[-1]:
        return currentList
    elif n == currentList[-1]:
        return list()
    else:
        while(currentList[i]!=n):
            #print(l, r, i, currentList)
            if l==r:
                break
            if l==r-1 and currentList[l]>n>currentList[r]:
                return currentList[:r]
            if currentList[i] < n:
                r = i
                i = l + (r-l)//2
            elif currentList[i] > n:
                l = i
                i = i + (r-l)//2
        return currentList[:i]

#sList = [3]
#print(binaryDeleteSmallerThan(3, sList))

f = open('ceremony-sub5-attempt0.txt', 'r')
fOutput = open('task2_5_2.txt','w')

T = int(f.readline())

for i in range(T):
    N = int(f.readline())
    #N, I = map(int, input().split())
    houses = list(map(int, f.readline().split()))
    amount = [0 for j in range(N)] # view to the [left, right] of house j
    #amount = [[0,0] for j in range(N)] # view to the [left, right] of house j

    if N==1:
        fOutput.write('Case #'+str(i)+": 0\n")
        continue
    elif N==2:
        fOutput.write('Case #'+str(i)+": 1\n")
        continue
    leftList = list()
    rightList = list()
    m = 0
    for j in range(1,N):
        if len(leftList) > 0:
            leftList = binaryDeleteSmallerThan(houses[j-1], leftList)
        leftList.append(houses[j-1])
        amount[j] = len(leftList)
        #amount[j][0] = len(leftList)
        #print(houses[j], leftList)
    for j in range(2,N):
        if len(rightList) > 0:
            rightList = binaryDeleteSmallerThan(houses[-j+1], rightList)
        rightList.append(houses[-j+1])
        amount[-j] += len(rightList)
        #amount[-j][1] += len(rightList)
        if amount[-j] > m:
            m = amount[-j]
        #print(houses[-j], rightList, houses[-j+1])
    print(i, m)
    fOutput.write('Case #'+str(i)+": "+str(m)+"\n")
