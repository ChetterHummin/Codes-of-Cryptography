#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
void menu() {
	printf("\n****************\n");
	printf("1.�����������\n");
	printf("2.�����������\n");
	printf("0.�˳�����\n");
	printf("*****************\n");
	printf("�����룺");
}
int checkLine(int a, int b) {  //������������һ����Ϊ���������У��򷵻�0�����򷵻�1  //a�����bΪ������֮ǰ�ĺ�
	int c = a > b ? (0) : (1);
	return c;
}
int checkNumbers(int m, int n) {  //�ж������Ƿ��ʣ���շת�������������Ƿ���0���෴����1
	//int n = p * q;
	//int ��_n = (p - 1) * (q - 1);

	int temp;
	if (m < n) {
		return 1;
	}
	if (m < n) {
		temp = m;
		m = n;
		n = temp;
	}temp = 1;
	while (temp != 0) {
		temp = m % n;
		m = n;
		n = temp;
	}
	if (m == 1) {
		return 0;
	}
	else {
		return 1;
	}
}
void jiami(int m, int n, int* Line,int sum) {
	int temp;
	int x, y;
	int k = 0;
	char plaintext_0[50];
	int length;
	int* key_0 = (int*)malloc(sizeof(int) * sum);
	for (int i = 0; i < sum;i++) {
		key_0[i] = (Line[i] * n) % m;
	}
	printf("���ɵĹ�ԿΪ��");
	for (int i = 0; i < sum;i++) {
		printf("%d  ",key_0[i]);
	}printf("\n");
	printf("������Ҫ���ܵ����ģ�");
	scanf("%s",plaintext_0);
	getchar();
	if ((strlen(plaintext_0) * 8) % sum == 0) {
		length = strlen(plaintext_0) * 8;
	}
	else {
		length = strlen(plaintext_0) * 8+(sum-(strlen(plaintext_0)*8)%sum);
	}
	int* plaintext = (int*)malloc(sizeof(int)*length);
	int* ciphetext = (int*)malloc(sizeof(int)*(length/sum));
	memset(plaintext, 0, sizeof(int) * length);
	for (int i = 0; i < strlen(plaintext_0);i++) {
		temp = plaintext_0[i];
		k = 0;
		while (temp!=0) {
			x = temp / 2;
			y = temp % 2; 
			temp = x;
			plaintext[8 * (i+1)-k-1] = y;
			k++;
		}		
	}
	for (int i = 0; i < (length / sum); i++) {
		temp = 0;
		for (int j = 0; j < sum;j++) {
			temp += key_0[j] * plaintext[i*sum+j];
		}
		ciphetext[i] = temp;
	}
	printf("���ɵ����Ķ����ƴ�Ϊ��\n");
	for (int i = 0; i < (length/8)*8;i++) {
		printf("%d",plaintext[i]);
		if (i%8==7){//(i%sum==sum-1) {
			printf("    ");
		}
	}printf("\n");
	printf("���ɵ����Ĵ�Ϊ��");
	for (int i = 0; i < (length / sum);i++) {
		printf("%d  ",ciphetext[i]);
	}printf("\n");
}
void jiemi(int m, int n, int* Line,int sum) {
	int x, y, k;
	int n_1=0, temp=0;
	int sum_1;
	while (temp!=1) {
		n_1++;
		temp=n_1* n% m;
	}
	printf("���ɵĽ��ܳ˷���Ԫn_1Ϊ%d\n",n_1);
	printf("��������Ҫ���ܵ����ĸ�����");
	scanf("%d",&sum_1);
	getchar();
	int* ciphetext_0 = (int*)malloc(sizeof(int) * sum_1);
	for (int i = 0; i < sum_1;i++) {
		printf("�������%d�����ģ�", i + 1);
		scanf("%d", &ciphetext_0[i]);
		getchar();
	}
	for (int i = 0; i < sum_1; i++) {
		ciphetext_0[i] = (ciphetext_0[i] * n_1) % m; //printf("%d",ciphetext_0[i]);
	}
	int* ciphetext = (int*)malloc(sizeof(int) * sum_1*sum);
	memset(ciphetext, 0, sizeof(int) * sum_1*sum);
	/*for (int i = 0; i < sum_1; i++) {
		temp = ciphetext_0[i];
		k = 0;
		while (temp != 0) {
			x = temp / 2;
			y = temp % 2;
			temp = x;
			ciphetext[8 * (i + 1) - k - 1] = y;
			k++;
		}
	}*/
	for (int i = 0,j=0; i < sum_1;i++) {
		temp = ciphetext_0[i]; //printf("%d",temp);
		j = sum-1;
		while (temp!=0) {
			if (Line[j] <= temp) {
				
				temp -= Line[j]; //printf("[%d]", temp);
				ciphetext[j + sum * i] = 1;
			}
			j--;
		}
	}
	for (int i = 0; i < sum_1;i++) {
		printf("%03d->",ciphetext_0[i]);
		for (int j = 0; j < sum; j++) {
			printf("%d",ciphetext[j+i*sum]);
		}printf("\n");
	}
	int* plaintext = (int*)malloc(sizeof(int)*((sum_1*sum)/8));
	for (int i = 0; i < ((sum_1 * sum) / 8);i++) {
		temp = 0;
		for (int j = 0; j < 8;j++) {
			if (ciphetext[j+i*8]) {
				temp += (int)pow(2,7-j);
			}
			
		}
		plaintext[i] = temp;
	}
	printf("���ܺ�õ���");
	for (int i = 0; i < ((sum_1 * sum) / 8);i++) {
		printf("%c",plaintext[i]);
	}
}
void backbag(int index) {
	int temp = 0;
	int temp_0 = 0;
	int sum = 6;
	int m, n;
	printf("�����볬�������е�Ԫ�ظ�����");
	scanf("%d", &sum);
	getchar();
	int* Line = (int*)malloc(sizeof(int) * sum);
	for (int i = 0; i < sum; i++) {
	A:		printf("�������%d��Ԫ�أ�", i + 1);
		scanf("%d", &Line[i]);
		getchar();
		temp_0 = temp;//+ Line[i];
		if (checkLine(Line[i], temp_0)) {
			printf("Ԫ��%d���ǳ��������У����������룡\n", Line[i]);
			goto A;
		}
		temp += Line[i];
	}
B:	printf("������m\n");
	scanf("%d", &m);
	getchar();
	printf("������n\n");
	scanf("%d", &n);
	if (checkNumbers(m,n)) {
		printf("m,n�����ʣ����������룡\n");
		goto B;
	}
	if (index == 1) {
		jiami(m, n, Line, sum);
	}
	else {
		jiemi(m, n, Line, sum);
	}	
}
int main() {
	int index;
	while (1) {
		menu();
		//printf("");
		scanf("%d",&index);
		getchar();
		switch (index) {
		case 1:
			backbag(index);
			break;
		case 2:
			backbag(index);
			break;
		case 0:
			exit(0);
		default:
			break;
		}
	}
	
	return 0;
}