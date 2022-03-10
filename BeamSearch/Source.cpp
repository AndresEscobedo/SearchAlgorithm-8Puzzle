#include "BeamSearch8P.h"
#include <malloc.h>
#include <stdio.h>

#pragma warning(disable:4996 6011 6262)

int main(int argc, char* argv[])
{
	BeamSearch b;
	bool resultado;
	resultado = b.busqueda_BeamSearch("12345x678", "12345678x", 4);
	if (resultado)
		printf("%s", b.devuelve_ruta());
	return(0);
}