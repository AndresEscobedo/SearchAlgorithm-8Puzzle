#include "Profundidad_iterativa_8P.h"
#include <stdio.h>

#pragma warning(disable:4996 6011 6262)

int main(int argc, char* argv[])
{
	Busqueda_Iterativa b;
	bool resultado;
	resultado = b.BusquedaIterativa("12345x678", "12345678x", 5, 2);
	if (resultado)
		printf("%s", b.devuelve_ruta());
	return(0);
}