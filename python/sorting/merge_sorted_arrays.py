import random
import sys

def random_input(size):
    array = []
    for i in range(0, size):
        array.append(random.randint(0,9999))

    return array

def merge(array1, array2, size1, size2, output):
    i = 0
    j = 0
    while True:
        if array1[i] <= array2[j]:
            output.append(array1[i])
            i = i + 1
            if i == size1:
                output.extend(array2[j:])
                break
        else:
            output.append(array2[j])
            j = j + 1
            if j == size2:
                output.extend(array1[i:])
                break


def merge_multiple_array(array_to_merge,i, j, output):

    if i == j:
        output.extend(array_to_merge[i])
        return

    number_of_arrays = j - i + 1
    if number_of_arrays == 1:
        merge(array_to_merge[i], array_to_merge[j], len(array_to_merge[i]), len(array_to_merge[j]), output)
        return 
    
    mid = (i + j) // 2 
    out1 = []
    out2 = []
    merge_multiple_array(array_to_merge, i, mid, out1)
    merge_multiple_array(array_to_merge, mid + 1, j, out2)

    merge(out1,out2, len(out1), len(out2), output)



def print_array(array_to_print, msg):
    if msg:
        print(msg)

    for array in array_to_print:
        print(array)

def main():
    array_to_sort = []
    for i in range(0, int(sys.argv[2])):
        random_array = random_input(int(sys.argv[1]))
        random_array.sort()
        array_to_sort.append(random_array)
    print_array(array_to_sort, "Array before sorting")
    output = []
    merge_multiple_array(array_to_sort, 0, len(array_to_sort) - 1, output)

    print("Array after merge")
    print(output)

if __name__ == '__main__':
    main()
