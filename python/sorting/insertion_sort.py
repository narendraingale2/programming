"""
Insertion sort
"""
import sys
import random
def input(size):
    """
    This function is to print input
    """
    a = []
    for i in range(0,int(size)):
        a.append(random.randint(0,99999))
    return a


def output():
    """
    This function is to print output
    """
    pass

def insert_at_sorting_position(a, size):
    """
    This function is to insert at sorting poistion
    """

    key = a[size-1]
   
    i = size - 2
    while a[i] > key and i > -1:
        a[i+1] = a[i]
        i = i - 1
    
    a[i+1] = key
    
def insertion_sort(a):
    """
    Main insertion sort function
    """
    for i in range(2,len(a)+1):
        insert_at_sorting_position(a,i)

def main():
    """
    This is main function
    """
    a = input(sys.argv[1])
    print("Array before sorting")
    print(a)
    insertion_sort(a)
    print("Array after sorting")
    print(a)

if __name__ == '__main__':
    main()
