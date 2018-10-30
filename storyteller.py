from collections import deque

f = open('test.txt', 'r')
f_output = open('task2_5.txt', 'w')

T = int(f.readline())

second = False

for i in range(T):
    mouses_amount = int(f.readline())
    mouses = list(map(int, f.readline().split()))
    mouses_time = []
    amount = 0

    if mouses_amount < 4:
        amount = sum(mouses)
        mouses_time = [0]
        for x in range(1, mouses_amount):
            mouses_time.append(mouses_time[-1]+mouses[x-1])

    elif mouses_amount%2 == 0:
        max_time = 0
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

    print(i, amount, mouses, mouses_time)
    f_output.write('Case #' + str(i) + ": " + str(amount) + "\n")

    if not second:
        [f_output.write(str(x) + " ") for x in mouses_time[:-1]]
        f_output.write(str(mouses_time[-1]))
        f_output.write("\n")

