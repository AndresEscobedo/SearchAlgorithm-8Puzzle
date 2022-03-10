#include "Busqueda_a_lo_ancho_8P.h"
#include <stdio.h>

#pragma warning(disable:4996 6011 6262)

int main(int argc, char* argv[])
{
	Busqueda_a_lo_ancho b;
	bool resultado;
	resultado = b.busqueda_a_lo_ancho("12345x678", "12345678x");
	if (resultado)
		printf("%s", b.devuelve_ruta());
	return(0);
}