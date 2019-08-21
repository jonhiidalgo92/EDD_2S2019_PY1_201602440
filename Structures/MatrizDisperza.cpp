#include "stdafx.h"
#include "MatrizDisperza.h"

#include <iostream>

using namespace std;

MatrizDisperza::MatrizDisperza(bool c)
{
	Cprincipal = NULL;
	CabeceraC = NULL;
	CabeceraF = NULL;
}



void MatrizDisperza::Insertar(int fil, int col, int R, int G, int B) {
	encontradofil = false;
	encontradoCol = false;

	if (Cprincipal == NULL) {
		NodoMatriz *nuevo = new NodoMatriz();
		nuevo->R = 0;
		nuevo->G = 0;
		nuevo->B = 0;
		nuevo->colores = "Matriz";

		Cprincipal = nuevo;
		insertarFila(fil);
		insertarColumna(col);
		Cprincipal->Abajo = CabeceraF;
		Cprincipal->Siguiente = CabeceraC;
		insertarCelda(fil, col, R, G, B);
	}
	else {

		for (int fila = 1; fila <= fil; fila++) {
			buscarfila(fila);
			if (encontradofil != true) {
				insertarFila(fila);
				Cprincipal->Abajo = CabeceraF;
			}
		}

		for (int columna = 1; columna <= col; columna++) {
			buscarcol(columna);
			if (encontradoCol != true) {
				insertarColumna(columna);
				Cprincipal->Siguiente = CabeceraC;
			}
		}

		insertarCelda(fil, col, R, G, B);
		asignar_limites(fil, col);
	}
}

void MatrizDisperza::insertarFila(int fil) {
	NodoMatriz *nuevo = new NodoMatriz();
	nuevo->fila = fil;
	nuevo->R = 0;
	nuevo->G = 0;
	nuevo->B = 0;
	nuevo->colores = "F:" + cadena(fil);

	NodoMatriz *temp = CabeceraF;
	bool estadoInsertar = false;
	if (CabeceraF == NULL) {
		CabeceraF = nuevo;
	}
	else {
		do {
			if (nuevo->fila < temp->fila) {
				nuevo->Abajo = temp;
				temp->Arriba = nuevo;
				if (temp->hash == CabeceraF->hash) {
					CabeceraF = nuevo;
				}
				estadoInsertar = true;
			}
			else {
				if (temp->Abajo != NULL) {
					if (nuevo->fila < temp->Abajo->fila) {
						nuevo->Abajo = temp->Abajo;
						temp->Abajo->Arriba = nuevo;
						temp->Abajo = nuevo;
						nuevo->Arriba = temp;
						estadoInsertar = true;
					}
				}
				else {
					temp->Abajo = nuevo;
					nuevo->Arriba = temp;
					estadoInsertar = true;
				}
			}
			temp = temp->Abajo;
		} while (estadoInsertar == false && temp != NULL);
	}
}

void MatrizDisperza::insertarColumna(int col) {
	NodoMatriz *nuevo = new NodoMatriz();
	nuevo->columna = col;
	nuevo->R = 0;
	nuevo->G = 0;
	nuevo->B = 0;
	nuevo->colores = "C:" + cadena(col);

	NodoMatriz *temp = CabeceraC;
	bool estadoInsertar = false;
	if (CabeceraC == NULL) {
		CabeceraC = nuevo;
	}
	else {
		do {
			if (nuevo->columna < temp->columna) {
				nuevo->Siguiente = temp;
				temp->Anterior = nuevo;
				if (temp->hash == CabeceraC->hash) {
					CabeceraC = nuevo;
				}
				estadoInsertar = true;
			}
			else {
				if (temp->Siguiente != NULL) {
					if (nuevo->columna < temp->Siguiente->columna) {
						nuevo->Siguiente = temp->Siguiente;
						temp->Siguiente->Anterior = nuevo;
						temp->Siguiente = nuevo;
						nuevo->Anterior = temp;
						estadoInsertar = true;
					}
				}
				else {
					temp->Siguiente = nuevo;
					nuevo->Anterior = temp;
					estadoInsertar = true;
				}
			}
			temp = temp->Siguiente;
		} while (estadoInsertar == false && temp != NULL);
	}
}

