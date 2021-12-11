def read_input(filename):
    with open(filename, 'r') as f:
        return f.read().split()


def num_of_increase(depths):
    return sum(int(depths[i]) < int(depths[i+1]) for i in range(len(depths)-1))


# consecutive triples share two elements, so we only need to compare the first of the early triplet and the third of the later triplet
def num_of_increase_in_threes(depths):
    return sum(int(depths[i]) < int(depths[i+3]) for i in range(len(depths)-3))


day = 1
filename = f'Day{day}-input.txt'
data = read_input(filename)
print("number of increases:", num_of_increase(data))
print("number of increases for triples:", num_of_increase_in_threes(data))
