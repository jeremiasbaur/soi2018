f = open('pipeline-sub1-attempt5.txt', 'r')
f_output = open('task3_1.txt', 'w')

testcases = int(f.readline())

for i in range(testcases):
    pumps_count, ltc = map(int, f.readline().split())
    pump_stations = list(map(int, f.readline().split()))
    pump_true = [[False, pump_stations[j]] for j in range(pumps_count)]
    impossible = False


    """if i == 90:
        j = 1
        print(ltc)
        while j != pumps_count:
            if pump_stations[j]-pump_stations[j-1]>ltc:
                print(ltc,pump_stations[j], pump_stations[j-1], pump_stations[j]-pump_stations[j-1])
            j+=1"""
    j = 1
    looking_from = 0
    while j != pumps_count:
        if pump_stations[j]-pump_stations[j-1] > ltc:
            impossible = True
            break
        elif pump_stations[j]-pump_stations[looking_from] == ltc:
            pump_true[j][0], pump_true[looking_from][0] = True, True
            looking_from = j
        elif pump_stations[j]-pump_stations[looking_from] > ltc:
            pump_true[looking_from][0], pump_true[j-1][0] = True, True
            looking_from = j-1
        j += 1
    pump_true[j-1][0] = True
    pump_true[0][0] = True

    if impossible:
        output = "Impossible"
    else:
        output = ""
        required_count = 0
        for j in range(pumps_count):
            if pump_true[j][0]:
                output += str(pump_true[j][1]) + " "
                required_count+=1
        output = str(required_count) + " " + output
        if required_count > 9000:
            output = required_count

    print('Case #%d: %s' %(i, output))
    f_output.write('Case #%d: %s\n' %(i, output))
