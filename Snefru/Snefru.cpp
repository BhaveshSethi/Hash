//Snefru Hash
#include<snefru.h>
#include<iostream.h>
#include<conio.h>

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
	for(idx=1;idx<=passes;idx++)
	{
		for(byteInWord = 1; byteInWord<=4; byteInWord++)
		{
			for(i=0; i<16; i++)
			{
				next = (i+1)%16;
				last = (i-1)%16;
				SBE = standardSBoxes[2*idx + ((i/2)%2) -1][(x[i]^0xff)];
				x[next] = x[next]^SBE;
				x[last] = x[last]^SBE;
			}
			for(i=0; i<16; i++)
				x[i] = rotate(x[i],rotateSchedule[byteInWord]);
		}
	}
	int32 res[16];
	for(i=0; i<16; i++)
		res[i] = x[15-i];
	x=res;
}
void main()
{
	clrscr();
//	cout<<sizeof(unsigned long int);
//	int32 a = 5;
//	cout<<rotate(a,32);
	getch();
}
