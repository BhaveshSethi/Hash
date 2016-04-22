//SHA2 Hash
#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<iomanip.h>


typedef unsigned long int int32;

int32 H[8] = { 0x6a09e667,
	       0xbb67ae85,
	       0x3c6ef372,
	       0xa54ff53a,
	       0x510e527f,
	       0x9b05688c,
	       0x1f83d9ab,
	       0x5be0cd19};

int32 k[64]={   0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
		0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
		0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
		0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
		0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
		0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
		0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
		0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
		0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2  };

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
void print(int32 P[], int i)
{
	cout<<endl;
	for(int j=0;j<i;j++)
		cout<<hex<<setw(8)<<setfill('0')<<P[j]<<" ";
}

int32 ROTR(int32 x, int shift)
{
	return (x>>shift | x<<(32-shift));
}

int32 ROTL(int32 x, int shift)
{
	return (x<<shift | x>>(32-shift));
}

int32 SHR(int32 x, int shift)
{
	return x>>shift;
}

void init(int32 w[64])
{

}


void main()
{
	clrscr();
	char str[64];
	int i,j,byteLength;
	int32 bitLength[2] = {0,0},w[64];

	cout<<"\n\tHashing Technique used SHA-2";

	memset(str,0,64);
	strcpy(str,"abc");
	increment(bitLength,8*(byteLength = strlen(str)));
	memset(w,0,256);

	cout<<"\n\t"<<str<<" "<<byteLength;
	str[byteLength] = (unsigned char)0x80;

	for(i=0;i<56;i+=4)
		w[i/4] = (((int32)str[i] & 0xffL) << 24) |
			  (((int32)str[i + 1] & 0xffL) << 16) |
			  (((int32)str[i + 2] & 0xffL) << 8) |
			  (((int32)str[i + 3] & 0xffL));

	w[14] = (int32)bitLength[0];
	w[15] = (int32)bitLength[1];

	init(w);

	print(w,16);
	getch();
}