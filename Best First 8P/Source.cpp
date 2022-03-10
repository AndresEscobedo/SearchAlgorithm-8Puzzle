#include "BestFirst8P.h"
#include <malloc.h>
#include <stdio.h>

#pragma warning(disable:4996 6011 6262)

int main(int argc, char* argv[])
{
	BestFirst b;
	bool resultado;
	resultado = b.busqueda_BestFirst("123456x78", "12345678x");
	if (resultado)
		printf("%s", b.devuelve_ruta());
	return(0);
}