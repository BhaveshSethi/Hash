//MD4 Hash
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>

#define A 0x01234567L
#define B 0x89abcdefL
#define C 0xfedcba98L
#define D 0x76543210L

#define F(X,Y,Z) ((X&Y) | ((0xffffffffL ^ X)&Z) )
#define G(X,Y,Z) ((X&Y) | (Y&Z) | (Z&X))
#define H(X,Y,Z) (X ^ Y ^ Z)

typedef unsigned long int int32;


void main()
{
	clrscr();
	char str[100];
	int bitLength,byteLength,i=0,N=0;
	int32 ip[50];

	memset(ip,0,200);

	//gets(str);
	strcpy(str,"lol");
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