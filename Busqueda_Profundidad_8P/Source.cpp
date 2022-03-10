#include "BusquedaProfundidad_8P.h"
#include <stdio.h>

#pragma warning(disable:4996 6011 6262)

int main(int argc, char* argv[])
{
	Busqueda_profundidad b;
	bool resultado;
	resultado = b.busqueda_primero_prof("12345x678", "12345678x");
	if (resultado)
		printf("%s", b.devuelve_ruta());
	return(0);
}