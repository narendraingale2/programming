import sys
import random


def merge_interval(intervals):
    intervals.sort()
    i = 0
    total_elements = len(intervals)
    while i < total_elements:
        start = intervals[i][0]
        end = intervals[i][1]
        j = i + 1
        while j < total_elements:
            if end >= intervals[j][0]:
                intervals[i][1] = intervals[j][1 ]
                del intervals[j]
                total_elements = len(intervals)
            j = j + 1
        i = i + 1

    
    return intervals


if __name__ == '__main__':
    intervals = [[1,3],[2,6],[8,10],[15,18]]
    merged_intervals = merge_interval(intervals)
    print(merged_intervals)
