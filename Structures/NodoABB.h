#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string> 
#include "NodoMatriz.h"
class NodoABB
{
public:
	NodoABB() {
		derecha = NULL;
		izquierda = NULL;
		contenido = "";
		filMax = 0;
		colMax = 0;
	}
	int id;
	NodoABB *derecha;
	NodoABB *izquierda;
	NodoMatriz *principal;
	NodoMatriz *filas;
	NodoMatriz *columnas;
	string contenido;
	int filMax;
	int colMax;


};