#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>  
#include<string.h>
#include<math.h>
#include<time.h>
#include<malloc.h>


void meau() {
	printf("\n****1、RC4解密****\n");
	printf("****2、RC4加密****\n");
	printf("****0、退出****\n");
	printf("*********************\n");
}
void jiami(int index) {
	FILE* fp1, * fp2;
	int temp;
	int S[256];
	int KEY[256];
	unsigned char plaintext[128];
	unsigned char ciphetext[128];
	char plaintextPath[30];
	char ciphetextPath[30];
	char key[30] ;
	for (int i = 0; i < 256; i++) {
		S[i] = i;
	}
	memset(plaintextPath, 0, sizeof(char) * 30);
	memset(ciphetextPath, 0, sizeof(char) * 30);
	memset(ciphetext, 0, sizeof(char) * 128);
	printf("\n请输入需要加解密的文件路径：");
	scanf("%s", plaintextPath);
	getchar();
	if ((fp1 = fopen(plaintextPath, "r")) == NULL) {
		printf("Can't open this file[%s].\n", plaintextPath);
		exit(0);
	}
	printf("请输入加解密后的文件保存路径：");
	scanf("%s", ciphetextPath);
	getchar();
	if ((fp2 = fopen(ciphetextPath, "w+")) == NULL) {
		printf("Can't open this file[%s].\n", ciphetextPath);
		exit(0);
	}
	fgets(plaintext, 128, fp1);
	printf("文件大小是%d字节\n",strlen(plaintext));
	printf("读取的内容是：\n");
	printf("%s",plaintext);
	printf("\n请输入密钥：");           
	gets(key);
	
	//scanf("%[^\n]s", key);  //scanf读取空格
	for (int i = 0,k=0; i < 256; i++) {
		
		KEY[i] = key[k];
		k++;
		if (k == strlen(key)) {
			k = 0;
		}
	}
	for (int i = 0, j = 0; i < 256; i++) {              //交换S[i]和S[j]的值扰乱S盒
		j = (j + S[i] + KEY[i]) % 256;
		temp = S[i];
		S[i] = S[j];
		S[j] = temp;
	}

	for (int t = 0,i=0,j=0; t < strlen(plaintext); t++) {
		i = (i + 1) % 256;
		j = (j + S[i]) % 256;
		temp = S[i];                       //交换S[i]和S[j]的值扰乱S盒
		S[i] = S[j];
		S[j] = temp;
		ciphetext[t] = (plaintext[t] ^ S[(S[i] + S[j]) % 256]);
	}
	printf("\n扰乱后的S盒是：\n");
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			printf("%02X  ", S[i * 16 + j]);
		}
		printf("\n");
	}
	if (index == 1) {
		printf("加密后得到的十六进制是：\n");
	}
	else {
		printf("解密后得到的十六进制是：\n");
	}
	
	for (int i = 0; i < strlen(plaintext); i++) {
		printf("%02X ", ciphetext[i]);
	}
	if (index == 1) {
		printf("加密后得到的值是：\n");
	}
	else {
		printf("解密后得到的值是：\n");
	}
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
	printf("开始写入文件：\n文件写入成功！\n");
	
}
int main() {
	int index = 0;
	while (1) {
		meau();
		printf("请选择：");
		scanf("%d",&index);
		getchar();
		switch (index) {
		case 1:
			jiami(1);
			break;
		case 2:
			jiami(0);
			break;
		case 0:
			exit(0);
		default:
			break;
		}
	}
	//jiami();
}