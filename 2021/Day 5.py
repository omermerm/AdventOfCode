from collections import defaultdict


def read_input(filename):
    with open(filename, 'r') as f:
        return f.read()


def parse_data(data):
    return [[list(map(int, p1.split(','))), list(map(int, p2.split(',')))] for p1, _, p2 in map(str.split, data.split('\n'))]


def coord_count(lines):
    points = defaultdict(lambda: 0)
    for p1, p2 in lines:
        if p1[0] > p2[0]:
            x_dir = -1
        elif p1[0] < p2[0]:
            x_dir = 1
        else:
            x_dir = 0

        if p1[1] > p2[1]:
            y_dir = -1
        elif p1[1] < p2[1]:
            y_dir = 1
        else:
            y_dir = 0

        cur_x, cur_y = p1
        while(cur_x != p2[0] or cur_y != p2[1]):
            points[(cur_x, cur_y)] += 1
            cur_x += x_dir
            cur_y += y_dir
        points[(p2[0], p2[1])] += 1

    return len(points) - list(points.values()).count(1)


day = 5
filename = f'Day{day}-input.txt'
lines = parse_data(read_input(filename))
axis_aligned = [line for line in lines if line[0][0] == line[1][0] or line[0][1] == line[1][1]]
print(f'Points where at least two vertical/horizontal lines overlap: {coord_count(axis_aligned)}')
print(f'Points where at least two lines (any kind) overlap: {coord_count(lines)}')
