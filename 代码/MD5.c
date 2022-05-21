#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>

#define PP(x) (x << 24) | ((x << 8) & 0xff0000) | ((x >> 8) & 0xff00) | (x >> 24)
#define F(x,y,z)  (((x)&(y))|((~x)&(z)))
#define G(x,y,z)  (((x)&(z))|((y)&(~z)))
#define H(x,y,z)  ((x)^(y)^(z))
#define I(x,y,z)  ((y)^((x)|(~z)))
#define RL(x,y)   (((x)<<(y))|((x)>>(32-(y))))//x向左循环移y位
//#define PP(x) (x << 24) | ((x << 8) & 0xff0000) | ((x >> 8) & 0xff00) | (x >> 24)
#define FF(a,b,c,d,x,s,ac) a=b+(RL((a+F(b,c,d)+x+ac),s))
#define GG(a,b,c,d,x,s,ac) a=b+(RL((a+G(b,c,d)+x+ac),s))
#define HH(a,b,c,d,x,s,ac) a=b+(RL((a+H(b,c,d)+x+ac),s))
#define II(a,b,c,d,x,s,ac) a=b+(RL((a+I(b,c,d)+x+ac),s))

//#include"MD_5.h"
//#define

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
void menu(){
	printf("\n***************MD5实验内容*****************\n");
	printf("============================================\n");
	printf("================1、键盘输入==================\n");
	printf("================2、文件输入==================\n");
	printf("================0、退出程序==================\n");
	printf("============================================\n");
}
void haish_md(unsigned char plaintext[], int length) {

	unsigned int A, B, C, D, a, b, c, d, temp, x[16];//len文件长，
	unsigned long long MD5_Code;
	A = 0x67452301;
	B = 0xefcdab89;
	C = 0x98badcfe;
	D = 0x10325476;
	a = A; b = B; c = C; d = D;
	unsigned int* Temp = (unsigned int)malloc(sizeof(unsigned int) * (length / 4));
	//unsigned int T = (int)(abs(sin(0)) * 2 ^ 32);
	memset(Temp, 0, sizeof(unsigned int) * (length / 4));
	for (int i = 0; i < (length / 4); i ++) {
		Temp[i] = plaintext[i*4] * 256 * 256 * 256
			+ plaintext[i*4 + 1] * 256 * 256
			+ plaintext[i*4 + 2] * 0x100
			+ plaintext[i * 4 + 3]; 
	}
	printf("初始的a=%x, b=%x, c=%x, d=%x\n", a, b, c, d);
	for (int i = 0; i < (length / 64); i++) {
		for (int j = 0; j < 16; j++) {
			x[j] = Temp[j + 16 * i];
		}
		for (int i = 0; i <16; i++) {              //输出512比特（64字节）划分为16组，每组4字节的结果（即X数组）
			printf("第%d组的值为%08x\n", i + 1, x[i]);
			
		}
		for (int j = 0; j < 16; j++) {             //FF
		
			FF(a, b, c, d, x[j], S[j], T[j]);
			temp = d; d = c; c = b; b = a; a = temp;
		}printf("第一轮16步结束后的a=%x, b=%x, c=%x, d=%x\n", a, b, c, d);
		for (int j = 0; j < 16; j++) {             //GG
			
			GG(a,b,c,d,x[(1+5*j)%16],S[j+16],T[j+16]);
			temp = d; d = c; c = b; b = a; a = temp;
		}printf("第二轮16步结束后的a=%x, b=%x, c=%x, d=%x\n", a, b, c, d);
		for (int j = 0; j < 16; j++) {             //HH
		
			HH(a, b, c, d, x[(5 + 3 * j) % 16], S[j+32], T[j+32]);
			temp = d; d = c; c = b; b = a; a = temp;
		}printf("第三轮16步结束后的a=%x, b=%x, c=%x, d=%x\n", a, b, c, d);
		for (int j = 0; j < 16; j++) {             //II
			
			II(a, b, c, d, x[(7 * j) % 16], S[j+48], T[j+48]);
			temp = d; d = c; c = b; b = a; a = temp;
		}printf("第四轮16步结束后的a=%x, b=%x, c=%x, d=%x\n", a, b, c, d);
		A += a;
		B += b;
		C += c;
		D += d;
		printf("a,b,c,d分别加到A,B,C,D上得到A=%x， B=%x, C=%x, D=%x\n", A, B, C, D);
	}
	
	//MD5_Code=
}
unsigned char filling(char plaintext_0[]) {
	int length = strlen(plaintext_0);
	int temp[8] = { 0 };
	long int Temp=0;
	int length_temp, length_end=80;
	if ((length * 8) % 512 != 448) {
		length_end = length-(length % 64)+64;
	}
	else {
		length_end = length + 8;
	}//printf("%d",length_end);
	unsigned char* plaintext = (unsigned char*)malloc(sizeof(unsigned char*) * length_end);
	memset(plaintext,0,sizeof(unsigned char)*length_end);
	if ((length*8)%512!=448) {
		for (int i = 0,j=0; i < length; i++) {
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
		for (int i = 0; i < (length_temp);i++) {
			temp[i % 4] = plaintext[i];
			Temp += temp[i%4] * ((int)pow(256, (i%4))); 
			if (i % 4 == 3) {
				PP(Temp);
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
	for (int i = cnt,j=length_end-8,t=0; i > 0; i-=2,j++) {
		if ((b[i] >= 48) || (b[i] <= 57)) {
			t += (b[i]-48)*16;
		}
		else {
			t += (b[i] - 55) * 16;
		}//printf("(%d)", t);
		if ((b[i-1] >= 48) || (b[i-1] <= 57)) {
			t += (b[i-1] - 48);
		}
		else {
			t += (b[i-1] - 55);
		}//printf("(%d)",t);
		plaintext[j] = t;
		t = 0;
	}
	int x = plaintext[length_end-5];
	plaintext[length_end - 5] = plaintext[length_end - 8];
	plaintext[length_end - 8] = x;
	x = plaintext[length_end-6];
	plaintext[length_end - 6] = plaintext[length_end-7];
	plaintext[length_end-7] = x;

	
	
	haish_md(plaintext,length_end);
	return plaintext;
}
void md(char plaintext[]) {
	filling(plaintext);
}
unsigned char readfile() {

}
int main() {
	FILE* fp;
	int index = 1;
	char* Plaintext;
	char ciphetextPath[30];
	char plaintext_0[80];
	//memset(plaintext_0, 0, sizeof(char) * 80); 
	//printf("请输入需要的Hash的字符串\n");
	//scanf("%[^\n]s", plaintext_0);             //scanf("%s", plaintext_0); 
	
	//getchar();
	//md(plaintext_0);
	while (1) {
		menu();
		printf("请选择：");
		scanf("%d", &index);
		getchar();
		switch (index) {
		case 1:
			memset(plaintext_0, 0, sizeof(char) * 80);
			printf("请输入需要的Hash的字符串\n");
			scanf("%[^\n]s", plaintext_0);
			getchar();
			md(plaintext_0);
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
			md(plaintext_0);
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
}