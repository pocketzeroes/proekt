void swap (int *a, int *b)
{
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}
int partition (int arr[], int low, int high)
{
  int pivot = arr[high];
  int i, pivot_index = low;
  for (i=low; i<high; i++) {
    if (arr[i] <= pivot) {
      swap(&arr[i], &arr[pivot_index]);
      pivot_index++;
    }
  }
  swap(&arr[pivot_index], &arr[i]);
  return pivot_index;
}
void quicksort(int arr[], int low, int high)
{
  if (low>=high) { return;}
  int p = partition(arr, low, high);
  quicksort(arr,low, p-1);
  quicksort(arr,p+1, high);
}
int* diffWaysToCompute(char *input, int *returnSize) {
    int *result = NULL;
    int l = 0;
    int size = strlen(input);
    for (int i=0; i<size; i++) {
        char ch = input[i];
        if (ch == '+' || ch == '-' || ch == '*') {
            int *returnSize1 = (int*)malloc(sizeof(int));
            int *returnSize2 = (int*)malloc(sizeof(int));
            char *input1 = (char*)malloc(sizeof(char) *(i+1));
            char *input2 = (char*)malloc(sizeof(char) *(size-(i+1)+1));
            int m=0, n=0;
            for (m=0; m<i;m++) {
              input1[n++] = input[m];
            }
            input1[n] = '\0';
            n=0;
            for (m=i+1; input[m] != '\0';m++) {
              input2[n++] = input[m];
            }
            input2[n] = '\0';
            int *result1 = diffWaysToCompute(input1, returnSize1);
            int *result2 = diffWaysToCompute(input2, returnSize2);
            for (int j=0; j<*returnSize1; j++) {
                for (int k=0; k<*returnSize2; k++) {
                    result = (int*)realloc(result, (l+1)*sizeof(int));
                    if (ch == '+') {
                        result[l++] = result1[j] + result2[k];
                    } else if (ch == '-') {
                        result[l++] = result1[j] - result2[k];
                    } else if (ch == '*') {
                        result[l++] = result1[j] * result2[k];
                    }
                }
            }
        }
    }
    if (l==0) {
        result = (int*)realloc(result, sizeof(int));
        result[l++] = atoi(input);
    }
    quicksort(result, 0, l-1);
    (*returnSize) = l;
    return result;
}
