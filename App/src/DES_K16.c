#include <stdio.h>
#include <stdlib.h>
#include "../head/DES_permutation.h"
#include "../head/DES_key_schedule.h"
#include "../head/DES_f.h"
#include "../head/DES_tables.h"


long rechercheK16(long chiffreJuste, long chiffreFaux[]) 
{	
	long K16 = 0x000000000000L;
	long dechiffJuste, dechiffFaux, L16, R15, L16f, R15f, verif, E_R15, E_R15f, tmp, tmpf;
	int r, c, rf, cf;
	
	//64 solutions possibles (car entrée de 6 bits) des 6 fautes pour les 8 Sbox
	int sol[8][6][64] = {{{0}}};
	//Nombre de solutions possibles des 6 fautes pour les 8 Sbox 
	int nbSol[8][6] = {{0}};
	
	
	//Chacune des 8 Sbox va etre attaquée par 6 chiffrés faux (parmi les 32 disponibles) qui sont indiqués dans cette table
	//Raison : K16 est composée de 48 bits = 8 entités de 6 bits qui vont etre réparties sur les 8 Sbox,
	//l'attaque n'altère qu'1 seul bit de R15, donc pour etre sur d'avoir une faute dans 
	int faux[8][6] = {
		{0, 31, 30, 29, 28, 27},
		{28, 27, 26, 25, 24, 23},
		{24, 23, 22, 21, 20, 19},
		{20, 19, 18, 17, 16, 15},
		{16, 15, 14, 13, 12, 11},
		{12, 11, 10, 9, 8, 7},
		{8, 7, 6, 5, 4, 3},
		{4, 3, 2, 1, 0, 31}
	};
	
	//On cherche L16 et R16 à partir d'un chiffre juste
	dechiffJuste = permutation(chiffreJuste, IP, 64, 64); 
	L16 = (dechiffJuste >> 32) & 0xFFFFFFFFL; 
	R15 = dechiffJuste & 0xFFFFFFFFL;	//car R16 = R15
	
	//Attaque des 8 Sbox à l'aide des 8 equations établies, chaque attaque va nous permettre de connaitre 8 bits de K16
	for (int s = 0; s < 8 ; s++) 
	{	
		//Chacune des 8 Sbox va etre attaquée par 6 chiffrés faux
		for (int f = 0; f < 6 ; f++) 
		{
			dechiffFaux = permutation(chiffreFaux[faux[s][f]], IP, 64, 64);
			L16f = (dechiffFaux >> 32) & 0xFFFFFFFFL; 
			R15f = dechiffFaux & 0xFFFFFFFFL;
	
			//On calcule les éléments de l'équation
			verif = permutation(L16 ^ L16f, Pinv, 32, 32);
			E_R15 = permutation(R15, E, 32, 48); 
			E_R15f = permutation(R15f, E, 32, 48);
			
			//On va tester toutes les valeurs possibles de k16 sur 6 bits : recherche exhaustive de 6 bits
			for (int k16i = 0 ; k16i < 64 ; k16i++) 
			{
				//Valeurs de 6 bits qu'on va rentrer dans la Sbox numéro s puis vérifier avec les 4 bits corréspondants de verif
				tmp = ((E_R15 & mask6[s]) >> ((7 - s) * 6)) ^ k16i;
				tmpf = ((E_R15f & mask6[s]) >> ((7 - s) * 6)) ^ k16i;
				
				//Calcul des lignes et colonnes de la Sbox
				r = 2 * ((tmp & 0x20) >> 5) + (tmp & 0x1);
				c = (tmp & 0x1E) >> 1;
				
				rf = 2 * ((tmpf & 0x20) >> 5) + (tmpf & 0x1);
				cf = (tmpf & 0x1E) >> 1;
				
				//Vérification de k16i : on compare les 4 bits de vérif et les 4 bits du XOR de Sbox
				int PP = (verif & mask4[s]) >> ((7 - s) * 4);
				int SS = Sbox[s][r][c] ^ Sbox[s][rf][cf];
				
				if ( PP ==	SS ) 
				{	
					sol[s][f][nbSol[s][f]] = k16i;
					nbSol[s][f]++;
				}
			}
		}
		
		//Affichage des solutions pour chaque faute de chaque Sbox
		printf("\nSbox %d\n", s + 1);
		for (int f = 0; f < 6; f++) 
		{
			printf("Faute %d : %d solutions\t", f+1, nbSol[s][f]);
			for (int i = 0; i < nbSol[s][i]; i++) 
				printf("%x ", sol[s][f][i]);
			printf("\n"); 
		}
		
		//Récupération de la solutions unique de chaque Sbox pour les 6 fautes et concaténation dans K16
		int numSolf0 = 0;
		long candidat = (long) sol[s][0][numSolf0];
		for (int f = 1; f < 6; f++)
		{
			int numSolf = 0;
			for (numSolf; numSolf < nbSol[s][f]; numSolf++)
				if (candidat == sol[s][f][numSolf])
					break;
			
			if (numSolf == nbSol[s][f]){
				if (numSolf0+1 >= nbSol[s][0]){
					printf("\nProblème Sbox %d faute %d pour trouver K16\n",s,f);
					break;
				}
				f = 1;
				numSolf0++;
				candidat = (long) sol[s][0][numSolf0];
			}
		}
		printf("Solution S%d = %lx\n",s+1,candidat);
		K16 = K16 << 6;
		K16 = K16 | candidat;
		printf("K16 actuel = %lx\n",K16);
		
	}
	
	return K16;
}
