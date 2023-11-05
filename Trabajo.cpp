// ejtema3.1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//






#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;
// hacer una funcion para rand

// Funciones varias
// Cargar carretera, primer ver si archivo esta bien;

bool cargaCarretera(tCarretera carretera) { 
	// bool que guarda la validez de carga carretera
	bool valido;
	string nombre;

	cout << "Introduce el nombre del archivo de la carrera : " << endl;
	cin >> nombre;

	fstream archivo;
	archivo.open(nombre) {
		// Nos abre el archivo de la carretera, 
		if ( archivo.is_open()){
			valido = true;
			char c;
			bool clavo;
			bool sorpresa;
			bool esPrimerNum = true;
			archivo.get(c);
			while (c != 'X') {
				// nos ponemos en los distintos casos escenario,  he visto que es c 
				if (c == 'C') {
					clavo = true; // te guarda que es un clavo hast lo contario
					sorpresa = false;
					esPrimerNum = true;
				}
				else if ( c== 'S'){
					sorpresa = true;
					clavo = false;
					esPrimerNum = true; // al poner esprimernum true se vuelve se te restablece la entrada al bucle
				}
				else if ( '0' <= c <= '9') {
					if (esPrimerNum) {
						esPrimerNum = false; // a partir de aqui el computer sabe es primer num es false
					}
					else { // el primer numero no pasa aqui xq es un else, y un numero dependiendo si clavo y sopresa es true se te guarda en un valor o otro
						if (clavo) { 
							// para llegar aqui
							// asociamos el primer numero que nos interesa xq guardamos la casilla de la carreterrra a un clavo
							carretera[c] = stringToEnum("CLAVO"); //REVISION
						}
						else if (sorpresa){
							carretera[c] = stringToEnum("SORPRESA");
						
						}
					}
				}
				archivo.get(c)
			}
		}
		else {
			valido = false;
		}
	}

	return valido; // al ser valido se te cargan los array q es lo que quieres
}
// // transforma la carretera en un string de tipo enumerado

tTipoPosicion stringToEnum(string s) {
	tTipoPosicion conversion = s;

	return conversion;


}

// Funciones de visualizacion de la carretera,
 
// dibujar linea horizontal superior
void dibujaLineaHorizontalSuperior() {
	cout << CHAR_ESQUINA_SUPERIOR_IZQUIERDA; 
	for (int k = 0; k < LONG_CARRETERA; k++) {
		cout << CHAR_LINEA_HORIZONTAL;
	}
	cout << CHAR_ESQUINA_SUPERIOR_DERECHA;
}
// dibujar linea horizontal inferior
void dibujaLineaHorizontalInferior() {
	cout << CHAR_ESQUINA_INFERIOR_IZQUIERDA;
	for (int k = 0; k < LONG_CARRETERA; k++) {
		cout << CHAR_LINEA_HORIZONTAL;
	}
	cout << CHAR_ESQUINA_INFERIOR_DERECHA;
}
// dibujo carril
void dibujaCarril(const tCarretera carretera, int posCoche) {
	cout << CHAR_LINEA_VERTICAL;
	for (int i = 0;i < LONG_CARRETERA;i++) {
		if (carretera[i] == "CLAVO"){
			cout<<  CHAR_CLAVO;
		}
		else if (carretera[i] == "SORPRESA") {
			cout << CHAR_SORPRESA;
		}
		else {
			cout << CHAR_NORMAL;
		}
	}
	cout << CHAR_LINEA_VERTICAL << endl << CHAR_LINEA_VERTICAL;

	for (int i = 0;i < LONG_CARRETERA;i++) {
		if (i == posCoche) {
			cout << CHAR_COCHE;
		}
		else {
			cout << CHAR_NORMAL;
		}
	}

	cout << CHAR_LINEA_VERTICAL;
}
// punto union anteriores funciones
void dibujaCarretera(const tCarretera carretera, int posCoche) {
	dibujaLineaHorizontalSuperior();
	dibujaCarril(carretera, posCoche)
	dibujaLineaHorizontalInferior();
}



