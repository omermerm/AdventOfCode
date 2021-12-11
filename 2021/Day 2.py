def read_input(filename):
    with open(filename, 'r') as f:
        return f.read()


def location(moves):
    depth = 0
    hor = 0
    for direction, amt in moves:
        if direction == 'forward':
            hor += amt
        elif direction == 'up':
            depth -= amt
        elif direction == 'down':
            depth += amt
        else:
            print("bad direction input")
    return depth, hor


def location_with_aim(moves):
    depth = 0
    hor = 0
    aim = 0
    for direction, amt in moves:
        if direction == 'forward':
            hor += amt
            depth += amt*aim
        elif direction == 'up':
            aim -= amt
        elif direction == 'down':
            aim += amt
        else:
            print("bad direction input")
    return depth, hor


day = 2
filename = f'Day{day}-input.txt'
data = [[x, int(y)] for x, y in map(str.split, read_input(filename).split('\n'))]
depth, hor_loc = location(data)
print("Product of depth and horizontal location (without aim):", depth*hor_loc)
depth_aim, hor_loc_aim = location_with_aim(data)
print("Product of depth and horizontal location (with aim):", depth_aim*hor_loc_aim)
