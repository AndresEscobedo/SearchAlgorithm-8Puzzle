#include "BranchAndBound8P.h"
#include <malloc.h>
#include <stdio.h>

#pragma warning(disable:4996 6011 6262)

int main(int argc, char* argv[])
{
	Busqueda_branch_and_bound b;
	bool resultado;
	resultado = b.busqueda_branch_and_bound("12345x678", "12345678x");
	if (resultado)
		printf("%s", b.devuelve_ruta());
	return(0);
}