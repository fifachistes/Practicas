// ej3.alex.kei.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
int const DIM = 3;
using namespace std;
typedef int tMatriz[DIM][DIM];

void cargaMatriz (tMatriz matriz);
int menu();
tMatriz suma(tMatriz matriz1, tMatriz matriz2);
tMatriz resta (tMatriz matriz1, tMatriz matriz2);
tMatriz multiplicacion (tMatriz matriz1, tMatriz matriz2);
tMatriz transponer (tMatriz matriz1, tMatriz matriz2);

void mostrarM (tMatriz matriz1);



int main()
{
	int caso;
	tMatriz matriz1;
	tMatriz matriz2;
	tMatriz matrizR;
	cout << "Inserta datos de matriz 1" << endl;
	cargaMatriz(matriz1);
	cout << "Inserta datos de matriz 2" << endl;
	cargaMatriz(matriz2);
	 

	do {
	 caso=	menu();
	 switch (caso) {

	 case 1: {
		matrizR = suma( matriz1, matriz2);
		mostrarM(matrizR);

		 break;
	 }
	 case 2: {
		 matrizR = resta (matriz1, matriz2);
		 mostrarM(matrizR);
		 break;
      }
	 case 3: {
		 matrizR = multiplicacion(matriz1, matriz2);
		 mostrarM(matrizR);

		 break;
	 }
	 case 4: {
		 matrizR = transponer (matriz1, matriz2);
		 mostrarM(matrizR);


		 break;
	 }
	 case 5: {

		 break;
	 }

		   while (caso !=6)
	
	



	//Trasposición
	for (int row = 0; row < DIM; row++) {
		for (int col = 0; col < DIM; col++) {
			resultado[row][col] = matriz1[col][row];
		}
	}

	//Silla

	return 0;
}

void cargaMatriz(tMatriz matriz) 
{
	for (int row = 0; row < DIM; row++) {
		for (int col = 0; col < DIM; col++) {
			cout << "Mete los datos de fila " << row << " columna " << col << endl;
			cin >> matriz[row][col];
		}
	}
}
int menu() {
	int aux;
	do {
		cout << "Opcion 1: sumar" << endl;
		cout << "Opcion 2: restar" << endl;
		cout << "Opcion 3: multiplicar" << endl;
		cout << "Opcion 4: trasponer" << endl;
		cout << "Opcion 5: hacer silla" << endl;
		cout<< "Opcion 6: salir" << endl;

		cin >> aux;
		
	} while (aux > 6 || aux < 1);

	return aux;
}

 tMatriz suma(tMatriz matriz1, tMatriz matriz2) {
	tMatriz resultado;
	for (int row = 0; row < DIM; row++) {
		for (int col = 0; col < DIM; col++) {
			resultado[row][col] = matriz1[row][col] + matriz2[row][col];
		}
	}

	return resultado;
}
void mostrarM(tMatriz matriz1) {
	for (int row = 0; row < DIM; row++) {
		for (int col = 0; col < DIM; col++) {
			cout << matriz1[row][col] << " ";
		}
		cout << endl;
	}
}
tMatriz resta(tMatriz matriz1, tMatriz matriz2) {
	tMatriz resultado;
	//Resta
	for (int row = 0; row < DIM; row++) {
		for (int col = 0; col < DIM; col++) {
			resultado[row][col] = matriz1[row][col] - matriz2[row][col];
		}
	}

	return resultado;
}

tMatriz multiplicacion(tMatriz matriz1, tMatriz matriz2) {
	tMatriz resultado;


	//Multiplicación
	for (int row = 0; row < DIM; row++) {
		for (int col = 0; col < DIM; col++) {
			int valorCelda = 0;
			//Calcular valor
			for (int x = 0; x < DIM; x++) {
				valorCelda += matriz1[row][x] * matriz2[x][col];
			}
			resultado[row][col] = valorCelda;
		}
	}
	return resultado;
}

tMatriz transponer(tMatriz matriz1, tMatriz matriz2) {
	//Trasposición
	for (int row = 0; row < DIM; row++) {
		for (int col = 0; col < DIM; col++) {
			resultado[row][col] = matriz1[col][row];
		}

		return resultado;


}