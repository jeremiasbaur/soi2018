import math

f = open('mergeball-sub2-attempt0.txt', 'r')
f_output = open('task1_2.txt', 'w')

testcases = int(f.readline())

for i in range(testcases):
    ball_amount = int(f.readline())
    balls = list(map(int, f.readline().split()))
    if math.log(ball_amount, 2).is_integer() or ball_amount == 1:
        result = "Single"
    else:
        result = "Multiple"

    print('Case #' + str(i) + ": " + result)
    f_output.write('Case #' + str(i) + ": " + result + "\n")
