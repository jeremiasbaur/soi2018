from collections import deque

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

def pop_to(n, stack, length):
    while True:
        if length > 0 and stack[-1]<= n:
            stack.pop()
            length-=1
        else:
            break
    return stack, length

f = open('ceremony-sub5-attempt0.txt', 'r')
f_output = open('task2_5.txt', 'w')

T = int(f.readline())

for i in range(T):
    N = int(f.readline())
    houses = list(map(int, f.readline().split()))
    amount = [0 for j in range(N)]

    if N==1:
        m = 0
    elif N==2:
        m = 1
    else:
        leftList = deque()
        rightList = deque()
        length = 0
        m = 0
        for j in range(1,N):
            if length > 0:
                leftList, length = pop_to(houses[j-1], leftList, length)
            leftList.append(houses[j-1])
            length += 1
            amount[j] = length
        length = 0
        for j in range(2,N):
            if len(rightList) > 0:
                rightList, length = pop_to(houses[-j+1], rightList, length)
            rightList.append(houses[-j+1])
            length += 1
            amount[-j] += length

            if amount[-j] > m:
                m = amount[-j]
    print(i, m)
    f_output.write('Case #' + str(i) + ": " + str(m) + "\n")
