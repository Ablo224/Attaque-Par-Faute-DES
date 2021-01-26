#include "solovayStrassen.h"


//n est l'entier à traiter et k le nombre d'iteration
int solovayStrassen(mpz_t n, int k) 
{	
	if (mpz_cmp_ui(n,2) < 0)
	{
		return 0;
	}

	if(mpz_cmp_ui(n, 2) == 0 || mpz_cmp_ui(n, 3) == 0)
	{
		return 1;
	}
	
	mpz_t tmp;
	mpz_init(tmp);
	mpz_mod_ui(tmp,n,2);
	if (mpz_cmp_ui(tmp,0) == 0){ // SI n % 2 est egale a 0
		mpz_clear(tmp);
		return 0;
	}
	
	int jacobi = 0;
	mpz_t i,randomNumber,exposant,resultatM,itt,r,nMoins1;
	mpz_inits(i,randomNumber,exposant,resultatM,itt,r,nMoins1,NULL);
	
	mpz_set_ui(itt,k);
	
	gmp_randstate_t state;
	gmp_randinit_default(state);
	mpz_sub_ui(nMoins1,n,1); //On fait exposant-1

	for (mpz_set_ui(i,0); mpz_cmp(i,itt) < 0; mpz_add_ui(i, i, 1))
	{
		gmp_randseed_ui(state, time(NULL)*(rand()%100 +1));	
		mpz_urandomm (randomNumber , state , n);
		
		if(mpz_cmp_ui(randomNumber, 2) < 0)
		{
			mpz_add_ui(randomNumber, randomNumber, 2);
		}
		
		jacobi = jacobiSymbol(randomNumber, n);
		
		mpz_div_ui(exposant, nMoins1, 2);
		mpz_mod_ui(r, nMoins1, 2);
		mpz_sub(exposant,exposant,r);
		squareAndMultiply(resultatM, randomNumber, exposant, n);

		if(jacobi == 0 || ( jacobi != -1 && mpz_cmp_ui(resultatM,jacobi) != 0) || (jacobi == -1 && mpz_cmp(resultatM, nMoins1) != 0)){
			mpz_clears(i,randomNumber,tmp, exposant, itt, resultatM,r,nMoins1,NULL);
			gmp_randclear(state);
			return 0;
		}
	}
	mpz_clears(i,randomNumber,tmp,resultatM, exposant, itt, r, nMoins1,NULL);
	gmp_randclear(state);
	return 1;
}
