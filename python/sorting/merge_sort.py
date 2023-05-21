"""
This script is to sort array using merge sort
"""
import random
import sys

def random_input(size):
    """
    Function to take randopm input
    """
    array_to_sort = []
    for i in range(0, size):
        array_to_sort.append(random.randint(0,9999))

    return array_to_sort

def merge(arra_to_sort, p, q, r):
    """
    Function to merge 2 sorted arrays
    intervals p -> q and q -> r
    """
    N1 = q - p + 1;
    N2 = r - q

    a1 = []
    a2 = []

    for i in range(0, N1):
        a1.append(arra_to_sort[p + i])

    for i in range(0, N2):
        a2.append(arra_to_sort[q + 1 + i])

    i = 0
    j = 0
    k = 0
    while True:
        if a1[i] <= a2[j]:
           arra_to_sort[ p + k ] = a1[i]
           i = i + 1
           k = k + 1
           if i == N1:
               while j < N2:
                   arra_to_sort[ p + k] = a2[j]
                   j = j + 1
                   k = k + 1
               break
        else:
            arra_to_sort [ p + k ] = a2[j]
            j = j + 1
            k = k + 1
            if j == N2:
                while i < N1:
                    arra_to_sort[p+k] = a1[i]
                    i = i + 1
                    k = k + 1
                break


def merge_sort(arra_to_sort, p, r):
    """
    main merge_sort routine
    """
    if p < r:
        mid = int((p + r) / 2)
        merge_sort(arra_to_sort, p, mid)
        merge_sort(arra_to_sort, mid + 1, r)
        merge(arra_to_sort, p, mid, r)


def main():
    """
    Main function
    """
    array_to_sort = random_input(int(sys.argv[1]))
    print("===============Array before sort===================")
    print(array_to_sort)
    merge_sort(array_to_sort, 0, len(array_to_sort)-1)
    print("===============Array after sort====================")
    print(array_to_sort)

if __name__ == '__main__':
    main()
