#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>  
#include<string.h>
#include<math.h>
#include<time.h>
#include<malloc.h>
/*
* 扩展 SM4 S盒
/* Sbox table: 8bit输入转化成8bit输出*/
static const unsigned char SboxTable[16][16] =
{
	{ 0xd6, 0x90, 0xe9, 0xfe, 0xcc, 0xe1, 0x3d, 0xb7, 0x16, 0xb6, 0x14, 0xc2, 0x28, 0xfb, 0x2c, 0x05 },
	{ 0x2b, 0x67, 0x9a, 0x76, 0x2a, 0xbe, 0x04, 0xc3, 0xaa, 0x44, 0x13, 0x26, 0x49, 0x86, 0x06, 0x99 },
	{ 0x9c, 0x42, 0x50, 0xf4, 0x91, 0xef, 0x98, 0x7a, 0x33, 0x54, 0x0b, 0x43, 0xed, 0xcf, 0xac, 0x62 },
	{ 0xe4, 0xb3, 0x1c, 0xa9, 0xc9, 0x08, 0xe8, 0x95, 0x80, 0xdf, 0x94, 0xfa, 0x75, 0x8f, 0x3f, 0xa6 },
	{ 0x47, 0x07, 0xa7, 0xfc, 0xf3, 0x73, 0x17, 0xba, 0x83, 0x59, 0x3c, 0x19, 0xe6, 0x85, 0x4f, 0xa8 },
	{ 0x68, 0x6b, 0x81, 0xb2, 0x71, 0x64, 0xda, 0x8b, 0xf8, 0xeb, 0x0f, 0x4b, 0x70, 0x56, 0x9d, 0x35 },
	{ 0x1e, 0x24, 0x0e, 0x5e, 0x63, 0x58, 0xd1, 0xa2, 0x25, 0x22, 0x7c, 0x3b, 0x01, 0x21, 0x78, 0x87 },
	{ 0xd4, 0x00, 0x46, 0x57, 0x9f, 0xd3, 0x27, 0x52, 0x4c, 0x36, 0x02, 0xe7, 0xa0, 0xc4, 0xc8, 0x9e },
	{ 0xea, 0xbf, 0x8a, 0xd2, 0x40, 0xc7, 0x38, 0xb5, 0xa3, 0xf7, 0xf2, 0xce, 0xf9, 0x61, 0x15, 0xa1 },
	{ 0xe0, 0xae, 0x5d, 0xa4, 0x9b, 0x34, 0x1a, 0x55, 0xad, 0x93, 0x32, 0x30, 0xf5, 0x8c, 0xb1, 0xe3 },
	{ 0x1d, 0xf6, 0xe2, 0x2e, 0x82, 0x66, 0xca, 0x60, 0xc0, 0x29, 0x23, 0xab, 0x0d, 0x53, 0x4e, 0x6f },
	{ 0xd5, 0xdb, 0x37, 0x45, 0xde, 0xfd, 0x8e, 0x2f, 0x03, 0xff, 0x6a, 0x72, 0x6d, 0x6c, 0x5b, 0x51 },
	{ 0x8d, 0x1b, 0xaf, 0x92, 0xbb, 0xdd, 0xbc, 0x7f, 0x11, 0xd9, 0x5c, 0x41, 0x1f, 0x10, 0x5a, 0xd8 },
	{ 0x0a, 0xc1, 0x31, 0x88, 0xa5, 0xcd, 0x7b, 0xbd, 0x2d, 0x74, 0xd0, 0x12, 0xb8, 0xe5, 0xb4, 0xb0 },
	{ 0x89, 0x69, 0x97, 0x4a, 0x0c, 0x96, 0x77, 0x7e, 0x65, 0xb9, 0xf1, 0x09, 0xc5, 0x6e, 0xc6, 0x84 },
	{ 0x18, 0xf0, 0x7d, 0xec, 0x3a, 0xdc, 0x4d, 0x20, 0x79, 0xee, 0x5f, 0x3e, 0xd7, 0xcb, 0x39, 0x48 }
};

/* 系统参数 */
static const unsigned long FK[4] = { 0xa3b1bac6, 0x56aa3350, 0x677d9197, 0xb27022dc };

