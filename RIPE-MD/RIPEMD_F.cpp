//RIPE-MD Hash
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<iomanip.h>

typedef unsigned long int int32;

int32 f(int i, int32 x, int32 y, int32 z)
{
	if(i<16)
		return (x^y^z);
	else if(i<32)
		return ((x&y) | ((~x) & z));
	else if(i<48)
		return ((x | (~y)) ^ z);
	else if(i<64)
		return ((x&z) | ((~z) & y));
	else
		return ((y | (~z)) ^ x);
}

int32 K[2][5] =
{{ 0x00000000,0x5a827999,0x6ed9eba1,0x8f1bbcdc,0xa953fd4e },
 { 0x50a28be6,0x5c4dd124,0x6d703ef3,0x7a6d76e9,0x00000000 }};

int r[2][80] = {{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
		  7, 4, 13, 1, 10, 6, 15, 3, 12, 0, 9, 5, 2, 14, 11, 8,
		  3, 10, 14, 4, 9, 15, 8, 1, 2, 7, 0, 6, 13, 11, 5, 12,
		  1, 9, 11, 10, 0, 8, 12, 4, 13, 3, 7, 15, 14, 5, 6, 2,
		  4, 0, 5, 9, 7, 12, 2, 10, 14, 1, 3, 8, 11, 6, 15, 13 },
		{ 5, 14, 7, 0, 9, 2, 11, 4, 13, 6, 15, 8, 1, 10, 3, 12,
		  6, 11, 3, 7, 0, 13, 5, 10, 14, 15, 8, 12, 4, 9, 1, 2,
		  15, 5, 1, 3, 7, 14, 6, 9, 11, 8, 12, 2, 10, 0, 4, 13,
		  8, 6, 4, 1, 3, 11, 15, 0, 5, 12, 2, 13, 9, 7, 10, 14,
		  12, 15, 10, 4, 1, 5, 8, 7, 6, 2, 13, 14, 0, 3, 9, 11 }};

int s[2][80] = {{ 11, 14, 15, 12, 5, 8, 7, 9, 11, 13, 14, 15, 6, 7, 9, 8,
		  7, 6, 8, 13, 11, 9, 7, 15, 7, 12, 15, 9, 11, 7, 13, 12,
		  11, 13, 6, 7, 14, 9, 13, 15, 14, 8, 13, 6, 5, 12, 7, 5,
		  11, 12, 14, 15, 14, 15, 9, 8, 9, 14, 5, 6, 8, 6, 5, 12,
		  9, 15, 5, 11, 6, 8, 13, 12, 5, 12, 13, 14, 11, 8, 5, 6 },
		{ 8, 9, 9, 11, 13, 15, 15, 5, 7, 7, 8, 11, 14, 14, 12, 6,
		  9, 13, 15, 7, 12, 8, 9, 11, 7, 7, 12, 7, 6, 15, 13, 11,
		  9, 7, 15, 11, 8, 6, 6, 14, 12, 13, 5, 14, 13, 13, 7, 5,
		  15, 5, 8, 11, 14, 14, 6, 14, 6, 9, 12, 9, 12, 5, 15, 8,
		  8, 5, 12, 9, 12, 5, 14, 6, 8, 13, 6, 5, 15, 13, 11, 11 }};

void print(int32 P[], int i)
{
	cout<<endl;
	for(int j=0;j<i;j++)
		cout<<hex<<setw(8)<<setfill('0')<<P[j]<<" ";
}

void printLE(int32 P[], int i)
{
	cout<<endl;
	for(int j=0;j<i;j++)
		cout<<hex<<setfill('0')<<setw(2)<<(P[j]&0xff)
					  <<setw(2)<<((P[j]>> 8)&0xff)
					  <<setw(2)<<((P[j]>>16)&0xff)
					  <<setw(2)<<((P[j]>>24)&0xff)<<" ";
}

void increment(int32 bitLength[2], int increment)
{
	if(bitLength[1] + increment > 0xffffffffL)
	{
		bitLength[0]++;
		bitLength[1] = increment + bitLength[1] - 0xffffffffL;
	}
	else
		bitLength[1]+=increment;
}

void write(FILE *h, int32 A)
{
	fprintf(h,"%02x",((A)&0xff));
	fprintf(h,"%02x",((A>>8)&0xff));
	fprintf(h,"%02x",((A>>16)&0xff));
	fprintf(h,"%02x ",((A>>24)&0xff));
}

int32 ROTL(int32 x, int shift)
{
	return (x<<shift | x>>(32-shift));
}

void main()
{
	clrscr();

	char str[64];
	int32 X[16], bitLength[2],A[2][5],T;
	int i,j,byteLength;

	cout<<"\n\tHashing Algorithm used RIPE-MD 160";

	fstream fin("test.txt",ios::binary|ios::in);
	FILE *hFile = fopen("hash.txt","wt");

	while(!fin.eof())
	{

		memset(str,0,64);
		memset(X,0,64);
		//strcpy(str,"message digest");
		fin>>str;
		bitLength[0] = bitLength[1] = 0;
		increment(bitLength,8*(byteLength = strlen(str)));

		//cout<<"\n\tInput String: "<<str<<" of length "<<byteLength;
		str[byteLength] = (unsigned char)0x80;

		for(i=0;i<56;i+=4)
			X[i/4] = (((int32)str[i] & 0xffL)) |
				 (((int32)str[i + 1] & 0xffL) << 8) |
				 (((int32)str[i + 2] & 0xffL) << 16) |
				 (((int32)str[i + 3] & 0xffL) << 24);

		X[15] = bitLength[0];
		X[14] = bitLength[1];
		//print(X,16);

		int32 h[5] =
		{ 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0 };

		for(i=0;i<5;i++)
			A[0][i] = A[1][i] = h[i];

		for(j=0;j<80;j++)
		{
			T = A[0][0] + f(j,A[0][1],A[0][2],A[0][3]) + X[r[0][j]] + K[0][j/16];
			T = ROTL(T,s[0][j]) + A[0][4];
			A[0][0] = A[0][4];
			A[0][4] = A[0][3];
			A[0][3] = ROTL(A[0][2],10);
			A[0][2] = A[0][1];
			A[0][1] = T;

			T = A[1][0] + f(79-j,A[1][1],A[1][2],A[1][3]) + X[r[1][j]] + K[1][j/16];
			T = ROTL(T,s[1][j]) + A[1][4];
			A[1][0] = A[1][4];
			A[1][4] = A[1][3];
			A[1][3] = ROTL(A[1][2],10);
			A[1][2] = A[1][1];
			A[1][1] = T;
		}

		T = h[1] + A[0][2] + A[1][3];
		h[1] = h[2] + A[0][3] + A[1][4];
		h[2] = h[3] + A[0][4] + A[1][0];
		h[3] = h[4] + A[0][0] + A[1][1];
		h[4] = h[0] + A[0][1] + A[1][2];
		h[0] = T;

		cout<<"\n\t"<<str<<": ";
		printLE(h,5);
		fprintf(hFile,"\n%10s: ",str);
		for(j=0;j<5;j++)
			write(hFile,h[j]);

	}
	fin.close();
	fclose(hFile);
	getch();
}