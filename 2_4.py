def binaryDeleteSmallerThan(n, currentList, lenList):
    #lenList = len(currentList)
    l = 0
    r = lenList - 1
    i = (l+r)//2

    if lenList==1:
        if n < currentList[-1]:
            return currentList
        else:
            return list()
    if n < currentList[-1]:
        return currentList
    #elif n == currentList[-1]:
    #    return list()
    else:
        while(currentList[i]!=n):
            #print(l, r, i, currentList)
            #print("While", l, i, r, currentList[i], n)
            if l>=r:# and currentList[l]>n>currentList[r]:
                return currentList[:r]
            if currentList[i] < n:
                r = i-1
                i = (l+r)//2
            elif currentList[i] > n:
                l = i+1
                i = (l+r)//2
        #print(currentList[i])
        return currentList[:i]

sList = [19,18,13,10,7,5,4,3,1]
print(binaryDeleteSmallerThan(19, sList, len(sList)))

f = open('ceremony-sub5-attempt0.txt', 'r')
fOutput = open('task2_5.txt','w')

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
    lLeft = 0
    lRight = 0
    m = 0
    for j in range(1,N):
        if lLeft > 0:
            leftList = binaryDeleteSmallerThan(houses[j-1], leftList, lLeft)
        leftList.append(houses[j-1])
        lLeft = len(leftList)
        amount[j] = lLeft
        #amount[j][0] = len(leftList)
        #print(houses[j], leftList)
    for j in range(2,N):
        if lRight > 0:
            rightList = binaryDeleteSmallerThan(houses[-j+1], rightList, lRight)
        rightList.append(houses[-j+1])
        lRight = len(rightList)
        amount[-j] += lRight
        #amount[-j][1] += len(rightList)
        if amount[-j] > m:
            m = amount[-j]
        #print(houses[-j], rightList, houses[-j+1])
    print(i, m)
    fOutput.write('Case #'+str(i)+": "+str(m)+"\n")
