f = open('pipeline-sub3-attempt0.txt', 'r')
f_output = open('task3_3.txt', 'w')

testcases = int(f.readline())

for i in range(testcases):
    pumps_count, ltc = map(int, f.readline().split())
    pump_stations = list(map(int, f.readline().split()))

    output = 'Case #%d: ' %(i)

    pumps_amount = []

    for ltc in range(1,M+1):
        last = False
        j = 1
        impossible = False
        looking_from = 0
        pump_amount = 1

        while j != pumps_count:
            if pump_stations[j]-pump_stations[j-1] > k:
                pump_amount = -1
                break
            elif pump_stations[j]-pump_stations[looking_from] == k:
                pump_amount += 1
                looking_from = j
                if j == pumps_count-1:
                    last = True
            elif pump_stations[j]-pump_stations[looking_from] > k:
                pump_amount += 1
                looking_from = j-1
                if j == pumps_count-1:
                    last = True
            j += 1

        if not last:
            pump_amount += 1

        pumps_amount.append(pumps_amount)
