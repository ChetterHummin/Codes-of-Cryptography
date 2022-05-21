#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<math.h>
const unsigned int IV_0[8] = {   //��ʼֵ
	0x7380166f, 0x4914b2b9, 0x172442d7, 0xda8a0600, 0xa96f30bc, 0xe38dee4d, 0xb0fb0e4e, 0x00000000
};
const unsigned int IV[8] = {   //��ʼֵ(����)
	0x7380166f, 0x4914b2b9, 0x172442d7, 0xda8a0600, 0xa96f30bc, 0x163138aa, 0xe38dee4d, 0xb0fb0e4e
};
const unsigned int T[2] = {  //����
	0x79cc4519,0x7a879d8a
};
#define PP(x) (x << 24) | ((x << 8) & 0xff0000) | ((x >> 8) & 0xff00) | (x >> 24)//��x�ߵ�λ������
#define RL(x,y) (((x)<<(y))|((x)>>(32-(y))))  //x����ѭ����yλ
#define FF(x,y,z,j) ((j>=0&&j<=15)?(x^y^z):((x&y)|(x&z)|(y&z)))        //��������
#define GG(x,y,z,j)  ((j>=0&&j<=15)?(x^y^z):((x&y)|((~x)&z)))            //��������
#define P_0(X) ((X)^(RL(X,9))^(RL(X,17)))                                //�û�����
#define P_1(X) ((X)^(RL(X,15))^(RL(X,23)))
void SM3(unsigned char plaintext[], int length) {
	unsigned int A, B, C, D, E,F,G,H, a, b, c, d, e,f,g,h, W[68],W_1[64],SS1,SS2,TT1,TT2;
	A = IV[0]; B = IV[1]; C = IV[2]; D = IV[3]; E = IV[4], F = IV[5], G = IV[6], H = IV[7];
	
	//printf("\n[%x  %x  %x %x  %x ]\n",a,b,c,d,e);
	//unsigned int W[512];
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
	for (int t = 0; t < (length / 64); t++) {                         //��Ϣ��չ
		a = A; b = B; c = C; d = D; e = E, f = F, g = G, h = H;
		for (int j = 0; j < 16; j++) {
			W[j] = Temp[j + 16 * t];
		}
		printf("W[0]^W[67]:\n");
		for (int j = 16; j < 68;j++) {
			W[j] = P_1(W[j-16]^W[j-9]^(RL(W[j-3],15)))^(RL(W[j-13],7))^W[j-6]; //printf("%08X  ", W[j]);
		}
		for (int i = 0; i < 68; i++) {
			printf("%08X  ",W[i]);
			if (i % 8 == 7) {
				printf("\n");
			}
		}
		printf("\nW_1[0]^W_1[64]:\n");
		for (int j = 0; j < 64; j++) {
			W_1[j] = W[j] ^ W[j+4];
		}
		for (int i = 0; i < 64; i++) {
			printf("%08X  ", W_1[i]);
			if (i % 8 == 7) {
				printf("\n");
			}
		}printf("A=%08X B=%08X C=%08X D=%08X E=%08X F=%08X G=%08X H=%08X \n", a, b, c, d, e, f, g, h);
		for (int i = 0,index=0; i < 64; i++) {
			if ((i>=0)&&(i<=15)) {
				index = 0;
			}
			else {
				index = 1;
			}
			//SS1 = rotate_left(((rotate_left(a, 12)) + e + (rotate_left(T[index], i))) & 0xFFFFFFFF, 7); printf("{%08X   %08X}\n", SS1, (rotate_left(T[index], i)));
			SS1 = RL((RL(a,12)+e+(RL(T[index],(i%32)))),7);
			SS2 = SS1 ^ (RL(a,12));
			TT1 = FF(a, b, c, i) + d + SS2 + W_1[i];
			TT2 = GG(e, f, g, i) + h + SS1 + W[i]; 
			d = c;
			c = (RL(b,9));
			b = a;
			a = TT1;
			h = g;
			g = (RL(f,19));
			f = e;
			e = P_0(TT2);
			//printf("%08X %08X %08X %08X",SS1,SS2,TT1,TT2);
			printf("��%02d�ֵĲ�����A=%08X B=%08X C=%08X D=%08X E=%08X F=%08X G=%08X H=%08X \n",i+1, a, b, c, d, e, f, g, h);
		}
		A ^= a; B ^=b; C ^= c; D ^= d; E ^= e; F ^= f; G ^= g; H ^= h;
	}
	printf("���ܺ�Ľ���ǣ�%08X %08X %08X %08X %08X %08X %08X %08X \n",A,B,C,D,E,F,G,H);
}
void menu() {
	printf("===============SM3ʵ������==================\n");
	printf("============================================\n");
	printf("================1����������==================\n");
	printf("================2���ļ�����==================\n");
	printf("================0���˳�����==================\n");
	printf("============================================\n");

}
unsigned int rotate_left(unsigned int a, unsigned int k)
{
	k = k % 32;
	return ((a << k) & 0xFFFFFFFF) | ((a & 0xFFFFFFFF) >> (32 - k));
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
	int Length = length * 8;
	//PP(Length); printf("%d",Length);
	char a[40] = "0123456789ABCDEF";//��һ������洢ʮ��������
	char b[100];//���������ʮ��������Ӧ��ʮ��������
	int n;
	int cnt = 0;//����
	n = Length;
	//scanf("%d", &n);//����Ҫת����ʮ������

	if (n == 0)
		printf("0");
	while (n != 0)
	{
		b[++cnt] = a[n % 16];//����cnt��1��ʼ
		n = n / 16;
	}

	if (cnt % 2 != 0) {
		b[cnt++] = '0';
	}
	for (int i = 1, j = length_end - 1, t = 0; i <= cnt; i += 2, j--) {
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

	SM3(plaintext, length_end);
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
		printf("��ѡ��");
		scanf("%d", &index);
		getchar();
		switch (index) {
		case 1:
			memset(plaintext_0, 0, sizeof(char) * 80);
			printf("��������Ҫ����SHA-1���ַ���\n");
			scanf("%[^\n]s", plaintext_0);
			getchar();
			filling(plaintext_0);
			break;
		case 2:
			memset(ciphetextPath, 0, sizeof(char) * 30);
			printf("��������Ҫ���ļ�·����");
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