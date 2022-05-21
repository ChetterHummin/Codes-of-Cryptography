#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<math.h>
#include <ctype.h>
#include<stdlib.h>

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

//#define PP(x) (x << 24) | ((x << 8) & 0xff0000) | ((x >> 8) & 0xff00) | (x >> 24)
#define F(x,y,z)  (((x)&(y))|((~x)&(z)))
#define G(x,y,z)  (((x)&(z))|((y)&(~z)))
#define H(x,y,z)  ((x)^(y)^(z))
#define I(x,y,z)  ((y)^((x)|(~z)))
//#define RL(x,y)   (((x)<<(y))|((x)>>(32-(y))))//x向左循环移y位
//#define PP(x) (x << 24) | ((x << 8) & 0xff0000) | ((x >> 8) & 0xff00) | (x >> 24)
#define FF(a,b,c,d,x,s,ac) a=b+(RL((a+F(b,c,d)+x+ac),s))
#define GG(a,b,c,d,x,s,ac) a=b+(RL((a+G(b,c,d)+x+ac),s))
#define HH(a,b,c,d,x,s,ac) a=b+(RL((a+H(b,c,d)+x+ac),s))
#define II(a,b,c,d,x,s,ac) a=b+(RL((a+I(b,c,d)+x+ac),s))
const unsigned int S[64] = {
		7,12,17,22,7,12,17,22,
		7,12,17,22,7,12,17,22,
		5,9,14,20,5,9,14,20,
		5,9,14,20,5,9,14,20,
		4,11,16,23,4,11,16,23,
		4,11,16,23,4,11,16,23,
		6,10,15,21,6,10,15,21,
		6,10,15,21,6,10,15,21
};
int T[64] = {
		0xD76AA478,0xE8C7B756,0x242070DB,0xC1BDCEEE,0xF57C0FAF,0x4787C62A,0xA8304613,0xFD469501,
		0x698098D8,0x8B44F7AF,0xFFFF5BB1,0x895CD7BE,0x6B901122,0xFD987193,0xA679438E,0x49B40821,
		0xF61E2562,0xC040B340,0x265E5A51,0xE9B6C7AA,0xD62F105D,0x02441453,0xD8A1E681,0xE7D3FBC8,
		0x21E1CDE6,0xC33707D6,0xF4D50D87,0x455A14ED,0xA9E3E905,0xFCEFA3F8,0x676F02D9,0x8D2A4C8A,
		0xFFFA3942,0x8771F681,0x6D9D6122,0xFDE5380C,0xA4BEEA44,0x4BDECFA9,0xF6BB4B60,0xBEBFBC70,
		0x289B7EC6,0xEAA127FA,0xD4EF3085,0x04881D05,0xD9D4D039,0xE6DB99E5,0x1FA27CF8,0xC4AC5665,
		0xF4292244,0x432AFF97,0xAB9423A7,0xFC93A039,0x655B59C3,0x8F0CCC92,0xFFEFF47D,0x85845DD1,
		0x6FA87E4F,0xFE2CE6E0,0xA3014314,0x4E0811A1,0xF7537E82,0xBD3AF235,0x2AD7D2BB,0xEB86D391
};
void menu() {
	printf("*************************************\n");
	printf("*************1、HMAC-MD5**************\n");
	printf("*************2、HMAC-SHA1*************\n");
	printf("*************0、退出******************\n");
	printf("*************************************\n");
}
unsigned char* SHA1(unsigned char plaintext[], int length) {

	unsigned char* MD5 = (unsigned char*)malloc(sizeof(unsigned char) * 20);
	
	unsigned int A, B, C, D, E, a, b, c, d, e, w[80];
	A = H[0]; B = H[1]; C = H[2]; D = H[3]; E = H[4];
	//a = A; b = B; c = C; d = D; e = E;
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
			+ plaintext[i * 4 + 3]; //printf("%X ",Temp[i]);
	}
	for (int t = 0; t < (length / 64); t++) {
		a = A; b = B; c = C; d = D; e = E;
		for (int j = 0; j < 16; j++) {
			w[j] = Temp[j + 16 * t];
		}
		for (int j = 16; j < 80; j++) {
			temp = RL((w[j - 3] ^ w[j - 8] ^ w[j - 14] ^ w[j - 16]), 1);
			w[j] = temp;

		}
		for (int i = 0; i <= 19; i++) {
			//printf("第%d步的参数；a=%08X  w[%d]=%08X\n", i + 1, a, i, w[i]);
			//printf("%08X  %08X  %08X %08X  %08X\n", RL(a, 5), ft1(b, c, d), e, w[i], K[0]);
			temp = RL(a, 5) + ft1(b, c, d) + e + w[i] + K[0];
			e = d; d = c; c = RL(b, 30); b = a; a = temp;
		}
		for (int i = 20; i <= 39; i++) {
			//printf("第%d步的参数；a=%08X  w[%d]=%08X\n", i + 1, a, i, w[i]);
			temp = RL(a, 5) + ft2(b, c, d) + e + w[i] + K[1];
			e = d; d = c; c = RL(b, 30); b = a; a = temp;
		}
		for (int i = 40; i <= 59; i++) {
			//printf("第%d步的参数；a=%08X  w[%d]=%08X\n", i + 1, a, i, w[i]);
			temp = RL(a, 5) + ft3(b, c, d) + e + w[i] + K[2];
			e = d; d = c; c = RL(b, 30); b = a; a = temp;
		}
		for (int i = 60; i <= 79; i++) {
			//printf("第%d步的参数；a=%08X  w[%d]=%08X\n", i + 1, a, i, w[i]);
			temp = RL(a, 5) + ft4(b, c, d) + e + w[i] + K[3];
			e = d; d = c; c = RL(b, 30); b = a; a = temp;
		}
		A += a; B += b; C += c; D += d; E += e;
		//printf("SHA-1 :%x %x %x %x %x\n", A, B, C, D, E);
	}
	//printf("SHA-1 Code:%x %x %x %x %x\n", A, B, C, D, E);

	MD5[0] = A / (256 * 256 * 256);
	A -= MD5[0] * 256 * 256 * 256;
	MD5[1] = (A) / (256 * 256);
	A -= MD5[1] * 256 * 256;
	MD5[2] = (A) / 256;
	A -= MD5[2] * 256;
	MD5[3] = (A);

	MD5[4] = B / (256 * 256 * 256);
	B -= MD5[4] * 256 * 256 * 256;
	MD5[5] = (B) / (256 * 256);
	B -= MD5[5] * 256 * 256;
	MD5[6] = (B) / 256;
	B -= MD5[6] * 256;
	MD5[7] = (B);

	MD5[8] = C / (256 * 256 * 256);
	C -= MD5[8] * 256 * 256 * 256;
	MD5[9] = (C) / (256 * 256);
	C -= MD5[9] * 256 * 256;
	MD5[10] = (C) / 256;
	C -= MD5[10] * 256;
	MD5[11] = (C);

	MD5[12] = D / (256 * 256 * 256);
	D -= MD5[12] * 256 * 256 * 256;
	MD5[13] = (D) / (256 * 256);
	D -= MD5[13] * 256 * 256;
	MD5[14] = (D) / 256;
	D -= MD5[14] * 256;
	MD5[15] = (D);
	
	MD5[16] = E / (256 * 256 * 256);
	E -= MD5[16] * 256 * 256 * 256;
	MD5[17] = (E) / (256 * 256);
	E -= MD5[17] * 256 * 256;
	MD5[18] = (E) / 256;
	E -= MD5[18] * 256;
	MD5[19] = (E);
	
	return MD5;
	
}
unsigned char* filling_sha1(unsigned char plaintext_0[]) {
	
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
			Temp += temp[i % 4] * ((int)pow(256, (3 - i % 4)));
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
	for (int i = 0, j = 0; i < length; i++) {
		plaintext[i] = plaintext_0[i];
	}
	
	int Length = length * 8;
	//PP(Length); printf("%d",Length);
	char a[40] = "0123456789ABCDEF";//用一个数组存储十六进制数
	char b[100];//储存输入的十进制数对应的十六进制数
	int n;
	unsigned c[2];
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


	for (int i = 1, j = 0, t = 0; i < cnt + 1; i++) {
		if ((b[i] >= 48) && (b[i] <= 57)) {
			c[j] = b[i] - 48; //printf("[- %X]",c[j]);
			j++;
		}
		else {
			c[j] = b[i] - 55; //printf("[ +%X]", c[j]);
			j++;
		}
		if ((j == 2) || (i == cnt)) {
			if (j == 2) {
				plaintext[length_end - 1 - t] = c[0] + c[1] * 16; //printf(" -%X", plaintext[length_end - 1 - 4 - t]);
				t++;
				j = 0;
			}
			else {
				plaintext[length_end - 1 - t] = c[0]; //printf(" +%X", plaintext[length_end - 1 - 4 - t]);
			}
		}
	}
	
	
	return SHA1(plaintext, length_end);
}
unsigned char* sha1(unsigned char plaintext[]) {
	
	return filling_sha1(plaintext);
}
unsigned char* haish_md(unsigned char plaintext[], int length) {
	//printf("\n=============\n");
	unsigned char* MD5 = (unsigned char*)malloc(sizeof(unsigned char) * 16);

	unsigned int A, B, C, D, a, b, c, d, temp, x[16];//len文件长，
	unsigned long long MD5_Code;
	A = 0x67452301;
	B = 0xefcdab89;
	C = 0x98badcfe;
	D = 0x10325476;
	a = A; b = B; c = C; d = D;
	int end[4];
	unsigned int* Temp = (unsigned int)malloc(sizeof(unsigned int) * (length / 4));
	//unsigned int T = (int)(abs(sin(0)) * 2 ^ 32);
	memset(Temp, 0, sizeof(unsigned int) * (length / 4));
	for (int i = 0; i < (length / 4); i++) {
		Temp[i] = plaintext[i * 4] * 256 * 256 * 256
			+ plaintext[i * 4 + 1] * 256 * 256
			+ plaintext[i * 4 + 2] * 0x100
			+ plaintext[i * 4 + 3];
	}
	for (int i = 0; i < (length / 4) - 2; i++) {
		Temp[i] = PP(Temp[i]);
	}
	//printf("初始的a=%x, b=%x, c=%x, d=%x\n", a, b, c, d);
	for (int i = 0; i < (length / 64); i++) {
		a = A; b = B; c = C; d = D;
		//printf("[%d]\n",i);


		//printf("初始的a=%x, b=%x, c=%x, d=%x\n", a, b, c, d);
		// printf("a,b,c,d分别加到A,B,C,D上得到A=%x， B=%x, C=%x, D=%x\n", A, B, C, D);
		
		for (int j = 0; j < 16; j++) {
			x[j] = Temp[j + 16 * i]; 
		}
		/*for (int i = 0; i < 16; i++) {              //输出512比特（64字节）划分为16组，每组4字节的结果（即X数组）
			printf("第%d组的值为%08x\n", i + 1, x[i]);

		}*/
		for (int j = 0; j < 16; j++) {             //FF

			FF(a, b, c, d, x[j], S[j], T[j]);
			temp = d; d = c; c = b; b = a; a = temp;
		}//printf("第一轮16步结束后的a=%x, b=%x, c=%x, d=%x\n", a, b, c, d);
		for (int j = 0; j < 16; j++) {             //GG

			GG(a, b, c, d, x[(1 + 5 * j) % 16], S[j + 16], T[j + 16]);
			temp = d; d = c; c = b; b = a; a = temp;
		}//printf("第二轮16步结束后的a=%x, b=%x, c=%x, d=%x\n", a, b, c, d);
		for (int j = 0; j < 16; j++) {             //HH

			HH(a, b, c, d, x[(5 + 3 * j) % 16], S[j + 32], T[j + 32]);
			temp = d; d = c; c = b; b = a; a = temp;
		}//printf("第三轮16步结束后的a=%x, b=%x, c=%x, d=%x\n", a, b, c, d);
		for (int j = 0; j < 16; j++) {             //II

			II(a, b, c, d, x[(7 * j) % 16], S[j + 48], T[j + 48]);
			temp = d; d = c; c = b; b = a; a = temp;
		}//printf("第四轮16步结束后的a=%x, b=%x, c=%x, d=%x\n", a, b, c, d);
		A += a;
		B += b;
		C += c;
		D += d;
		//printf("a,b,c,d分别加到A,B,C,D上得到A=%x， B=%x, C=%x, D=%x\n", A, B, C, D);
	}
	MD5[3] = A / (256 * 256 * 256);
	A -= MD5[3] * 256 * 256 * 256;
	MD5[2] = (A) / (256 * 256);
	A -= MD5[2] * 256 * 256;
	MD5[1] = (A) / 256;
	A -= MD5[1] * 256;
	MD5[0] = (A);

	MD5[7] = B / (256 * 256 * 256);
	B -= MD5[7] * 256 * 256 * 256;
	MD5[6] = (B) / (256 * 256);
	B -= MD5[6] * 256 * 256;
	MD5[5] = (B) / 256;
	B -= MD5[5] * 256;
	MD5[4] = (B);

	MD5[11] = C / (256 * 256 * 256);
	C -= MD5[11] * 256 * 256 * 256;
	MD5[10] = (C) / (256 * 256);
	C -= MD5[10] * 256 * 256;
	MD5[9] = (C) / 256;
	C -= MD5[9] * 256;
	MD5[8] = (C);

	MD5[15] = D / (256 * 256 * 256);
	D -= MD5[15] * 256 * 256 * 256;
	MD5[14] = (D) / (256 * 256);
	D -= MD5[14] * 256 * 256;
	MD5[13] = (D) / 256;
	D -= MD5[13] * 256;
	MD5[12] = (D);
	
	return MD5;
}
unsigned char* filling_md(char plaintext_0[]) {
	unsigned char* MD;
	unsigned char* MD5 = (unsigned char*)malloc(sizeof(unsigned char) * 16);

	int length = strlen(plaintext_0);
	int temp[8] = { 0 };
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
		
	}
	int Length = length * 8; 
	char a[40] = "0123456789ABCDEF";//用一个数组存储十六进制数
	char b[100];//储存输入的十进制数对应的十六进制数
	unsigned char c[2];
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
	//for (int i = cnt; i > 0; i--)/*上面cnt从1开始所以i>0，不用输出b[0]。逆序输出*/
		//printf("%c", b[i]);
	for (int i = 1, j = 0, t = 0; i < cnt + 1; i++) {
		if ((b[i] >= 48) && (b[i] <= 57)) {
			c[j] = b[i] - 48; 
			j++;
		}
		else {
			c[j] = b[i] - 55; 
			j++;
		}
		if ((j == 2) || (i == cnt)) {
			if (j == 2) {
				plaintext[length_end - 1 - 4 - t] = c[0] + c[1] * 16; 
				t++;
				j = 0;
			}
			else {
				plaintext[length_end - 1 - 4 - t] = c[0]; 
			}
		}
	}
	
	
	
	return haish_md(plaintext,length_end);
}
unsigned char* md(char plaintext[]) {
	
	return filling_md(plaintext);
	
}

