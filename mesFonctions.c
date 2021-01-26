#include "mesFonctions.h"

liste creer_liste(){return NULL;}

int est_vide(liste l)
{
	if(l == NULL)
		return 1;
	return 0;
}

void affiche_liste(liste l)
{
	
	if(est_vide(l))
	{
		printf("La liste est vide \n");
		return;
	}
	while(l)
	{
		printf("%d ",l->val);
		l = l->suiv;
	}
	printf("\n");
}

liste libere_liste(liste l)
{
	liste tmp;
	while(l)
	{
		tmp = l->suiv;
		free(l);
		l = tmp;
	}
	return NULL;
}


liste ajoute_elem_debut(liste l,int i)
{
	liste new = malloc(sizeof(struct elem));
	new->val = i;
	new->suiv = l;
	return new;
}


liste supprime_elem_debut(liste l)
{
	if(est_vide(l))
	{
		return l;
	}

	liste tmp;
	tmp = l->suiv;
	free(l);
	return tmp;
}


void pgcd(mpz_t resultat, const mpz_t a, const mpz_t b) // pgcd(1,1)
{
	if(mpz_cmp(a,b) == 0)
	{
		mpz_set(resultat, a);
		//printf("a == b\n");
	}
	else if(mpz_cmp(a, b) > 0) // si la val mpz_cmp positif
	{
		if(mpz_cmp_ui(b, 0) == 0) // si la val mpz_cmp == 0
		{
			mpz_set(resultat, a);
			//printf("b == 0\n");
		}
		else if(mpz_cmp_ui(b, 1) == 0)
		{
			mpz_set_ui(resultat, 1);
			//printf("b == 1\n");

		}
		else
		{
			mpz_t reste;
			mpz_init(reste);

			mpz_mod(reste, a, b);
			pgcd(resultat, b, reste);
			//printf("pgcd b a mod b\n");

			mpz_clear(reste);
		}
	}
	else
	{
		pgcd(resultat, b, a);
		//printf("pgcd b a\n");
	}
}


void squareAndMultiply(mpz_t resultat, const mpz_t x, const mpz_t expo, const mpz_t modul)
{
	mpz_set(resultat, x);
	liste expoB = creer_liste();
	expoB = getBinaire(expo);
	// printf("OK pour expoBinMPZ\n");
	expoB = supprime_elem_debut(expoB);

	while(expoB)
	{
		mpz_mul(resultat, resultat, resultat);
		mpz_mod(resultat, resultat, modul);
		if(expoB->val == 1)
		{
			mpz_mul(resultat, resultat, x);
			mpz_mod(resultat, resultat, modul);
		}

		expoB = supprime_elem_debut(expoB);
	}
	
	expoB = libere_liste(expoB);
}


liste getBinaire(const mpz_t expo)
{
	int r = 0;
	liste maListe = creer_liste();
	mpz_t rest, tmp;
	mpz_inits(rest, tmp, NULL);
	mpz_set(tmp, expo);

	while(mpz_cmp_ui(tmp, 0) > 0)
	{
		r = (int) mpz_cdiv_r_ui(rest, tmp, 2);
		//printf("r = %d\n", r);
		maListe = ajoute_elem_debut(maListe, r);
		mpz_div_ui(tmp, tmp, 2);

	}
	mpz_clears(rest, tmp, NULL);
	//affiche_liste(maListe);
	return maListe;
}

int jacobiSymbol(mpz_t a, mpz_t b) 
{
	mpz_t resultat,tmpa,tmpb,tmp,tmp2;
	int t;
	mpz_inits(resultat,tmpa,tmpb,tmp,tmp2,NULL);
	mpz_set(tmpa,a);
	mpz_set(tmpb,b);
	if(mpz_cmp_ui(tmpa,1) == 0)
	{
		return 1;
	}
	pgcd(resultat, a, b);
	if(mpz_cmp_ui(resultat, 1) != 0)
	{
		return 0;
	}

	mpz_mod(tmpa,tmpa,tmpb);// a = a % b
	t=1;
	while(mpz_cmp_ui(tmpa,0) != 0)
	{
		mpz_mod_ui(tmp,tmpa,2);
		while(mpz_cmp_ui(tmp,0) == 0)
		{ //Tant que a % 2 = 0
			mpz_div_ui(tmpa,tmpa,2);
			mpz_mod_ui(tmp,tmpb,8);
			if ((mpz_cmp_ui(tmp,3) == 0 || mpz_cmp_ui(tmp,5) == 0)) 
				t = -t;
			mpz_mod_ui(tmp,tmpa,2);
		}
		mpz_set(tmp,tmpa);
		mpz_set(tmpa,tmpb);
		mpz_set(tmpb,tmp);
		mpz_mod_ui(tmp,tmpa,4);
		mpz_mod_ui(tmp2,tmpb,4);
		if (mpz_cmp_ui(tmp,3) == 0 && mpz_cmp_ui(tmp2,3) == 0) 
			t = - t;
		mpz_mod(tmpa,tmpa,tmpb);
	}
	if (mpz_cmp_ui(tmpb,1) == 0)
	{
		mpz_clears(resultat,tmp,tmp2,tmpa,tmpb,NULL);
		return t; 
	}
	else 
	{
		mpz_clears(resultat,tmp,tmp2,tmpa,tmpb,NULL);
		return 0;
	}
}

