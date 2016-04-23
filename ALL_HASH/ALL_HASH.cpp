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