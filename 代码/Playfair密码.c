#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>  
#include<string.h>




char* changekey(char *key) {
	static char key1[26]="\0";                                  // ��̬�ֲ�����
    static int keysize[26];
	int k;
	for (int i = 0; key[i]; i++) {

		if (key[i] >= 'a' && key[i] <= 'z') {                              //�ٽ���Կ����ȫ��ת���ɴ�д
			key[i] -= 32;
		}
	}
	for (int i = 0; key[i]; i++) {                                    //�ڲ�������J��ĸ�滻��I��ĸ
		if (key[i] == 'J') {
			key[i] = 'I';
		}
	}
	printf("J����I���key�ǣ�%s\n", key);
	for (int i = 0; key[i]; i++) {                                //�۽���Կ���ظ����ֵ���ĸ�޳�
		for (int j=i+1; key[j]; j++) {
			if (key[i] != key[j]) {
				//j++;
				
			}
			else {
				k = j;// + 1;
				while (key[k]) {
					key[k] = key[k+1];
					k++;
				}
				key[k - 1] = '\0';

			}
		}
	}
	printf("ȥ�غ��key�ǣ�  %s\n", key);
	for (int m = 0; m < strlen(key); m++) {
		key1[m] = key[m];
		keysize[key[m]-'A'] = 1;
	}
	for (int i = 0,k=0; i < 26; i++) {
		if (i ==('J' - 'A')) {
			continue; 
		}
		if (keysize[i] == 0) {
			key1[k + strlen(key)] = 'A' + i; 
			k++;
			
		}
	}	
	printf("����key�ǣ�    %s\n", key1);
	printf("key�γɵľ����ǣ�\n");
	for (int i = 0;i<25; i++) {
		printf("%c ", key1[i]);
		if ((i + 1) % 5 == 0)
		{
			printf("\n");
		}
	}
	return key1;
}
char* changemingwen(char*mingwen) {
	int a = 20;
	static char mingwen1[26] = "\0";
	
	//char* p = NULL;
	//p = (char*)malloc(sizeof(char) * 30);
	
	for (int i = 0; mingwen[i]; i++) {

		if (mingwen[i] >= 'a' && mingwen[i] <= 'z') {                              //�ٽ���������ȫ��ת���ɴ�д
			mingwen[i] -= 32;
		}
	}
	for (int i = 0; mingwen[i]; i++) {                                    //�ڲ�������J��ĸ�滻��I��ĸ
		if (mingwen[i] == 'J') {
			mingwen[i] = 'I';
		}
	}
	printf("J����I��������ǣ�%s\n", mingwen);
	//�۽���������һ�飬�������������ĸһ�������Z�������ͬ����ĸ��Z������A - Y��˳����Ƶ������
	//�ܾ���������ַ���������������������һ����ĸ������ĸ��������һ����ĸ��Z������A - Y��˳����Ƶ������

	int k = 0;
	while (k<strlen(mingwen))//(mingwen[k]!=0)
	{
		if ((mingwen[k] == mingwen[k + 1]) && (k % 2 == 0)&&(mingwen[k+1]!=0)) {
			for (int m = strlen(mingwen); m > k+1; m--) {
				mingwen[m] = mingwen[m - 1];
			}
			if (mingwen[k] == 'Z') {
				mingwen[k + 1] = 'A';
			}
			else {
				mingwen[k + 1] = 'Z';
			}
		}
		
		k++;
	}
	if (k%2!=0) {
		if (mingwen[k-1] == 'Z') {
			mingwen[k] = 'A';
		}
		else {
			mingwen[k] = 'Z';
		}
	}
	
	printf("������������ǣ�  %s\n", mingwen);
	
	return mingwen;
}
void meau() {
	printf("\n*************\n");
	printf("1��Playfair����\n");
	printf("2��Playfair����\n");
	printf("0���˳�\n");
	printf("***************\n");
}
void jiami(char* key1, char* mingwen1) {
	int row, row1,row2;                //��
	int col, col1,col2;                //��
	int k = 0, j = 0, t = 0;
	int p;
	char miwen[30] = "\0";
	memset(miwen, 0, sizeof(char) * 30);  
	
	while (mingwen1[k]!=0) {
		while (mingwen1[k] != key1[j]) {
			j++;
		}
		row1 = j / 5;
		col1 = j % 5; 
		while (mingwen1[k+1] != key1[t]) {
			 t++;
		}
		row2 = t / 5;
		col2 = t % 5; 
		if (row1 == row2) {
			col1 = (col1 + 1) % 5;
			col2 = (col2 + 1) % 5;
			miwen[k] = key1[row1 * 5 + col1];
			miwen[k+1] = key1[row2 * 5 + col2];
			
		}
		else if (col1 == col2) {
			row1 = (row1 + 1) % 5;
			row2 = (row2 + 1) % 5;
			miwen[k] = key1[row1 * 5+col1];
			miwen[k+1] = key1[row2 * 5+col2];
			
		}
		else {
			p = col1;
			col1 = col2;
			col2 = p;
			miwen[k] = key1[row1 * 5+col1];
			miwen[k+1] = key1[row2 * 5+col2];
			
			
		} 	
		j = 0;
		t = 0;
		k = k + 2;
		
	}
	printf("���ܺ�������ǣ�  %s\n", miwen);
}
void jiemi(char* key1, char miwen1[]) {
	int row, row1, row2;                //��
	int col, col1, col2;                //��
	int k = 0, j = 0, t = 0;
	int p;
	char mingwen[30] = "\0";
	memset(mingwen, 0, sizeof(char) * 30);
	//printf("%d\n", strlen(miwen1));
	//printf("[%s]\n", miwen1);
	while (miwen1[k] != 0) {
		while (miwen1[k] != key1[j]) {
			j++;
		}
		row1 = j / 5;
		col1 = j % 5;
		while (miwen1[k + 1] != key1[t]) {
			t++;
		}
		row2 = t / 5;
		col2 = t % 5;
		if (row1 == row2) {
			col1 = (col1 - 1+5) % 5;
			col2 = (col2 - 1+5) % 5;
			mingwen[k] = key1[row1 * 5 + col1];
			mingwen[k + 1] = key1[row2 * 5 + col2];
			//printf("[%c %c]", mingwen[k], mingwen[k + 1]);
		}
		else if (col1 == col2) {
			row1 = (row1 - 1+5) % 5;
			row2 = (row2 - 1+5) % 5;
			mingwen[k] = key1[row1 * 5 + col1];
			mingwen[k + 1] = key1[row2 * 5 + col2];
			//printf("[%c %c]", mingwen[k], mingwen[k + 1]);
		}
		else {
			p = col1;
			col1 = col2;
			col2 = p;
			mingwen[k] = key1[row1 * 5 + col1];
			mingwen[k + 1] = key1[row2 * 5 + col2];
			//printf("[%c %c]", mingwen[k], mingwen[k + 1]);

		}
		j = 0;
		t = 0;
		k = k + 2;
		//printf("%d", k);
	}//printf("%d\n", strlen(mingwen));
	printf("���ܺ�������ǣ�  %s\n", mingwen);
}
int main() {

	int index = 1;
	char mingwen[30] = "\0";
	char miwen[30] = "\0";
	char *key1;
	char* mingwen1;
	char* miwen1;
	char key[26];
	
	//change(key);
	while (1) {
		meau();
		printf("\n**************\n");
		printf("��ѡ��\n");
		scanf("%d", &index);
		//gets();
		getchar();
		switch (index) {
		case 0:
				printf("");
				exit(0);
		case 1:
			printf("");
			memset(mingwen, 0, sizeof(char) * 30);
			memset(key, 0, sizeof(char) * 26);
			printf("����������\n");
			gets(mingwen);
			printf("��������Կ\n");
			gets(key);
			key1=changekey(key);
			mingwen1=changemingwen(mingwen);
			printf("������������ǣ�  %s\n", mingwen);
			jiami(key1,mingwen1);
			break;
		case 2:
			printf("");
			memset(miwen, 0, sizeof(char) * 30);
			memset(key, 0, sizeof(char) * 26);
			printf("����������\n");
			gets(miwen);
			printf("��������Կ\n");
			gets(key);
			key1 = changekey(key);
			//miwen1 = mingwen;
			jiemi(key1, miwen);
			break;
		default:
			printf("��������ȷ�����֣�\n");


		}
	}
	return 0;
}