from collections import deque

f = open('mergeball-sub3-attempt0.txt', 'r')
f_output = open('task1_3.txt', 'w')

testcases = int(f.readline())

for i in range(testcases):
    ball_amount = int(f.readline())
    balls = deque(map(int, f.readline().split()))

    merged = False
    new_balls = deque()
    for j in range(1, ball_amount):
        if merged:
            merged = False
            continue
        if balls[j-1] == balls[j] and not merged:
            merged = True
            new_balls.append(balls[j]*2)
            continue
        new_balls.append(balls[j])

    print(new_balls)

    #print('Case #' + str(i) + ": " + result)
    #f_output.write('Case #' + str(i) + ": " + result + "\n")
