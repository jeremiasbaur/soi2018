import math, time

f = open('pipeline-sub2-attempt4.txt', 'r')
f_output = open('task3_2.txt', 'w')

testcases = int(f.readline())

def binary_search_r(pump_stations, look_for):
    l = 0
    r = len(pump_stations)-1

    while l<r:
        m = (l+r)//2
        if pump_stations[m] < look_for:
            l = m + 1
        else: #pump_stations[m] > look_for:
            r = m
        #print(pump_stations, look_for, l, r)
    return l

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
    return l
    if math.fabs(pump_stations[l]-look_for) > math.fabs(pump_stations[r]-look_for):
        #print("right: ",l, r, look_for)
        return r
    else:
        #print("left: ",l, r, look_for)
        return l

for i in range(testcases):
    pumps_count, max_pumps = map(int, f.readline().split())
    pump_stations = list(map(int, f.readline().split()))
    pump_true = [False for x in range(pumps_count)]

    if pumps_count == 1:
        print('Case #%d: %d\n%d' %(i, 0,pump_stations[0]))
        f_output.write('Case #%d: %d\n%d\n' %(i, 0,pump_stations[0]))
        continue

    #ltc = (pump_stations[-1] - pump_stations[0]) / (max_pumps-1)
    #print(ltc)
    """if i == 90:
        j = 1
        print(ltc)
        while j != pumps_count:
            if pump_stations[j]-pump_stations[j-1]>ltc:
                print(ltc,pump_stations[j], pump_stations[j-1], pump_stations[j]-pump_stations[j-1])
            j+=1"""

    prev_mid = -1
    count_pumps = 0
    l = pump_stations[0]
    r = pump_stations[-1]
    while count_pumps != max_pumps:
        mid = (l+r)//2
        #print(prev_mid)
        j = 1
        looking_from = 0
        pump_true = [False for x in range(pumps_count)]
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
            print("Impossible", l)
            continue

        pump_true[j-1] = True
        pump_true[0] = True
        required_count = 0
        for j in range(pumps_count):
            if pump_true[j]:
                required_count+=1

        print(required_count, mid, max_pumps, l, r, prev_mid)

        if l >= r:
            j = 1
            looking_from = 0
            pump_true = [False for x in range(pumps_count)]
            impossible = False
            ltc = prev_mid
            print(j!=pumps_count)

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
                print(j)

            pump_true[pumps_count-1] = True
            pump_true[0] = True
            required_count = 0
            print("lol true",pump_true)
            for j in range(pumps_count):
                if pump_true[j]:
                    required_count+=1

            j = 1
            while required_count != max_pumps and j != pumps_count:
                print("kkk",required_count, max_pumps)
                if not pump_true[j]:
                    pump_true[j] = True
                    required_count += 1
                j+=1
            print("last",required_count,prev_mid)

        prev_mid = ltc
        print(prev_mid)
        if required_count == max_pumps:
            break
        elif required_count > max_pumps:
            l = mid + 1
        else:
            r = mid - 1

    counter = 1
    output = str(pump_stations[0]) + " "
    for j in range(1, pumps_count):
        if pump_true[j]:
            output += str(pump_stations[j]) + " "
            counter += 1

    print('Case #%d: %s\n%s' %(i, counter,output))
    f_output.write('Case #%d: %s\n%s\n' %(i, counter, output))

"""import math

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
"""
