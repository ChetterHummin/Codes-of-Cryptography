#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>  
#include<string.h>
#include<math.h>
#include<time.h>
int MulFactor[4][4] = { {0x02, 0x03, 0x01, 0x01},
                       {0x01, 0x02, 0x03, 0x01},
                       {0x01, 0x01, 0x02, 0x03},
                       {0x03, 0x01, 0x01, 0x02} };

int MulFactor_1[4][4] = { {0x0E, 0x0B, 0x0D, 0x09},
                         {0x09, 0x0E, 0x0B, 0x0D},
                         {0x0D, 0x09, 0x0E, 0x0B},
                         {0x0B, 0x0D, 0x09, 0x0E} };//解密使用

int S[16][16] = { {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
                 {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
                 {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
                 {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
                 {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
                 {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
                 {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
                 {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
                 {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
                 {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
                 {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
                 {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
                 {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
                 {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
                 {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
                 {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16} };

int S_1[16][16] = { {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb},
                   {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb},
                   {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e},
                   {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25},
                   {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92},
                   {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84},
                   {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06},
                   {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b},
                   {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73},
                   {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e},
                   {0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b},
                   {0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4},
                   {0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f},
                   {0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef},
                   {0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61},
                   {0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}
};//解密使用

int RCon[11][4] = {
        {0x00, 0x00, 0x00, 0x00},
        {0x01, 0x00, 0x00, 0x00},
        {0x02, 0x00, 0x00, 0x00},
        {0x04, 0x00, 0x00, 0x00},
        {0x08, 0x00, 0x00, 0x00},
        {0x10, 0x00, 0x00, 0x00},
        {0x20, 0x00, 0x00, 0x00},
        {0x40, 0x00, 0x00, 0x00},
        {0x80, 0x00, 0x00, 0x00},
        {0x1B, 0x00, 0x00, 0x00},
        {0x36, 0x00, 0x00, 0x00} };

void meau() {
    printf("=========AES加密算法=========\n");
    printf("1.Zero填充\n");
    printf("2.X923填充\n");
    printf("3.PKCS7填充\n");
    printf("4.ISO10126填充\n");
    printf("0.退出程序\n");
}
char* Zero(char* plaintext) {
    int  i, j, k;
    if (strlen(plaintext) % 16) {
        i = strlen(plaintext);
        j = i / 16;
        k = i % 16;
        for (int n = i; n < j*16 + 16; n++) {
            plaintext[n] = '0x00';
        }
    }
    printf("Zero模式下填充的明文为%s\n", plaintext);
    return plaintext;
}
char* PKCS7(char* plaintext) {
    int  i, j, k;
    if (strlen(plaintext) % 16) {
        i = strlen(plaintext);
        j = i / 16;
        k = i % 16;
        for (int n = i,m=16-k; n < j * 16 + 16; n++) {
            plaintext[n] =m;
        }
    }
    printf("PKCS7模式下填充的明文为%s\n", plaintext);
    return plaintext;
}
char* X923(char* plaintext) {
    int  i, j, k;
    if (strlen(plaintext) % 16) {
        i = strlen(plaintext);
        j = i / 16;
        k = i % 16;
        for (int n = i; n < j * 16 + 16-1; n++) {
            plaintext[n] = '0x00';
        }
        plaintext[j * 16 + 16-1] = 16 - k;
    }
    printf("X923模式下填充的明文为%s\n", plaintext);
    return plaintext;
}
char* ISO10126(char* plaintext) {
    int  i, j, k;
    if (strlen(plaintext) % 16) {
        i = strlen(plaintext);
        j = i / 16;
        k = i % 16;
        srand(time(NULL));
        for (int n = i; n < j * 16 + 16-1; n++) {
            plaintext[n] = rand()%127;
        }
        plaintext[j * 16 + 16-1] = 16 - k;
    }
    printf("ISO10126模式下填充的明文为%s\n", plaintext);
    return plaintext;
}
int** changekey(char key[]) {
    
    int** W = NULL;
    W = (int**)malloc(sizeof(int*) * 4);
    for (int i = 0; i < 4; i++) {
        W[i] = (int*)malloc(sizeof(int) * 44);
        memset(W[i], 0, sizeof(int) * 44);
    }
    printf("========正在产生子密钥======\n");
    printf("======完成矩阵化的矩阵为======\n");
    for (int i = 0, j = 0; i < 4; i++) {
        for (; j < 4; j++) {
            printf(" %X ", key[i + 4 * j]);
        }
        j = 0;
        printf("\n");
    }
    int row = 0;//行
    int col = 0;//列
    int m, n;//高位，低位
    int x;
    for (; col < 4; col++) {
        for (; row < 4; row++) {
           
            W[row][col]= key[row + 4 * col];
        }
        row = 0;
    }
    for (; col < 44; col++) {
        if (col % 4 == 0) {
            x = W[0][col];
            for (row = 0; row < 3; row++) {
                W[row][col] = W[row + 1][col-1];
            }
            W[row][col] = W[0][col-1];
            for (row = 0; row < 4; row++) {
                m = W[row][col] / 16;
                n = W[row][col] % 16;
                W[row][col] = S[m][n];
                W[row][col] = W[row][col] ^ W[row][col - 4] ^ RCon[col/4][row];
            }
        }
        else if (col % 4 != 0) {
            for (row = 0; row < 4; row++) {
                W[row][col] = W[row][col - 1] ^ W[row][col - 4];
            }
        }
    }
    printf("========产生的10轮子密钥============\n");
    for (int k = 0,i=0,j=4; k < 10;k++) {
        printf("第%2d轮子密钥是：",k+1);
        for (int l = j + 4; j < l; j++) {
            for (; i < 4; i++) {
                printf(" %02X ", W[i][j]);
            }
            i = 0;
        }
        printf("\n");
    }
    return W;
}
int** SubBytes(int** plaintext_0,int length) {
    int m, n;
    for (int i=0;i<4;i++) {
        for (int j = 0; j < length; j++) {
            m = plaintext_0[i][j] / 16;
            n = plaintext_0[i][j] % 16;
            plaintext_0[i][j] = S[m][n];
        }
    }
    printf("======完成SubBytes变换的矩阵为：===========\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < length;j++) {
            printf(" %02X ", plaintext_0[i][j]);
        }
        printf("\n");
    }
    return plaintext_0;
}
int** ShiftRows(int** plaintext_0, int length) {
    int** plaintext_1 = NULL;
    plaintext_1 = (int**)malloc(sizeof(int*) * 4);
    for (int i = 0; i < 4; i++) {
        plaintext_1[i] = (int*)malloc(sizeof(int) * length);
        memset(plaintext_1[i], 0, sizeof(int) * length);
    }//printf("\n%d\n",length );
    for (int k = 0; k < length / 4; k++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4-i; j++) {
                plaintext_1[i][j+4*k] = plaintext_0[i][i+j+4*k];
            }
            for (int j=0;j<i;j++) {
                plaintext_1[i][j +4 - i + 4 * k] = plaintext_0[i][j+4*k];
            }
        }
    }
    for (int i=0;i<4;i++) {
        for (int j=0;j<length;j++) {
            plaintext_0[i][j] = plaintext_1[i][j];
        }
    }
    printf("======完成ShiftRows变换的矩阵为：===========\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < length; j++) {
            printf(" %02X ", plaintext_0[i][j]);
        }
        printf("\n");
    }
    return plaintext_0;
}
int** MixColumns(int** plaintext_0, int length) {
    int sum=0;
    int sum0, sum1, sum2, sum3;
    int Sum[4] = {0};
    int** plaintext_1 = NULL;
    plaintext_1 = (int**)malloc(sizeof(int*) * 4);
    for (int i = 0; i < 4; i++) {
        plaintext_1[i] = (int*)malloc(sizeof(int) * length);
        memset(plaintext_1[i], 0, sizeof(int) * length);
    }//printf("\n%d\n", length);
    for (int k = 0; k < (length/4); k++) {
        for (int i = 0; i < 4; i++) {  //i行j列
            for (int j = 0,sum=0; j < 4; j++) {
                for (int l = 0; l < 4; l++) {
                    if (MulFactor[i][l] == 1) {
                        Sum[l] = plaintext_0[l][j + 4*k];
                    }
                    else if (MulFactor[i][l]==2) {
                        if (plaintext_0[l][j + 4 * k] >= 128) {
                            sum = plaintext_0[l][j + 4 * k] << 1;
                            Sum[l] = sum ^ 27;
                        }
                        else {
                            sum = plaintext_0[l][j + 4 * k] << 1;
                            Sum[l] = sum; 
                        }
                    }
                    else if (MulFactor[i][l] == 3) {
                        if (plaintext_0[l][j + 4 * k] >= 128) {
                            sum = plaintext_0[l][j + 4 * k] << 1;
                            Sum[l] = (sum ^ 27)^ plaintext_0[l][j + 4 * k];
                        }
                        else {
                            Sum[l] = (2 * plaintext_0[l][j + 4 * k]) ^ plaintext_0[l][j + 4 * k];
                            //sum = plaintext_0[l][i + 4 * k] << 1;
                            //Sum[l] = sum;
                        }
                    }
                    else {
                        printf("\nshit\n");
                    }
                }
                if ((Sum[0] ^ Sum[1] ^ Sum[2] ^ Sum[3]) > 0XFF) {
                    plaintext_1[i][j + 4 * k] = (Sum[0] ^ Sum[1] ^ Sum[2] ^ Sum[3])%0X100;
                }
                else {
                    plaintext_1[i][j + 4 * k] = Sum[0] ^ Sum[1] ^ Sum[2] ^ Sum[3];
                }
                //plaintext_1[i][j] = Sum[0] ^ Sum[1] ^ Sum[2] ^ Sum[3];
            }
        }
    }
    printf("======完成MixColumns变换的矩阵为：===========\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < length; j++) {
            printf(" %02X ", plaintext_1[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < length; j++) {
            plaintext_0[i][j]=plaintext_1[i][j];
        }
        
    }
    return plaintext_0;
}
int** AddRounKey(int** plaintext_0, int** W, int length,int i) {

    for (int k = 0; k < (length / 4); k++) {
        for (int m = 0; m < 4; m++) {
            for (int n = 0; n < 4; n++) {
                plaintext_0[n][m + 4 * k] = plaintext_0[n][m + 4 * k]^W[n][m+(i)*4];
            }
        }
    }
    printf("======完成AddRounKey变换的矩阵为：===========\n");
    for (int  m= 0;  m< 4; m++) {
        for (int n = 0; n < length; n++) {
            printf(" %02X ", plaintext_0[m][n]);
        }
        printf("\n");
    }
    return plaintext_0;
}
int** jiami(char *plaintext,int **W,int length) {
    int** plaintext_0 = NULL;
    int** plaintext_1 = NULL;
    plaintext_0 = (int**)malloc(sizeof(int*) * 4);
    for (int i = 0; i < 4; i++) {
        plaintext_0[i] = (int*)malloc(sizeof(int) * (strlen(plaintext)/4));
        memset(plaintext_0[i], 0, sizeof(int) * (strlen(plaintext) / 4));
    }
    //printf("\n%d\n", strlen(plaintext));
    printf("=========完成矩阵化的矩阵为：=========\n");
    for (int i = 0, j = 0; i < 4; i++) {
        for (; j < (strlen(plaintext) / 4); j++) {
            printf(" %02X ", plaintext[i + 4 * j]);
            plaintext_0[i][j] = plaintext[i + 4 * j];
        }
        j = 0;
        printf("\n");
    }
    printf("对明文进行初始变换：\n");
    AddRounKey(plaintext_0, W, (strlen(plaintext) / 4), 0);
    for (int i = 0; i < 9; i++) {
        printf("开始第%d轮加密=====》\n",i+1);
        SubBytes(plaintext_0, (strlen(plaintext) / 4));
        ShiftRows(plaintext_0, (strlen(plaintext) / 4));
        MixColumns(plaintext_0, (strlen(plaintext) / 4));
        AddRounKey(plaintext_0, W, (strlen(plaintext) / 4), i+1);
    }
    printf("开始第10轮加密=====》\n");
    SubBytes(plaintext_0, (strlen(plaintext) / 4));
    ShiftRows(plaintext_0, (strlen(plaintext) / 4));
    //MixColumns(plaintext_0, (strlen(plaintext) / 4));
    AddRounKey(plaintext_0, W, (strlen(plaintext) / 4), 10);

    printf("明文是：");
    for (int i = 0; i < length; i++) {
        printf("%c", plaintext[i]);
    }
    printf("\n密钥是：");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%c",W[j][i]);
        }
    }
    printf("\nAES的加密结果是：");
    for (int j = 0; j < (strlen(plaintext) / 4); j++) {
        for (int i = 0; i < 4; i++) {
            printf(" %02X ", plaintext_0[i][j]);
        }
    }
    printf("\n");
    //plaintext_1= SubBytes(plaintext_0, (strlen(plaintext) / 4));
    //plaintext_1 = ShiftRows(plaintext_0, (strlen(plaintext) / 4));
    //plaintext_1 = MixColumns(plaintext_0, (strlen(plaintext) / 4));
    return plaintext_0;
}
int main() {
    int index = 1;
    char key[16];
    char plaintext[120];  //明文
    char ciphetext[120];  //密文
    int** W = NULL;
    int length;
    while (1) {
        meau();
        printf("请选择明文填充方式：");
        scanf("%d", &index);
        getchar();
        switch (index) {
        case 1:
            memset(plaintext,0,sizeof(char)*120);
            memset(key, 0, sizeof(char) * 16);
            printf("请输入16位的密钥：");
            gets(key);
            while (strlen(key) != 16) {
                printf("您所输入的密钥不是16字节，请重新输入！\n请输入16位的密钥：");
                gets(key);
            }
            printf("请输入明文，（不超过100字节)：");
            gets(plaintext);
            while (strlen(plaintext) > 100) {
                printf("您所输入的明文不符合要求，请重新输入！\n请输入明文，（不超过100字节)：");
                gets(plaintext);
                
            }length = strlen(plaintext);
            W=changekey(key);
            Zero(plaintext);
            //printf("\n%d\n", strlen(plaintext));
            jiami(plaintext,W,length);
            break;
        case 2:
            memset(plaintext, 0, sizeof(char) * 120);
            memset(key, 0, sizeof(char) * 16);
            printf("请输入16位的密钥：");
            gets(key);
            while (strlen(key) != 16) {
                printf("您所输入的密钥不是16字节，请重新输入！\n请输入16位的密钥：");
                gets(key);
            }
            printf("请输入明文，（不超过100字节)：");
            gets(plaintext);
            while (strlen(plaintext) > 100) {
                printf("您所输入的明文不符合要求，请重新输入！\n请输入明文，（不超过100字节)：");
                gets(plaintext);
                
            }length = strlen(plaintext);
            W = changekey(key);
            X923(plaintext);
            //printf("\n%d\n", strlen(plaintext));
            jiami(plaintext, W, length);
            break;
        case 3:
            memset(plaintext, 0, sizeof(char) * 120);
            memset(key, 0, sizeof(char) * 16);
            printf("请输入16位的密钥：");
            gets(key);
            while (strlen(key) != 16) {
                printf("您所输入的密钥不是16字节，请重新输入！\n请输入16位的密钥：");
                gets(key);
            }
            printf("请输入明文，（不超过100字节)：");
            gets(plaintext);
            while (strlen(plaintext) > 100) {
                printf("您所输入的明文不符合要求，请重新输入！\n请输入明文，（不超过100字节)：");
                gets(plaintext);
                
            }length = strlen(plaintext);
            W = changekey(key);
            PKCS7(plaintext);
            //printf("\n%d\n", strlen(plaintext));
            jiami(plaintext, W, length);
            break;
        case 4:
            memset(plaintext, 0, sizeof(char) * 120);
            memset(key, 0, sizeof(char) * 16);
            printf("请输入16位的密钥：");
            gets(key);
            while (strlen(key) != 16) {
                printf("您所输入的密钥不是16字节，请重新输入！\n请输入16位的密钥：");
                gets(key);
            }
            printf("请输入明文，（不超过100字节)：");
            gets(plaintext);
            while (strlen(plaintext) > 100) {
                printf("您所输入的明文不符合要求，请重新输入！\n请输入明文，（不超过100字节)：");
                gets(plaintext);
                
            }length = strlen(plaintext);
            W = changekey(key);
            ISO10126(plaintext);
            //printf("\n%d\n", strlen(plaintext));
            jiami(plaintext, W, length);
            break;
        case 0:
            exit();
        default:
            break;
        }
   }
    return 0;
}