import sys

def lcs_length(string1, string2):
    m = len(string1)
    n = len(string2)
    lcs_table = [[None]*(n+1) for i in range(m+1)]
    lcs_dir_table = [[None]*(n+1) for i in range(m+1)]
    # 0 upwords
    # 1 backword
    # 2 digonal

    for i in range(0,m+1):
        lcs_table[i][0] = 0
    
    for j in range(0,n+1):
        lcs_table[0][j] = 0

    for i in range(1, m + 1):
        for j in range(1,n+1):
            if i == 0 or j == 0:
                lcs_table[i][j] = 0
            elif string1[i-1] == string2[j-1]:
                lcs_table[i][j] = lcs_table[i-1][j-1] + 1
                lcs_dir_table[i][j] = 2
            elif lcs_table[i-1][j] >= lcs_table[i][j-1]:
                    lcs_table[i][j] = lcs_table[i-1][j]
                    lcs_dir_table[i][j] = 0
            else:
                lcs_table[i][j] = lcs_table[i][j-1]
                lcs_dir_table[i][j] = 1
        
    print(f"Length of longest common subsequence = {lcs_table[m][n]}")
    print_lcs_string(lcs_dir_table, string1, m, n, m, n)

def print_lcs_string(lcs_dir_table,string1, m, n, i, j):
    if i == -1 or j == -1:
        return 
    
    if lcs_dir_table[i][j] == 2:
        print_lcs_string(lcs_dir_table, string1, m, n, i-1, j-1)
        print(string1[i-1],end="")
    elif lcs_dir_table[i][j] == 0:
        print_lcs_string(lcs_dir_table, string1, m, n, i-1, j)
    else:
        print_lcs_string(lcs_dir_table,string1,m,n,i, j-1)


        
            
             


def main():
    lcs_length(sys.argv[1],sys.argv[2])


if '__main__' == __name__:
    main()