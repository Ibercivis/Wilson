/*
 * =====================================================================================
 *
 *       Filename:  wilson.c
 *
 *    Description:  Búsqueda de números de Wilson.
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


	/* Abrimos ficheros de entrada y de salida */
	fi=fopen("numbers","r");
	if(fi==NULL)
	{
		printf("Error en la apertura de numbers\n");
		exit(-1);
	}
	fo=fopen("output","a+");
	if(fo==NULL)
	{
		printf("Error en la apertura de output\n");
		exit(-1);
	}

	/* Nos vamos al principio de fo */
	fseek(fo,0L, SEEK_SET);


	/* Leemos el fichero para ver si ya hemos realizado algún primo de la lista */
	while (fgets (buff, LINESZ, fi)) {
		if(fgets(buff2, LINESZ,fo))
		{
			/* Hemos podido leer la línea del fichero de salida */
			sscanf(buff,"%lld",&primo);
			sscanf(buff2,"%lld",&compr);
			if(primo!=compr)
			{
				printf("Ambos deberían coincidir\n");
				exit(-555);
			}
		}
		else
		{
			/*No hemos podido leer la línea del fichero de salida, hacemos los cálculos */
			sscanf(buff,"%lld",&primo);
			printf("Haciendo cálculos para el primo %lld\n", primo);
			mu=get_representacion(1,primo);
			for(i=2;i<=primo-1;i++)
			{
				mu=mul(mu,get_representacion(i,primo),primo);
			}
			/* Escribimos en el fichero de salida */
			/* El primo, su cuadrado y el módulo */
			/* Si es número Wilson, el módulo vale 0 */
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




