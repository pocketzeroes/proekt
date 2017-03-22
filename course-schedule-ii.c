bool helper(int **list, int *len, int start, char *flag, char *visited, int *res, int *returnSize) {
    flag[start] = 1; 
	int i;
	for (i = 0; i < len[start]; i++) {
		int key = list[start][i];
		if (visited[key]) continue;
		if (flag[key]) return false;
		if (!len[key]) {
			res[(*returnSize)++] = key;
			visited[key] = 1;
			continue;
		}
		if (!helper(list, len, key, flag, visited, res, returnSize)) return false;
	}
	flag[start] = 0; 
	visited[start] = 1;
	res[(*returnSize)++] = start;
	return true;
}
int* findOrder(int numCourses, int** prerequisites, int prerequisitesRowSize, int prerequisitesColSize, int* returnSize) {
	if (numCourses < 1) return 0;
	int *res = malloc(numCourses * sizeof(int));
	*returnSize = 0;
	int **list = calloc(numCourses, sizeof(int *));
	int *len = calloc(numCourses, sizeof(int));
	int i;
	for (i = 0; i < prerequisitesRowSize; i++) {
		int left = prerequisites[i][0];
		int right = prerequisites[i][1];
		len[left]++;
		list[left] = realloc(list[left], len[left] * sizeof(int));
		list[left][len[left] - 1] = right;
	}
	char *flag = calloc(numCourses, 1);  
	char *visited = calloc(numCourses, 1);
	for (i = 0; i < numCourses; i++) {
		if (visited[i]) continue; 
		if (!len[i]) {
			res[(*returnSize)++] = i;
			visited[i] = 1;
			continue;
		}
		if (!helper(list, len, i, flag, visited, res, returnSize)) {
			*returnSize = 0;
			return res;
		}
	}
	return res;
}
