# pull_input.py

import os
import sys

from aocd import get_data


def main(
        year,
        day):
    if not os.path.exists(str(year)):
        os.mkdir(str(year))

    day_str = str(day).zfill(2)

    print('pulling', year, day_str)

    input_folder = 'input'

    if not os.path.exists(input_folder):
        os.mkdir(input_folder)

    data = get_data(day=day, year=year)

    with open(os.path.join(input_folder, f'{day_str}_input'), 'w') as f:
        f.write(data)

    print(year, day, 'pulled successfully')


if __name__ == '__main__':
    main(int(sys.argv[1]), int(sys.argv[2]))

