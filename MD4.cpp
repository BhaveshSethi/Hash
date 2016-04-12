//MD4 Hash
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>

#define F(X,Y,Z) ((X&Y) | ((0xffffffffL ^ X)&Z) )
#define G(X,Y,Z) ((X&Y) | (Y&Z) | (Z&X))
#define H(X,Y,Z) (X ^ Y ^ Z)

typedef unsigned long int int32;

#define R1(a,b,c,d,k,s,X) { \
	a += F(b,c,d) + X[k]; \
	a = rotateLeft(a,s);   \
}
#define R2(a,b,c,d,k,s,X) { \
	a += G(b,c,d) + X[k] + 0x5A827999; \
	a = rotateLeft(a,s); \
}
#define R3(a,b,c,d,k,s,X) { \
	a += H(b,c,d) + X[k] + 0x6ED9EBA1; \
	a = rotateLeft(a,s); \
}

int32 rotateLeft(int32 x, int shift)
{
	return (x<<shift | x>>(32-shift));
}

void main()
{
	clrscr();
	char str[100];
	int bitLength,byteLength,i=0,N=0,j;
	int32 ip[50];
	int32 X[16],AA,BB,CC,DD;
	int32 A = 0x01234567L,
	      B = 0x89abcdefL,
	      C = 0xfedcba98L,
	      D = 0x76543210L;

	memset(ip,0,200);
	//gets(str);
	strcpy(str,"");
	cout<<str<<" "<<(byteLength = strlen(str))<<endl;
	bitLength = 8*byteLength;

	while(byteLength%64 != 56)
	{
		if(!(i++))
			str[byteLength++] = (unsigned char)(128);
		else
			str[byteLength++] = (unsigned char)(0);
	}

	cout<<byteLength<<endl;

	for(i=0;i<byteLength;i+=4)
		ip[i/4] = (((int32)str[i] & 0xffL) << 24) |
			  (((int32)str[i + 1] & 0xffL) << 16) |
			  (((int32)str[i + 2] & 0xffL) << 8) |
			  (((int32)str[i + 3] & 0xffL));

	N = i/4;
	ip[N++] = 0;
	ip[N++] = (int32)(bitLength);


	for(i=0;i<N/16;i++)
	{
		for(j=0;j<16;j++)
			X[j] = ip[i*16 + j];
		AA = A;
		BB = B;
		CC = C;
		DD = D;

		R1(A,B,C,D,0,3,X);
		R1(D,A,B,C,1,7,X);
		R1(C,D,A,B,2,11,X);
		R1(B,C,D,A,3,19,X);
		R1(A,B,C,D,4,3,X);
		R1(D,A,B,C,5,7,X);
		R1(C,D,A,B,6,11,X);
		R1(B,C,D,A,7,19,X);
		R1(A,B,C,D,8,3,X);
		R1(D,A,B,C,9,7,X);
		R1(C,D,A,B,10,11,X);
		R1(B,C,D,A,11,19,X);
		R1(A,B,C,D,12,3,X);
		R1(D,A,B,C,13,7,X);
		R1(C,D,A,B,14,11,X);
		R1(B,C,D,A,15,19,X);

		R2(A,B,C,D,0,3,X);
		R2(D,A,B,C,4,5,X);
		R2(C,D,A,B,8,9,X);
		R2(B,C,D,A,12,13,X);
		R2(A,B,C,D,1,3,X);
		R2(D,A,B,C,5,5,X);
		R2(C,D,A,B,9,9,X);
		R2(B,C,D,A,13,13,X);
		R2(A,B,C,D,2,3,X);
		R2(D,A,B,C,6,5,X);
		R2(C,D,A,B,10,9,X);
		R2(B,C,D,A,14,13,X);
		R2(A,B,C,D,3,3,X);
		R2(D,A,B,C,7,5,X);
		R2(C,D,A,B,11,9,X);
		R2(B,C,D,A,15,13,X);

		R3(A,B,C,D,0,3,X);
		R3(D,A,B,C,8,9,X);
		R3(C,D,A,B,4,11,X);
		R3(B,C,D,A,12,15,X);
		R3(A,B,C,D,2,3,X);
		R3(D,A,B,C,10,9,X);
		R3(C,D,A,B,6,11,X);
		R3(B,C,D,A,14,15,X);
		R3(A,B,C,D,1,3,X);
		R3(D,A,B,C,9,9,X);
		R3(C,D,A,B,5,11,X);
		R3(B,C,D,A,13,15,X);
		R3(A,B,C,D,3,3,X);
		R3(D,A,B,C,11,9,X);
		R3(C,D,A,B,7,11,X);
		R3(B,C,D,A,15,15,X);

		A = A + AA;
		B = B + BB;
		C = C + CC;
		D = D + DD;

	}

	cout<<endl<<hex<<A<<" "<<B<<" "<<C<<" "<<D;

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