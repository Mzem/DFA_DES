#include <stdio.h>
#include <stdlib.h>
#include "../head/DES_permutation.h"
#include "../head/DES_tables.h"


//Rotation à gauche des bits de chaque moitié C et D (28 bits) de T (56 bits)
long LeftShift(long T) 
{
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
	long T = permutation(K, PC1, 64, 56);
	
	for(int i = 0; i < 16; i++) {
		if (v[i] == 1)
			T = LeftShift(T);
		else
			T = LeftShift(LeftShift(T));

		Ki[i] = permutation(T, PC2, 56, 48);
	}
}
