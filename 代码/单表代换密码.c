#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>  
#include<string.h>
void meau() {
	printf("***********************************************\n");
	printf("************1.代换加密\n");
	printf("************2.代换解密\n");
	printf("************0.退出程序\n");
	printf("************************************************\n");
}
void showDetail(char key[]) {
	int i = 0;
	while (key[i]) {
		printf("明文字母%c->密文字母%c\n", 65 + i, key[i]);
		i++;
	}
}

void jiami(char key[], char mingwen[]) {              //加密
	char miwen[30] = "\0";
	int i = 0, j = 0;
	//printf("请输入明文\n");
	//gets(mingwen);
	printf("");
	while (mingwen[j]) {
		//for(i=0;i<26;i++){}
		if (mingwen[j] >= 'A' && mingwen[j] <= 'Z') {
			miwen[j] = key[mingwen[j] - 65];

		}
		else if (mingwen[j] >= 'a' && mingwen[j] <= 'z') {
			miwen[j] = key[mingwen[j] - 97] + 32;

		}
		else {
			miwen[j] = mingwen[j];
		}
		j++;
	}
	printf("加密后的结果为%s\n", miwen);

}
void jiemi(char key[], char miwen[]) {               //解密
	char mingwen[30] = "\0";
	int i = 0, j = 0;
	printf("传入密文为%s\n", miwen);
	printf("传入密钥为%s\n", key);
	while (miwen[j]) {
		if (miwen[j] >= 'A' && miwen[j] <= 'Z') {
			while (miwen[j] != key[i]) {
				i++;

			}
			mingwen[j] = 65 + i;
			i = 0;
		}
		else if (miwen[j] >= 'a' && miwen[j] <= 'z') {
			while ((miwen[j] - 32) != key[i])
			{
				i++;
			}
			mingwen[j] = 65 + i + 32;
			i = 0;
		}
		else {
			mingwen[j] = miwen[j];
		}
		j++;
	}
	printf("解密后的结果为%s\n", mingwen);
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
