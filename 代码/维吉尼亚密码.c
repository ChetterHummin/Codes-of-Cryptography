#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>  
#include<string.h>
void meau() {
	printf("***********************************************\n");
	printf("************1.ά�����Ǽ���\n");
	printf("************2.ά�����ǽ���\n");
	printf("************0.�˳�����\n");
	printf("************************************************\n");
}
void jiami(char key[], char mingwen[]) {
	char miwen[30] = "\0";
	int i = 0, j = 0, k = 0;
	int m, n;
	m = strlen(mingwen);//���ĳ���
	n = strlen(key);//��Կ����
	for (i; i < m; i++) {
		if (mingwen[i] >= 'A' && mingwen[i] <= 'Z') {
			if (j != m) {
				miwen[k] = ((mingwen[i] - 'A') - (key[i] - 'A')) % 26 + 'A';//(mingwen+key)mod(26)
			}
			else {
				j = 0;//��Կѭ��
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
		printf("���������ѡ��");
		scanf("%d", &index);
		getchar();

		switch (index) {
		case 0:
			printf("");
			exit(0);
		case 1:
			printf("��ѡ���˴������ܣ�\n");
			printf("����������\n");
			gets(mingwen);
			printf("��������Կ\n");
			gets(key);
			showDetail(key);
			jiami(key, mingwen);
			break;
		case 2:
			printf("��ѡ���˴������ܣ�\n");
			printf("����������\n");
			gets(miwen);
			printf("��������Կ\n");
			gets(key);
			showDetail(key);
			jiemi(key, miwen);
			break;
		default:
			printf("��������ȷ�����֣�\n");
		}
	}
	return 0;
}