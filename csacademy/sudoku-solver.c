#include <stdio.h>

int Data[9][9];
int Este[9][9][10];

void ReadData(int Data[9][9]){
	int i, j;
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			scanf("%d", &Data[i][j]);
		}
	}
}
void Show(int Data[9][9]){
	int i, j;
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			printf("%d ", Data[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void MakeEste(int Data[9][9], int Este[9][9][10]){
	int i, j, k, l;
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			for(k = 1; k <= 9; k++){
				Este[i][j][k] = 1;
			}
		}
	}
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++) if (Data[i][j]){
			for(k = 1; k <= 9; k++){
				Este[i][j][k] = 0;
			}
			for(k = 0; k < 9; k++){
				Este[i][k][Data[i][j]] = 0;
			}
			for(k = 0; k < 9; k++){
				Este[k][j][Data[i][j]] = 0;
			}
			for(k = i-i%3; k < i-i%3+3; k++){
				for(l = j-j%3; l < j-j%3+3; l++){
					Este[k][l][Data[i][j]] = 0;
				}
			}
		}
	}
}
int Search(int Data[9][9], int Este[9][9][10]){
	int i, j, k, l, m;
	int sol;
	int ok;
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++) if (!Data[i][j]){
			sol = 0;
			ok = 1;
			for(k = 1; k <= 9; k++){
				if (Este[i][j][k]){
					if (sol) ok = 0;
					sol = k;
				}
			}
			if (ok && !sol){
				return -1;
			}
			if (ok && sol){
				Data[i][j] = sol;
				return 1;
			}
		}
	}
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++) if (!Data[i][j]){
			for(k = 0; k < 9; k++) if (Este[i][j][k]){
				for(sol = l = 0; l < 9; l++){
					if (Este[i][l][k]) sol++;
				}
				if (sol == 1){
					Data[i][j] = k;
					return 1;
				}
				for(sol = l = 0; l < 9; l++){
					if (Este[l][j][k]) sol++;
				}
				if (sol == 1){
					Data[i][j] = k;
					return 1;
				}
				sol = 0;
				for(l = i-i%3; l < i-i%3+3; l++){
					for(m = j-j%3; m < j-j%3+3; m++){
						if (Este[l][m][k]) sol++;
					}
				}
				if (sol == 1){
					Data[i][j] = k;
					return 1;
				}
			}
		}
	}
	return 0;
}
int IsDone(int Data[9][9]){
	int i, j;
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			if (!Data[i][j]) return 0;
		}
	}
	return 1;
}
int Solve(int deep, int Data[9][9], int Este[9][9][10]){
	int i, j, k;
	int sol;
	int end;
	int tmp[9][9];
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			tmp[i][j] = Data[i][j];
		}
	}
	for(;(sol = Search(Data, Este)) == 1;){
		MakeEste(Data, Este);
	}
	if (sol == -1){
		for(i = 0; i < 9; i++){
			for(j = 0; j < 9; j++){
				Data[i][j] = tmp[i][j];
			}
		}
		return -1;
	}
	if (IsDone(Data)){
		return 0;
	}
	end = 1;
	for(i = 0; i < 9 && end; i++){
		for(j = 0; j < 9 && end; j++) if (!Data[i][j]){
			for(k = 1; k <= 9; k++) if (Este[i][j][k]){
				Data[i][j] = k;
				MakeEste(Data, Este);
				if (!Solve(deep + 1, Data, Este)){
					return 0;
				}
				Data[i][j] = 0;
				MakeEste(Data, Este);
			}
			end = 0;
		}
	}
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			Data[i][j] = tmp[i][j];
		}
	}
	return -1;
}
int main(){
	ReadData(Data);
	MakeEste(Data, Este);
	if (Solve(1, Data, Este) == -1){
		printf("error Inconsistency!\n");
	}
    else{
		Show(Data);
	}
	return 0;
}






















































