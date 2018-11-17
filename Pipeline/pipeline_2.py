import math

f = open('pipeline-sub2-attempt0.txt', 'r')
f_output = open('task3_2.txt', 'w')

testcases = int(f.readline())

def binary_search(pump_stations, look_for):
    l = 0
    r = len(pump_stations)-1

    while l<=r:
        m = (l+r)//2
        if pump_stations[m] < look_for:
            l = m + 1
        else: #pump_stations[m] > look_for:
            r = m -1
        #print(pump_stations, look_for, l, r)
    if math.fabs(pump_stations[l]-look_for) > math.fabs(pump_stations[r]-look_for):
        #print("right: ",l, r, look_for)
        return r
    else:
        #print("left: ",l, r, look_for)
        return l

def get_current_index(pump_stations, start, end, spaces):
    if (math.ceil((end-start)/spaces)+(end-start)//spaces)/2 >= (end-start)/spaces:
        step = (end-start)//spaces
    else:
        step = math.ceil((end-start)/spaces)
    #print(step)
    #step = (end-start)//spaces
    start_next = binary_search(pump_stations, start + step)
    end_next = binary_search(pump_stations, end - step)

    if math.fabs(start+step - pump_stations[start_next]) > math.fabs(end-step - pump_stations[end_next]):
        #print(pump_stations[end_next],"1")
        return False, pump_stations[end_next], end_next
    else:
        #print(pump_stations[start_next],"2")
        return True, pump_stations[start_next], start_next

for i in range(testcases):
    pumps_count, max_pumps = map(int, f.readline().split())
    pump_stations = list(map(int, f.readline().split()))
    pump_true = [False for x in range(pumps_count)]

    spaces = max_pumps - 1
    start = pump_stations[0]
    end = pump_stations[-1]
    pump_true[0] = True
    pump_true[-1] = True

    while spaces > 1:
        result = get_current_index(pump_stations, start, end, spaces)
        if result[0]:
            start = result[1]
            pump_true[result[2]] = True
        else:
            end = result[1]
            pump_true[result[2]] = True
        spaces -= 1

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
    j = 1
    while counter != max_pumps and j != pumps_count:
        #print(counter, max_pumps)
        if not pump_true[j]:
            pump_true[j] = True
            counter += 1
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
        print("Case #%d: %d\n%s" %(i, max_ltc, "Over 9000"))
        f_output.write("Case #%d: %d\n%s\n" %(i, max_ltc, "Over 9000"))
    else:
        print("Case #%d: %d\n%s" %(i, max_ltc, counter))
        f_output.write("Case #%d: %d\n%s\n" %(i, max_ltc, output))
