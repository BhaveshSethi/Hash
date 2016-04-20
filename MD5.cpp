//MD4 Hash
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>

#define F(X,Y,Z) ((X&Y) | ((0xffffffffL ^ X)&Z) )
#define G(X,Y,Z) ((X&Z) | ((0xffffffffL ^ Z)&Y) )
#define H(X,Y,Z) (X ^ Y ^ Z)
#define I(X,Y,Z) (Y ^ ((0xffffffffL ^ Z) | X))

typedef unsigned long int int32;

int32 T[64] = {	0xd76aa478L,0xe8c7b756L,0x242070dbL,0xc1bdceeeL,
		0xf57c0fafL,0x4787c62aL,0xa8304613L,0xfd469501L,
		0x698098d8L,0x8b44f7afL,0xffff5bb1L,0x895cd7beL,
		0x6b901122L,0xfd987193L,0xa679438eL,0x49b40821L,

		0xf61e2562L,0xc040b340L,0x265e5a51L,0xe9b6c7aaL,
		0xd62f105dL,0x2441453L,0xd8a1e681L,0xe7d3fbc8L,
		0x21e1cde6L,0xc33707d6L,0xf4d50d87L,0x455a14edL,
		0xa9e3e905L,0xfcefa3f8L,0x676f02d9L,0x8d2a4c8aL,

		0xfffa3942L,0x8771f681L,0x6d9d6122L,0xfde5380cL,
		0xa4beea44L,0x4bdecfa9L,0xf6bb4b60L,0xbebfbc70L,
		0x289b7ec6L,0xeaa127faL,0xd4ef3085L,0x4881d05L,
		0xd9d4d039L,0xe6db99e5L,0x1fa27cf8L,0xc4ac5665L,

		0xf4292244L,0x432aff97L,0xab9423a7L,0xfc93a039L,
		0x655b59c3L,0x8f0ccc92L,0xffeff47dL,0x85845dd1L,
		0x6fa87e4fL,0xfe2ce6e0L,0xa3014314L,0x4e0811a1L,
		0xf7537e82L,0xbd3af235L,0x2ad7d2bbL,0xeb86d391L};


int32 rotateLeft(int32 x, int shift)
{
	return (x<<shift | x>>(32-shift));
}

void R1(int32 &a,int32 b,int32 c,int32 d,int k,int s,int32 X[],int i) {
	a += F(b,c,d) + X[k] + T[i];
	a = b + rotateLeft(a,s);
}
void R2(int32 &a,int32 b,int32 c,int32 d,int k,int s,int32 X[],int i) {
	a += G(b,c,d) + X[k] + T[i];
	a = b + rotateLeft(a,s);
}
void R3(int32 &a,int32 b,int32 c,int32 d,int k,int s,int32 X[],int i) {
	a += H(b,c,d) + X[k] + T[i];
	a = b + rotateLeft(a,s);
}

void R4(int32 &a,int32 b,int32 c,int32 d,int k,int s,int32 X[],int i) {
	a += I(b,c,d) + X[k] + T[i];
	a = b + rotateLeft(a,s);
}

