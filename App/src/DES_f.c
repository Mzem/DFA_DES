#include <stdio.h>
#include <stdlib.h>
#include "../head/DES_permutation.h"
#include "../head/DES_tables.h"

long f(long R, long Ki) 
{
	//On expand les 32 bits de R pour avoir 48 bits, puis on XOR avec Ki : T = ERxorKi
	long T = permutation(R, E, 32, 48) ^ Ki;
	
	//Ce résultat de 48 bits est représenté comme 8 entités de 6 bits
	//Pour chacune de ces 8 entité de 6 bits, on va appliquer la Sbox corréspondante pour avoir 4 bits en sortie
	//Chaque 4 bits trouvés vont se concaténer au résultat pour avoir un résultat de 32 bits après les 8 tours de Sbox
	long res = 0x0L;
	for (int i = 0 ; i < 8 ; i++)
	{
		//On récupère les 6 bits à partir de la 48-i*6 ème position : premier décalage à droite pour avoir les bons 6 bits au début, puis on masque pour garder que ces 6 bits
		long B = (T >> (48 - 6 - i*6)) & 0x3FL;
		//On calcule la ligne de Sbox[i], avec le bit 1 et 6 de B
		int r = 2 * ((B & 0x20) >> 5) + (B & 0x1);
		//On calcule la colonne de Sbox[i] avec le bit 2, 3, 4 et 5 de B
		int c = (B & 0x1E) >> 1;
		
		//On ajoute les 4 bits provenant de la valeur du Sbox (qu'on décale à gauche pour mettre à la bonne position à chaque fois) au résultat (qui va faire 32 bits)
		res = res | (Sbox[i][r][c] << (32 - 4 - i*4));
	}
	//Permutation du résultat de 32 bits
	return permutation(res, P, 32, 32);
}
