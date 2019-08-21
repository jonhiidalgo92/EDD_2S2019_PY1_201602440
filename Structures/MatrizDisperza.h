#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "NodoMatriz.h"


using namespace std;


class MatrizDisperza
{
private:
	int filMax = 0;
	int colMax = 0;

public:

	NodoMatriz * CabeceraC;
	NodoMatriz *CabeceraF;
	NodoMatriz *Cprincipal;
	bool encontradofil = false;
	bool encontradoCol = false;
	string relaciones = "", labels = "", rank = "";


	MatrizDisperza(bool c);
	void Insertar(int fil, int col, int R, int G, int B);
	void insertarFila(int fil);
	void insertarColumna(int col);
	void insertarCelda(int x, int y, int R, int G, int B);

	string cadena(int n);
	void buscarfila(int fil);
	void buscarcol(int col);
	void buscarCelda(int col, int fil);

	NodoMatriz *ObtenerCelda(int col, int fil);

	void graficar(int id, NodoMatriz *principal);
	void graficar2(int id, NodoMatriz *principal);
	void recorrer(NodoMatriz *inicio);
	void asignar_limites(int fil, int col);
};
