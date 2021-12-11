from bisect import insort


def read_input(filename):
    with open(filename, 'r') as f:
        return f.read()


def parse_data(data):
    par_dic = {')': '(', ']': '[', '}': '{', '>': '<'}
    corrupted, incomplete, okay = [], [], []
    for row in data.split('\n'):
        corrupt = False
        stack = []
        for c in row:
            if c in ['(', '{', '[', '<']:
                stack.append(c)
            elif stack.pop(-1) != par_dic[c]:
                corrupted.append((row, c))
                corrupt = True
                break
            else:
                pass
        if corrupt:
            pass
        elif stack != []:
            incomplete.append((row, stack))
        else:
            okay.append(row)
    return corrupted, incomplete, okay


def score_corruptions(corruptions):
    scoring = {
        ')': 3,
        ']': 57,
        '}': 1197,
        '>': 25137
        }
    return sum(scoring[cor] for cor in corruptions)


def score_completions(incomplete_stacks):
    par_score = {'(': 1, '[': 2, '{': 3, '<': 4}
    scores = []
    for stack in incomplete_stacks:
        score = 0
        while(stack != []):
            score = score*5 + par_score[stack.pop(-1)]
        insort(scores, score)
    return scores


day = 10
filename = f'Day{day}-input.txt'
corrupted, incomplete, okay = parse_data(read_input(filename))
corruption_score = score_corruptions([cor[1] for cor in corrupted])
print(f'Total corruption score: {score_corruptions([cor[1] for cor in corrupted])}')
completions_score = score_completions([inc[1] for inc in incomplete])
completions_winner = completions_score[len(completions_score) // 2]
print(f'Middle completion score: {completions_winner}')
