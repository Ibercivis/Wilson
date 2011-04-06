/*
 * =====================================================================================
 *
 *       Filename:  wilson.h
 *
 *    Description:  Búsqueda de números de Wilson.
 *
 *        Version:  2.0
 *        Created:  15/11/10 17:30:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Francisco Sanz (Fs), frasanz@bifi.es
 *        Company:  BIFI, Universidad de Zaragoza
 *
 * =====================================================================================
 */
typedef unsigned long long u64;
typedef struct 
{
	u64 r1;
	u64 r2;
} representacion;
representacion get_representacion(u64 a, u64 p);
representacion mul(representacion a, representacion b, u64 p);

