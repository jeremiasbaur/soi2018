from collections import deque

f = open('mergeball-sub3-attempt0.txt', 'r')
f_output = open('task1_3.txt', 'w')

testcases = int(f.readline())

for i in range(testcases):
    ball_amount = int(f.readline())
    balls = list(map(int, f.readline().split()))

    no_change = True
    while no_change:
        merged = False
        no_change = False
        new_balls = deque()
        j = 0
        while j<len(balls) and len(balls)>1:
            if balls[j] == balls[j+1-len(balls)]:
                new_balls.append(balls[j]*2)

                if j+2<=len(balls)-1:
                    [new_balls.append(balls[x]) for x in range(j+2, len(balls))]
                #print(j+2, new_balls)
                #time.sleep(1)
                no_change = True
                balls = new_balls
                break
            new_balls.append(balls[j])
            j+=1
        if no_change:
            balls = new_balls

    if len(balls) == 1:
        print('Case #' + str(i) + ": Single")
        f_output.write('Case #' + str(i) + ": Single\n")
    else:
        print('Case #' + str(i) + ": Multiple")
        f_output.write('Case #' + str(i) + ": Multiple\n")
