import sys
def swap_case(string_to_swap):
    swapped_str = ''
    for c in string_to_swap:
        if c.islower():
            swapped_str = swapped_str + c.upper()
        else:
            swapped_str = swapped_str + c.lower()

    return swapped_str

def main():
    if len(sys.argv) != 2:
        print("Either one argument is passed OR multiple arguments passed to the string")
        sys.exit(1)

    print(swap_case(sys.argv[1]))

if __name__ == '__main__':
    main()
