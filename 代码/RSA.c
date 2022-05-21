#define _CRT_SECURE_NO_WARNINGS
/**@created dy Chetter Hummin 20220511
*/
#include<stdio.h>
#include<string.h>
#include<math.h>
int checknumber(int temp) {  //判断是否为素数，如果是返回0，相反返回1
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
int checknumbers(int e, int p, int q) {  //判断两者是否互质，（辗转相除法），如果是返回0，相反返回1
	int n = p * q;
	int φ_n = (p-1) * (q-1);
	int temp;
	if (e > φ_n) {
		return 1;
	}
	if (e < φ_n) {
		temp = e;
		e = φ_n;
		φ_n = temp;
	}temp = 1;
	while (temp != 0) {
		temp = e % φ_n;
		e = φ_n;
		φ_n = temp;
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
	int temp=0;//临时变量
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
	printf("加密结果是：(最后的非偶数位默认填0)\n");
	for (int i = 0; i < length;i++) {
		printf("  %04d",plaintext[i]);
	}

}
int main() {
	char plaintext[80];
	int p, q, e;
	printf("请输入需要加密的字符串：");
	scanf("%[^\n]s", plaintext);
	getchar();
P:printf("请输入p=");
	scanf("%d", &p);
	getchar();
	if (checknumber(p)) {
		printf("您输入的p不是素数，请重新输入！\n");
		goto P;
	}
Q:printf("请输入q=");
	scanf("%d", &q);
	getchar();
	if (checknumber(q)) {
		printf("您输入的q不是素数，请重新输入！\n");
		goto Q;
	}
E:printf("请输入e=");
	scanf("%d", &e);
	getchar();
	if (checknumbers(e, p, q)) {
		printf("您输入的e与n不是互质的，请重新输入！\n");
		goto E;
	}
	jiami(plaintext,e,p,q);
	return 0;
}