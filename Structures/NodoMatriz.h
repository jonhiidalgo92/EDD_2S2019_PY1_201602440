#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class NodoMatriz
{

public:

	//Apuntadores
	NodoMatriz * Arriba;
	NodoMatriz *Abajo;
	NodoMatriz *Siguiente;
	NodoMatriz *Anterior;

	//Variables De las Coordenadas
	int fila;
	int columna;


	//Variables Almacenan color
	int R;
	int G;
	int B;
	string colores;

	//Variables Utilizadas Para Graficar
	int id;

	//Variables de Random
	int contador;
	string concat;
	long long hash;

	NodoMatriz()
	{
		for (int a = 0; a<7; a++)
		{
			contador = rand() % 9;
			concat += cadena(contador);
		}

		std::string::size_type sz;
		hash = stol(concat, &sz);
	}



private:
	string cadena(int n)
	{
		stringstream flujo;
		flujo << n;
		return(flujo.str());
	}


};
