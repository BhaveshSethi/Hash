//Snefru Hash
#include<snefru.h>
#include<iostream.h>
#include<conio.h>
#include<iomanip.h>

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
void main()
{
	clrscr();
//	cout<<sizeof(unsigned long int);
//	int32 a = 5;
//	cout<<rotate(a,32);
	int32 ip[16],op[16];
	int i;
	memset(ip,0,64);
	hash512(op,ip,8);
	for(i=0;i<4;i++)
		cout<<hex<<(unsigned long int)op[i]<<" ";
	hash512(ip,op,8);
	cout<<"\n";
	for(i=0;i<4;i++)
		cout<<hex<<(unsigned long int)ip[i]<<" ";
	getch();
}
