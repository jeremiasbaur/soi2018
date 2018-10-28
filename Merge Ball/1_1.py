f = open('merge-ball-sub1-attempt0.txt', 'r')
f_output = open('task1_1.txt', 'w')

testcases = int(f.readline())

for i in range(testcases):
    ball_amount = int(f.readline())
    balls = list(map(int, f.readline().split()))
    multiplier = (ball_amount//2)*2
    print('Case #' + str(i) + ": " + str(balls[0]*multiplier))
    f_output.write('Case #' + str(i) + ": " + str(balls[0]*multiplier) + "\n")
