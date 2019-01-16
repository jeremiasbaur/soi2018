f = open('pipeline-sub3-attempt0.txt', 'r')
f_output = open('task3_3.txt', 'w')

testcases = int(f.readline())

for i in range(testcases):
    pumps_count, ltc = map(int, f.readline().split())
    pump_stations = list(map(int, f.readline().split()))

    output = 'Case #%d: ' %(i)

    for k in range(1,ltc+1):
        pump_true = [[False, pump_stations[j]] for j in range(pumps_count)]
        last = False
        j = 1
        impossible = False
        looking_from = 0
        pump_true[0][0] = True
        pump_amount = 1

        while j != pumps_count:
            if pump_stations[j]-pump_stations[j-1] > k:
                pump_amount = -1
                impossible = True
                break
            elif pump_stations[j]-pump_stations[looking_from] == k:
                pump_true[j][0], pump_true[looking_from][0] = True, True
                pump_amount += 1
                looking_from = j
                if j == pumps_count-1:
                    last = True
            elif pump_stations[j]-pump_stations[looking_from] > k:
                pump_true[looking_from][0], pump_true[j-1][0] = True, True
                pump_amount += 1
                looking_from = j-1
                if j == pumps_count-1:
                    last = True
            j += 1

        if not last:
            pump_amount += 1

        pump_true[-1][0] = True
        c = 0
        for l in pump_true:
            if l[0]:
                c += 1

        if not impossible:
            output += str(c) + " "
        else:
            output += "-1 "

    print(output)
    f_output.write(output + "\n")
