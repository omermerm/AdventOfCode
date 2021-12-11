from queue import SimpleQueue
from itertools import product


def read_input(filename):
    with open(filename, 'r') as f:
        return f.read()


def parse_data(data):
    return [list(map(int, row)) for row in data.split('\n')]


def simulate_flashes(grid, stages=1):
    m, n = len(grid), len(grid[0])
    flashes = 0
    for _ in range(stages):
        flashers = SimpleQueue()
        flashed = []
        for row in range(m):
            for col in range(n):
                grid[row][col] += 1
                if grid[row][col] == 10:
                    flashers.put((row, col))
        while(not flashers.empty()):
            r, c = flashers.get()
            flashed.append((r, c))
            for r_off, c_off in product([-1, 0, 1], repeat=2):
                nr, nc = r + r_off, c + c_off
                if 0 <= nr < m and 0 <= nc < n and (nr, nc) != (r, c):
                    grid[nr][nc] += 1
                    if grid[nr][nc] == 10:
                        flashers.put((nr, nc))
        flashes += len(flashed)
        for r, c in flashed:
            grid[r][c] = 0
    return flashes


def all_flashed(grid):
    return sum(sum(row) for row in grid) == 0


day = 11
filename = f'Day{day}-input.txt'
octopus_grid = parse_data(read_input(filename))
steps = 100
print(f'The total number of flashes after {steps} steps is {simulate_flashes(octopus_grid, steps)}')
# it is implicitly assumed that the octopuses don't synchronize before the 101th step
while(True):
    simulate_flashes(octopus_grid)
    steps += 1
    if all_flashed(octopus_grid):
        break

print(f'The first time all the octopuses flashed syncvhronously is at step {steps}')
