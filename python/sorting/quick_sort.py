import sys
import random

def random_input(size):
    array_to_sort = []

    for i in range(0, size):
        array_to_sort.append(random.randint(0,999))

    return array_to_sort

def partition(array_to_sort, p, r):
    pivot = array_to_sort[r]
    i = p
    j = p - 1

    while i < r:
        if(array_to_sort[i] < pivot):
            j = j + 1
            temp = array_to_sort[j]
            array_to_sort[j] = array_to_sort[i]
            array_to_sort[i] = temp
        i = i + 1

    temp = array_to_sort[j+1]
    array_to_sort[j+1] = pivot
    array_to_sort[r] = temp
    
    return j + 1

def quick_sort(array_to_sort, p, r):
    if p < r:
        q = partition(array_to_sort,p,r)
        quick_sort(array_to_sort, p, q-1)
        quick_sort(array_to_sort, q+1, r)

def main():
    array_to_sort = random_input(int(sys.argv[1]))
    print("===============Array before sort=========")
    print(array_to_sort)
    quick_sort(array_to_sort, 0, len(array_to_sort)-1)
    print("===============Array after sort==========")
    print(array_to_sort)

if __name__ == '__main__':
    main()
