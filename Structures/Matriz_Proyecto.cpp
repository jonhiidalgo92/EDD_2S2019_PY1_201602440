// Matriz_Proyecto.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MatrizDisperza.h"


int main(int argc, char *argv[])
{
	MatrizDisperza * mat = new MatrizDisperza(true);
	mat->Insertar(15, 10, 255, 229, 204);
	mat->Insertar(3, 6, 255, 229, 204);
	mat->Insertar(5, 2, 255, 229, 204);
	mat->Insertar(16, 11, 255, 229, 204);
	mat->Insertar(4, 1, 255, 229, 204);
	mat->Insertar(1, 1, 255, 229, 204);
	mat->Insertar(2, 2, 255, 229, 204);
	mat->Insertar(2, 3, 255, 229, 204);
	mat->Insertar(15, 1, 255, 229, 204);
	mat->Insertar(15, 2, 255, 229, 204);
	mat->Insertar(15, 3, 255, 229, 204);
	mat->graficar(1, mat->Cprincipal);



    return 0;
}

