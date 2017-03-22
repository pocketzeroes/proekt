inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int* findDiagonalOrder(int** matrix, int matrixRowSize, int matrixColSize, int* returnSize) {
	if (matrixRowSize == 0) return NULL;
	int h = matrixRowSize, w = matrixColSize, id = 0;
	int*res = malloc(sizeof(int)*h*w);
	for (int i = 0; i < h+w; i++) {
		int lb = max(0, i-w+1), ub = min(i,h-1);
		if (i%2 == 0) for (int j = ub; j >= lb; j--) res[id++] = matrix[j][i-j];
		else for (int j = lb;j <= ub; j++) res[id++] = matrix[j][i-j];
	}
   *returnSize=id;
	return res;
}
