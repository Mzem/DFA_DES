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

//Permute les bits de l'entree aPermuter, selon la table table[], le nombre d'éléments de table[] doit etre égal à tailleSortie
long permutation(long aPermuter, int table[] ,int tailleEntree, int tailleSortie) {
		
	long res = 0x0L;
	long pos = 0x1L;
	long tmp;
	
	//On va selectionner le bit à la position table[i] de aPermuter et le rajouter à res à la position taille-i
	for (int i = 0; i < tailleSortie; i++) 
	{
		//On se positionne dans tmp en mettant le bit 1 dans la position table[i]
		tmp = pos << (tailleEntree - table[i]);
		
		//On récupère le bit de aPermuter à cette position
		tmp = aPermuter & tmp;
		
		//On met ce bit (s'il vaut 1) à la position actuelle (la plus forte)
		if (tmp != 0){
			//On place ce bit à 1 dans la bonne position
			tmp = 0x1L;
			tmp = tmp << (tailleSortie - i - 1);
		} 
		
		//On melange ce nouveau bit avec res
		res = res | tmp;
	}
	return res;
}
