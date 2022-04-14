#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>  
#include<string.h>
#include<math.h>
int ROL_TIMES[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
int PC_1[56] = { 56, 48, 40, 32, 24, 16, 8, 0,
                57, 49, 41, 33, 25, 17, 9, 1,
                58, 50, 42, 34, 26, 18, 10, 2,
                59, 51, 43, 35, 62, 54, 46, 38,
                30, 22, 14, 6, 61, 53, 45, 37,
                29, 21, 13, 5, 60, 52, 44, 36,
                28, 20, 12, 4, 27, 19, 11, 3 };
int PC_2[48] = { 13, 16, 10, 23, 0, 4, 2, 27,
                14, 5, 20, 9, 22, 18, 11, 3,
                25, 7, 15, 6, 26, 19, 12, 1,
                40, 51, 30, 36,46, 54, 29, 39,
                50, 44, 32, 46, 43, 48, 38, 55,
                33, 52, 45, 41, 49, 35, 28, 31 };

/*void ByteToBit(char ch, char bit[8]) {
    int cnt;
    for (cnt = 0; cnt < 8; cnt++) {
        *(bit + cnt) = (ch >> cnt) & 1;
    }
}
void Char8ToBit64(char ch[8], char bit[64]) {
    int cnt;
    for (cnt = 0; cnt < 8; cnt++) {
        ByteToBit(*(ch + cnt), bit + (cnt << 3));
    }
}*/
int* PC1_Transform(int* key[]){                                         //(char key[64], char tempbts[56]) {
    //int tempbts[56] = {0};
    int* tempbts = (int*)malloc(56 * sizeof(int));
    for (int i = 0; i < 56; i++) {
        tempbts[i] = key[PC_1[i]];
    }
    
    return tempbts;
}
PC2_Transform(int* tempbts) {
    int* subKey = (int*)malloc(48 * sizeof(int));
    for (int i = 0; i < 48; i++) {
        subKey[i] = tempbts[PC_2[i]];
    }
    return subKey;
}
int* DES_ROL(int* tempbts, int i) {
 
    int* data = (int*)malloc(56 * sizeof(int));
    memset(data, 0,sizeof(int) * 56);
    //memcpy(data,tempbts,strlen(tempbts));
    for (int j = 0; j < 56; j++) {
        data[j] = tempbts[j];
    }
    for (int j = ROL_TIMES[i]; j < 28; j++) {
        tempbts[j - ROL_TIMES[i]] = tempbts[j];
    }
    for (int j = 0; j < ROL_TIMES[i]; j++) {
        tempbts[28 - ROL_TIMES[i] + j] = data[j];
    }
    for (int j = ROL_TIMES[i]; j < 28; j++) {
        tempbts[j - ROL_TIMES[i]+28] = tempbts[j+28];
    }
    for (int j = 0; j < ROL_TIMES[i]; j++) {
        tempbts[28 - ROL_TIMES[i] + j+28] = data[j+28];
    }
  
    
 /*   for (int m = 0, n = 0; m<7; m++) {                          //m行n列
        //memcpy(data,tempbts+ROL_TIMES[i]*sizeof(int),)
        for (int k = ROL_TIMES[i]; k <4; k++) {
            tempbts[k - ROL_TIMES[i]+8*m] = tempbts[k+8*m];
        }
        for (int j = 0; j < ROL_TIMES[i]; j++) {
            tempbts[4 - ROL_TIMES[i]+8*m] = data[j+8*m];
        }
    }
    for (int m = 0, n = 0; m < 7; m++) {                          //m行n列
        for (int k = ROL_TIMES[i]; k < 4; k++) {
            tempbts[k - ROL_TIMES[i] + 8 * m+4] = tempbts[k + 8 * m+4];
        }
        for (int j = 0; j < ROL_TIMES[i]; j++) {
            tempbts[4 - ROL_TIMES[i] + 8 * m+4] = data[j + 8 * m+4];
        }
    }*/
    return tempbts;
}

int* Char8ToBit64(char *bit) {
    int j;
    //int key[64] = {0};
    int* key = (int*)malloc(64*sizeof(int));
    memset(key, 0, sizeof(int) * 64);
    for (int m = 0,n=7,l=0; m < 8; m++) {                        //短除法
        int k = bit[m];
        while (k) {
            j = k % 2;
            k = k / 2;
            key[n + 8 * l] = j;
            n--;
        }
        n = 7;
        l++;
    }
    return key;
}
int* Byte2Bit(int* subKey) {
    int* answer=(int*)malloc(12 * sizeof(int));
    memset(answer, 0, sizeof(int) * 12);
    
    for (int i = 0,j=0; i < 12; i++) {
        for (j = 0; j < 4; j++) { 
            if (subKey[j + 4 * i]) {
                answer[i] += (int)pow(2,3-j ); 
            }
        }
        j = 0;
    }
    return answer;
}
int main() {
    char bit[9] = { '0x0','0x0','0x0','0x0','0x0','0x0','0x0','0x0' };
    int index = 1;
    while (index) {
        if (strlen(bit) > 8) {
            printf("输入错误，请重新输入！\n");
        }
        printf("请输入8字节的密钥：");
        scanf("%s", &bit);
        getchar();
        if (strlen(bit) <= 8) {
            index = 0;
        }
    }
    if (strlen(bit) < 8) {
        for (int j = 7; j >=strlen(bit);j--) {
            bit[j] = 0X0;
        }
    }
    int* p, * q;
    int* tempbts;
    int* answer;
    tempbts =PC1_Transform(Char8ToBit64(bit));
    
    for (int i = 0; i < 16; i++) {
        answer= Byte2Bit(PC2_Transform(DES_ROL(tempbts, i)));
        printf("第%d轮生成的子密钥是：", i+1);
        for (int i = 0; i < 12; i++) {
            printf("%X", answer[i]);
        }
        printf("\n");
    }
    
}