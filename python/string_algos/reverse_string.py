import sys
def reverse_string(str_to_revers):
    return str_to_revers[::-1]

def main():
    if len(sys.argv) != 2:
        print("Either one argument is passed OR multiple arguments passed to the string")
        sys.exit(1)

    print(reverse_string(sys.argv[1]))

if __name__ == '__main__':
    main()
    
