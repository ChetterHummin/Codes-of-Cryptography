#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>

int* LFSR_A5(char x[], char y[], char z[], int sum) {

	int* stream=(int*)malloc(sizeof(int) * sum);
	int number_0 = 0, number_1 = 0;
	int number;
	int temp;
	int bit = 0;
	int XLFSR[19];
	int YLFSR[22];
	int ZLFSR[23];
	for (int i = 0; i < 19; i++) {
		XLFSR[i] = x[i] - 48;
		
	}
	for (int i = 0; i < 22; i++) {
		YLFSR[i] = y[i] - 48; //printf("%d\n", YLFSR[i]);
	}
	for (int i = 0; i < 23; i++) {
		ZLFSR[i] = z[i] - 48; //printf("%d\n", ZLFSR[i]);
	}

	while (bit<=sum) {
		number_0 = 0;
		number_1 = 0;
		//printf("{%d -%d %d %d}", bit,XLFSR[8], YLFSR[10], ZLFSR[10]);
		if (XLFSR[8]==0) {
			number_0++;
		}
		else {
			number_1++;
		}
		if (YLFSR[10] == 0) {
			number_0++;
		}
		else {
			number_1++;
		}
		if (ZLFSR[10] == 0) {
			number_0++;
		}
		else {
			number_1++;
		}
		(number_0 > number_1) ? (number=0) : (number=1);
		if (number==XLFSR[8]) {
			temp = XLFSR[13] ^ XLFSR[16] ^ XLFSR[17] ^ XLFSR[18]; //printf("{X%d}", temp);
			for (int i = 18; i >0; i--) {
				XLFSR[i] = XLFSR[i-1];
			}
			XLFSR[0] = temp; 
		}
		if (number == YLFSR[10]) {
			temp = YLFSR[20] ^ YLFSR[21];
			for (int i = 21; i >0; i--) {
				YLFSR[i] = YLFSR[i - 1];
			}
			YLFSR[0] = temp; //printf("{Y%d}", temp);
		}
		if (number==ZLFSR[10]) {
			temp = ZLFSR[7] ^ ZLFSR[20] ^ ZLFSR[21] ^ ZLFSR[22];
			for (int i = 22; i >0; i--) {
				ZLFSR[i] = ZLFSR[i-1];
			}
			ZLFSR[0] = temp; //printf("{Z%d}",temp);
		}
		stream[bit] = XLFSR[18] ^ YLFSR[21] ^ ZLFSR[22];
		//printf("%d[%d ]%d%d%d", bit,stream[bit],XLFSR[18],YLFSR[21],ZLFSR[22]);
		bit++; 
		/*for (int i = 0; i < 19; i++) {
			printf("%d ", XLFSR[i]);
		}printf("\n");
		for (int i = 0; i < 22; i++) {
			printf("%d ", YLFSR[i]);
		}printf("\n");
		for (int i = 0; i < 23; i++) {
			printf("%d ", ZLFSR[i]);
		}*/
	}
	printf("����Կ�ǣ�");
	for (int i = 0; i < sum; i++) {
		printf("%d", stream[i]);
	}
	return stream;
}

int main() {
	int index;
	int sum;
	char x[30] = { 0 };
	//	char*x = (char*)malloc(sizeof(char) * 30);
	char y[30] = { 0 };
	char z[30] = { 0 };
A:
	printf("��������Ҫ���ɵ�λ����");
	scanf("%d", &sum);
	if (sum <= 1) {
		printf("���ɵ�λ���������1\n");
		goto A;
	}
X:
	printf("������XLFSR�ĳ�ʼ״̬��19λ)");
	scanf("%s", &x);
	getchar();
	if (strlen(x) != 19) {
		printf("�������벻���Ϲ���\n");
		goto X;
	}
	for (int i = 0; i < 19; i++) {
		if ((x[i]!='1')&&(x[i]!='0')) {
			printf("�������벻���Ϲ���\n");
			goto X;
		}
	}
Y:
	printf("������YLFSR�ĳ�ʼ״̬��22λ)");
	scanf("%s", &y);
	if (strlen(y) != 22) {
		printf("�������벻���Ϲ���\n");
		goto Y;
	}
	for (int i = 0; i < 22; i++) {
		if ((y[i] != '1') && (y[i] != '0')) {
			printf("�������벻���Ϲ���\n");
			goto Y;
		}
	}
Z:
	printf("������ZLFSR�ĳ�ʼ״̬��23λ)");
	scanf("%s", &z);
	if (strlen(z) != 23) {
		printf("�������벻���Ϲ���\n");
		goto Z;
	}
	for (int i = 0; i < 23; i++) {
		if ((z[i] != '1') && (z[i] != '0')) {
			printf("�������벻���Ϲ���\n");
			goto Z;
		}
	}
	LFSR_A5(x,y,z,sum);
	
}