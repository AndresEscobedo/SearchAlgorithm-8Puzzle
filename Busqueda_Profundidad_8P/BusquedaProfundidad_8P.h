#pragma once

#define MAX_CHAR_NOMBRE 9
#define MAX_HIJOS 4
#define MAX_ENLACES 4
#define MAX_ELEMENTOS_AGENDA 100000
#define MAX_RUTA 20000


// Almacena la información de un nodo del árbol o agenda
struct nodo
{
	nodo* padre; // Nodo padre
	char matrix[MAX_CHAR_NOMBRE]; // Nombre del nodo del grafo
	nodo* hijos[MAX_HIJOS]; // Listado de los hijos del nodo
	unsigned int cantidad_de_hijos; // Cantidad de hijos en el listado
};

class Busqueda_profundidad
{
public:
	Busqueda_profundidad();
	~Busqueda_profundidad();
	bool busqueda_primero_prof(const char* nodo_inicio, const char* nodo_final);
	char* devuelve_ruta();
private:
	void devuelve_enlaces_del_nodo(nodo* nodo_actual);
	bool esta_en_ancestros(nodo* actual, char* posible_hijo);
	void crea_nodo(const char* nombre, nodo* padre, nodo*& nodo_creado);
	void agrega_hijo(nodo* padre, nodo* hijo);
	bool nodos_iguales_en_nombre(const char* nodo1, const char* nodo2);
	void agrega_un_nodo_al_final_de_la_agenda(nodo* nodo_a_agregar);
	nodo* Agenda[MAX_ELEMENTOS_AGENDA];
	unsigned int cantidad_de_elementos_en_la_Agenda;
	nodo* Arbol;
	nodo* nodo_encontrado_final;
	nodo* enlaces_del_nodo[MAX_ENLACES];
	unsigned int cantidad_de_enlaces_del_nodo;
	void swap_Char(unsigned int indice1, unsigned int indice2, nodo* nodo_actual);
};

