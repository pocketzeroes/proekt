#include <stdio.h>
#include <stdlib.h>
typedef struct MedianFinder{
    int *maxHeap;
    int *minHeap;
    int maxHeapCapacity;
    int minHeapCapacity;
    int maxHeapSize;
    int minHeapSize;
    double median;
}MedianFinder;
void swap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}
void addHeap(int **heap, int *size, int *capacity, int data) {
    if (*size == *capacity) {
        int newCapacity = (*capacity) * 2;
        int *newHeap = (int *)malloc(newCapacity * sizeof(int));
        for (int i = 0; i < *capacity; i++) {
            newHeap[i] = (*heap)[i];
        }
        if (*heap)
            free(*heap);
        *heap = newHeap;
        *capacity = newCapacity;
    }
    (*heap)[*size] = data;
    (*size)++;
}
void siftUpMax(int *heap, int size) {
    int parent, child;
    child = size - 1;
    while (child > 0) {
        parent = (child - 1) / 2;
        if (heap[parent] < heap[child])
            swap(&heap[parent], &heap[child]);
        child = parent;
    }
}
void siftDownMax(int *heap, int size) {
    int parent, child;
    parent = 0; child = 1;
    while (child < size) {
        if (child + 1 < size && heap[child] < heap[child + 1])
            child = child + 1;
        if (heap[parent] >= heap[child]) break;
        swap(&heap[parent], &heap[child]);
        parent = child;
        child = parent * 2 + 1;
    }
}
void siftUpMin(int *heap, int size) {
    int parent, child;
    child = size - 1;
    while (child > 0) {
        parent = (child - 1) / 2;
        if (heap[parent] > heap[child])
            swap(&heap[parent], &heap[child]);
        child = parent;
    }
}
void siftDownMin(int *heap, int size) {
    int parent, child;
    parent = 0; child = 1;
    while (child < size) {
        if (child + 1 < size && heap[child] > heap[child + 1])
            child = child + 1;
        if (heap[parent] <= heap[child]) break;
        swap(&heap[parent], &heap[child]);
        parent = child;
        child = parent * 2 + 1;
    }
}
struct MedianFinder* medianFinderCreate() {
    struct MedianFinder *mf = (struct MedianFinder *)malloc(sizeof(struct MedianFinder));
    mf->maxHeap         = (int *)malloc(sizeof(int));
    mf->minHeap         = (int *)malloc(sizeof(int));
    mf->maxHeap[0]      = mf->minHeap[0]      = 0;
    mf->minHeapSize     = mf->maxHeapSize     = 0;
    mf->minHeapCapacity = mf->maxHeapCapacity = 1;
    mf->median          = 0;
    return mf;
}
void medianFinderAddNum(struct MedianFinder* mf, int num) {
    if (mf == NULL) return;
    if (mf->maxHeapSize == mf->minHeapSize) {
        if (num > mf->median) {
            addHeap(&mf->minHeap, &mf->minHeapSize, &mf->minHeapCapacity, num);
            siftUpMin(mf->minHeap, mf->minHeapSize);
            mf->median = mf->minHeap[0];
        }
        else {
            addHeap(&mf->maxHeap, &mf->maxHeapSize, &mf->maxHeapCapacity, num);
            siftUpMax(mf->maxHeap, mf->maxHeapSize);
            mf->median = mf->maxHeap[0];
        }
    }
    else {
        if (num > mf->minHeap[0]) {
            addHeap(&mf->minHeap, &mf->minHeapSize, &mf->minHeapCapacity, num);
            siftUpMin(mf->minHeap, mf->minHeapSize);
            if (mf->minHeapSize >= mf->maxHeapSize + 2) {
                addHeap(&mf->maxHeap, &mf->maxHeapSize, &mf->maxHeapCapacity, mf->minHeap[0]);
                siftUpMax(mf->maxHeap, mf->maxHeapSize);
                swap(&mf->minHeap[0], &mf->minHeap[mf->minHeapSize - 1]);
                mf->minHeapSize--;
                siftDownMin(mf->minHeap, mf->minHeapSize);
            }
        }
        else {
            addHeap(&mf->maxHeap, &mf->maxHeapSize, &mf->maxHeapCapacity, num);
            siftUpMax(mf->maxHeap, mf->maxHeapSize);
            if (mf->maxHeapSize >= mf->minHeapSize + 2) {
                addHeap(&mf->minHeap, &mf->minHeapSize, &mf->minHeapCapacity, mf->maxHeap[0]);
                siftUpMin(mf->minHeap, mf->minHeapSize);
                swap(&mf->maxHeap[0], &mf->maxHeap[mf->maxHeapSize - 1]);
                mf->maxHeapSize--;
                siftDownMax(mf->maxHeap, mf->maxHeapSize);
            }
        }
        mf->median = mf->maxHeap[0] + (mf->minHeap[0] - mf->maxHeap[0]) / 2.0;
    }
}
double medianFinderFindMedian(struct MedianFinder* mf) {
    if (mf == NULL) return 0;
    return mf->median;
}
void medianFinderFree(struct MedianFinder* mf) {
    if (mf == NULL) return;
    if (mf->maxHeap) free(mf->maxHeap);
    if (mf->minHeap) free(mf->minHeap);
    free(mf);
}
