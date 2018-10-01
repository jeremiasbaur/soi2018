T = int(input())

def binaryDeleteSmallerThan(n, currentList):
    l = 0
    r = len(currentList) - 1
    i = r//2

    while(currentList[i]!=n):
        if currentList[i]>n:
            r = i
            i = l + (r-l)//2
            print(l, i, r)
        elif currentList[i]<n:
            l = i
            i = i + (r-l)//2
            print(l, i, r)
    print(currentList[i],n)

sList = [1,3,5,6,7,9,10,12,13,16]
print(binaryDeleteSmallerThan(13, sList))

for i in range(T):
    N = int(input())
    #N, I = map(int, input().split())
    houses = list(map(int, input().split()))

    leftList = list()
    rightList = list()

