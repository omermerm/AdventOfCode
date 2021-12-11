from itertools import product


def read_input(filename):
    with open(filename, 'r') as f:
        return f.read()


def parse_data(data):
    return [[int(d) for d in row] for row in data.split('\n')]


def make_digraph_and_initials(grid):
    m, n = len(grid), len(grid[0])
    digraph = {coords: [] for coords in product(range(m), range(n))}
    initials = []
    for row, col in product(range(m), range(n)):
        initial = True
        for r, c in [(row+1, col), (row-1, col), (row, col+1), (row, col-1)]:
            if 0 <= r < m and 0 <= c < n:
                if grid[r][c] <= grid[row][col]:
                    initial = False
                elif grid[r][c] < 9:
                    digraph[(row, col)].append((r, c))
        if initial:
            initials.append((row, col))
    return digraph, initials


def cone_size(digraph, node):
    visited = {node}
    stack = [node]
    while(stack != []):
        cur = stack.pop(-1)
        for child in digraph[cur]:
            if child not in visited:
                visited.add(child)
                stack.append(child)
    return len(visited)


day = 9
filename = f'Day{day}-input.txt'
grid = parse_data(read_input(filename))
digraph, initials = make_digraph_and_initials(grid)
print(f'Total risk level of all low points: {sum(grid[r][c]+1 for r,c in initials)}')
basin_sizes = sorted([cone_size(digraph, initial) for initial in initials], reverse=True)
print(f'Product of three largest basin sizes: {basin_sizes[0]*basin_sizes[1]*basin_sizes[2]}')
