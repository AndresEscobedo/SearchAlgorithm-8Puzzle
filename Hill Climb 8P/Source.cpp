#include "HillClimb8P.h"

#include <stdio.h>

#pragma warning(disable:4996 6011 6262)

int main(int argc, char* argv[])
{
	Busqueda_hill_climbing b;
	bool resultado;
	resultado = b.busqueda_hill_climbing("123456x78", "12345678x");
	if (resultado)
		printf("%s", b.devuelve_ruta());
	return(0);
}