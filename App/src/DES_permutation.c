#include <stdio.h>
#include <stdlib.h>

long binaire (long n) {	
	long i = 1, bin = 0;
	while (n >= 1) {
		bin += (n%2)*i;
		n = n/2;
		i = i*10;
	}
	return bin;
}

long Permutation(long aPermuter, int table[], int tailleSortie) {
		
	long res = 0x0000000000000000L;
	long pos = 0x0000000000000001L;
	long tmp;
	
	//On va selectionner le bit à la position table[i] de aPermuter et le rajouter à res à la position taille-i
	for(int i = 0; i < tailleSortie; i++) 
	{
		//On se positionne dans tmp en mettant le bit 1 dans la position table[i]
		tmp = pos << (table[i] - 1);
		
		//On récupère le bit de aPermuter à cette position
		tmp = aPermuter & tmp;
		
		//On met ce bit (s'il vaut 1) à la position taille - i
		if (tmp != 0){
			//On crée un nombre hexa ayant tailleSortie bits, dont seul le bit de poids fort vaut 1
			tmp = 0x1L;
			tmp = tmp << (tailleSortie - 1);
			//On place ce bit à 1 dans la bonne position
			tmp = tmp >> i;
		} 
		
		//On melange ce nouveau bit avec res
		res = res | tmp;
	}
	return res;
}
