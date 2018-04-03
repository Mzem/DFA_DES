#include <stdio.h>
#include <stdlib.h>
#include "../head/DES_permutation.h"
#include "../head/DES_key_schedule.h"
#include "../head/DES_f.h"
#include "../head/DES_algo.h"
#include "../head/DES_tables.h"

long bitsPerdus(long mask) 
{
	long pos[] = {14, 15, 19, 20, 51, 54, 58, 60};
	long res = 0x0L;
	
	for(int i = 0; i < 8; i++) 
		res = res | ( ((mask >> i) & 1) << (64 - pos[i]) );

	return res;
}

long rechercheK56b(long clair, long chiffre, long K16) 
{
	//On remet les 48 bits de K16 à la bonne position pour K (algo dérivation clés)
	//On applique l'inverse de PC2, on passe de 48 à 56 bits avec 8 bits faux, dont les positions vont etre sauvegardées
	//On applique ensuite l'inverse de PC1, on passe de 56 à 64 bits avec 8 autres bits faux (bits de parité), les positions de 8 bits perdus par PC2 changent de position, on les resauvegarde
	long K48b = permutation(permutation(K16, PC2inv, 48, 56), PC1inv, 56, 64);
	
	printf("\n48 bons bits de K = %lx\n", K48b);
	
	//Recherche exhaustive sur les 8 bits perdus manquants de K avec DES
	//Positions dans K48b des bits perdus par PC1inv(PC2inv) : 14, 15, 19, 20, 51, 54, 58, 60
	//Pas de problème si les 8 bits de parité sont faux car ils n'interviennent pas dans le DES
	long mask = 0x00L;
	long Ktest = K48b;
	
	//On va tester toutes les possibilités pour les valeurs des 8 bits perdus dans les positions sauvegardées, donc 256 possibiliés
	while( mask < 256 && chiffre != DES(clair, Ktest) ) 
	{
		Ktest = K48b | bitsPerdus(mask);
		mask = mask + 1;
	}
	//Si on testé les 256 possibilités pour les 8 bits perdus, on n'arrive donc pas à trouver les 56 bits de la clé K
	if (mask == 256)
		printf("\nProblème : impossible de trouver K 56 bits\n");
	
	return Ktest;
}

long bitsParite(long K56b) 
{
	long res = K56b;
	long tmp, parite;
	
	for(int i = 0; i < 8; i++) {
		parite = 0;
		for(int j = 0; j < 8; j++) {
			if(j != 7) {
				tmp = 0x1L << ( ((7 - i) * 8) + (7 - j) );
				tmp = K56b & tmp;
				parite = tmp ? parite ^ 1 : parite ^ 0;
			}
			else {
				tmp = !parite;
				res |= tmp << ((7 - i) * 8);
			}
		}
	}
	return res;
}

long rechercheK(long clair, long chiffre, long K16) 
{	
	//Recherche 56 bits de K à partir de K16 (8 bits manquants)
	long K56b = rechercheK56b(clair, chiffre, K16);
	
	printf("\n56 bons bits de K = %lx\n", K56b);
	
	//Calcul des 8 bits de parité restants
	long K64b = bitsParite(K56b);
	
	return K64b;
}