/* 固定参数 */
static const unsigned long CK[32] =
{
	0x00070e15, 0x1c232a31, 0x383f464d, 0x545b6269,
	0x70777e85, 0x8c939aa1, 0xa8afb6bd, 0xc4cbd2d9,
	0xe0e7eef5, 0xfc030a11, 0x181f262d, 0x343b4249,
	0x50575e65, 0x6c737a81, 0x888f969d, 0xa4abb2b9,
	0xc0c7ced5, 0xdce3eaf1, 0xf8ff060d, 0x141b2229,
	0x30373e45, 0x4c535a61, 0x686f767d, 0x848b9299,
	0xa0a7aeb5, 0xbcc3cad1, 0xd8dfe6ed, 0xf4fb0209,
	0x10171e25, 0x2c333a41, 0x484f565d, 0x646b7279
};
void meau() {
	printf("\n******国家密码算法SM4*******\n");
	printf("*****1.加密******\n");
	printf("*****2.解密******\n");
	printf("*****0.退出******\n");
	printf("***************************\n");
}
char* PKCS7(char* plaintext) {
	int  i, j, k;
	if (strlen(plaintext) % 16) {
		i = strlen(plaintext);
		j = i / 16;
		k = i % 16;
		for (int n = i, m = 16 - k; n < j * 16 + 16; n++) {
			plaintext[n] = m;
		}
	}
	printf("PKCS7模式下填充的明文为%s\n", plaintext);
	return plaintext;
}
int* setkey_1(unsigned long* setkey, int time) {
	unsigned long size[4];
	unsigned long mid, mid_1, mid_2;
	int high, low;//高位，低位

	mid = setkey[time + 1] ^ setkey[time + 2] ^ setkey[time + 3] ^ CK[time]; //printf("[% 02X]", mid);
	size[0] = mid / (16 * 16 * 16 * 16 * 16 * 16);
	mid -= size[0] * (16 * 16 * 16 * 16 * 16 * 16);
	size[1] = mid / (16 * 16 * 16 * 16);
	mid -= size[1] * (16 * 16 * 16 * 16);
	size[2] = mid / (16 * 16);
	mid -= size[2] * (16 * 16);
	size[3] = mid; //printf("[%02X  %02X  %02X %02X]",size[0],size[1],size[2],size[3]);
	for (int i = 0; i < 4; i++) {
		high = size[i] / 16;
		low = size[i] % 16;
		size[i] = SboxTable[high][low];
	}//printf("[%02X  %02X  %02X %02X]", size[0], size[1], size[2], size[3]);
	mid = size[0] * 16 * 16 * 16 * 16 * 16 * 16 + size[1] * 16 * 16 * 16 * 16 + size[2] * 16 * 16 + size[3]; //printf("[%02X]", mid);
	mid_1 = mid;
	mid_2 = mid;
	mid_1 = (mid_1 >> (32 - 13)) | (mid_1 << 13);
	mid_2 = (mid_2 >> (32 - 23)) | (mid_2 << 23);
	//printf("[%02X  %02X  %02X]",mid,mid_1,mid_2);
	setkey[time + 4] = mid ^ mid_1 ^ mid_2;
	setkey[time + 4] ^= setkey[time];
	return setkey;
}
int* setkey(char key[]) {
	unsigned long* setkey;//[4*36];
	setkey = (unsigned long*)malloc(sizeof(unsigned long*) * 4 * 36);

	for (int i = 0; i < 4; i++) {
		setkey[i] = key[i * 4] * 16 * 16 * 16 * 16 * 16 * 16 + key[i * 4 + 1] * 16 * 16 * 16 * 16 + key[i * 4 + 2] * 16 * 16 + key[i * 4 + 3];
	}
	for (int i = 0; i < 4; i++) {
		setkey[i] ^= FK[i];
	}

	//setkey_1(setkey,0);
	for (int i = 0; i < 32; i++) {
		setkey_1(setkey, i);
	}
	/*for (int i = 0; i < 32; i++) {
		printf("第%02d轮的子秘钥是 %02X ", i + 1, setkey[i + 4]);
		if ((i + 1) % 4 == 0) {
			printf("\n");
		}
	}*/
	return setkey;
}
int* jiami_1(unsigned long* plaintext_0, int time, int* Skey) {
	unsigned long size[4];
	unsigned long mid, mid_1, mid_2, mid_3, mid_4;
	int high, low;//高位，低位	

	mid = plaintext_0[time + 1] ^ plaintext_0[time + 2] ^ plaintext_0[time + 3] ^ Skey[time + 4];
	size[0] = mid / (16 * 16 * 16 * 16 * 16 * 16);
	mid -= size[0] * (16 * 16 * 16 * 16 * 16 * 16);
	size[1] = mid / (16 * 16 * 16 * 16);
	mid -= size[1] * (16 * 16 * 16 * 16);
	size[2] = mid / (16 * 16);
	mid -= size[2] * (16 * 16);
	size[3] = mid;
	for (int i = 0; i < 4; i++) {
		high = size[i] / 16;
		low = size[i] % 16;
		size[i] = SboxTable[high][low];
	}
	mid = size[0] * 16 * 16 * 16 * 16 * 16 * 16 + size[1] * 16 * 16 * 16 * 16 + size[2] * 16 * 16 + size[3];
	mid_1 = (mid >> (32 - 2)) | (mid << 2);
	mid_2 = (mid >> (32 - 10)) | (mid << 10);
	mid_3 = (mid >> (32 - 18)) | (mid << 18);
	mid_4 = (mid >> (32 - 24)) | (mid << 24);
	plaintext_0[time + 4] = mid ^ mid_1 ^ mid_2 ^ mid_3 ^ mid_4;
	plaintext_0[time + 4] ^= plaintext_0[time];
	//printf("第%d轮{%X}", time + 1, plaintext_0[time + 4]);
	return plaintext_0;
}
int* jiami_0(unsigned char plaintext[], int* Skey) {     //明文处理
	unsigned long* plaintext_0;//[4*36];
	unsigned long* ciphetext;//[4*36];
	unsigned long mid;
	int length = strlen(plaintext);
	plaintext_0 = (unsigned long*)malloc(sizeof(unsigned long*) * 36);
	ciphetext = (unsigned long*)malloc(sizeof(unsigned long*) * length);


	for (int k = 0; k < (length / 16); k++) {
		for (int i = 0; i < 4; i++) {
			plaintext_0[i] = (plaintext[i * 4]) * 16 * 16 * 16 * 16 * 16 * 16
				+ (plaintext[i * 4 + 1]) * 16 * 16 * 16 * 16
				+ (plaintext[i * 4 + 2]) * 16 * 16
				+ (plaintext[i * 4 + 3]);
			//printf("\n%X  %X  %X  %d", plaintext[i * 4]%256, plaintext[i * 4 + 1]%256, plaintext[i * 4 + 2]%256, plaintext[i * 4 + 3]%256);
		}

		for (int i = 0; i < 32; i++) {
			jiami_1(plaintext_0, i, Skey);
		}
		for (int i = 0; i < 4; i++) {
			mid = plaintext_0[35 - i];
			ciphetext[4 * i + 0] = mid / (16 * 16 * 16 * 16 * 16 * 16);
			mid -= ciphetext[4 * i + 0] * (16 * 16 * 16 * 16 * 16 * 16);
			ciphetext[4 * i + 1] = mid / (16 * 16 * 16 * 16);
			mid -= ciphetext[4 * i + 1] * (16 * 16 * 16 * 16);
			ciphetext[4 * i + 2] = mid / (16 * 16);
			mid -= ciphetext[4 * i + 2] * (16 * 16);
			ciphetext[4 * i + 3] = mid;
		}

	}

	return ciphetext;
}
void jiami() {
	FILE* fp1, * fp2;
	char plaintextPath[30];
	char plaintext[128];
	char ciphetextPath[30];
	char ciphetext[128];
	char key[30];
	unsigned long* key_0;//[4*36];
	key_0 = (unsigned long*)malloc(sizeof(unsigned long*) * 36);
	memset(plaintextPath, 0, sizeof(char) * 30);
	memset(ciphetextPath, 0, sizeof(char) * 30);
	memset(key, 0, sizeof(char) * 30);
	memset(ciphetext, 0, sizeof(char) * 128);
	printf("请输入需要加密的文件路径：");
	gets(plaintextPath);
	if ((fp1 = fopen(plaintextPath, "r")) == NULL) {
		printf("Can't open this file[%s].\n", plaintextPath);
		exit(0);
	}
	printf("请输入16位的密钥：");
	gets(key);
	while (strlen(key) != 16) {
		printf("您所输入的密钥不是16字节，请重新输入！\n请输入16位的密钥：");
		gets(key);
	}
	printf("请输入加密后的文件路径：");
	gets(ciphetextPath);
	if ((fp2 = fopen(ciphetextPath, "w+")) == NULL) {
		printf("Can't open this file[%s].\n", ciphetextPath);
		exit(0);
	}
	fgets(plaintext, 80, fp1);
	PKCS7(plaintext);
	//fgets(ciphetext,80,fp2);
	printf("[%s]\n", plaintext);
	int* Skey = NULL;
	int* Splaintext = NULL;
	Skey = setkey(key);
	for (int i = 0; i < 32; i++) {
		printf("第%02d轮的子秘钥是 %02X ", i + 1, Skey[i + 4]);
		if ((i + 1) % 4 == 0) {
			printf("\n");
		}
	}
	Splaintext = jiami_0(plaintext, Skey);
	printf("EBC模式下国密SM4的加密结果是：\n");
	for (int i = 0; i < strlen(plaintext); i++) {
		printf(" %02X", Splaintext[i]);
	}
	for (int i = 0; i < strlen(plaintext); i++) {
		ciphetext[i] = Splaintext[i];
	}
	fputs(ciphetext, fp2);

	if (fclose(fp1)) {
		printf("Can't close the file![%s].\n", plaintextPath);
		exit(0);
	}
	if (fclose(fp2)) {
		printf("Can't close the file![%s].\n", ciphetextPath);
		exit(0);
	}
}
void jiemi() {
	FILE* fp;

	char plaintext[128];
	char ciphetextPath[30];
	unsigned char ciphetext[128];
	char key[30];
	/*char key_0[35];
	memset(key_0, 0, sizeof(unsigned long)*36);*/
	unsigned long* key_0;//[4*36];
	key_0 = (unsigned long*)malloc(sizeof(unsigned long*) * 36);
	memset(ciphetextPath, 0, sizeof(char) * 30);
	memset(key, 0, sizeof(char) * 30);
	memset(ciphetext, 0, sizeof(char) * 128);
	printf("请输入需要解密的文件路径：");
	gets(ciphetextPath);
	if ((fp = fopen(ciphetextPath, "r")) == NULL) {
		printf("Can't open this file[%s].\n", ciphetextPath);
		exit(0);
	}
	printf("请输入16位的密钥：");
	gets(key);
	while (strlen(key) != 16) {
		printf("您所输入的密钥不是16字节，请重新输入！\n请输入16位的密钥：");
		gets(key);
	}

	fgets(ciphetext, 80, fp);
	//PKCS7(ciphetext);

	printf("[%s]\n", ciphetext);
	int* Skey = NULL;
	int* Sciphetext = NULL;
	Skey = setkey(key);
	
	for (int i = 0; i < 32; i++) {
		key_0[i + 4] = Skey[35 - i];
	}
	for (int i = 0; i < 32; i++) {
		printf("第%02d轮的子秘钥是 %02X ", i + 1, key_0[i + 4]);
		if ((i + 1) % 4 == 0) {
			printf("\n");
		}
	}
	Sciphetext = jiami_0(ciphetext, key_0);
	/*for (int i = 0; i < strlen(ciphetext); i++) {
		ciphetext[i] = Sciphetext[i];
	}*/
	printf("\nEBC模式下国密SM4的解密结果是：\n");
	for (int i = 0; i < strlen(ciphetext); i++) {
		printf("%c", Sciphetext[i]);
	}

	if (fclose(fp)) {
		printf("Can't close the file![%s].\n", ciphetextPath);
		exit(0);
	}
}
int main() {
	int index = 0;
	while (1) {
		meau();
		printf("请选择：");
		scanf("%d", &index);
		getchar();
		switch (index) {
		case 1:
			jiami();
			break;
		case 2:
			jiemi();
			break;
		case 0:
			exit(0);
		default:
			break;
		}
	}
}