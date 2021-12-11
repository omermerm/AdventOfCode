
def read_input(filename):
    with open(filename, 'r') as f:
        return f.read()


def parse_data(data):
    return list(map(int, data.split(',')))


def pop_growth(initial_state, num_days):
    days_till_growth = [0]*9
    for fish in initial_state:
        days_till_growth[fish] += 1

    for _ in range(num_days):
        reproducers = days_till_growth[0]
        days_till_growth = days_till_growth[1:] + [reproducers]
        days_till_growth[6] += reproducers

    return sum(days_till_growth)


day = 6
filename = f'Day{day}-input.txt'
initial_state = parse_data(read_input(filename))
print(f'Number of lanternfish after 80 days: {pop_growth(initial_state, 80)}')
print(f'Number of lanternfish after 256 days: {pop_growth(initial_state, 256)}')
