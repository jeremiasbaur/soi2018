import math

f = open('pipeline-sub2-attempt0.txt', 'r')
f_output = open('task3_2.txt', 'w')

testcases = int(f.readline())

def binary_search(pump_stations, look_for):
    l = 0
    r = len(pump_stations)-1

    while l<r:
        m = (l+r)//2
        if pump_stations[m] < look_for:
            l = m + 1
        else: #pump_stations[m] > look_for:
            r = m
        #print(pump_stations, look_for, l, r)
    if math.fabs(pump_stations[l]-look_for) > math.fabs(pump_stations[r]-look_for):
        #print(r)
        return r
    else:
        #print(l)
        return l

def get_current_index(pump_stations, start, end, spaces):
    if (math.ceil((end-start)/spaces)+(end-start)//spaces)/2 > (end-start)//spaces:
        step = (end-start)//spaces
    else:
        step = math.ceil((end-start)/spaces)
    start_next = binary_search(pump_stations, start + step)
    end_next = binary_search(pump_stations, end - step)

    if math.fabs(start+step - pump_stations[start_next]) > math.fabs(end-step - pump_stations[end_next]):
        print(pump_stations[end_next],"1")
        return False, pump_stations[end_next], end_next
    else:
        print(pump_stations[end_next],"2")
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

    output = 'Case #%d: ' %(i)

    print(output, pump_true)
    #f_output.write(output + "\n")
