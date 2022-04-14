#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>  
#include<string.h>
void meau() {
	printf("***********************************************\n");
	printf("************1.维吉尼亚加密\n");
	printf("************2.维吉尼亚解密\n");
	printf("************0.退出程序\n");
	printf("************************************************\n");
}
void jiami(char key[], char mingwen[]) {
	char miwen[30] = "\0";
	int i = 0, j = 0, k = 0;
	int m, n;
	m = strlen(mingwen);//明文长度
	n = strlen(key);//密钥长度
	for (i; i < m; i++) {
		if (mingwen[i] >= 'A' && mingwen[i] <= 'Z') {
			if (j != m) {
				miwen[k] = ((mingwen[i] - 'A') - (key[i] - 'A')) % 26 + 'A';//(mingwen+key)mod(26)
			}
			else {
				j = 0;//密钥循环
			}
		}
		else if (mingwen[i] >= 'a' && mingwen[i] <= 'z') {
			if (j != m) {
				miwen[k] = ((mingwen[i] - 'a') - (key[i] - 'a')) % 26 + 'a';//(mingwen+key)mod(26)
			}
			else {
				j = 0;//
			}
		}
		else {
			miwen[k] = mingwen[i];
		}
	}
	k++;
}
void jiemi() {

}
int main() {
	int index;
	char key[26] = "\0";
	char mingwen[30] = "\0";
	char miwen[30] = "\0";
	while (1) {
		meau();
		printf("请输入你的选择：");
		scanf("%d", &index);
		getchar();

		switch (index) {
		case 0:
			printf("");
			exit(0);
		case 1:
			printf("您选择了代换加密！\n");
			printf("请输入明文\n");
			gets(mingwen);
			printf("请输入密钥\n");
			gets(key);
			showDetail(key);
			jiami(key, mingwen);
			break;
		case 2:
			printf("您选择了代换解密！\n");
			printf("请输入密文\n");
			gets(miwen);
			printf("请输入密钥\n");
			gets(key);
			showDetail(key);
			jiemi(key, miwen);
			break;
		default:
			printf("请输入正确的数字！\n");
		}
	}
	return 0;
}