#include "busqueda_prof_lim_8P.h"
#include <stdio.h>

#pragma warning(disable:4996 6011 6262)

int main(int argc, char* argv[])
{
	Busqueda_Profundidad_Limitada b;
	bool resultado;
	resultado = b.Busqueda("12345x678", "12345678x", 13);
	if (resultado)
		printf("%s", b.devuelve_ruta());
	return(0);
}