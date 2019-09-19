#include "stdafx.h"
#include "ArbolBB.h"

NodoABB *nuevoNod(int dato) {
	NodoABB *temp = new NodoABB();
	temp->id = dato;
	temp->izquierda = temp->derecha = NULL;
	temp->principal = temp->columnas = temp->filas = NULL;
	return temp;
}

bool Binario::existeB(NodoABB *raiz, int dato) {

	if (raiz == NULL) {
		return false;
	}

	if (raiz->id == dato) {
		return true;
	}
	else {
		if (dato < raiz->id) {
			return existeB(raiz->izquierda, dato);
		}
		else {
			return existeB(raiz->derecha, dato);
		}
	}
}

bool Binario::existe(int dato) {
	return existeB(raiz, dato);
}

NodoABB *Binario::insertar(NodoABB *raiz, int dato) {

	if (raiz == NULL) {
		return nuevoNod(dato);
	}

	if (dato < raiz->id) {
		raiz->izquierda = insertar(raiz->izquierda, dato);
	}
	else {
		raiz->derecha = insertar(raiz->derecha, dato);
	}
	return raiz;
}

void Binario::add(int dato) {
	if (!existe(dato)) {
		raiz = insertar(raiz, dato);
		no_Nodos++;
	}
	else {
		cout << "El dato ya existe" << endl;
	}

}

NodoABB *minValue(NodoABB *nodo)
{
	Nodo_ABB *current = nodo;

	while (current && current->derecha != NULL)
		current = current->derecha;

	return current;
}

NodoABB *Binario::eliminar(NodoABB *raiz, int dato) {

	if (raiz == NULL) {
		return raiz;
	}

	if (raiz->id > dato) {
		raiz->izquierda = eliminar(raiz->izquierda, dato);
		return raiz;
	}
	else if (raiz->id < dato) {
		raiz->derecha = eliminar(raiz->derecha, dato);
		return raiz;
	}
	else {
		if (raiz->izquierda == NULL) {
			NodoABB *temp = raiz->derecha;
			free(raiz);
			return temp;

		}
		else if (raiz->derecha == NULL) {
			NodoABB *temp = raiz->izquierda;
			free(raiz);
			return temp;
		}

		NodoABB *temp = minValue(raiz->izquierda);
		raiz->id = temp->id;
		raiz->principal = temp->principal;
		raiz->filas = temp->filas;
		raiz->columnas = temp->columnas;
		raiz->izquierda = eliminar(raiz->izquierda, temp->id);
	}

	return raiz;
}

void Binario::elim(int dato) {
	if (existe(dato)) {
		raiz = eliminar(raiz, dato);
		no_Nodos--;
	}
	else {
		cout << "El dato " << dato << " no existe" << endl;
	}
}

NodoABB *Binario::buscarNodo(NodoABB *raiz, int dato) {
	if (raiz == NULL) {
		return NULL;
	}

	if (raiz->id == dato) {
		return raiz;
	}
	else {
		if (dato < raiz->id) {
			return buscarNodo(raiz->izquierda, dato);
		}
		else {
			return buscarNodo(raiz->derecha, dato);
		}
	}
}

NodoABB *Binario::busNodo(int dato) {
	if (existe(dato)) {
		return buscarNodo(raiz, dato);
	}
	return NULL;
}

NodoABB *Binario::ModNodo(NodoABB *raiz, int dato, NodoABB *matriz) {

	if (raiz->id == dato) {
		raiz->principal = matriz->principal;
		raiz->columnas = matriz->columnas;
		raiz->filas = matriz->filas;
		raiz->contenido = matriz->contenido;
		return raiz;
	}
	else {
		if (dato < raiz->id) {
			raiz->izquierda = ModNodo(raiz->izquierda, dato, matriz);
		}
		else {
			raiz->derecha = ModNodo(raiz->derecha, dato, matriz);
		}
	}
	return raiz;
}

void Binario::modificar(int dato, NodoABB *matriz) {
	if (existe(dato)) {
		raiz = ModNodo(raiz, dato, matriz);
	}
}

//Crear Arbol espejo usando un segundo nodo para graficarlo cuando se pida
void Binario::Espejo(NodoABB *raiz_E) {
	if (raiz_E == NULL)
		return;
	else
	{
		NodoABB *temp;

		Espejo(raiz_E->izquierda);
		Espejo(raiz_E->derecha);

		temp = raiz_E->izquierda;
		raiz_E->izquierda = raiz_E->derecha;
		raiz_E->derecha = temp;
	}
}

void Binario::graficar() {

	grafica = "";

	ofstream arch;

	arch.open("ABB.dot");
	arch << "digraph g{" << endl;
	arch << "\tnode [shape=record,width=.9,height=.5,style=filled,fillcolor=orangered2];\n";

	grafica = recorrer(raiz);

	arch << grafica;
	arch << "}" << endl;
	arch.close();
	system("dot -Tpng ABB.dot -o ABB.png");
	system("ABB.png");
}

