#include <stdio.h>
#include <stdlib.h>
#include "../head/DES_algo.h"
#include "../head/DES_K16.h"
#include "../head/DES_K.h"


int main()
{
	// Clair et chiffrés : bloc de 64 bits en hexadecimal
	long clair = 0xABFB379DEA2A26FBL;
	long chiffreJuste = 0x8FA98EE0E9F5CBAFL;
	long chiffreFaux[] = {0x8DAD8EA4E9F4CBABL, 0x8FBB8EA0E9F5CBAFL, 0x8FB98CA4E9F4CBAFL, 0x8EB98AA6E9F5CBAFL, 0x8EF98AA4FBF4CBAFL, 0x8EE98EE0F9F7CBAFL, 0x8FE98AE0E9F5C9AFL, 0x8EE98EE1A9F5CBADL, 0x86E98AE1E9E1CBAFL, 0x8FA18EE0E9E1CBAFL, 0x8FA986E1E9E5CBAFL, 0xCFA99EE9A9E5CBAFL, 0xCFA98EE1E1A1CBAFL, 0x8FA99EE0E9FDCBAEL, 0x8FA99EE0E9B5C3AFL, 0xCFA99EE0EDF5CBE7L, 0xEFA99EE0EDB5DAAEL, 0x8F898EE0EDF5DBAFL, 0x8FA9AEE0E9F5DAEFL, 0x8FA9CFC0E9F5CAEFL, 0x8BA98FE0C9F5DAEFL, 0x9FA9CFE0E9D5CBAFL, 0x9BA98FE0E9F5EBAFL, 0x9BA9CFE0E8F58B8FL, 0x1FA98FF0E8F58BAFL, 0x8F298EE0E8F5CFAFL, 0x8FA90EF0E9F58BAFL, 0x8FA88E60E8F58BABL, 0x8FAC8EF068F58FAFL, 0x8FAC8EE0E975CBBFL, 0x8FA88EE0E9F54BABL, 0x8FAC8EE4E9F4CB3BL};
	
	
	//Exemple d'exécution d'un chiffrement DES
	printf("\n######################################################################\n\n");
	
	printf("Exemple exécution DES\n\n");
	printf("\nRésultat DES : %lx\n", DES(clair, 0x8FA98EE0E9F5CBAFL));
	
	printf("\n######################################################################\n\n");
	
	printf("Recherche K16\n");
	
	//Recherche K16 pour chaque faute
	long K16 = rechercheK16(chiffreJuste, chiffreFaux);
	
	printf("\nK16 = %lx\n", K16);
	
	printf("\n######################################################################\n\n");
	
	return EXIT_SUCCESS;
}
