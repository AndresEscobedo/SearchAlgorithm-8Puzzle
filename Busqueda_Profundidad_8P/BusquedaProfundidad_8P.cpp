#include "BusquedaProfundidad_8P.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>


using namespace std;

#pragma warning(disable:4996 6011 6387 26495)

Busqueda_profundidad::Busqueda_profundidad()
{
	cantidad_de_elementos_en_la_Agenda = 0;

	for (unsigned int i = 0; i < MAX_ENLACES; i++)
		enlaces_del_nodo[i] = (nodo*)malloc(sizeof(nodo));
	cantidad_de_enlaces_del_nodo = 0;
}

Busqueda_profundidad::~Busqueda_profundidad()
{
	if (nodo_encontrado_final != NULL)
		free(nodo_encontrado_final);
	for (unsigned int i = 0; i < MAX_ENLACES; i++)
		free(enlaces_del_nodo[i]);
	nodo* nodo_actual;
	if (Arbol == NULL)
		return;
	if (Arbol->cantidad_de_hijos == 0)
	{
		free(Arbol);
		return;
	}
	cantidad_de_elementos_en_la_Agenda = 0;
	for (unsigned i = 0; i < Arbol->cantidad_de_hijos; i++)
		Agenda[cantidad_de_elementos_en_la_Agenda++] = Arbol->hijos[i];
	free(Arbol);
	while (cantidad_de_elementos_en_la_Agenda != 0)
	{
		nodo_actual = Agenda[cantidad_de_elementos_en_la_Agenda - 1];
		cantidad_de_elementos_en_la_Agenda--;
		if (nodo_actual != NULL && nodo_actual->cantidad_de_hijos < MAX_HIJOS)
		{
			for (unsigned i = 0; i < nodo_actual->cantidad_de_hijos; i++)
				Agenda[cantidad_de_elementos_en_la_Agenda++] = nodo_actual->hijos[i];
			free(nodo_actual);
		}
	}
}

//Método que intercambia las posiciones de dos indices dentro de una arreglo de char
void Busqueda_profundidad::swap_Char(unsigned int indice1, unsigned int indice2, nodo* nodo_actual)
{
	char temporal = nodo_actual->matrix[indice1];
	nodo_actual->matrix[indice1] = nodo_actual->matrix[indice2];
	nodo_actual->matrix[indice2] = temporal;
}

// Busca el indice en donde se encuentra el espacio en blanco y apartir de su posición decide si agregar 1, 2, 3 o 4 enlaces
void Busqueda_profundidad::devuelve_enlaces_del_nodo(nodo* nodo_actual)
{

	cantidad_de_enlaces_del_nodo = 0;
	int indice_X = 10;
	for (int i = 0; i < 9; i++)
	{
		if (nodo_actual->matrix[i] == 'x')
		{
			indice_X = i;
			break;
		}
	}
	if (indice_X - 3 > 0)
	{
		strcpy(enlaces_del_nodo[cantidad_de_enlaces_del_nodo]->matrix, nodo_actual->matrix);
		swap_Char(indice_X, indice_X - 3, enlaces_del_nodo[cantidad_de_enlaces_del_nodo]);
		cantidad_de_enlaces_del_nodo++;
	}
	if (indice_X + 3 < 9)
	{
		strcpy(enlaces_del_nodo[cantidad_de_enlaces_del_nodo]->matrix, nodo_actual->matrix);
		swap_Char(indice_X, indice_X + 3, enlaces_del_nodo[cantidad_de_enlaces_del_nodo]);
		cantidad_de_enlaces_del_nodo++;
	}
	if (indice_X % 3 == 0)
	{
		strcpy(enlaces_del_nodo[cantidad_de_enlaces_del_nodo]->matrix, nodo_actual->matrix);
		swap_Char(indice_X, indice_X + 1, enlaces_del_nodo[cantidad_de_enlaces_del_nodo]);
		cantidad_de_enlaces_del_nodo++;
	}
	else if ((indice_X == 2) || (indice_X == 5) || (indice_X == 8))
	{
		strcpy(enlaces_del_nodo[cantidad_de_enlaces_del_nodo]->matrix, nodo_actual->matrix);
		swap_Char(indice_X, indice_X - 1, enlaces_del_nodo[cantidad_de_enlaces_del_nodo]);
		cantidad_de_enlaces_del_nodo++;
	}
	else
	{
		strcpy(enlaces_del_nodo[cantidad_de_enlaces_del_nodo]->matrix, nodo_actual->matrix);
		swap_Char(indice_X, indice_X + 1, enlaces_del_nodo[cantidad_de_enlaces_del_nodo]);
		cantidad_de_enlaces_del_nodo++;

		strcpy(enlaces_del_nodo[cantidad_de_enlaces_del_nodo]->matrix, nodo_actual->matrix);
		swap_Char(indice_X, indice_X - 1, enlaces_del_nodo[cantidad_de_enlaces_del_nodo]);
		cantidad_de_enlaces_del_nodo++;
	}
}

