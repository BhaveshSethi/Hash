/*****************************************************************
This program is developed by Bhavesh Sethi.
It is used to calculate HASH VALUES using algorithms:
	1. MD5
	2. Snefru
	3. SHA2
	4. RIPE-MD
These algorithms are freely available on internet.

This program is only for demonstration purposes.
A test file "test.txt" is used to show the working of Algorithms.
*******************************************************************/
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
	FILE *hFile;
	char str[64];
	int32 res[16];
	int i;

	switch(ch)
	{
		case '1':
			hFile = fopen("hashMD5.txt","wt");
		break;
		case '2':
			hFile = fopen("hashSHA2.txt","wt");
		break;
		case '3':
			hFile = fopen("hashSNEF.txt","wt");
		break;
		case '4':
			hFile = fopen("hashRIPE.txt","wt");
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
		<<"\n\t4. RIPE_MD\n\t5. ALL_HASH for a word\n\t6. Exit "
		<<"\n\tPress 1-6 to select ";
		ch = getch();

		if(ch == '5')
		{
			FILE *hFile1 = fopen("hash_MD5.txt","at");
			FILE *hFile2 = fopen("hash_SHA.txt","at");
			FILE *hFile3 = fopen("hash_SNE.txt","at");
			FILE *hFile4 = fopen("hash_RMD.txt","at");

			memset(str,0,64);
			cout<<"\n\n\tEnter Word ";
			cin>>str;
			cout<<"\n\tMD5 Hash: \n\t";MD5(str,res);
			fprintf(hFile1,"\n%10s: ",str);
			for(i=0;i<4;i++)
			{
				fprintf(hFile1,"%02x",((res[i])&0xff));
				fprintf(hFile1,"%02x",((res[i]>>8)&0xff));
				fprintf(hFile1,"%02x",((res[i]>>16)&0xff));
				fprintf(hFile1,"%02x ",((res[i]>>24)&0xff));
			}

			cout<<"\n\tSHA2 Hash: \n";SHA2(str,res);
			fprintf(hFile2,"\n%10s: ",str);
			for(i=0;i<8;i++)
				fprintf(hFile2,"%08lx ",res[i]);

			cout<<"\n\tSnefru Hash: \n\t";Snefru(str,res);
			fprintf(hFile3,"\n%10s: ",str);
			for(i=0;i<4;i++)
				fprintf(hFile3,"%08lx ",res[i]);

			cout<<"\n\tRIPE_MD Hash: \n\t";RIPE_MD(str,res);
			fprintf(hFile4,"\n%10s: ",str);
			for(i=0;i<5;i++)
			{
				fprintf(hFile4,"%02x",((res[i])&0xff));
				fprintf(hFile4,"%02x",((res[i]>>8)&0xff));
				fprintf(hFile4,"%02x",((res[i]>>16)&0xff));
				fprintf(hFile4,"%02x ",((res[i]>>24)&0xff));
			}

			fclose(hFile1);
			fclose(hFile2);
			fclose(hFile3);
			fclose(hFile4);
			continue;
		}

		if(ch>'0' && ch<'5')
			writeFile(ch);

	}while(ch!='6');

	//getch();
}