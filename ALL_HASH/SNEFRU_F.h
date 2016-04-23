//Snefru Hash

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
	E512(block,passes);
	for(i=0; i<4; i++)
		res[i] = x[i] ^ block[15-i];
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

void convert(char* str, int32 i, int32 ip[16])
{
	for(int32 j=0;j<48;j+=4)
	{
		ip[4 + j/4] = (((int32)str[i + j] & 0xffL) << 24) |
			      (((int32)str[i + j + 1] & 0xffL) << 16) |
			      (((int32)str[i + j + 2] & 0xffL) << 8) |
			      (((int32)str[i + j + 3] & 0xffL));
	}
}
void print(int32 P[], int i)
{
	for(int j=0;j<i;j++)
		cout<<hex<<setw(8)<<setfill('0')<<P[j]<<" ";
}

void Snefru(char word[64], int32 res[])
{
	int32 bitLength[2] = {0,0},ip[16],op[16];
	int i;
	char str[64];

	memset(str,0,64);
	strcpy(str,word);
	increment(bitLength,8*strlen(str));
	memset(ip,0,64);
	memset(op,0,64);

	for(int counter=0; (counter+48) <= (bitLength[1]/8); counter+=48)
	{
		convert(str,counter,ip);
		//print(ip,16);
		hash512(op,ip,8);

		for(i=0;i<4;i++)
			ip[i] = op[i];
	}

	if(counter*8 < bitLength[1])
	{
		counter += (bitLength[1]/8);
		while(counter%48!=0)
			str[counter++] = 0;
		convert(str,(counter-48),ip);
		//print(ip,16);
		hash512(op,ip,8);

		for(i=0;i<4;i++)
			ip[i] = op[i];
	}

	ip[14] = bitLength[0];
	ip[15] = bitLength[1];
	//print(ip,16);
	hash512(op,ip,8);
	print(op,4);
	for(i=0;i<4;i++)
		res[i] = op[i];
}