// Ve si un nodo cualquiera está en los ancestros de actual
bool Busqueda_profundidad::esta_en_ancestros(nodo* actual, char* posible_hijo)
{
	if (actual->padre == NULL)
		return(false);
	while (strcmp(actual->matrix, posible_hijo) != 0)
	{
		if (actual->padre == NULL)
			return(false);
		actual = actual->padre;
	}
	return(true);
}

// devuelve un nodo
void  Busqueda_profundidad::crea_nodo(const char* nombre, nodo* padre, nodo*& nodo_creado)
{
	nodo_creado = (nodo*)malloc(sizeof(nodo));
	nodo_creado->padre = padre;
	nodo_creado->cantidad_de_hijos = 0;
	strcpy(nodo_creado->matrix, nombre);
}

// Agrega un nodo hijo a un padre
void  Busqueda_profundidad::agrega_hijo(nodo* padre, nodo* hijo)
{
	hijo->padre = padre;
	padre->hijos[padre->cantidad_de_hijos] = hijo;
	padre->cantidad_de_hijos++;
}

// Verifica si dos nodos son iguales
bool Busqueda_profundidad::nodos_iguales_en_nombre(const char* nodo1, const char* nodo2)
{
	return(strcmp(nodo1, nodo2) == 0);
}

// Agrega un nodo al final de la agenda
void Busqueda_profundidad::agrega_un_nodo_al_final_de_la_agenda(nodo* nodo_a_agregar)
{
	Agenda[cantidad_de_elementos_en_la_Agenda] = nodo_a_agregar;
	cantidad_de_elementos_en_la_Agenda++;
}

// Realiza el algoritmo de búsqueda primero a lo ancho
// Datos del grafo
// Cantidad de datos que hay del grafo (líneas del archivo del grafo)
// Nombre del nodo de inicio
// Nombre del nodo final
// Devuelve del Arbol el nodo en el que encontró el nodo final
bool Busqueda_profundidad::busqueda_primero_prof(const char* nodo_inicio, const char* nodo_final)
{
	nodo* nodo_actual; // Crea un nodo y lo inicializa
	nodo* nuevo_hijo;
	// Crea el nodo inicial del árbol y coloca el inicio en la raiz del árbol
	crea_nodo(nodo_inicio, NULL, Arbol);
	// Añado el nodo inicial a la agenda
	agrega_un_nodo_al_final_de_la_agenda(Arbol);
	while (cantidad_de_elementos_en_la_Agenda != 0)
	{
		// Saca el primer elemento de la agenda y lo elimina
		nodo_actual = Agenda[--cantidad_de_elementos_en_la_Agenda];

		// Comparo el nodo primero con la meta
		// Si las cadenas son iguales strcmp devuelve 0
		if (nodos_iguales_en_nombre(nodo_actual->matrix, nodo_final))
		{
			// Realiza una copia del nodo actual
			nodo_encontrado_final = (nodo*)malloc(sizeof(nodo));
			memcpy(nodo_encontrado_final, nodo_actual, sizeof(nodo));
			return(true);
		}

		// Devuelve los posibles hijos
		devuelve_enlaces_del_nodo(nodo_actual);
		for (unsigned int i = 0; i < cantidad_de_enlaces_del_nodo; i++)
		{
			if (!esta_en_ancestros(nodo_actual, enlaces_del_nodo[i]->matrix))
			{
				// Creamos el nodo hijo
				crea_nodo(enlaces_del_nodo[i]->matrix, nodo_actual, nuevo_hijo);
				// Agrega ese hijo al árbol en el nodo actual
				agrega_hijo(nodo_actual, nuevo_hijo);
				// Agrego hijos[i]  al final de la agenda
				agrega_un_nodo_al_final_de_la_agenda(nuevo_hijo);
			}
		}
	}
	nodo_encontrado_final = NULL;
	return(false);
}

char* Busqueda_profundidad::devuelve_ruta()
{
	char* devuelve = (char*)malloc(sizeof(char) * MAX_RUTA);
	char* temporal = (char*)malloc(sizeof(char) * 9);
	nodo* actual = nodo_encontrado_final;
	if (actual == NULL)
		return(devuelve);
	strcpy(devuelve, "");
	do
	{
		strcat(devuelve, " ");
		strcpy(temporal, actual->matrix);
		strcat(devuelve, strrev(temporal));
		actual = actual->padre;
	} while (actual != NULL);
	strrev(devuelve);
	return(devuelve);
}