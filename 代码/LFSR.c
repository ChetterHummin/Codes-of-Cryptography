#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>  
#include<string.h>
#include<math.h>
#include<time.h>
#include<malloc.h>

int* LSRF(int row, char system[], char condition[]) {
	int condition_0[30];
	int index = 1, arrow = 1;
	int num=-1;
	int** Pool = NULL;
	int col=300;
	col= (int)(pow(2, row) - 1); 
	Pool = (int**)malloc(sizeof(int*) * row); 
	for (int i = 0; i < row; i++) {
		Pool[i] = (int*)malloc(sizeof(int) * col);
		memset(Pool[i], 0, sizeof(int) * col);
	}
	int* line = (int*)malloc(sizeof(int) * 8);
	for (int i = 0; i < row; i++) {
		condition_0[i] = condition[i] - 48;
	}
	for (int i = 0; i < row; i++) {
		Pool[i][0] = condition_0[i]; 
	}
	printf("t0时刻的状态是：");
	for (int i = 0; i < row; i++) {
		printf("%d ",Pool[i][0]);
	}
	printf("\n");
	while(index) {
		for (int i = 0; i < row; i++) {
			if (system[i] == 49) {
				if (num == -1) {
					num = Pool[i][arrow - 1];
				}
				else {
					num ^= Pool[i][arrow - 1];
				}
			}
		}
		Pool[0][arrow] = num;
		for (int i = 1; i < row;i++) {
			Pool[i][arrow] = Pool[i-1][arrow-1];
		}
		printf("t%d时刻的状态是：",arrow);
		for (int i = 0; i < row; i++) {
			printf("%d ", Pool[i][arrow]);
		}
		printf("\n");
		index = 0;
		for (int i = 0; i < row; i++) {
			if (Pool[i][arrow] != Pool[i][0]) {
				index = 1; 
			}		
		}
		arrow++; 
		num = -1;
	}
	printf("产生的序列是：");
	for (int i = 0; i < arrow; i++) {
		printf("%d ",Pool[row-1][i]);
	}
	printf("\n周期是：%d",arrow-1);
	if (arrow - 1 >= 8) {
		for (int i = 0; i < 8; i++) {
			line[i] = Pool[row - 1][i];
		}		
	}else{
		for (int i = 0, j = 0; i < 8; i++) {
			//for (int j = 0; j < arrow - 1; j++)
			line[i] = Pool[row - 1][j];
			
			j++;
			if (j >= arrow) {
				j = 0;
			}
		}
	}
	return line;
}
void jiami(int Line[]) {
	FILE* fp1,*fp2;

	char plaintext[128];
	char ciphetext[128];
	char plaintextPath[30];
	char ciphetextPath[30];
	unsigned char key;
	int line[8];
	int sum = 0;
	
	memset(plaintextPath, 0, sizeof(char) * 30);
	memset(ciphetextPath, 0, sizeof(char) * 30);
	memset(ciphetext, 0, sizeof(char) * 128);
	printf("\n请输入需要加解密的文件路径：");
	scanf("%s",plaintextPath);
	if ((fp1 = fopen(plaintextPath, "r")) == NULL) {
		printf("Can't open this file[%s].\n", plaintextPath);
		exit(0);
	}
	printf("请输入加解密后的文件路径：");
	scanf("%s", ciphetextPath);
	if ((fp2 = fopen(ciphetextPath, "w+")) == NULL) {
		printf("Can't open this file[%s].\n", ciphetextPath);
		exit(0);
	}
	fgets(plaintext, 80, fp1);
	for (int i = 0; i < 8; i++) {
		sum += Line[i] * ((int)(pow(2, i)));
	}
	key = sum;
	for (int i = 0; i < strlen(plaintext); i++) {
		ciphetext[i] = plaintext[i] ^ key;
	}
	//printf("%d",key);
	printf("%s",ciphetext);
	fputs(ciphetext, fp2);
	if (fclose(fp1)) {
		printf("Can't close the file![%s].\n", plaintextPath);
		exit(0);
	}
	if (fclose(fp2)) {
		printf("Can't close the file![%s].\n", ciphetextPath);
		exit(0);
	}
}
int main() {
	int sum;
	char system[30] = { 0 };
	char condition[30] = { 0 };
	int* Line;
A:
	printf("\n请输入线性移位寄存器的阶数：");
	scanf("%d", &sum);
	if (sum < 2) {
		goto A;
	}
B:
	printf("\n请输入反馈函数中的系数（从a%d到a1的顺序）：", sum);
	scanf("%s", system);
	if (strlen(system) != sum) {
		goto B;
	}
	else {
		for (int i = 0; i < sum; i++) {
			if ((system[i] != '0') && (system[i] != '1')) {
				goto B;
			}
		}
	}
C:
	printf("请输入初始状态（从a%d到a1的顺序）：",sum);
	scanf("%s", condition);
	if (strlen(condition) != sum) {
		goto C;
	}
	else {
		for (int i = 0; i < sum; i++) {
			if (condition[i] != '0' && condition[i] != '1') {
				goto C;
			}
		}
	}
	Line =LSRF(sum, system,condition);
	jiami(Line);
}