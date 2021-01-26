#ifndef MESFONCTIONS_H
#define MESFONCTIONS_H

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct elem
{
	int val;
	struct elem *suiv;
};

typedef struct elem* liste;

liste creer_liste();

int est_vide(liste l);

void affiche_liste(liste l);

liste libere_liste(liste l);

liste ajoute_elem_debut(liste l,int i);

liste supprime_elem_debut(liste l);

liste getBinaire(const mpz_t expo);

void pgcd(mpz_t resultat, const mpz_t a, const mpz_t b);

void squareAndMultiply(mpz_t resultat, const mpz_t x, const mpz_t expo, const mpz_t modul);

int jacobiSymbol(mpz_t a, mpz_t b);


#endif
