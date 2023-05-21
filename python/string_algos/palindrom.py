import sys
def is_palindrom(str1):
    if(str1 == str1[::-1]):
        return True
    return False

def main():
    if len(sys.argv) != 2:
        print("Either one argument is passed OR multiple arguments passed to the string")
        sys.exit(1)

    if is_palindrom(sys.argv[1]):
        print("String is palindrom")
    else:
        print("String is not palindrom")

if __name__ == '__main__':
    main()
    
