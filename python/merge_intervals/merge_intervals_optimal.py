def merge_intervals_optimal(intervals):
    intervals.sort()
    stack = []
    stack.append(intervals[0])

    for interval in intervals[1:]:
        if stack[-1][0] <= interval[0] <= stack[-1][1]:
            stack[-1][1] = max(interval[1],stack[-1][1])
        else:
            stack.append(interval)

    return stack

if __name__ == '__main__':
    intervals = [[1,3],[2,6],[8,10],[15,18]]
    merged_intervals = merge_intervals_optimal(intervals)
    print(merged_intervals)

