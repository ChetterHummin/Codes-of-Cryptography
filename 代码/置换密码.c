#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
void meau() {
	printf("**********************\n");
	printf("1.*****置换加密\n");
	printf("2.*****置换解密\n");
	printf("0.*****退出\n");
	printf("**********************\n");
}
void jiami(int key[],char mingwen[],int keylenth) {
	char miwen[30] = "\0";
	int i = 0,j = 0, k = 0;
	//printf("传入的明文为%s\n", mingwen);
	//printf("传入的密钥为%d%d%d%d\n", key[0],key[1],key[2],key[3],key[4]);
	for ( i = 0; i < strlen(mingwen); i++) {
		if (k == keylenth) {

			k = 0;
			j++;//轮数
			miwen[i] = mingwen[keylenth * j + key[k] - 1]; //printf("[%c]", miwen[i]);
		}
		else {
			miwen[i] = mingwen[keylenth * j + key[k] - 1]; //printf("[%c]", miwen[i]);
		}
		k++;
	}
	//printf("加密后长度%d", strlen(miwen));
	//printf("加密后的值是：%s\n",miwen);
}
void jiemi(int key[], char miwen[], int keylenth) {
	char mingwen[30] = "\0";
	int i = 0, j = 0, k = 0;
	
	for (i = 0; i < strlen(miwen); i++) {
		if (k == keylenth) {

			k = 0;
			j++;//轮数
			mingwen[i] = miwen[4 * j + key[k] - 1]; 
		}
		else {
			mingwen[i] = miwen[4 * j + key[k] - 1]; 
		}
		k++;
	}
	printf("解密后的值是：%s\n", mingwen);
}
int main() {

	int keylength;
	char mingwen[30] = "\0";
	char miwen[30] = "\0";
	int key[10] ;
	int index;
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
			printf("您选择了置换加密！\n");
			printf("请输入明文\n");
			gets(mingwen);
			do
			{
				printf("请输入密钥长度\n");
				scanf("%d", &keylength);
			} while ( strlen(mingwen) % keylength != 0 );

			for (int i=0; i < keylength;i++) {
				printf("\n请输入第%d个序号：",i+1);
				scanf("%d", &key[i]);
				getchar();
			}
			jiami(key, mingwen,keylength);
			break;
		case 2:
			printf("您选择了置换解密！\n");
			printf("请输入密文\n");
			gets(miwen);
			printf("请输入密钥长度\n");
			scanf("%d", &keylength);
			for (int i=0; i < keylength; i++) {
				printf("\n请输入第%d个序号：",i+1);
				scanf("%d",&key[i]);
			}
			jiemi(key, miwen,keylength);
			break;
		default:
			printf("请输入正确的数字！\n");
		}
	}
	return 0;
}