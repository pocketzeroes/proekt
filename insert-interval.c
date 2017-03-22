typedef struct Interval Interval;
Interval* insert(Interval* intervals, int size, Interval newInterval, int* returnSize)
{
    size++;
    Interval *arr = (Interval*)malloc(sizeof(Interval)*size);
    int j = 0;
    int i = 0;
    int count=0;
    while(i < size-1)
    {
        if(intervals[i].start < newInterval.start || count)
            arr[i+count] = intervals[i++];
        else
            arr[i] = newInterval, count++;
    }
    if(count == 0) arr[i] = newInterval;
    *returnSize = 0;
    int max = 0;
    i = 0;
    while(i < size)
    {
        Interval t;
        t.start = arr[i].start;
        int j = i+1;
        max = arr[i].end;
        while(j<size && arr[j].start<=max)
        {
            if(arr[j].end > max) max = arr[j].end;
            j++;
        }
        i = j;
        t.end = max;
        *returnSize += 1;
        arr[*returnSize-1] = t;
    }
    return arr;
}
