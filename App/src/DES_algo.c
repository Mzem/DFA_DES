#include <stdio.h>
#include <stdlib.h>
#include "../head/DES_permutation.h"
#include "../head/DES_key_schedule.h"
#include "../head/DES_f.h"
#include "../head/DES_tables.h"


long DES(long clair, long K) 
{
	printf("Clair DES = %lx\n",clair);
	printf("Clé DES = %lx\n\n",K);
	
	//Dérivation de la clé K (64 bits) en 16 sous-cles
	long Ki[16] = {0};
	DES_key_schedule(Ki, K);
	
	for (int k = 0 ; k < 16 ; k++) printf("K%d = %lx\n",k+1,Ki[k]);	
	
	//Permutation initiale IP
	long clairIP = permutation(clair, IP, 64, 64);
	
	printf("\nClairIP = %lx\n",clairIP);
	
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
	return permutation( (R << 32) | L, IPinv, 64, 64);
	
	return 0;

}
