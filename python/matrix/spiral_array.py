import sys
import random


def random_input(size):
    array = []
    for i in range(0, size):
        array.append(random.randint(0,9999))

    return array


def print_array(array_to_print, msg):
    if msg:
        print(msg)

    for array in array_to_print:
        print(array)

def print_spiral_array(array_to_spiral, m, n):
    total_count = m * n
    ans = []
    seen = [[0 for i in range(0,n+1)] for j in range(0,m+1)]
    i = 0
    j = 0
    direction = 0
    # 0 forword
    # 1 down
    # 2 back
    # 3 up
    for count in range(0, (m+1)*(n+1)):
        ans.append(array_to_spiral[i][j])
        seen[i][j] = True
        if direction == 0:
            if j == n or seen[i][j+1]:
                direction = 1
                i = i + 1
                continue
            else:
                j = j + 1

        if direction == 1:
            if i == m or seen[i+1][j]:
                direction = 2
                j = j -1
                continue
            else:
                i = i + 1

        if direction == 2:
            if j == 0 or seen[i][j-1]:
                direction = 3
                i = i - 1
                continue
            else:
                j = j - 1

        if direction == 3:
            if i == 0 or seen[i-1][j]:
                direction = 0
                j = j + 1
            else:
                i = i - 1

    return ans

def main():
    array_to_spiral = []
    for i in range(0, int(sys.argv[2])):
        random_array = random_input(int(sys.argv[1]))
        array_to_spiral.append(random_array)
    print_array(array_to_spiral, "Array before sorting")
    ans = print_spiral_array(array_to_spiral,len(array_to_spiral) - 1, len(array_to_spiral[0]) - 1)
    print("Spiral array is read")
    print(ans)


if __name__ == '__main__':
    main()