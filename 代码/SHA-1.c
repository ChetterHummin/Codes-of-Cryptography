#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<math.h>
const unsigned int H[5] = {
	0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0
};
const unsigned int K[4] = {
	0X5A827999, 0X6ED9EBA1, 0X8F1BBCDC, 0XCA62C1D6
};
#define PP(x) (x << 24) | ((x << 8) & 0xff0000) | ((x >> 8) & 0xff00) | (x >> 24)//将x高低位互换，
#define RL(x,y) (((x)<<(y))|((x)>>(32-(y))))  //x向左循环移y位
#define ft1(b, c, d) ((b&c) | ((~b)&d)) //(0≤t≤19)
#define ft2(b,c,d) (b^c^d) //(20≤t≤39)
#define ft3(b, c, d) ((b&c) | (b&d) | (c&d)) //(40≤t≤59)
#define ft4(b,c,d) (b^c^d)//(60≤t≤79)
void SHA1(unsigned char plaintext[], int length) {
	unsigned int A, B, C, D, E, a, b, c, d, e,w[80];
	A = H[0]; B = H[1]; C = H[2]; D = H[3]; E = H[4];
	a = A; b = B; c = C; d = D; e = E;
	//printf("\n[%x  %x  %x %x  %x ]\n",a,b,c,d,e);
	unsigned int W[512];
	unsigned int temp;
	unsigned int* Temp = (unsigned int)malloc(sizeof(unsigned int) * (length / 4));
	//unsigned int T = (int)(abs(sin(0)) * 2 ^ 32);
	memset(Temp, 0, sizeof(unsigned int) * (length / 4));
	for (int i = 0; i < (length / 4); i++) {
		Temp[i] = plaintext[i * 4] * 256 * 256 * 256
			+ plaintext[i * 4 + 1] * 256 * 256
			+ plaintext[i * 4 + 2] * 0x100
			+ plaintext[i * 4 + 3];
	}
	for (int t = 0; t < (length / 64); t++) {
		for (int j = 0; j < 16; j++) {
			w[j] = Temp[j + 16 * t];
		}
		for (int j = 16; j < 80; j++) {
			temp = RL((w[j-3] ^ w[j-8] ^ w[j-14] ^ w[j-16]),1);
			w[j] = temp;
			
		}
		for (int i = 0; i <= 19; i++) {
			printf("第%d步的参数；a=%08X  w[%d]=%08X\n",i+1, a, i,w[i]);
			//printf("%08X  %08X  %08X %08X  %08X\n", RL(a, 5), ft1(b, c, d), e, w[i], K[0]);
			temp = RL(a, 5) + ft1(b, c, d) +e + w[i] + K[0];
			e = d; d = c; c = RL(b, 30); b = a; a = temp; 
		}
		for (int i = 20; i <= 39; i++) {
			printf("第%d步的参数；a=%08X  w[%d]=%08X\n", i + 1, a, i, w[i]);
			temp = RL(a, 5) + ft2(b, c, d) + e + w[i] + K[1];
			e = d; d = c; c = RL(b, 30); b = a; a = temp; 
		}
		for (int i = 40; i <= 59; i++) {
			printf("第%d步的参数；a=%08X  w[%d]=%08X\n", i + 1, a, i, w[i]);
			temp = RL(a, 5) + ft3(b, c, d) + e + w[i] + K[2];
			e = d; d = c; c = RL(b, 30); b = a; a = temp; 
		}
		for (int i = 60; i <= 79; i++) {
			printf("第%d步的参数；a=%08X  w[%d]=%08X\n", i + 1, a, i, w[i]);
			temp = RL(a, 5) + ft4(b, c, d) + e + w[i] + K[3];
			e = d; d = c; c = RL(b, 30); b = a; a = temp; 
		}
		A += a; B += b; C += c; D += d; E += e;
		
	}
	printf("SHA-1 Code:%x%x%x%x%x\n", A, B, C, D, E);
	/*for (int i = 0; i < 80; i++) {
		printf("%08x\n",w[i]);
	}*/
	
}
void menu() {
	printf("===============SHA-1实验内容=================\n");
	printf("============================================\n");
	printf("================1、键盘输入==================\n");
	printf("================2、文件输入==================\n");
	printf("================0、退出程序==================\n");
	printf("============================================\n");
	
}
unsigned char filling(char plaintext_0[]) {
	int length = strlen(plaintext_0);
	unsigned int temp[8] = { 0 };
	long int Temp = 0;
	int length_temp, length_end = 80;
	if ((length * 8) % 512 != 448) {
		length_end = length - (length % 64) + 64;
	}
	else {
		length_end = length + 8;
	}//printf("%d",length_end);
	
	unsigned char* plaintext = (unsigned char*)malloc(sizeof(unsigned char*) * length_end);
	memset(plaintext, 0, sizeof(unsigned char) * length_end);
	if ((length * 8) % 512 != 448) {
		for (int i = 0, j = 0; i < length; i++) {
			plaintext[i] = plaintext_0[i];
		}
		plaintext[length] = 0x80;
		if (length % 4 == 0) {
			length_temp = length;
		}
		else {
			length_temp = (length / 4) + 1;
			length_temp *= 4;
		}
		for (int i = 0; i < (length_temp); i++) {
			temp[i % 4] = plaintext[i];
			Temp += temp[i % 4] * ((int)pow(256, (3-i % 4)));
			if (i % 4 == 3) {
				//PP(Temp);
				temp[i % 4 - 3] = Temp / (256 * 256 * 256);
				Temp -= temp[i % 4 - 3] * 256 * 256 * 256;
				temp[i % 4 - 2] = (Temp) / (256 * 256);
				Temp -= temp[i % 4 - 2] * 256 * 256;
				temp[i % 4 - 1] = (Temp) / 256;
				Temp -= temp[i % 4 - 1] * 256;
				temp[i % 4] = (Temp);
				for (int j = 0; j < 4; j++) {
					plaintext[i - j] = temp[i % 4 - j];
				}//printf("    %x %x %x %x\n", temp[i%4-3], temp[i % 4 - 2], temp[i % 4 - 1], temp[i % 4]);
				Temp = 0;
			}

		}
	}
	int Length = length * 8;
	//PP(Length); printf("%d",Length);
	char a[40] = "0123456789ABCDEF";//用一个数组存储十六进制数
	char b[100];//储存输入的十进制数对应的十六进制数
	int n;
	int cnt = 0;//计数
	n = Length;
	//scanf("%d", &n);//输入要转换的十进制数

	if (n == 0)
		printf("0");
	while (n != 0)
	{
		b[++cnt] = a[n % 16];//这里cnt从1开始
		n = n / 16;
	}

	if (cnt % 2 != 0) {
		b[cnt++] = '0';
	}
	for (int i = 1, j = length_end-1, t = 0; i <= cnt; i += 2, j--) {
		if ((b[i] >= 48) || (b[i] <= 57)) {
			t += (b[i] - 48) * 16;
		}
		else {
			t += (b[i] - 55) * 16;
		}//printf("(%d)", t);
		if ((b[i + 1] >= 48) || (b[i + 1] <= 57)) {
			t += (b[i + 1] - 48);
		}
		else {
			t += (b[i + 1] - 55);
		}//printf("(%d)",t);
		plaintext[j] = t;
		t = 0;
	}
	/*int x = plaintext[length_end - 5];
	plaintext[length_end - 5] = plaintext[length_end - 8];
	plaintext[length_end - 8] = x;
	x = plaintext[length_end - 6];
	plaintext[length_end - 6] = plaintext[length_end - 7];
	plaintext[length_end - 7] = x;
	//printf("[%c]", b[0]);*/
	/*for (int i = 0; i < 64; i++) {
		printf("%02X", plaintext[i]);
		if (i % 4 == 3) {
			printf("\n");
		}
	}*/


	SHA1(plaintext, length_end);
	return plaintext;
}
int main() {
	FILE* fp;
	int index = 1;
	char* Plaintext;
	char ciphetextPath[30];
	char plaintext_0[80];

	while (1) {
		menu();
		printf("请选择：");
		scanf("%d", &index);
		getchar();
		switch (index) {
		case 1:
			memset(plaintext_0, 0, sizeof(char) * 80);
			printf("请输入需要计算SHA-1的字符串\n");
			scanf("%[^\n]s", plaintext_0);
			getchar();
			filling(plaintext_0);
			break;
		case 2:
			memset(ciphetextPath, 0, sizeof(char) * 30);
			printf("请输入需要的文件路径：");
			gets(ciphetextPath);
			if ((fp = fopen(ciphetextPath, "r")) == NULL) {
				printf("Can't open this file[%s].\n", ciphetextPath);
				exit(0);
			}
			fgets(plaintext_0, 80, fp);
			filling(plaintext_0);
			if (fclose(fp)) {
				printf("Can't close the file![%s].\n", ciphetextPath);
				exit(0);
			}
			break;
		case 0:
			exit(0);
		default:
			break;
		}
	}
	return 0;
}