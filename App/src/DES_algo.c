#include <stdio.h>
#include <stdlib.h>
#include "../head/DES_key_schedule.h"


long DES(long clair, long K) 
{
	// Dérivation de la clé K (64 bits) en 16 sous-cles
	long Ki[16] = {0};
	DES_key_schedule(Ki, K);
	
	return 0;

}
