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

void writeFile(char ch)
{

	fstream fin("test.txt",ios::in|ios::binary);
	FILE *hFile = fopen("all-hash.txt","wt");
	fprintf(hFile,"ALL HASH: Hashing Technique used: ");
	char str[64];
	int32 res[16];
	int i;

	switch(ch)
	{
		case '1':
			fprintf(hFile,"MD5");
		break;
		case '2':
			fprintf(hFile,"SHA2");
		break;
		case '3':
			fprintf(hFile,"Snefru");
		break;
		case '4':
			fprintf(hFile,"RIPE_MD");
		break;
	}
	while(!fin.eof())
	{
		fin>>str;
		cout<<"\n\t"<<setw(10)<<setfill(' ')<<str<<": ";
		fprintf(hFile,"\n%10s: ",str);
		switch(ch)
		{
			case '1':
				MD5(str,res);
				for(i=0;i<4;i++)
				{
					fprintf(hFile,"%02x",((res[i])&0xff));
					fprintf(hFile,"%02x",((res[i]>>8)&0xff));
					fprintf(hFile,"%02x",((res[i]>>16)&0xff));
					fprintf(hFile,"%02x ",((res[i]>>24)&0xff));
				}
			break;
			case '2':
				cout<<endl;
				SHA2(str,res);
				for(i=0;i<8;i++)
					fprintf(hFile,"%08lx ",res[i]);
			break;
			case '3':
				Snefru(str,res);
				for(i=0;i<4;i++)
					fprintf(hFile,"%08lx ",res[i]);

			break;
			case '4':
				RIPE_MD(str,res);
				for(i=0;i<5;i++)
				{
					fprintf(hFile,"%02x",((res[i])&0xff));
					fprintf(hFile,"%02x",((res[i]>>8)&0xff));
					fprintf(hFile,"%02x",((res[i]>>16)&0xff));
					fprintf(hFile,"%02x ",((res[i]>>24)&0xff));
				}
			break;
		}
	}
	fin.close();
	fclose(hFile);
}

void main()
	{
	clrscr();

	char ch,str[64];
	int32 res[16];
	int i;

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
			cout<<"\n\tMD5 Hash: \n\t";MD5(str,res);
			cout<<"\n\tSHA2 Hash: \n";SHA2(str,res);
			cout<<"\n\tSnefru Hash: \n\t";Snefru(str,res);
			cout<<"\n\tRIPE_MD Hash: \n\t";RIPE_MD(str,res);
			continue;
		}

		if(ch>'0' && ch<'5')
			writeFile(ch);

	}while(ch!='6');

	//getch();
}