void MatrizDisperza::insertarCelda(int x, int y, int R, int G, int B) {
	NodoMatriz *tempY;
	NodoMatriz *tempX;
	NodoMatriz *nuevo = new NodoMatriz();
	nuevo->fila = x;
	nuevo->columna = y;
	nuevo->R = R;
	nuevo->G = G;
	nuevo->B = B;
	nuevo->colores = cadena(R) + "-" + cadena(G)  +"-" + cadena(B) + "\\n ";


	tempX = Cprincipal;
	while (tempX != NULL) {
		if (tempX->columna == x) {
			tempY = tempX;
			bool estadoInsertar = false;
			do {
				if (nuevo->fila == tempY->fila) {
					tempY->colores = nuevo->colores;
					estadoInsertar = true;
				}
				else {
					if (nuevo->fila < tempY->fila) {
						nuevo->Abajo = tempY;
						tempY->Arriba = nuevo;
						if (tempY->hash == tempX->hash) {
							tempX = nuevo;
						}
						estadoInsertar = true;
					}
					else {
						if (tempY->Abajo != NULL) {
							if (nuevo->fila < tempY->Abajo->fila) {
								nuevo->Abajo = tempY->Abajo;
								tempY->Abajo->Arriba = nuevo;
								tempY->Abajo = nuevo;
								nuevo->Arriba = tempY;
								estadoInsertar = true;
							}
						}
						else {
							tempY->Abajo = nuevo;
							nuevo->Arriba = tempY;
							estadoInsertar = true;
						}
					}
				}

				tempY = tempY->Abajo;
			} while (estadoInsertar == false && tempY != NULL);
			estadoInsertar = false;
			break;

		}
		else {
			tempX = tempX->Siguiente;
		}
	}

	tempY = Cprincipal;
	while (tempY != NULL) {
		if (tempY->fila == y) {
			tempX = tempY;

			bool estadoInsertar = false;
			do {
				if (nuevo->columna == tempX->columna) {
					tempX->colores = nuevo->colores;
					estadoInsertar = true;
				}
				else {
					if (nuevo->columna < tempX->columna) {
						nuevo->Siguiente = tempX;
						tempX->Anterior = nuevo;
						if (tempX->hash == tempY->hash) {
							tempY = nuevo;
						}
						estadoInsertar = true;
					}
					else {
						if (tempX->Siguiente != NULL) {
							if (nuevo->columna < tempX->Siguiente->columna) {
								nuevo->Siguiente = tempX->Siguiente;
								tempX->Siguiente->Anterior = nuevo;
								tempX->Siguiente = nuevo;
								nuevo->Anterior = tempX;
								estadoInsertar = true;
							}
						}
						else {
							tempX->Siguiente = nuevo;
							nuevo->Anterior = tempX;
							estadoInsertar = true;
						}
					}
				}

				tempX = tempX->Siguiente;
			} while (estadoInsertar == false && tempX != NULL);
			estadoInsertar = false;
			break;

		}
		else {
			tempY = tempY->Abajo;
		}
	}
}

void MatrizDisperza::buscarfila(int fil) {
	NodoMatriz *temp = Cprincipal;
	encontradofil = false;
	do {
		if (temp->fila == fil) {
			encontradofil = true;
		}
		else {
			temp = temp->Abajo;
		}
	} while (temp != NULL && encontradofil != true);
}

void MatrizDisperza::buscarcol(int col) {
	NodoMatriz *temp = Cprincipal;
	encontradoCol = false;
	do {
		if (temp->columna == col) {
			encontradoCol = true;

		}
		else {
			temp = temp->Siguiente;
		}
	} while (temp != NULL && encontradoCol != true);
}

void MatrizDisperza::buscarCelda(int col, int fil) {
	NodoMatriz *tempY;
	NodoMatriz *tempX;
	tempX = Cprincipal;
	while (tempX != NULL) {
		if (tempX->columna == col) {
			tempY = tempX;
			while (tempY != NULL) {
				if (tempY->fila == fil) {

					cout << "El contador en (" << fil << "," << col << ") es......" << cadena(tempY->hash) << endl;
					break;
				}
				else {
					tempY = tempY->Abajo;
				}
			}
			break;
		}
		else {
			tempX = tempX->Siguiente;
		}
	}

}

NodoMatriz *MatrizDisperza::ObtenerCelda(int col, int fil) {
	NodoMatriz *tempY;
	NodoMatriz *tempX;
	tempX = Cprincipal;
	while (tempX != NULL) {
		if (tempX->columna == col) {
			tempY = tempX;
			while (tempY != NULL) {
				if (tempY->fila == fil) {

					return tempY;
				}
				else {
					tempY = tempY->Abajo;
				}
			}
			break;
		}
		else {
			tempX = tempX->Siguiente;
		}
	}
	return NULL;
}

void MatrizDisperza::asignar_limites(int fil, int col) {
	if (fil > filMax) {
		filMax = fil;
	}
	if (col > colMax) {
		colMax = col;
	}
}


void MatrizDisperza::graficar(int id, NodoMatriz *principal) {
	relaciones = "";
	labels = "";
	rank = "";
	ofstream archivo;
	archivo.open("Matriz_Capa" + cadena(id) + ".dot");
	archivo << "digraph G {" << endl;
	archivo << "\tnode [shape=record,width=.9,height=.5];" << endl;
	recorrer(principal);
	archivo << relaciones;
	archivo << labels;
	archivo << rank;
	archivo << "}" << endl;
	archivo.close();
	string str = "dot -Tpng Matriz_Capa" + cadena(id) + ".dot -o Matriz_Capa" + cadena(id) + ".png -Gcharset=latin1";
	const char *command = str.c_str();
	system(command);
	str = "Matriz_Capa" + cadena(id) + ".png";
	const char *command2 = str.c_str();
	system(command2);
	
}

