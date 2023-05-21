"""
There is a sequence of words in CamelCase as a string of letters, , having the following properties:

It is a concatenation of one or more words consisting of English letters.
All letters in the first word are lowercase.
For each of the subsequent words, the first letter is uppercase and rest of the letters are
lowercase.
"""
import sys

def camelcase(string):
    """
    This function will return number of camel case letters
    """
    prev_char = string[0]
    cnt = 1
    for char in string[0:]:
        if prev_char.islower() and char.isupper():
            cnt = cnt + 1
    return cnt

def main():
    """
    Main function
    """

    if len(sys.argv) != 2:
        print("Either one argument is passed OR multiple arguments passed to the string")
        sys.exit(1)

    print(camelcase(sys.argv[1]))

if __name__ == '__main__':
    main()
