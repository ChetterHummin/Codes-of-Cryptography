#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>  
#include<string.h>
#include<math.h>
#include<time.h>
#include<malloc.h>


void meau() {
	printf("\n****1��RC4����****\n");
	printf("****2��RC4����****\n");
	printf("****0���˳�****\n");
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
	printf("\n��������Ҫ�ӽ��ܵ��ļ�·����");
	scanf("%s", plaintextPath);
	getchar();
	if ((fp1 = fopen(plaintextPath, "r")) == NULL) {
		printf("Can't open this file[%s].\n", plaintextPath);
		exit(0);
	}
	printf("������ӽ��ܺ���ļ�����·����");
	scanf("%s", ciphetextPath);
	getchar();
	if ((fp2 = fopen(ciphetextPath, "w+")) == NULL) {
		printf("Can't open this file[%s].\n", ciphetextPath);
		exit(0);
	}
	fgets(plaintext, 128, fp1);
	printf("�ļ���С��%d�ֽ�\n",strlen(plaintext));
	printf("��ȡ�������ǣ�\n");
	printf("%s",plaintext);
	printf("\n��������Կ��");           
	gets(key);
	
	//scanf("%[^\n]s", key);  //scanf��ȡ�ո�
	for (int i = 0,k=0; i < 256; i++) {
		
		KEY[i] = key[k];
		k++;
		if (k == strlen(key)) {
			k = 0;
		}
	}
	for (int i = 0, j = 0; i < 256; i++) {              //����S[i]��S[j]��ֵ����S��
		j = (j + S[i] + KEY[i]) % 256;
		temp = S[i];
		S[i] = S[j];
		S[j] = temp;
	}

	for (int t = 0,i=0,j=0; t < strlen(plaintext); t++) {
		i = (i + 1) % 256;
		j = (j + S[i]) % 256;
		temp = S[i];                       //����S[i]��S[j]��ֵ����S��
		S[i] = S[j];
		S[j] = temp;
		ciphetext[t] = (plaintext[t] ^ S[(S[i] + S[j]) % 256]);
	}
	printf("\n���Һ��S���ǣ�\n");
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			printf("%02X  ", S[i * 16 + j]);
		}
		printf("\n");
	}
	if (index == 1) {
		printf("���ܺ�õ���ʮ�������ǣ�\n");
	}
	else {
		printf("���ܺ�õ���ʮ�������ǣ�\n");
	}
	
	for (int i = 0; i < strlen(plaintext); i++) {
		printf("%02X ", ciphetext[i]);
	}
	if (index == 1) {
		printf("���ܺ�õ���ֵ�ǣ�\n");
	}
	else {
		printf("���ܺ�õ���ֵ�ǣ�\n");
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
	printf("��ʼд���ļ���\n�ļ�д��ɹ���\n");
	
}
int main() {
	int index = 0;
	while (1) {
		meau();
		printf("��ѡ��");
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