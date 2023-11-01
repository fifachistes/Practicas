// tema3ej5.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
using namespace std;

int main()
{
	char car;
	int i = 0, x = 0, z = 0;
	cout << "Mete lo que quieras en verdad=" << endl;
	cin >> car;
	while (car != '*'){
		
		if (car >= 'a' && car <= 'z' || car >= '1' && car <= '9' || car >= 'A' && car <= 'Z') {
			cout << car << " es alfanumerico." << endl;
			if (car >= 'a' && car <= 'z') {
				cout << "Es una minuscula" << endl;
				i++;

			}
			if (car >= 'A' && car <= 'Z') {
				cout << " Es una mayuscula" << endl;
				x++;
			}
			if (car >= '1' && car <= '9') {
				cout << "Es un numero" << endl;
				z++;
			}
			cin >> car;
		}
		}


		cout << " El num de digitos es =" << z << " El numero de minusculas =" << i << "El numero de mayusculas es =" << x << endl;

	
	return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
