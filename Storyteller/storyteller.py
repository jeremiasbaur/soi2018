f = open('storytelling-sub2-attempt0.txt', 'r')
f_output = open('task5_2.txt', 'w')

T = int(f.readline())

second = False

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
            if min_waiter[0] > mouses[j-1] + mouses[j] + mouses[j+1-mouses_amount]:
                min_waiter[0] = mouses[j-1] + mouses[j] + mouses[j+1-mouses_amount]
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

        time_first = mouses[min_waiter[1][0]]
        time_sec = mouses[min_waiter[1][1]]
        time_first_n = mouses[min_waiter[1][0]-1]
        time_sec_n = mouses[min_waiter[1][1]+1-mouses_amount]

        if min_waiter[1][1] + 1 == mouses_amount:
            j_start = 0
            j = 1
        elif min_waiter[1][1] + 2 == mouses_amount:
            j_start = min_waiter[1][1] + 1
            j = 0
        else:
            j_start = min_waiter[1][1] + 1
            j = j_start+1

        mouses_time = [0 for x in range(mouses_amount)]

        no_zero = True
        last_no_zero = mouses[j_start]
        while True:
            if j == mouses_amount:
                j = 0
            if no_zero:
                mouses_time[j] = max(last_no_zero, mouses[j+1-mouses_amount])
                no_zero = False
            else:
                last_no_zero = mouses[j]
                mouses_time[j] = 0
                no_zero = True
            if j == j_start:
                #mouses_time[j] = 0
                break
            j+=1
        if time_first_n < time_sec_n:
            mouses_time[min_waiter[1][0]] = time_first_n
            mouses_time[min_waiter[1][1]] = max(time_first_n + time_first, time_sec_n)
        else:
            mouses_time[min_waiter[1][0]] = max(time_sec_n + time_sec, time_first_n)
            mouses_time[min_waiter[1][1]] = time_sec_n

        mouses_time[min_waiter[1][0]-1] = 0
        mouses_time[min_waiter[1][1]+1-mouses_amount] = 0
        print(min_waiter)
    print('Case #%d: %d' %(i, amount), mouses_time, mouses)
    f_output.write('Case #%d: %d\n' %(i, amount))

    if not second:
        for x in mouses_time:
            f_output.write(str(x) + " ")
        f_output.write("\n")
