/*
 * =====================================================================================
 *
 *       Filename:  wilson.c
 *
 *    Description:  Wilson prime search.
 *
 *        Version:  2.0
 *        Created:  15/11/10 17:19:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Francisco Sanz (Fs), frasanz@bifi.es
 *        Company:  BIFI, Universidad de Zaragoza
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "wilson.h"
#define LINESZ 256

int main()
{
	FILE * fi;
	FILE * fo;
	u64 primo;
	u64 compr;
	representacion mu;
	char buff[LINESZ];
	char buff2[LINESZ];
	int i;


	/* Open input and output files */
	fi=fopen("numbers","r");
	if(fi==NULL)
	{
		printf("Error opening numbers.\n");
		exit(-1);
	}
	fo=fopen("output","a+");
	if(fo==NULL)
	{
		printf("Error opening output\n");
		exit(-1);
	}

	/* To the begining of fo */
	fseek(fo,0L, SEEK_SET);


	/* We read fi and fo to check if some number is done.*/
	while (fgets (buff, LINESZ, fi)) {
		if(fgets(buff2, LINESZ,fo))
		{
			/*We can read*/
			sscanf(buff,"%lld",&primo);
			sscanf(buff2,"%lld",&compr);
			if(primo!=compr)
			{
				printf("Both numbers must be the same\n");
				exit(-555);
			}
		}
		else
		{
			/* We start with the calculation*/
			sscanf(buff,"%lld",&primo);
			printf("Doing the test to the prime:%lld\n", primo);
			mu=get_representacion(1,primo);
			for(i=2;i<=primo-1;i++)
			{
				mu=mul(mu,get_representacion(i,primo),primo);
			}
			/* We write in the output file */
			/* the prime, the prime² and the module*/
			/* If it is a wilson prime, the module must equals 0*/
			fprintf(fo,"%lld %lld %lld \n",primo, primo*primo, (mu.r1*primo+mu.r2+1)%(primo*primo));
		}
	}
	fclose(fi);
	fclose(fo);
	return 0;
}

representacion get_representacion(u64 a, u64 p)
{
	representacion re;
	re.r1=a/p;
	re.r2=a%p;
	return re;
}

representacion mul(representacion a, representacion b, u64 p)
{
	representacion mul;
	mul.r2=(a.r2*b.r2)%p;
	mul.r1=(a.r2*b.r2)/p;
	mul.r1=(mul.r1+a.r1*b.r2+b.r1*a.r2)%p;
	return mul;
}




