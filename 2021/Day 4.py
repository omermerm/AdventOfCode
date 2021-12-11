from collections import defaultdict


def read_input(filename):
    with open(filename, 'r') as f:
        return f.read()


def parse_data(data):
    data = data.split('\n\n')
    numbers = data[0].split(',')
    boards = []
    for board in data[1:]:
        rows = board.split('\n')
        boards.append([row.split() for row in rows])
    return numbers, boards


def index_boards(boards):
    indexer = defaultdict(list)
    num_boards = len(boards)
    rows, cols = len(boards[0]), len(boards[0][0])
    for i in range(num_boards):
        for row in range(rows):
            for col in range(cols):
                num = boards[i][row][col]
                indexer[num].append((i, row, col))
    return indexer


def mark(board, row, col):
    board[row][col] = True
    return all(num is True for num in board[row]) or all(board[i][col] is True for i in range(len(board)))


def play_game(numbers, boards, indexer, completed, condition='loser'):
    for number in numbers:
        for i, row, col in indexer[number]:
            if not completed[i] and mark(boards[i], row, col):  # in this implementation boards stop playing once they win
                completed[i] = True
                if condition == 'winner':
                    return i, number
                elif all(completed):
                    return i, number
                else:
                    pass
    return None


def compute_score(board, number):
    unmarked_sum = sum(sum(int(num) for num in row if num is not True) for row in board)
    return unmarked_sum*int(number)


day = 4
filename = f'Day{day}-input.txt'
numbers, boards = parse_data(read_input(filename))
indexer = index_boards(boards)
completed = [False]*len(boards)
winner, winner_number = play_game(numbers, boards, indexer, completed, condition='winner')
winner_score = compute_score(boards[winner], winner_number)
print(f'The score of the winning board is: {winner_score}. The winning board is {winner+1} and the final number called is {winner_number}')
loser, loser_number = play_game(numbers, boards, indexer, completed, condition='loser')
loser_score = compute_score(boards[loser], loser_number)
print(f'The score of the losing board is: {loser_score}. The winning board is {loser+1} and the final number called is {loser_number}')
