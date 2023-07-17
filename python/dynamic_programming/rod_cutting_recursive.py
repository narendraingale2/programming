def cut_rod(price, n):
    if n == 0:
        return 0 

    q = float('-inf')
    for i in range(1, n+1):
        q = max(q, price[i-1] + cut_rod(price, n - i))
    
    return q

def main():
    arr = [1,5,8,9,10,17,17,20]
    size = len(arr)
    print("Maximum obtianable value is ",cut_rod(arr, size))

if __name__ == '__main__':
    main()