// definir si posicion es sorpresa
bool esSorpresa(const tCarretera carretera, int posCoche) {
	return  carretera[posCoche] == "SORPRESA";
}
// definir se es clavo
bool esClavo(const tCarretera carretera, int posCoche) {
	return carreterra[posCoche] == "CLAVO";
}
// funcion que calcula la siguient o anterior posicion sorpresa
int buscaPosicionSorpresa(const tCarretera carretera, int posIni, int incr) {
	int posicion = 0;

	if (incr == -1) {
		for (int i = posIni-1; i > 0; i--) {
			if (carretera[i] == "SORPRESA") {
				posicion = i;
			}
		}
	}
	else if (incr == 1) {
		for (int i = posIni+1; i < LONG_CARRETERA; i++) {
			if (carretera[i] == "SORPRESA") {
				posicion = i;
			}
		}
	}

	return posicion;
}
// funcion avanza teniendo en cuenta las reglas marcadas
int avanza(int posCoche) {
	int nueva_pos = posCoche;
	int pasos;

	if (DEBUG) {
		cout << "Introduce un número de pasos : " << endl;
		cin >> pasos;
	}
	else {
		pasos = 0 + rand() % (MAX_PASOS + 1 - 0);
	}

	nueva_pos += pasos;

	if (nueva_pos < 0) {
		nueva_pos = 0;
	}
	else if (nueva_pos > LONG_CARRETERA) {
		nueva_poas = LONG_CARRETERA;
	}

	return nueva_pos;
}
// Función que calcula si el coche ha terminado la carrera
bool haLlegado(int posCoche) {
	return posCoche >= LONG_CARRERA;
}
//  calcule la posicion viendo los parametros marcados
bool calculaPosición(const tCarretera carretera, int& posCoche, int& tiempoParado) {
	bool esSorpresa = false;

	if (carretera[posCoche] == "CLAVO") {
		tiempoParado += 3;
	}
	else if (carrera[posCoche] == "SORPRESA") {
		int valorRandom = rand() % 2 == 0;

		if (valorRandom) {
			incr = 1;
		}
		else {
			incr = -1;
		}

		posCoche = buscaPosicionSorpresa(carretera, posCoche, incr);

		esSorpresa = true;
	}

	return esSorpresa;
}

// avanzar el carril
void avanzaCarril(const tCarretera carretera, int& posCoche, int& tiempoParado) {
	if (haLlegado(posCoche)) {
		posCoche = LONG_CARRETERA;
	}
	else {
		dibujaCarretera(carretera, posCoche);
		if (calculaPosición(carretera, posCoche, tiempoParado)) {
			dibujaCarretera(carretera, posCoche);
		}
	}
}

// mientras no llegue a la meta tiene que haber movimiento
void simulaCarrera(const tCarretera carretera, int posCoche, int tiempoParado) {
	while (!haLlegado(posCoche)) {
		avanzaCarril(carretera, posCoche, tiempoParado)
	}
}

const int LONG_CARRETERA = 10;
const int MAX_PASOS = 3;
const bool DEBUG = true;
const char CHAR_LINEA_HORIZONTAL = 205; // ˭
const char CHAR_ESQUINA_SUPERIOR_IZQUIERDA = 201; // ╔═
const char CHAR_ESQUINA_SUPERIOR_DERECHA = 187; // ═╗
const char CHAR_ESQUINA_INFERIOR_IZQUIERDA = 200; // ╚═
const char CHAR_ESQUINA_INFERIOR_DERECHA = 188; // ═╝
const char CHAR_LINEA_VERTICAL = 186; // ║
const char CHAR_COCHE = 254; // ■
const char CHAR_CLAVO = 193; // ┴
 
const char CHAR_SORPRESA = 63; // ?
const char CHAR_NORMAL = 32;

int main() {
	srand(time(NULL));
	
	typedef string tTipoPosicion;
	int posCoche = 0;
	int tiempoParado = 0;
	
	bool exito = cargaCarretera();

	if (exito) {
		simulaCarrera();
	}

	return 0;
}

