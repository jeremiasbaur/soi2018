f = open('pipeline-sub2-attempt12.txt', 'r')
f_output = open('task3_2.txt', 'w')

testcases = int(f.readline())

for i in range(testcases):
    pumps_count, max_pumps = map(int, f.readline().split())
    pump_stations = list(map(int, f.readline().split()))
    pump_true = [False for x in range(pumps_count)]

    if pumps_count == 1:
        print('Case #%d: %d\n%d' %(i, 0,pump_stations[0]))
        f_output.write('Case #%d: %d\n%d\n' %(i, 0,pump_stations[0]))
        continue

    prev_mid = -1
    count_pumps = 0
    l = 0
    for j in range(1,pumps_count):
        l = max(l, pump_stations[j]-pump_stations[j-1])
    r = pump_stations[-1]-pump_stations[0]
    while count_pumps != max_pumps:
        if l>=r:
            pump_true = [False for x in range(pumps_count)]
            j = 1
            looking_from = 0
            impossible = False
            ltc = l
            while j != pumps_count:
                if pump_stations[j]-pump_stations[j-1] > ltc:
                    impossible = True
                    break
                elif pump_stations[j]-pump_stations[looking_from] == ltc:
                    pump_true[j], pump_true[looking_from] = True, True
                    looking_from = j
                elif pump_stations[j]-pump_stations[looking_from] > ltc:
                    pump_true[looking_from], pump_true[j-1] = True, True
                    looking_from = j-1
                j += 1
            pump_true[j-1] = True
            pump_true[0] = True
            print(l,r, "Case: ",i)
            break
        mid = (l+r)//2

        pump_true = [False for x in range(pumps_count)]
        j = 1
        looking_from = 0
        impossible = False
        ltc = mid
        while j != pumps_count:
            if pump_stations[j]-pump_stations[j-1] > ltc:
                impossible = True
                break
            elif pump_stations[j]-pump_stations[looking_from] == ltc:
                pump_true[j], pump_true[looking_from] = True, True
                looking_from = j
            elif pump_stations[j]-pump_stations[looking_from] > ltc:
                pump_true[looking_from], pump_true[j-1] = True, True
                looking_from = j-1
            j += 1

        if impossible:
            l = mid + 1
            prev_mid = ltc
            continue

        pump_true[j-1] = True
        pump_true[0] = True
        required_count = 0
        for j in range(pumps_count):
            if pump_true[j]:
                required_count+=1

        if required_count > max_pumps:
            l = mid + 1
        else:
            r = mid

    counter = 0
    for j in pump_true:
        if j:
            counter+=1

    j = 1
    while counter!= max_pumps:
        if not pump_true[j]:
            pump_true[j] = True
            counter+=1
        j+=1

    last = pump_stations[0]
    max_ltc = 0
    counter = 1
    output = str(pump_stations[0]) + " "
    for j in range(1, pumps_count):
        if pump_true[j]:
            output += str(pump_stations[j]) + " "
            max_ltc = max(max_ltc, pump_stations[j]-last)
            last = pump_stations[j]
            counter += 1



    if counter > 9000:
        f_output.write("Case #%d: %d\n%s\n" %(i, max_ltc, "Over 9000"))
    else:
        f_output.write("Case #%d: %d\n%s\n" %(i, max_ltc, output))