void hmac_md5(char plaintext_0[], char KEY_0[]) {
	unsigned char* MD5;
	char KEY[200];
	int KEY_1[200];
	unsigned char Opad[200];
	char Ipad[200];
	if (strlen(KEY_0) > 64) {
		MD5 = md(KEY_0);
		
		for (int i = 0; i < 16; i++) {
			KEY_1[i] = (MD5[i]+256)%256;
			
		}free(MD5);
		for (int i = 0; i < 16; i++) {
			KEY[i] = KEY_1[i];
		}
		for (int i = 0; i < 16; i++) {
			printf("  %X", KEY_1[i]);
		}
		for (int i = 16; i < 64; i++) {
			KEY[i] = 0x00;
		}
	}
	else {
		for (int i = 0; i < strlen(KEY_0); i++) {
			KEY[i] = KEY_0[i];
		}
		for (int i = strlen(KEY_0); i < 64; i++) {
			KEY[i] = 0X00;
		}
	}
	
	for (int i = 0; i < 64; i++) {
		Ipad[i] =0x36  ^ KEY[i];
	}
	for (int i = 0; i < 64; i++) {
		Opad[i] = 0x5c ^ KEY[i];
	}
	for (int i = 64; i < 64 + strlen(plaintext_0); i++) {
		Ipad[i] = plaintext_0[i-64];
	}Ipad[64 + strlen(plaintext_0)] = '\0';
	
	MD5 = md(Ipad);//,64+strlen(plaintext_0));
	for (int i = 0; i < 16; i++) {
		KEY_1[i] = (MD5[i] + 256) % 256;

	}//free(MD5);
	
	for (int i = 64; i < 64 + 16; i++) {
		Opad[i] = KEY_1[i - 64];
	}Opad[64 + 16] = '\0'; //free(MD5);
	
	MD5 = md(Opad);//, 64 + strlen(plaintext_0));
	for (int i = 0; i < 16; i++) {
		KEY_1[i] = (MD5[i] + 256) % 256;

	}free(MD5);
	printf("\nHMACMD5结果是：");
	for (int i = 0; i < 16; i++) {
		printf("%x",KEY_1[i]);
	}printf("\n");
}
void hmac_sha1(char plaintext_0[], char KEY_0[]) {
	unsigned char* MD5;
	char KEY[200];
	int KEY_1[200];
	unsigned char Opad[300];
	unsigned char Ipad[300];
	if (strlen(KEY_0) > 64) {
		MD5 = sha1(KEY_0);

		for (int i = 0; i < 20; i++) {
			KEY_1[i] = (MD5[i] + 256) % 256;

		}free(MD5);
		for (int i = 0; i < 20; i++) {
			KEY[i] = KEY_1[i];
		}
		for (int i = 20; i < 64; i++) {
			KEY[i] = 0x00;
		}
	}
	else {
		for (int i = 0; i < strlen(KEY_0); i++) {
			KEY[i] = KEY_0[i];
		}
		for (int i = strlen(KEY_0); i < 64; i++) {
			KEY[i] = 0X00;
		}
	}
	
	for (int i = 0; i < 64; i++) {
		Ipad[i] = 0x36 ^ KEY[i];
	}
	for (int i = 0; i < 64; i++) {
		Opad[i] = 0x5c ^ KEY[i];
	}
	for (int i = 64; i < 64 + strlen(plaintext_0); i++) {
		Ipad[i] = plaintext_0[i - 64];
	}Ipad[64 + strlen(plaintext_0)] = '\0';
	
	MD5 = sha1(Ipad);//,64+strlen(plaintext_0));
	
	for (int i = 0; i < 20; i++) {
		KEY_1[i] = ((MD5[i]) + 256) % 256;

	}//free(MD5);
	for (int i = 64; i < 64 + 20; i++) {
		Opad[i] = KEY_1[i - 64];
	}Opad[64 + 20] = '\0'; //free(MD5);
	MD5 = sha1(Opad);//, 64 + strlen(plaintext_0));
	for (int i = 0; i < 20; i++) {
		KEY_1[i] = (MD5[i] + 256) % 256;

	}free(MD5);
	printf("\nHMACSHA1结果是：");
	for (int i = 0; i < 20; i++) {
		printf("%x", KEY_1[i]);
	}printf("\n");
}
int main() {

	int index = 1;
	char* Plaintext;
	char ciphetextPath[30];
	char KEY[80];
	char plaintext_0[80];
	while (1) {
		menu();
		printf("请选择：");
		scanf("%d", &index);
		getchar();

		memset(plaintext_0, 0, sizeof(char) * 80);
		printf("请输入明文\n");
		scanf("%[^\n]s", plaintext_0);
		getchar();
		memset(KEY, 0, sizeof(char) * 80);
		printf("请输入KEY\n");
		scanf("%[^\n]s", KEY);
		getchar();
		switch (index) {
		case 1:
			hmac_md5(plaintext_0,KEY);
			break;
		case 2:
			hmac_sha1(plaintext_0,KEY);
			break;
		case 0:
			exit(0);
		default:
			break;
		}
	}
}