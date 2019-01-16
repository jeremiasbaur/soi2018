from collections import deque

def pop_to(n, stack, length):
    while True:
        if length > 0 and stack[-1]<= n:
            stack.pop()
            length-=1
        else:
            break
    return stack, length

f = open('ceremony-sub3-attempt0.txt', 'r')
f_output = open('task2_3.txt', 'w')

T = int(f.readline())

for i in range(T):
    N,index = map(int, f.readline().split())
    houses = list(map(int, f.readline().split()))
    amount = [0 for j in range(N)]

    if N==1:
        amount[index] = 0
    elif N==2:
        amount[index] = 1
    elif index == 0:
        amount[index] = 1
        height = houses[1]
        for j in range(2, len(houses)):
            if height < houses[j]:
                height = houses[j]
                amount[index] += 1
    else:
        leftList = deque()
        rightList = deque()
        length = 0

        for j in range(1, N):
            if length > 0:
                leftList, length = pop_to(houses[j-1], leftList, length)
            leftList.append(houses[j-1])
            length += 1
            amount[j] = length
        length = 0
        for j in range(2, N):
            if len(rightList) > 0:
                rightList, length = pop_to(houses[-j+1], rightList, length)
            rightList.append(houses[-j+1])
            length += 1
            amount[-j] += length

    print(i, amount[index])
    f_output.write('Case #' + str(i) + ": " + str(amount[index]) + "\n")
