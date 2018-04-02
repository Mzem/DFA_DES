#include <stdio.h>
#include <stdlib.h>
#include "../head/DES_permutation.h"

int PC1[] = {
	57,	49,	41,	33,	25,	17,	9,
	1,	58,	50,	42,	34,	26,	18,
	10,	2,	59,	51,	43,	35,	27,
	19,	11,	3,	60,	52,	44,	36,
	
	63,	55,	47,	39,	31,	23,	15,
	7,	62,	54,	46,	38,	30,	22,
	14,	6,	61,	53,	45,	37,	29,
	21,	13,	5,	28,	20,	12,	4
};

int PC2[] = {
	14,	17,	11,	24,	1,	5,
	3,	28,	15,	6,	21,	10,
	23,	19,	12,	4,	26,	8,
	16,	7,	27,	20,	13,	2,
	41,	52,	31,	37,	47,	55,
	30,	40,	51,	45,	33,	48,
	44,	49,	39,	56,	34,	53,
	46,	42,	50,	36,	29,	32
};

//Rotation à gauche des bits de chaque moitié C et D (28 bits) de T (56 bits)
long LeftShift(long T) {
	long C = (T & 0xFFFFFFF0000000L) >> 28;
	long D = T & 0x0000000FFFFFFFL;;
	long tmp;
	
	//On prend le bit le plus fort de C
	tmp = C >> 27;
	//On décale les bits à gauche
	C = C << 1;
	//On retire le bit de poids fort de C
	C = C & 0x0FFFFFFFL;
	//On met ce bit à la bonne position (début)
	C = C | tmp;
	

	//On prend le bit le plus fort de D
	tmp = D >> 27;
	//On décale les bits à gauche
	D = D << 1;
	//On retire le bit de poids fort de D
	D = D & 0x0FFFFFFFL;
	//On met ce bit à la bonne position (début)
	D = D | tmp;
	
	C = C << 28;
	return (C | D) & 0xFFFFFFFFFFFFFFL;
}

void DES_key_schedule(long Ki[], long K)
{
	// Nombre de permutations à effectuer
	int v[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
	
	// Division de K en deux entités de 28 bits (C et D sont les deux moitiés de T)
	long T = permutation(K, PC1, 56);
	
	for(int i = 0; i < 16; i++) {
		if (v[i] == 1)
			T = LeftShift(T);
		else
			T = LeftShift(LeftShift(T));

		Ki[i] = permutation(T, PC2, 48);
	}
}
