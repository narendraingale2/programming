import sys
import random


def merge_interval(intervals):
    intervals.sort()
    print(intervals)
    i = 0
    total_elements = len(intervals)
    while i < total_elements:
        start = intervals[i][0]
        end = intervals[i][1]
        j = i + 1
        while j < total_elements:
            if intervals[i][1] >= intervals[j][0]:
                if intervals[i][1] <= intervals[j][1]:
                    intervals[i][1] = intervals[j][1]
                del intervals[j]
                total_elements = len(intervals)
            else:
                j = j + 1
        i = i + 1

    
    return intervals


if __name__ == '__main__':
    intervals = [[1,4],[0,2],[3,5]] 
    print(intervals)
    merged_intervals = merge_interval(intervals)
    print(merged_intervals)
