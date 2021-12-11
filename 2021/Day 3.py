
def read_input(filename):
    with open(filename, 'r') as f:
        return f.read()


def gamma_epsilon(bin_cols):
    n = len(bin_cols[0])
    sums = [sum(col) for col in bin_cols]
    gamma = [1 if s >= n // 2 else 0 for s in sums]
    epsilon = [1-gamma[i] if sums[i] < n else gamma[i] for i in range(len(gamma))]  # making sure the most common bit and least common bits are different
    gamma_int = int(''.join(str(b) for b in gamma), base=2)
    epsilon_int = int(''.join(str(b) for b in epsilon), base=2)
    return gamma_int, epsilon_int


def get_rating(bin_nums, rating_type):
    if rating_type == 'co2':
        bit_op = lambda x: 1-x
    elif rating_type == 'oxygen':
        bit_op = lambda x: x
    else:
        raise Exception("unknown rating_type")

    idxs = list(range(len(bin_nums)))
    pos = 0
    bin_len = len(bin_nums[0])
    while(len(idxs) > 1 and pos < bin_len):
        n = len(idxs)
        common = 1 if sum(bin_nums[idx][pos] for idx in idxs) >= ((n+1) // 2) else 0  # the +1 is for the case n is odd
        desired_bit = bit_op(common)
        idxs = [idx for idx in idxs if bin_nums[idx][pos] == desired_bit]
        pos += 1
    rating = bin_nums[idxs[0]]
    return int(''.join(str(b) for b in rating), base=2)


day = 3
filename = f'Day{day}-input.txt'
data = [[int(c) for c in bin] for bin in read_input(filename).split()]
transposed_data = [[data[i][j] for i in range(len(data))] for j in range(len(data[0]))]
gamma, epsilon = gamma_epsilon(transposed_data)
print("Gamma rate, Epsilon rate, and their product:", gamma, epsilon, gamma*epsilon)
oxygen = get_rating(data, 'oxygen')
co2 = get_rating(data, 'co2')
print("Oxygen generator rating, CO2 scrubber rating, and their product:", oxygen, co2, oxygen*co2)
