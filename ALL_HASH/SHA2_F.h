//SHA2 Hash

typedef unsigned long int int32;


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

int32 Ch(int32 x, int32 y, int32 z)
{
	return ((x&y)^(~(x)&z));
}

int32 Maj(int32 x, int32 y, int32 z)
{
	return ((x&y) ^ (y&z) ^ (z&x));
}

void init(int32 w[64])
{
	int32 s0,s1;
	for(int i=16;i<64;i++)
	{
		s0 = ROTR(w[i-15],7) ^ ROTR(w[i-15],18) ^ SHR(w[i-15],3);
		s1 = ROTR(w[i-2],17) ^ ROTR(w[i-2],19) ^ SHR(w[i-2],10);
		w[i] = w[i-16] + s0 + w[i-7] + s1;
	}
}

void SHA2(char word[64], int32 res[16])
{
	char str[64];
	int32 bitLength[2] = {0,0};
	int  byteLength,i,j;
	int32 w[64],a[8],T1,T0,S1,S0,hash[8] = { 0x6a09e667,0xbb67ae85,
						 0x3c6ef372,0xa54ff53a,
						 0x510e527f,0x9b05688c,
						 0x1f83d9ab,0x5be0cd19};

	memset(str,0,64);
	strcpy(str,word);
	increment(bitLength,8*(byteLength = strlen(str)));
	memset(w,0,256);

	//cout<<"\n\tInput String: "<<str<<" of length "<<byteLength;
	str[byteLength] = (unsigned char)0x80;

	for(i=0;i<56;i+=4)
		w[i/4] = (((int32)str[i] & 0xffL) << 24) |
			  (((int32)str[i + 1] & 0xffL) << 16) |
			  (((int32)str[i + 2] & 0xffL) << 8) |
			  (((int32)str[i + 3] & 0xffL));

	w[14] = (int32)bitLength[0];
	w[15] = (int32)bitLength[1];

	init(w);

	//print(w,16);

	for(i=0;i<8;i++)
		a[i] = hash[i];

	for(i=0;i<64;i++)
	{
		S1 = ROTR(a[4],6) ^ ROTR(a[4],11) ^ ROTR(a[4],25);
		T1 = S1 + a[7] + Ch(a[4],a[5],a[6]) + k[i] + w[i];

		S0 = ROTR(a[0],2) ^ ROTR(a[0],13) ^ ROTR(a[0],22);
		T0 = S0 + Maj(a[0],a[1],a[2]);

		S0 = a[7];
		for(j=7;j>0;j--)
		{
			a[j] = a[j-1];
		}

		a[4] += T1;
		a[0] = T1 + T0;
	}

	for(i=0;i<8;i++)
		hash[i] += a[i];

	//cout<<"\n\tHash generated :";
	print(hash,8);
	for(i=0;i<8;i++)
		res[i] = hash[i];
}