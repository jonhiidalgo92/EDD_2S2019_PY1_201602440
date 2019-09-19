#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string> 
#include "MatrizDisperza.h"
#include "NodoABB.h"

class Binario
{
private:
	string grafica = "";

public:

	Binario(bool a) {
		raiz = NULL;
		principal = NULL;
		no_Nodos = 0;
	}
	NodoABB *raiz;
	NodoABB *raiz_Espejo;
	NodoMatriz *principal;
	string hojas = "";
	string preOrd = "";
	string inOrd = "";
	string posOrd = "";
	int no_Nodos;

	bool existeB(NodoABB *raiz, int dato);
	bool existe(int dato);
	NodoABB *insertar(NodoABB *raiz, int dato);
	void add(int dato);
	NodoABB *eliminar(NodoABB *raiz, int dato);
	void elim(int dato);
	NodoABB *buscarNodo(NodoABB *raiz, int dato);
	NodoABB *busNodo(int dato);
	NodoABB *ModNodo(NodoABB *raiz, int dato, NodoABB *matriz);
	void modificar(int dato, NodoABB *matriz);
	void Espejo(NodoABB *raiz_E);
	void graficar();
	void graficar_Espejo();
	string recorrer(NodoABB *raiz);
	void crear_IMG(NodoABB *inicio);
	void splitear_Capas(string str, MatrizDisperza imagen_completa, int id);
	void PreOrden(NodoABB *raiz);
	void InOrden(NodoABB *raiz);
	void PostOrden(NodoABB *raiz);
	void buscarHojas(NodoABB *raiz);
	string bHojas();
	string cadena(int n);
};