void MatrizDisperza::graficar2(int id, NodoMatriz *principal) {
	string cuerpo = "";
	NodoMatriz *tempY = principal->Abajo;
	NodoMatriz *tempX;

	while (tempY != NULL) {
		cuerpo += "<tr>";
		tempX = tempY->Siguiente;
		while (tempX != NULL) {
			cuerpo += "<td BGCOLOR = \"" + tempX->colores + "\" height=\"40\" width=\"40\"></td>";
			tempX = tempX->Siguiente;
		}
		cuerpo += "</tr>\n";
		tempY = tempY->Abajo;
	}


	std::ofstream archivo;
	archivo.open("Imagen_" + cadena(id) + ".dot");
	archivo << "digraph G {" << endl;
	archivo << "\tnode [shape=none] \nMat1 [label=<\n <table border=\"0\" cellborder=\"0\" cellspacing = \"0\">" << endl;
	archivo << cuerpo;
	archivo << "</table>>]; \n }" << endl;
	archivo.close();
	string str = "dot -Tpng Imagen_" + cadena(id) + ".dot -o Imagen_" + cadena(id) + ".png -Gcharset=latin1";
	const char *command = str.c_str();
	system(command);
	str = "Imagen_" + cadena(id) + ".png";
	const char *command2 = str.c_str();
	system(command2);
}

void MatrizDisperza::recorrer(NodoMatriz *inicio) {
	NodoMatriz *tempY = inicio;
	NodoMatriz *tempX = inicio;


	while (tempY != NULL) {
		if (tempY != NULL) {
			if (tempY->Abajo != NULL) {
				relaciones += "\tNode" + cadena(tempY->hash) + "->" + "Node" + cadena(tempY->Abajo->hash) + "; \n";
				relaciones += "\tNode" + cadena(tempY->hash) + "->" + "Node" + cadena(tempY->Abajo->hash) + "[dir=back]; \n";
			}
			labels += "\n \tNode" + cadena(tempY->hash) + "[label = \"" + tempY->colores + "\"] \n";
		}
		tempY = tempY->Abajo;
	}

	bool bandera = false;
	bool primero = true;
	while (tempX != NULL) {
		if (tempX != NULL) {
			if (tempX->Siguiente != NULL) {
				relaciones += "\tNode" + cadena(tempX->hash) + "->" + "Node" + cadena(tempX->Siguiente->hash) + "; \n";
				relaciones += "\tNode" + cadena(tempX->hash) + "->" + "Node" + cadena(tempX->Siguiente->hash) + "[dir=back]; \n";
			}
			labels += "\n \tNode" + cadena(tempX->hash) + "[label = \"" + tempX->colores + "\"] \n";
			tempY = tempX->Siguiente;
			bandera = false;
			while (tempY != NULL) {
				if (tempY != NULL) {
					if (tempY->Abajo != NULL) {
						relaciones += "\tNode" + cadena(tempY->hash) + "->" + "Node" + cadena(tempY->Abajo->hash) + "; \n";

					}
					if (tempY->Arriba != NULL) {
						if (bandera == true) {
							relaciones += "\tNode" + cadena(tempY->hash) + "->" + "Node" + cadena(tempY->Arriba->hash) + "; \n";
							labels += "\n \tNode" + cadena(tempY->hash) + "[label = \"" + tempY->colores + "\"] \n";
						}
						bandera = true;
					}
					if (primero != true) {
						labels += "\n \tNode" + cadena(tempY->hash) + "[color=\"" + tempY->colores + "\",style=filled, label = \"" + tempY->colores + "\"] \n"; // modificar este para el terreno
					}
					else {
						labels += "\n \tNode" + cadena(tempY->hash) + "[label = \"" + tempY->colores + "\"] \n";
						primero = false;
					}

				}
				tempY = tempY->Abajo;
			}
		}

		tempX = tempX->Siguiente;
		primero = true;
	}

	tempY = inicio;

	while (tempY != NULL) {
		tempX = tempY->Abajo;
		bandera = false;
		while (tempX != NULL) {
			if (tempX != NULL) {
				if (tempX->Siguiente != NULL) {
					relaciones += "\tNode" + cadena(tempX->hash) + "->" + "Node" + cadena(tempX->Siguiente->hash) + "[constraint=false]\n";
				}
				if (tempX->Anterior != NULL) {
					if (bandera == true) {
						relaciones += "\tNode" + cadena(tempX->hash) + "->" + "Node" + cadena(tempX->Anterior->hash) + "[constraint=false]\n";
					}
					bandera = true;
				}
			}
			tempX = tempX->Siguiente;
		}
		tempY = tempY->Abajo;
	}

	tempY = inicio;

	while (tempY != NULL) {
		tempX = tempY;
		rank += "\t{rank = same; Node" + cadena(tempX->hash);
		while (tempX != NULL) {
			rank += ",Node" + cadena(tempX->hash);
			tempX = tempX->Siguiente;
		}
		rank += "};\n";
		tempY = tempY->Abajo;
	}

}


string MatrizDisperza::cadena(int n) {
	stringstream flujo;
	flujo << n;
	return(flujo.str());
}
