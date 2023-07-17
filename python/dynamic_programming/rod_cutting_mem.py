r = []
def initialize_memo(size):
    for i in range(size):
        r.append(float('-inf'))

    
def cut_rod(price, n):
    if r[n-1]>=0:
        return r[n]
    if n == 0:
        return 0 

    q = float('-inf')
    for i in range(1, n+1):
        q = max(q, price[i-1] + cut_rod(price, n - i))
    
    r[n-1] = q
    return q

def main():
    arr = [1,5,8,9,10,17,17,20]
    size = len(arr)
    initialize_memo(len(arr))
    print("Maximum obtianable value is ",cut_rod(arr, size))
    print(r)

if __name__ == '__main__':
    main()