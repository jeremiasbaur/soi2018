import heapq, math

f = open('mergeball-sub4-attempt0.txt', 'r')
f_output = open('task1_4.txt', 'w')

testcases = int(f.readline())

for i in range(testcases):
    ball_amount, ball_max_size = map(int, f.readline().split())
    balls = list(map(int, f.readline().split()))

    heap = set()
    for j in range(ball_amount):
        for x in range(int(math.log(ball_max_size, 2)+1)):

            if balls[j]*2**x<=ball_max_size:
                heap.add(balls[j]*2**x)

    print('Case #%d: %d %s' %(i, len(heap), ''.join([str(x) + ' ' for x in sorted(heap)])))
    f_output.write('Case #%d: %d %s\n' %(i, len(heap), ''.join([str(x) + ' ' for x in sorted(heap)])))
