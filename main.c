#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "solovayStrassen.h"




int main(int argc, char const *argv[])
{
	//test des 1000 premières valeurs
	
	 /*int test;
	 mpz_t m_test;
 	 mpz_inits(m_test,NULL);
 	 int iter = 100;
 	 for (int i = 0; i < 1000 ; ++i)
 	 {
 		mpz_set_ui(m_test,i);
 		test = solovayStrassen(m_test, iter);
 		if(test == 1)
			printf(" %d est premiers\n", i);
		else
			printf(" %d n'est pas premiers \n",i);
 		
 	}
 	mpz_clears(m_test, NULL);*/
 	
 	
 	//fin du test des 1000 premières valeurs
 	
 	///////////////////////////////////////////////////////////////////
 	
 	//debut de la valeur passé sur le terminal
 	mpz_t n;
 	mpz_inits(n,NULL);
 	
 	
 	int retour_solovay, iteration;
 	iteration = atoi(argv[1]);
 	mpz_set_str(n,argv[2],10);

 	retour_solovay = solovayStrassen(n, iteration);
 	printf("\n\n\t\tle nombre passé en argument au terminal : ");
 	if(retour_solovay == 1)
 	{
		printf(" %s \n",argv[2]);
		printf(" est premiers\n");
	}
	else
	{
		printf(" %s \n",argv[2]);
		printf("n'est pas premiers\n");
	}
 	
 	mpz_clears(n,NULL);
 	
 	//fin du test
 	
	return 0;
}


// gcc -Wall -g main.c mesFonctions.c solovayStrassen.c -o test -lgmp
// ./test 
