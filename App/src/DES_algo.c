#include <stdio.h>
#include <stdlib.h>
#include "../head/DES_permutation.h"
#include "../head/DES_key_schedule.h"
#include "../head/DES_f.h"

int IP[] = {
	58,	50,	42,	34,	26,	18,	10,	2,
	60,	52,	44,	36,	28,	20,	12,	4,
	62,	54,	46,	38,	30,	22,	14,	6,
	64,	56,	48,	40,	32,	24,	16,	8,
	57,	49,	41,	33,	25,	17,	9,	1,
	59,	51,	43,	35,	27,	19,	11,	3,
	61,	53,	45,	37,	29,	21,	13,	5,
	63,	55,	47,	39,	31,	23,	15,	7
};
	
int IPinv[] = {
	40,	8,	48,	16,	56,	24,	64,	32,
	39,	7,	47,	15,	55,	23,	63,	31,
	38,	6,	46,	14,	54,	22,	62,	30,
	37,	5,	45,	13,	53,	21,	61,	29,
	36,	4,	44,	12,	52,	20,	60,	28,
	35,	3,	43,	11,	51,	19,	59,	27,
	34,	2,	42,	10,	50,	18,	58,	26,
	33,	1,	41,	9,	49,	17,	57,	25
};

long DES(long clair, long K) 
{
	printf("clair = %lx\n",clair);
	printf("K = %lx\n",K);
	
	//Dérivation de la clé K (64 bits) en 16 sous-cles
	long Ki[16] = {0};
	DES_key_schedule(Ki, K);
	
	for (int k = 0 ; k < 16 ; k++) printf("Ki = %lx\n",Ki[k]);	
	
	//Permutation initiale IP
	long clairIP = permutation(clair, IP, 64);
	
	printf("clairIP = %lx\n",clairIP);
	
	//Séparation du bloc clair en 2 motiés de 32 bits
	long L = (clairIP & 0xFFFFFFFF00000000L) >> 32;
	long R = clairIP & 0x00000000FFFFFFFFL;
	
	printf("L0 = %lx\n",L);
	printf("R0 = %lx\n",R);
	
	//16 tours de Feistel
	long LiPlus1, RiPlus1;
	for (int i = 0; i < 16; i++) {
		LiPlus1 = R;
		RiPlus1 = L ^ f(R, Ki[i]);
		//On sauvegarde ces nouvelles valeurs
		L = LiPlus1;
		R = RiPlus1;
		
		printf("L%d = %lx\n",i+1,L);
		printf("R%d = %lx\n",i+1,R);
	}
	
	//Permutation IP inverse sur (R16, L16) (blocs invérsés, c'est comme si on les avait pas inversés au dernier tour de Feitsel)
	return permutation( (R << 32) | L, IPinv, 64);
	
	return 0;

}
