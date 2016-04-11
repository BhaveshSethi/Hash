//Snefru Hash
#include<snefru.h>
#include<iostream.h>
#include<conio.h>
#include<iomanip.h>
#include<stdio.h>

#define blockSize 512

int rotateSchedule[4] = {16,8,16,24};

int32 rotate(int32 x, int shift)
{
	return (x>>shift | x<<(32-shift));
}

void E512(int32 x[16], int passes)
{
	int idx,byteInWord,i,next,last;      	//Assumption bytes in a word are 4
	int32 SBE;
	for(idx=0;idx<passes;idx++)
	{
		/*
		cout<<endl<<idx;
		for(i=0;i<4;i++)
			cout<<setw(8)<<hex<<" "<<(int32)x[i];
		*/
		for(byteInWord = 0; byteInWord<4; byteInWord++)
		{
			for(i=0; i<16; i++)
			{
				next = (i+1)%16;
				last = (i+15)%16;
				SBE = standardSBoxes[2*idx + ((i/2)%2)][(x[i] & 0xffL)];
				x[next] = x[next]^SBE;
				x[last] = x[last]^SBE;
			}
			for(i=0; i<16; i++)
				x[i] = rotate(x[i],rotateSchedule[byteInWord]);
		}
	}
}

void hash512(int32 res[16], int32 x[16], int passes)
{
	int i;
	int32 block[16];
	for(i=0;i<16;i++)
		block[i]=x[i];
	memset(res,0,64);
	E512(x,passes);
	for(i=0; i<4; i++)
		res[i] = block[i] ^ x[15-i];
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

void main()
{
	clrscr();
//	cout<<sizeof(unsigned long int);
//	int32 a = 5;
//	cout<<rotate(a,32);
	int32 ip[16],op[16],bitLength[2] = {0,0};
	char str[48],ch;
	int i,flag=1;

	for(i=0; i<4; i++)
		op[i] = 0;

	FILE *xFile;
	xFile = fopen("test.txt","rb");

	while(flag)
	{
		ch=fgetc(xFile);
		i = 0;
		while(ch!=EOF)
		{
			str[i++]=ch;
			//cout<<ch;
			if(i==48)
				break;
			ch=fgetc(xFile);
		}

		increment(bitLength,8*i);

		if(i==0)
			break;
		else if(i<48)
		{
			flag=0;
			for(;i<48;i++)
				str[i]=0;
		}

		for(i=0;i<4;i++)
			ip[i] = op[i];
		for(i=0;i<12;i++)
			ip[i+4] = (((int32)str[4*i] & 0xffL) << 24) |
				  (((int32)str[4*i + 1] & 0xffL) << 16) |
				  (((int32)str[4*i + 2] & 0xffL) << 8) |
				  (((int32)str[4*i + 3] & 0xffL));
		/*
		for(i=0;i<16;i++)
			cout<<hex<<ip[i]<<" ";
		*/

		hash512(op,ip,8);

		/*
		for(i=0;i<16;i++)
			cout<<hex<<op[i]<<" ";
		*/
	}
	fclose(xFile);

	for(i=0;i<16;i++)
		ip[i] = op[i];

	ip[14] = bitLength[0];
	ip[15] = bitLength[1];

	hash512(op,ip,8);

	/*
	memset(ip,0,64);
	do
	{
		size = scanf;
		cout<<endl<<str<<endl;
	}while(size>0);
	hash512(op,ip,8);
	for(i=0;i<4;i++)
		cout<<hex<<(unsigned long int)op[i]<<" ";
	hash512(ip,op,8);
	cout<<"\n";
	*/
	for(i=0;i<4;i++)
		cout<<hex<<(unsigned long int)op[i]<<" ";
	getch();
}
