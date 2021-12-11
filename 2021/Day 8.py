
def read_input(filename):
    with open(filename, 'r') as f:
        return f.read()


def parse_data(data):
    lines = []
    for digits, num in map(lambda x: x.split('|'), data.split('\n')):
        lines.append([sorted(map(set, digits.split()), key=len, reverse=True), num.split()])
    return lines


def decode(digits, number):
    dic = [None]*10
    dic[1] = digits.pop(-1)
    dic[7] = digits.pop(-1)
    dic[4] = digits.pop(-1)
    five_segs = [digits.pop(-1) for _ in range(3)]
    six_segs = [digits.pop(-1) for _ in range(3)]
    dic[8] = digits.pop(-1)

    def superset_of_dig(digit, sub_digit):
        return set.intersection(digit, sub_digit) == sub_digit
    dic[3] = next(filter(lambda x: superset_of_dig(x, dic[1]), five_segs))
    five_segs.remove(dic[3])
    dic[6] = next(filter(lambda x: not superset_of_dig(x, dic[1]), six_segs))
    six_segs.remove(dic[6])
    dic[5] = next(filter(lambda x: superset_of_dig(dic[6], x), five_segs))
    five_segs.remove(dic[5])
    dic[2] = five_segs.pop(-1)
    dic[9] = next(filter(lambda x: superset_of_dig(x, dic[5]), six_segs))
    six_segs.remove(dic[9])
    dic[0] = six_segs.pop(-1)

    rev_dic = {tuple(sorted(dic[i])): i for i in range(10)}
    return [rev_dic[tuple(sorted(dig))] for dig in number]


def count_digits(nums_as_lists):
    acc = {d: 0 for d in range(10)}
    for num in nums_as_lists:
        for d in num:
            acc[d] += 1
    return acc


day = 8
filename = f'Day{day}-input.txt'
encoded = parse_data(read_input(filename))
decoded = [decode(digits, number) for digits, number in encoded]
dig_count = count_digits(decoded)
print(f'Number of 1, 4, 7, 8 in decoded numbers: {sum(dig_count[x] for x in [1, 4, 7, 8])}')
print(f'Sum of all decoded output values: {sum(sum(num[~i]*(10**i) for i in range(len(num))) for num in decoded)}')
