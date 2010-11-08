/*
 * =====================================================================================
 *
 *       Filename:  wilson.c
 *
 *    Description:  Búsqueda de números de Wilson.
 *
 *        Version:  1.0
 *        Created:  08/11/10 15:18:39
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
#include <gmp.h>

/* Devuelve 1 si es primo de Wilson */
int main(int argc, char * argv[])
{
	
	const char *uso=
		"\nUso: %s [Número primo]\n\n";
	if((argc>1) && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) {
		printf (uso, argv[0]);
		exit(1);
	}

	/* Definimos e inicializamos */
	unsigned long primo;

	mpz_t p;
	mpz_t primo_cuadrado;
	mpz_t n_grande;

	mpz_init(p);
	mpz_init(primo_cuadrado);
	mpz_init(n_grande);

	/* Escaneamos el número elegido */
	if(argc>1)
		primo=atol(argv[1]);
	else
		primo=563;


	/* Miramos en primer lugar si es primo */
	mpz_set_ui(p,primo);
	if(!mpz_probab_prime_p(p,10))
	{
		printf("El número %d ni siquiera es primo.\n",primo);
		printf("Probamos primer primo que encontremos a partir de %d.\n",primo);
		mpz_nextprime(p,p);
		primo=mpz_get_ui(p);
	}
	
	/* Comenzamos */
	printf("\nAnálisis para el número %d\n",primo);

	/* Calculamos el factorial */
	printf("\tcálculo del factorial...\n");
	mpz_fac_ui(n_grande,primo-1);

	/* Le sumamos 1 al resultado */
	mpz_add_ui(n_grande,n_grande,1);

	/* Calculamos el cuadrado del primo */
	mpz_ui_pow_ui(primo_cuadrado,primo,2);

	/* Un primo p es primo de Wilson si p^2 divide a (p-1)!+1 */
	/* mpz_divisible_p devuelve non-zero si n_grande es divisible por primo_cuadrado */
	printf("\tcomprobando divisibilidad...\n");
	if(mpz_divisible_p(n_grande,primo_cuadrado))
		printf("%d es número de Wilson.\n",primo);
	else
		printf("%d no es número de Wilson.\n",primo);

	/* Limpiamos memoria */
	mpz_clear(n_grande);
	mpz_clear(primo_cuadrado);
	mpz_clear(p);

	return 0;
}
