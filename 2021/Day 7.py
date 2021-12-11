
def read_input(filename):
    with open(filename, 'r') as f:
        return f.read()


def parse_data(data):
    return list(map(int, data.split(',')))


def fuel_consumption(nums):
    nums.sort()
    med = nums[len(nums) // 2]
    return sum(abs(med - n) for n in nums)


def fuel_consumption2(nums):
    dist = lambda x: (x*(x+1)) // 2

    def sum_dist(loc):
        return sum(dist(abs(n-loc)) for n in nums)
    nums.sort()
    lo, hi = nums[0], nums[-1]
    while(lo+1 < hi):
        mid = (lo + hi) // 2
        if sum_dist(mid) >= sum_dist(mid-1):
            hi = mid-1
        else:
            lo = mid
    return min(sum_dist(lo), sum_dist(hi))


day = 7
filename = f'Day{day}-input.txt'
positions = parse_data(read_input(filename))
print(f'Fuel required to align to optimal position with constant consumption rate: {fuel_consumption(positions)}')
print(f'Fuel required to align to optimal position with real fuel consumption rate: {fuel_consumption2(positions)}')
