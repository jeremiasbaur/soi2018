from collections import deque

f = open('storytelling-sub4-attempt6.txt', 'r')
f_output = open('task5_4.txt', 'w')

T = int(f.readline())

second = True

for i in range(T):
    mouses_amount = int(f.readline())
    mouses = list(map(int, f.readline().split()))
    mouses_time = []
    amount = 0
    max_time = 0

    if mouses_amount < 4:
        amount = sum(mouses)
        mouses_time = [0]
        for x in range(1, mouses_amount):
            mouses_time.append(mouses_time[-1]+mouses[x-1])

    elif mouses_amount%2 == 0:
        for j in range(mouses_amount):
            max_time = max(max_time, mouses[j-1]+mouses[j])
            if j%2==0:
                mouses_time.append(0)
            else:
                if j+1 == mouses_amount:
                    mouses_time.append(max(mouses[j-1],mouses[0]))
                else:
                    mouses_time.append(max(mouses[j-1],mouses[j+1]))
        amount = max_time
    else:
        min_waiter = [10**10,()]
        for j in range(mouses_amount):
            if min_waiter[0] > min(min_waiter[0], mouses[j-1] + mouses[j] + mouses[j+1-mouses_amount]):
                min_waiter[0] = min(min_waiter[0], mouses[j-1] + mouses[j] + mouses[j+1-mouses_amount])
                if j - 1 == -1:
                    min_waiter[1] = (mouses_amount-1,j)
                else:
                    min_waiter[1] = (j-1,j)
            max_time = max(max_time, mouses[j-1]+mouses[j])
        amount = 10**10
        if min_waiter[0] > 0:
            if mouses[min_waiter[1][0]-1] < mouses[min_waiter[1][1]+1-mouses_amount]:

                amount = mouses[min_waiter[1][0]-1] + mouses[min_waiter[1][0]] + mouses[min_waiter[1][1]]
            else:
                amount = mouses[min_waiter[1][1]+1-mouses_amount] + mouses[min_waiter[1][0]] + mouses[min_waiter[1][1]]
            amount = max(max_time, amount)
        else:
            amount = max_time

    print('Case #%d: %d' %(i, amount))
    f_output.write('Case #%d: %d\n' %(i, amount))

    if not second:
        [f_output.write(str(x) + " ") for x in mouses_time[:-1]]
        f_output.write(str(mouses_time[-1]))
        f_output.write("\n")