//Crea la grafica del arbol espejo
void Binario::graficar_Espejo() {

	grafica = "";
	//crea una "copia" de la raiz en el espejo para que no altere la raiz principal
	raiz_Espejo = raiz;
	Espejo(raiz_Espejo); //ejecuta el metodo de espejo que cambia las direcciones de los punteros

	ofstream arch;

	arch.open("ABB_Espejo.dot");
	arch << "digraph g{" << endl;
	arch << "\tnode [shape=record,width=.9,height=.5,style=filled,fillcolor=orangered2];\n";
	grafica = recorrer(raiz);
	arch << grafica;
	arch << "}" << endl;
	arch.close();
	system("dot -Tpng ABB_Espejo.dot -o ABB_Espejo.png");
	system("ABB_Espejo.png");
	Espejo(raiz_Espejo);
}

string Binario::recorrer(NodoABB *inicio) {
	if (inicio != NULL) {

		if (inicio->izquierda != NULL) {
			grafica += "\tNode" + cadena(inicio->id) + ":C0->" + "Node" + cadena(inicio->izquierda->id) + ":C3; \n";
		}
		if (inicio->derecha != NULL) {
			grafica += "\tNode" + cadena(inicio->id) + ":C1->" + "Node" + cadena(inicio->derecha->id) + ":C3; \n";
		}

		recorrer(inicio->izquierda);
		recorrer(inicio->derecha);
		grafica += "\n \tNode" + cadena(inicio->id) + "[label = \"<C0>|<C3>Capa_" + cadena(inicio->id) + "|<C1>\"] \n";
	}
	return grafica;
}

void Binario::crear_IMG(NodoABB *inicio) {
	MatrizDisperza imagen_completa = new MatrizDisperza(true);
	string contenido, linea;

	for (int fil = 0; fil <= inicio->filMax; fil++) {
		for (int col = 0; col <= inicio->colMax; col++) {
			imagen_completa.Insertar(inicio->id, fil + 1, col + 1,7,7);
		}
	}

	contenido = inicio->contenido;
	splitear_Capas(contenido, imagen_completa, inicio->id);
	imagen_completa.graficar2(inicio->id, imagen_completa.Cprincipal);
}

void Binario::splitear_Capas(string str, MatrizDisperza imagen_completa, int id) {
	string palabra = "";
	bool encontradoF, encontradoC;
	int fila, columna;
	string color;

	for (auto x : str) {
		if (x == '{') {
			encontradoC = false;
			encontradoF = false;
			palabra = "";
		}
		else if (x == ',') {

			if (encontradoF == false) {
				//cout << "la coordenada en fila es: " << palabra << endl;
				fila = atoi(palabra.c_str());
				encontradoF = true;
			}
			else if (encontradoC == false) {
				//cout << "la coordenada en columna es: " << palabra << endl;
				columna = atoi(palabra.c_str());
				encontradoC = true;
			}
			palabra = "";
		}
		else if (x == ';') {
			color = palabra;
			imagen_completa.Insertar(id, fila, columna,color);
			encontradoC = false;
			encontradoF = false;
			palabra = "";
		}
		else if (x == '}') {
			fila = 0;
			columna = 0;
			encontradoC = false;
			encontradoF = false;
		}
		else if (x == '\n') {
			palabra = "";
		}
		else {
			palabra += x;
		}
	}
}

void Binario::PreOrden(NodoABB *raiz) {
	if (raiz != NULL) {
		//cout << raiz->id << " ";
		preOrd += cadena(raiz->id) + " ";

		PreOrden(raiz->izquierda);
		PreOrden(raiz->derecha);
	}
}

void Binario::InOrden(NodoABB *raiz) {
	if (raiz != NULL) {
		InOrden(raiz->izquierda);

		//cout << raiz->id << " ";
		inOrd += cadena(raiz->id) + " ";

		InOrden(raiz->derecha);
	}
}

void Binario::PostOrden(NodoABB *raiz) {
	if (raiz != NULL) {
		PostOrden(raiz->izquierda);
		PostOrden(raiz->derecha);

		//cout << raiz->id << " ";
		posOrd += cadena(raiz->id) + " ";
	}
}

void Binario::buscarHojas(NodoABB *raiz) {
	if (raiz != NULL) {
		if (raiz->izquierda == NULL && raiz->derecha == NULL) {
			hojas += "capa_" + cadena(raiz->id) + " ";
		}
		buscarHojas(raiz->izquierda);
		buscarHojas(raiz->derecha);
	}
}

string Binario::bHojas() {
	hojas = "";
	buscarHojas(raiz);
	return hojas;
}

string Binario::cadena(int n) {
	stringstream flujo;
	flujo << n;
	return(flujo.str());
}