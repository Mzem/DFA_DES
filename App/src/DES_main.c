#include <stdio.h>
#include <stdlib.h>
#include "../head/DES_algo.h"
#include "../head/DES_atq.h"


int main()
{
	// Clair et chiffrés : bloc de 64 bits en hexadecimal
	long clair = 0xABFB379DEA2A26FBL;
	long chiffreJuste = 0x8FA98EE0E9F5CBAFL;
	long chiffreFaux[] = {0x8DAD8EA4E9F4CBABL, 0x8FBB8EA0E9F5CBAFL, 0x8FB98CA4E9F4CBAFL, 0x8EB98AA6E9F5CBAFL, 0x8EF98AA4FBF4CBAFL, 0x8EE98EE0F9F7CBAFL, 0x8FE98AE0E9F5C9AFL, 0x8EE98EE1A9F5CBADL, 0x86E98AE1E9E1CBAFL, 0x8FA18EE0E9E1CBAFL, 0x8FA986E1E9E5CBAFL, 0xCFA99EE9A9E5CBAFL, 0xCFA98EE1E1A1CBAFL, 0x8FA99EE0E9FDCBAEL, 0x8FA99EE0E9B5C3AFL, 0xCFA99EE0EDF5CBE7L, 0xEFA99EE0EDB5DAAEL, 0x8F898EE0EDF5DBAFL, 0x8FA9AEE0E9F5DAEFL, 0x8FA9CFC0E9F5CAEFL, 0x8BA98FE0C9F5DAEFL, 0x9FA9CFE0E9D5CBAFL, 0x9BA98FE0E9F5EBAFL, 0x9BA9CFE0E8F58B8FL, 0x1FA98FF0E8F58BAFL, 0x8F298EE0E8F5CFAFL, 0x8FA90EF0E9F58BAFL, 0x8FA88E60E8F58BABL, 0x8FAC8EF068F58FAFL, 0x8FAC8EE0E975CBBFL, 0x8FA88EE0E9F54BABL, 0x8FAC8EE4E9F4CB3BL};
	
	/*
	
	// Recherche K16 pour chaque faute
	recherche_K16(chiffreJuste, chiffreFaux);
	
	//0, 61, 41, 37, 15, 29, 48, 23
	long K16 = (
		(53L << 7 * 6) |
		(10L << 6 * 6) |
		(49L << 5 * 6) |
		(29L << 4 * 6) |
		(41L << 3 * 6) |
		(57L << 2 * 6) |
		(10L << 6) |
		61L
	);
	
	// Recherche K : 8 bits manquants
	long K_56bits = recherche_K(clair, chiffre, K16);
	
	// Calculer les 8 bits de parité restants
	long K_64bits = calcul_bits_parite(K_56bits);
	printf("%lx\n", K_64bits);
	
	*/
	
	printf("#######################################\n");
	printf("#######################################\n");
	
	return EXIT_SUCCESS;
}
