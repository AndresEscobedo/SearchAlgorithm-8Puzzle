#include "BeamSearch8P.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

using namespace std;

#pragma warning(disable:4996 6011 6387 26495)

BeamSearch::BeamSearch()
{
	cantidad_de_elementos_en_la_Agenda = 0;
	for (unsigned int i = 0; i < MAX_ENLACES; i++)
		enlaces_del_nodo[i] = (nodo*)malloc(sizeof(nodo) * MAX_ENLACES);
	cantidad_de_enlaces_del_nodo = 0;
}

BeamSearch::~BeamSearch()
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
void BeamSearch::swap_Char(unsigned int indice1, unsigned int indice2, nodo* nodo_actual)
{
	char temporal = nodo_actual->matrix[indice1];
	nodo_actual->matrix[indice1] = nodo_actual->matrix[indice2];
	nodo_actual->matrix[indice2] = temporal;
}

// Busca el indice en donde se encuentra el espacio en blanco y apartir de su posición decide si agregar 1, 2, 3 o 4 enlaces
void BeamSearch::devuelve_enlaces_del_nodo(nodo* nodo_actual)
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
		enlaces_del_nodo[cantidad_de_enlaces_del_nodo]->costo = 1;
		cantidad_de_enlaces_del_nodo++;
	}
	if (indice_X + 3 < 9)
	{
		strcpy(enlaces_del_nodo[cantidad_de_enlaces_del_nodo]->matrix, nodo_actual->matrix);
		swap_Char(indice_X, indice_X + 3, enlaces_del_nodo[cantidad_de_enlaces_del_nodo]);
		enlaces_del_nodo[cantidad_de_enlaces_del_nodo]->costo = 1;
		cantidad_de_enlaces_del_nodo++;
	}
	if (indice_X % 3 == 0)
	{
		strcpy(enlaces_del_nodo[cantidad_de_enlaces_del_nodo]->matrix, nodo_actual->matrix);
		swap_Char(indice_X, indice_X + 1, enlaces_del_nodo[cantidad_de_enlaces_del_nodo]);
		enlaces_del_nodo[cantidad_de_enlaces_del_nodo]->costo = 1;
		cantidad_de_enlaces_del_nodo++;
	}
	else if ((indice_X == 2) || (indice_X == 5) || (indice_X == 8))
	{
		strcpy(enlaces_del_nodo[cantidad_de_enlaces_del_nodo]->matrix, nodo_actual->matrix);
		swap_Char(indice_X, indice_X - 1, enlaces_del_nodo[cantidad_de_enlaces_del_nodo]);
		enlaces_del_nodo[cantidad_de_enlaces_del_nodo]->costo = 1;
		cantidad_de_enlaces_del_nodo++;
	}
	else
	{
		strcpy(enlaces_del_nodo[cantidad_de_enlaces_del_nodo]->matrix, nodo_actual->matrix);
		swap_Char(indice_X, indice_X + 1, enlaces_del_nodo[cantidad_de_enlaces_del_nodo]);
		enlaces_del_nodo[cantidad_de_enlaces_del_nodo]->costo = 1;
		cantidad_de_enlaces_del_nodo++;

		strcpy(enlaces_del_nodo[cantidad_de_enlaces_del_nodo]->matrix, nodo_actual->matrix);
		swap_Char(indice_X, indice_X - 1, enlaces_del_nodo[cantidad_de_enlaces_del_nodo]);
		enlaces_del_nodo[cantidad_de_enlaces_del_nodo]->costo = 1;
		cantidad_de_enlaces_del_nodo++;
	}
}

// Ve si un nodo cualquiera está en los ancestros de actual
bool BeamSearch::esta_en_ancestros(nodo* actual, char* posible_hijo)
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
void BeamSearch::crea_nodo(const char* nombre, nodo* padre, float distancia_al_padre, nodo*& nodo_creado)
{
	nodo_creado = (nodo*)malloc(sizeof(nodo));
	nodo_creado->padre = padre;
	nodo_creado->cantidad_de_hijos = 0;
	if (padre != NULL)
		nodo_creado->costo = padre->costo + distancia_al_padre;
	else
		nodo_creado->costo = distancia_al_padre;
	strcpy(nodo_creado->matrix, nombre);
}

// Agrega un nodo hijo a un padre
void BeamSearch::agrega_hijo(nodo* padre, nodo* hijo)
{
	hijo->padre = padre;
	padre->hijos[padre->cantidad_de_hijos] = hijo;
	padre->cantidad_de_hijos++;
}

// Verifica si dos nodos son iguales
bool BeamSearch::nodos_iguales_en_nombre(const char* nodo1, const char* nodo2)
{
	return(strcmp(nodo1, nodo2) == 0);
}

// Elimina un elemento de la agenda dado por indice 
void BeamSearch::elimina_elemento_agenda(unsigned int indice_a_eliminar)
{
	for (unsigned int i = indice_a_eliminar; i < cantidad_de_elementos_en_la_Agenda - 1; i++)
		Agenda[i] = Agenda[i + 1];
	cantidad_de_elementos_en_la_Agenda--;
}

// Deja en la agenda solamente los k nodos de menor costo
void BeamSearch::deja_en_la_agenda_solo_los_mejores_k_elementos(unsigned int k)
{
	nodo* temporal;
	if (k > cantidad_de_elementos_en_la_Agenda)
		k = cantidad_de_elementos_en_la_Agenda;
	for (unsigned int i = 0; i < k; i++)
		for (unsigned int j = i + 1; j < cantidad_de_elementos_en_la_Agenda; j++)
			if (Agenda[i]->costo > Agenda[j]->costo)
			{
				temporal = Agenda[j];
				Agenda[j] = Agenda[i];
				Agenda[i] = temporal;
			}
	cantidad_de_elementos_en_la_Agenda = k;
}

// Agrega un nodo al final de la agenda
void BeamSearch::agrega_un_nodo_al_final_de_la_agenda(nodo* nodo_a_agregar)
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
bool BeamSearch::busqueda_BeamSearch(const char* nodo_inicio, const char* nodo_final, const int k_elementos)
{
	nodo* nodo_actual; // Crea un nodo y lo inicializa
	nodo* nuevo_hijo;
	// Crea el nodo inicial del árbol y coloca el inicio en la raiz del árbol
	crea_nodo(nodo_inicio, NULL, 0.0f, Arbol);
	// Añado el nodo inicial a la agenda
	agrega_un_nodo_al_final_de_la_agenda(Arbol);
	while (cantidad_de_elementos_en_la_Agenda != 0)
	{
		// Saca el primer elemento de la agenda y lo elimina
		nodo_actual = Agenda[0];
		elimina_elemento_agenda(0);
		// Comparo el primer nodo de la agenda con la meta
		if (nodos_iguales_en_nombre(nodo_actual->matrix, nodo_final)) {
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
				crea_nodo(enlaces_del_nodo[i]->matrix, nodo_actual, enlaces_del_nodo[i]->costo, nuevo_hijo);
				// Agrega ese hijo al árbol en el nodo actual
				agrega_hijo(nodo_actual, nuevo_hijo);
				// Agrego hijos[i]  al final de la agenda
				agrega_un_nodo_al_final_de_la_agenda(nuevo_hijo);
			}
		}
		// Deja solo los K mejores en la agenda
		deja_en_la_agenda_solo_los_mejores_k_elementos(k_elementos);
	}
	nodo_encontrado_final = NULL;
	return(false);
}

char* BeamSearch::devuelve_ruta()
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