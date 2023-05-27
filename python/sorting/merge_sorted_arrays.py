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

    out1 = []
    out2 = []

    if j - i == 1:
        print(f"Merging arrays array_to_merg[i]={array_to_merge[i]}, array_to_merge[j]={array_to_merge[j]}")
        merge(array_to_merge[i], array_to_merge[j], len(array_to_merge[i]) - 1, len(array_to_merge[j]) - 1, output)
        print(f"Array after merge={output}")
        return 
    merge_multiple_array(array_to_merge, i, (i+j)//2, out1)
    merge_multiple_array(array_to_merge, (i + j)//2, j, out2)
    
    print(f"out1={out1}")
    print(f"out2={out2}")
    merge(out1, out2, len(out1) - 1, len(out2) - 1, output)



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

    print(output)

if __name__ == '__main__':
    main()
