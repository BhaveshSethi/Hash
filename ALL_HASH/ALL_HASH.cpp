//ALL HASH
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<iomanip.h>

#include<snefru.h>
#include<MD5_FILE.h>
#include<SNEFRU_F.h>
#include<SHA2_F.h>
#include<RIPEMD_F.h>

void RIPE_MD(char word[64])
{
	char str[64];
	int32 X[16], bitLength[2],A[2][5],T;
	int i,j,byteLength;

	memset(str,0,64);
	memset(X,0,64);
	strcpy(str,word);
	bitLength[0] = bitLength[1] = 0;
	increment(bitLength,8*(byteLength = strlen(str)));

	str[byteLength] = (unsigned char)0x80;

	for(i=0;i<56;i+=4)
		X[i/4] = (((int32)str[i] & 0xffL)) |
			 (((int32)str[i + 1] & 0xffL) << 8) |
			 (((int32)str[i + 2] & 0xffL) << 16) |
			 (((int32)str[i + 3] & 0xffL) << 24);

	X[15] = bitLength[0];
	X[14] = bitLength[1];
	//print(X,16);

	int32 hash[5] =
	{ 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0 };

	for(i=0;i<5;i++)
		A[0][i] = A[1][i] = hash[i];

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

	T = hash[1] + A[0][2] + A[1][3];
	hash[1] = hash[2] + A[0][3] + A[1][4];
	hash[2] = hash[3] + A[0][4] + A[1][0];
	hash[3] = hash[4] + A[0][0] + A[1][1];
	hash[4] = hash[0] + A[0][1] + A[1][2];
	hash[0] = T;

	printLE(hash,5);

}

void main()
{
	clrscr();

	char ch,str[64];

	cout<<"\n\tALL_HASH";

	do
	{
		cout<<"\n\n\t>>>Select<<<\n\t1. MD5\n\t2. SHA2\n\t3. SNEFRU"
		<<"\n\t4. RIPE_MD\n\t5. ALL_HASH for a word\n\t6. Exit ";
		ch = getch();

		if(ch == '5')
		{
			memset(str,0,64);
			cout<<"\n\n\tEnter Word ";
			cin>>str;
			cout<<"\n\tMD5 Hash: \n\t";MD5(str);
			cout<<"\n\tSHA2 Hash: \n\t";SHA2(str);
			cout<<"\tSnefru HAsh: \n\t";Snefru(str);
			cout<<"\n\tRIPE_MD Hash: \n\t";RIPE_MD(str);
			continue;
		}

		switch(ch)
		{
			case '1':

			break;
			case '2':

			break;
			case '3':

			break;
			case '4':

			break;
			default:
				cout<<"\n\tEnter Again ";
		}
	}while(ch!='6');

	//getch();
}