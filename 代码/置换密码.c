#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
void meau() {
	printf("**********************\n");
	printf("1.*****�û�����\n");
	printf("2.*****�û�����\n");
	printf("0.*****�˳�\n");
	printf("**********************\n");
}
void jiami(int key[],char mingwen[],int keylenth) {
	char miwen[30] = "\0";
	int i = 0,j = 0, k = 0;
	//printf("���������Ϊ%s\n", mingwen);
	//printf("�������ԿΪ%d%d%d%d\n", key[0],key[1],key[2],key[3],key[4]);
	for ( i = 0; i < strlen(mingwen); i++) {
		if (k == keylenth) {

			k = 0;
			j++;//����
			miwen[i] = mingwen[keylenth * j + key[k] - 1]; //printf("[%c]", miwen[i]);
		}
		else {
			miwen[i] = mingwen[keylenth * j + key[k] - 1]; //printf("[%c]", miwen[i]);
		}
		k++;
	}
	//printf("���ܺ󳤶�%d", strlen(miwen));
	//printf("���ܺ��ֵ�ǣ�%s\n",miwen);
}
void jiemi(int key[], char miwen[], int keylenth) {
	char mingwen[30] = "\0";
	int i = 0, j = 0, k = 0;
	
	for (i = 0; i < strlen(miwen); i++) {
		if (k == keylenth) {

			k = 0;
			j++;//����
			mingwen[i] = miwen[4 * j + key[k] - 1]; 
		}
		else {
			mingwen[i] = miwen[4 * j + key[k] - 1]; 
		}
		k++;
	}
	printf("���ܺ��ֵ�ǣ�%s\n", mingwen);
}
int main() {

	int keylength;
	char mingwen[30] = "\0";
	char miwen[30] = "\0";
	int key[10] ;
	int index;
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
			printf("��ѡ�����û����ܣ�\n");
			printf("����������\n");
			gets(mingwen);
			do
			{
				printf("��������Կ����\n");
				scanf("%d", &keylength);
			} while ( strlen(mingwen) % keylength != 0 );

			for (int i=0; i < keylength;i++) {
				printf("\n�������%d����ţ�",i+1);
				scanf("%d", &key[i]);
				getchar();
			}
			jiami(key, mingwen,keylength);
			break;
		case 2:
			printf("��ѡ�����û����ܣ�\n");
			printf("����������\n");
			gets(miwen);
			printf("��������Կ����\n");
			scanf("%d", &keylength);
			for (int i=0; i < keylength; i++) {
				printf("\n�������%d����ţ�",i+1);
				scanf("%d",&key[i]);
			}
			jiemi(key, miwen,keylength);
			break;
		default:
			printf("��������ȷ�����֣�\n");
		}
	}
	return 0;
}