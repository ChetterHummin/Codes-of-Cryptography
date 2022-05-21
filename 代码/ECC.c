#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
typedef struct Point
{
	int x;
	int y;
	struct Point* next;
}Point;
typedef struct Points {
	Point* P;
	int length;
}Points;
int checkPoint(Points*Set,Point point) {
	
	Point* m,*n;
	m = Set;
	for (int i = 0; i < Set->length; i++) {
		if ((m->x==point.x)&&(m->y==point.y)) {
			return 0;
		}
		m = m->next;
	}
	return 1;
}
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
/*Points* getPoint(int a, int b, int p) {                                                     //废了
	printf("\n%d %d %d\n",a,b,p);
	Points* Set=(Points*)malloc(sizeof(Points));
	int temp;
	int t;
	temp = (p - 1) / 2;
	Point* m = Set;
	Set->length = 0;
	for (int i = 0; i < p; i++) {
		//printf("%d",(int)(pow((double)i,(double)temp)));
		if ((long)(pow(i, temp)) % p == 1) {
			//printf("[%d]",i);                                                               //采用欧拉准则判别平方剩余：若p是一个奇数，则Z是模p的平方剩余的充要条件是：𝒁^(((𝒑−𝟏))/𝟐)≡𝟏(𝒎𝒐𝒅 𝒑)
			t = 0;
			Point* n = (Point*)malloc(sizeof(Point));
			for (int j = 0; j <= (p / 2); j++) {                                                          //求解Z的两个模p的平方根
				if (((j * j) % p) == ((i * i * i + a * i + b)%p)) {                                                                                //y^2=(x^3+ax+b)mod p
					n->x = i;
					n->y = j; printf("[%d _%d]", i, j);
					t = 1;
					//break;
				}
			}if (t==1) {
				m->next = n;
				m = n;
				Set->length++;
				if ((p - m->y) % p != m->y) {
					Point* n = (Point*)malloc(sizeof(Point));
					n->x = i;
					n->y = (p - m->y); printf("[%d %d]", i, p - m->y);

					m->next = n;
					m = n;
					Set->length++;
				}
			}
			
		}
	}
	return Set;
}*/
Points* getPoint(int a, int b, int p) {
	Points* Set = (Points*)malloc(sizeof(Points));
	int temp;
	int t;
	temp = (p - 1) / 2;
	Point* m = Set;
	Set->length = 0;
	for (int i = 0; i < p; i++) {
		for (int j = 0; j <= temp; j++) {
			
			if (((j * j) % p) == ((i * i * i + a * i + b) % p)) {
				
				Point* n = (Points*)malloc(sizeof(Points));
				n->x = i;
				n->y = j;
				m->next = n;
				m = n;
				Set->length++; printf("(%02d,%02d)", i, j); if (Set->length % 5 == 0) { printf("\n"); }
				if ((p-j)%p!=j) {
					Point* n = (Points*)malloc(sizeof(Points));
					n->x = i;
					n->y = p-j;
					m->next = n;
					m = n;
					Set->length++; printf("(%02d,%02d)", i, p - j); if (Set->length % 5 == 0) { printf("\n"); }
				}
				break;
			}
		}
	}
	return Set;
}
void addition(Point A,Point B,int a,int p) {
	Point C;
	int k;
	//k = ((3*A.x*A.x+a) / (2*A.y)) % p;//similiar
	//k = ((A.y-B.y) / (A.x - B.x))%p;//dissimiliar
	int m, n;
	if ((A.x==B.x)&&(A.y==B.y)) {
		m = 3 * A.x * A.x + a;
		n = 2 * A.y;
	}
	else {
		m = A.y - B.y;
		n = A.x - B.x;
		if (m < 0) {
			m += p;
		}
		if (n<0) {
			n += p;
		}
	}
	for (int i = 0; i < p;i++) {
		if ((i*n)%p==(m%p)) {
			k = i;
			break;
		}
	}
	C.x = (k * k - A.x - B.x) % p;
	C.y = (k * (A.x - C.x) - A.y) % p;
	if (C.x<0) {
		C.x += p;
	}
	if (C.y<0) {
		C.y += p;
	}
	printf("A+B=(%d,%d)",C.x,C.y);
}
void simpleECC() {
	int a, b, p;
	Points* Set;
	printf("请分别输入椭圆曲线的a,b,p:");
	scanf("%d,%d,%d", &a, &b, &p);
	getchar();
	while (checknumber(p)) {
		printf("您输入的p不是素数，请重新输入p=");
		scanf("%d", &p);
		getchar();
		//goto P;
	}
	while (4 * a * a * a + 27 * b * b == 0) {
		printf("您输入的a，b不符合规范，请重新输入a,b：");
		scanf("%d,%d", &a, &b);
		getchar();
	}
	printf("椭圆曲线的式子为：");
	if ((a != 0) && (b != 0)) {
		if (a == 1) {
			printf("y^2=x^3+x+%d", b);
		}
		else {
			printf("y^2=x^3+%dx+%d", a, b);
		}
	}
	if ((a != 0) && (b == 0)) {
		if (a == 1) {
			printf("y^2=x^3+x");
		}
		else {
			printf("y^2=x^3+%dx", a);
		}
	}
	if ((a == 0) && (b != 0)) {
		printf("y^2=x^3+%d", b);
	}
	if ((a == 0) && (b == 0)) {
		printf("y^2=x^3");
	}
	printf("\n");
	Set=getPoint(a, b, p);
	printf("\n一共有%d组有限域上的点\n",Set->length);
	Point A, B;
	X:printf("请输入点A=");
	scanf("%d,%d",&A.x,&A.y);
	getchar();
	if (checkPoint(Set,A)) {
		printf("点A不存在于椭圆曲线集合上请重新输入！\n");
		goto X;
	}
	Y:printf("请输入点B=");
	scanf("%d,%d", &B.x, &B.y);
	getchar();
	if (checkPoint(Set, B)) {
		printf("点B不存在于椭圆曲线集合上请重新输入！\n");
		goto Y;
	}
	addition(A,B,a,p);
}
int main() {
	simpleECC();
}