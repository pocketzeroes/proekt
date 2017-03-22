void Findmax(int *nums, int size, int *cache, int length);
void Merge(int *nums1, int left, int* nums2, int right, int* cache);
int compare(int* nums1, int *nums2, int size);
int* maxNumber(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize){
	int* cache = (int*)malloc(sizeof(int) * k);
	memset(cache, 0, k * sizeof(int));
	int* cache3 = (int*)malloc(sizeof(int) * k);
	int i, j, t;
	*returnSize = k;
	for(i = 0; i <= k; ++i){
		int left = i;
		int cache1[left+1];
		int right = k - i;
		int cache2[right+1];
		if(left > nums1Size || right > nums2Size){
			continue;
		}
		Findmax(nums1, nums1Size, cache1, left);
		Findmax(nums2, nums2Size, cache2, right);
		Merge(cache1, left, cache2, right, cache3);
		t = compare(cache, cache3, k);
		if(t < 0){
			for(j = 0; j < k; ++j){
				cache[j] = cache3[j];
			}
		}
	}
	return cache;
}
void Findmax(int *nums, int size, int *cache, int length){
	int start = 0;
	int end = size - length;
	int i, j, sum;
	for(i = 0; i < length; ++i){
		sum = -1;
		for(j = start; j <= end; ++j)
		{
			if(sum < nums[j]){
				sum = nums[j];
				start = j + 1;
			}
		}
		if(end != size - 1){
			end += 1;
		}
		cache[i] = sum;
	}
}
void Merge(int *nums1, int left, int* nums2, int right, int* cache){
	int i = 0;
	int j = 0;
	int k = 0;
	while(i < left && j < right){
		if(nums1[i] > nums2[j]){
			cache[k++] = nums1[i++];
		}
		else if(nums1[i] == nums2[j]){
			int temp = left - i <= right - j ? 	left - i : right - j;
			int temp2 = compare(nums1 + i, nums2 + j, temp);
			if(temp2 == 0){
				if(temp == left - i){
					temp2 = -1;
				}
				else{
					temp2 = 1;
				}
			}
			if(temp2 > 0){
				cache[k++] = nums1[i++];
			}
			else{
				cache[k++] = nums2[j++];
			}
		}
		else{
			cache[k++] = nums2[j++];
		}
	}
	while(i < left){
		cache[k++] = nums1[i++];
	}
	while(j < right){
		cache[k++] = nums2[j++];
	}
}
int compare(int* nums1, int *nums2, int size){
	int i;
	for(i = 0; i < size; ++i){
		if(nums1[i] > nums2[i]){
			return 1;
		}
		if(nums1[i] < nums2[i]){
			return -1;
		}
	}
	return 0;
}


