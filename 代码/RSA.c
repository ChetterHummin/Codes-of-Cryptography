#define _CRT_SECURE_NO_WARNINGS
/**@created dy Chetter Hummin 20220511
*/
#include<stdio.h>
#include<string.h>
#include<math.h>
int checknumber(int temp) {  //�ж��Ƿ�Ϊ����������Ƿ���0���෴����1
	int index = (int)sqrt((double)temp);
	if (temp <= 2) {
		return 1;
	}
	for (int i = 2; i <= index; i++) {
		if (temp % i == 0) {
			return 1;
		}
	}
	return 0;
}
int checknumbers(int e, int p, int q) {  //�ж������Ƿ��ʣ���շת�������������Ƿ���0���෴����1
	int n = p * q;
	int ��_n = (p-1) * (q-1);
	int temp;
	if (e > ��_n) {
		return 1;
	}
	if (e < ��_n) {
		temp = e;
		e = ��_n;
		��_n = temp;
	}temp = 1;
	while (temp != 0) {
		temp = e % ��_n;
		e = ��_n;
		��_n = temp;
	}
	if (e == 1) {
		return 0;
	}
	else {
		return 1;
	}
}
int jiami(char plaintext_0[],int e,int p,int q) {
	int plaintext[80] = {0};
	int length = 0;
	int n = p * q; 
	int Temp[2];
	int temp=0;//��ʱ����
	for (int i = 0, j = 0; i < strlen(plaintext_0); i++) {
		
		if (((plaintext_0[i] <= 90) && (plaintext_0[i] >= 65)) || ((plaintext_0[i] <= 122) && (plaintext_0[i] >= 97))) {
			if ((plaintext_0[i] <= 90 && plaintext_0[i] >= 65)) {
				Temp[temp] = plaintext_0[i] - 65;
			}
			if (((plaintext_0[i] <= 122) && (plaintext_0[i] >= 97))) {
				Temp[temp] = plaintext_0[i] - 97;
			}
			temp++; 
		}
		if (temp == 2) {
			plaintext[j] = Temp[0] * 100 + Temp[1];
			j++;
			temp = 0;
		}
		if ((temp==1)&&(i==strlen(plaintext_0)-1)) {
			plaintext[j] = Temp[0];//*100;
			j++;
		}
		length = j; 
		
	}
	for (int i = 0; i <length;i++) {
		temp = (plaintext[i] * plaintext[i]) % n;
		for (int j = 3; j <= e; j++) {
			temp *= plaintext[i];
			temp %= n;
		}
		plaintext[i] = temp; 
	}
	printf("���ܽ���ǣ�(���ķ�ż��λĬ����0)\n");
	for (int i = 0; i < length;i++) {
		printf("  %04d",plaintext[i]);
	}

}
int main() {
	char plaintext[80];
	int p, q, e;
	printf("��������Ҫ���ܵ��ַ�����");
	scanf("%[^\n]s", plaintext);
	getchar();
P:printf("������p=");
	scanf("%d", &p);
	getchar();
	if (checknumber(p)) {
		printf("�������p�������������������룡\n");
		goto P;
	}
Q:printf("������q=");
	scanf("%d", &q);
	getchar();
	if (checknumber(q)) {
		printf("�������q�������������������룡\n");
		goto Q;
	}
E:printf("������e=");
	scanf("%d", &e);
	getchar();
	if (checknumbers(e, p, q)) {
		printf("�������e��n���ǻ��ʵģ����������룡\n");
		goto E;
	}
	jiami(plaintext,e,p,q);
	return 0;
}