void main()
{
	clrscr();
	char str[100];
	int bitLength,byteLength,i=0,N=0,j;
	int32 ip[50];
	int32 X[16],AA,BB,CC,DD;
	int32 A = 0x67452301L,
	      B = 0xefcdab89L,
	      C = 0x98badcfeL,
	      D = 0x10325476L;

	cout<<"\n\tHashing Technique used MD5";
	cout<<"\n\tEnter String to Hash ";
	memset(ip,0,200);
	//gets(str);
	strcpy(str,"a");
	byteLength = strlen(str);
	cout<<str<<" "<<byteLength<<endl;
	bitLength = 8*byteLength;

	while(byteLength%64 != 56)
	{
		if(!(i++))
			str[byteLength++] = (unsigned char)(128);
		else
			str[byteLength++] = (unsigned char)(0);
	}

	//cout<<byteLength<<endl;

	for(i=0;i<byteLength;i+=4)
		ip[i/4] = (((int32)str[i] & 0xffL) << 24) |
			  (((int32)str[i + 1] & 0xffL) << 16) |
			  (((int32)str[i + 2] & 0xffL) << 8) |
			  (((int32)str[i + 3] & 0xffL));

	N = i/4;
	ip[N++] = 0;
	ip[N++] = (int32)(bitLength);

	for(i=0;i<N;i++)
	cout<<hex<<ip[i]<<" ";

	/*AA=A;
	R1(A,B,C,D,0,0,X);
	cout<<endl<<A;
	AA += F(B,C,D) + X[1];
	cout<<endl<<AA<<" "<<F(B,C,D);
	*/
	for(i=0;i<N/16;i++)
	{
		for(j=0;j<16;j++)
			X[j] = ip[i*16 + j];

		AA = A;
		BB = B;
		CC = C;
		DD = D;

		R1(A,B,C,D, 0, 7,X, 0);
		R1(D,A,B,C, 1,12,X, 1);
		R1(C,D,A,B, 2,17,X, 2);
		R1(B,C,D,A, 3,22,X, 3);
		R1(A,B,C,D, 4, 7,X, 4);
		R1(D,A,B,C, 5,12,X, 5);
		R1(C,D,A,B, 6,17,X, 6);
		R1(B,C,D,A, 7,22,X, 7);
		R1(A,B,C,D, 8, 7,X, 8);
		R1(D,A,B,C, 9,12,X, 9);
		R1(C,D,A,B,10,17,X,10);
		R1(B,C,D,A,11,22,X,11);
		R1(A,B,C,D,12, 7,X,12);
		R1(D,A,B,C,13,12,X,13);
		R1(C,D,A,B,14,17,X,14);
		R1(B,C,D,A,15,22,X,15);

		R2(A,B,C,D, 1, 5,X,16);
		R2(D,A,B,C, 6, 9,X,17);
		R2(C,D,A,B,11,14,X,18);
		R2(B,C,D,A, 0,20,X,19);
		R2(A,B,C,D, 5, 5,X,20);
		R2(D,A,B,C,10, 9,X,21);
		R2(C,D,A,B,15,14,X,22);
		R2(B,C,D,A, 4,20,X,23);
		R2(A,B,C,D, 9, 5,X,24);
		R2(D,A,B,C,14, 9,X,25);
		R2(C,D,A,B, 3,14,X,26);
		R2(B,C,D,A, 8,20,X,27);
		R2(A,B,C,D,13, 5,X,28);
		R2(D,A,B,C, 2, 9,X,29);
		R2(C,D,A,B, 7,14,X,30);
		R2(B,C,D,A,12,20,X,31);

		R3(A,B,C,D, 5, 4,X,32);
		R3(D,A,B,C, 8,11,X,33);
		R3(C,D,A,B,11,16,X,34);
		R3(B,C,D,A,14,23,X,35);
		R3(A,B,C,D, 1, 4,X,36);
		R3(D,A,B,C, 4,11,X,37);
		R3(C,D,A,B, 7,16,X,38);
		R3(B,C,D,A,10,23,X,39);
		R3(A,B,C,D,13, 4,X,40);
		R3(D,A,B,C, 0,11,X,41);
		R3(C,D,A,B, 3,16,X,42);
		R3(B,C,D,A, 6,23,X,43);
		R3(A,B,C,D, 9, 4,X,44);
		R3(D,A,B,C,12,11,X,45);
		R3(C,D,A,B,15,16,X,46);
		R3(B,C,D,A, 2,23,X,47);

		R4(A,B,C,D, 0, 6,X,48);
		R4(D,A,B,C, 7,10,X,49);
		R4(C,D,A,B,14,15,X,50);
		R4(B,C,D,A, 5,21,X,51);
		R4(A,B,C,D,12, 6,X,52);
		R4(D,A,B,C, 3,10,X,53);
		R4(C,D,A,B,10,15,X,54);
		R4(B,C,D,A, 1,21,X,55);
		R4(A,B,C,D, 8, 6,X,56);
		R4(D,A,B,C,15,10,X,57);
		R4(C,D,A,B, 6,15,X,58);
		R4(B,C,D,A,13,21,X,59);
		R4(A,B,C,D, 4, 6,X,60);
		R4(D,A,B,C,11,10,X,61);
		R4(C,D,A,B, 2,15,X,62);
		R4(B,C,D,A, 9,21,X,63);

		A = A + AA;
		B = B + BB;
		C = C + CC;
		D = D + DD;

	}

	cout<<endl<<"Hash generated: "<<hex<<A<<" "<<B<<" "<<C<<" "<<D;

	/*
	for(i=0;i<N;i++)
		cout<<hex<<ip[i]<<" ";
	*/
	/*
	int32 X=0x00101001L,Y=0x01101010L,Z=0x01011010L;
	cout<<hex<<H(X,Y,Z)<<endl;
	cout<<hex<<(X&Y)<<" "<<(Y&Z)<<" "<<(Z&X);
	*/
	getch();
}