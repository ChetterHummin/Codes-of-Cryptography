#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>  
#include<string.h>
void meau() {
	printf("***********************************************\n");
	printf("************1.��������\n");
	printf("************2.��������\n");
	printf("************0.�˳�����\n");
	printf("************************************************\n");
}
void showDetail(char key[]) {
	int i = 0;
	while (key[i]) {
		printf("������ĸ%c->������ĸ%c\n", 65 + i, key[i]);
		i++;
	}
}

void jiami(char key[], char mingwen[]) {              //����
	char miwen[30] = "\0";
	int i = 0, j = 0;
	//printf("����������\n");
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
	printf("���ܺ�Ľ��Ϊ%s\n", miwen);

}
void jiemi(char key[], char miwen[]) {               //����
	char mingwen[30] = "\0";
	int i = 0, j = 0;
	printf("��������Ϊ%s\n", miwen);
	printf("������ԿΪ%s\n", key);
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
	printf("���ܺ�Ľ��Ϊ%s\n", mingwen);
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
