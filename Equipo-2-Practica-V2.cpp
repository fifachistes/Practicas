// Kei Rodriguez Hachimaru y Alejandro Redondo Fuentes
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int LONG_CARRETERA = 20;
const int MAX_PASOS = 3; // numerox maximo pasos en un movimiento en los 2 modos
const bool DEBUG = false;

const char CHAR_LINEA_HORIZONTAL = 205; // ━
const char CHAR_ESQUINA_SUPERIOR_IZQUIERDA = 201; // ┏
const char CHAR_ESQUINA_SUPERIOR_DERECHA = 187; // ┓
const char CHAR_ESQUINA_INFERIOR_IZQUIERDA = 200; // ┗
const char CHAR_ESQUINA_INFERIOR_DERECHA = 188; // ┛
const char CHAR_LINEA_VERTICAL = 186; // ┃
const char CHAR_COCHE = 254; // ■
const char CHAR_CLAVO = 193; // ┴
const char CHAR_SORPRESA = 63; // ?
const char CHAR_NORMAL = 32;

typedef enum { CLAVO, SORPRESA, NORMAL } tTipoPosicion; // typedef da un nombre a un tipo de datos definido en el programa
typedef tTipoPosicion tCarretera[LONG_CARRETERA]; // tTipoPosicion hace como de int, tipo elementos array

bool cargaCarretera(tCarretera carretera);
void dibujaLineaHorizontalSuperior();
void dibujaLineaHorizontalInferior();
void dibujaCarril(const tCarretera carretera, int posCoche);
void dibujaCarretera(const tCarretera carretera, int posCoche);
bool esSorpresa(const tCarretera carretera, int posCoche);
bool esClavo(const tCarretera carretera, int posCoche);
int buscaPosicionSorpresa(const tCarretera carretera, int posIni, int incr);
int avanza(int posCoche);
bool haLlegado(int posCoche);
bool calculaPosicion(const tCarretera carretera, int& posCoche, int& tiempoParado);
void avanzaCarril(const tCarretera carretera, int& posCoche, int& tiempoParado);
void simulaCarrera(const tCarretera carretera, int posCoche, int tiempoParado);

int main() {
    srand(time(NULL));
    int posCoche = 0;
    int tiempoParado = 0;

    tCarretera carretera;

    for (int i = 0; i < LONG_CARRETERA; i++) {
        carretera[i] = NORMAL;
    }

    bool exito = cargaCarretera(carretera);


    if (exito) {
        simulaCarrera(carretera, posCoche, tiempoParado);

        cout << "SE HA COMPLETADO LA CARRERA" << endl;
        cout << endl << "DESEA REALIZAR OTRA SIMULACION? (S/N)" << endl;
        char continuar;
        cin >> continuar;
        if (continuar == 'S') {
            posCoche = 0;
            tiempoParado = 0;

            for (int i = 0; i < LONG_CARRETERA; ++i) {
                carretera[i] = NORMAL;
            }

            exito = cargaCarretera(carretera);

            if (exito) {
                simulaCarrera(carretera, posCoche, tiempoParado);
            }
        }
    }
    else {
        cout << "Error, no se ha podido cargar el fichero";
    }

    return 0;
}

bool cargaCarretera(tCarretera carretera) {
    bool valido;
    string nombre;

    cout << "Dame el nombre del archivo : ";
    cin >> nombre;

    fstream archivo;
    archivo.open(nombre);
    if (archivo.is_open()) {
        valido = true;

        string valor;
        int numeroValores;
        int posicion;

        tTipoPosicion tipoPosicion;


        archivo >> valor;
        while (valor != "XX") {
            if (valor == "CLAVO") {
                archivo >> numeroValores;

                for (int i = 0; i < numeroValores; i++) {
                    archivo >> posicion;
                    carretera[posicion] = CLAVO;
                }
            }
            else if (valor == "SORPRESA") {
                archivo >> numeroValores;

                for (int i = 0; i < numeroValores; i++) {
                    archivo >> posicion;
                    carretera[posicion] = SORPRESA;
                }
            }

            /*
            tipoPosicion = stringToEnum(valor);
            archivo >> numeroValores;
            for (int i = 0; i < numeroValores; i++) {
                    archivo >> posicion;
                    carretera[posicion] = tipoPosicion;
             }
            */

            archivo >> valor;
        }
    }
    else {
        valido = false;
    }

    return valido;
}

// no se invoca. 
tTipoPosicion stringToEnum(const string s) {
    tTipoPosicion conversion;

    if (s == "CLAVO") {
        conversion = CLAVO;
    }
    else if (s == "SORPRESA") {
        conversion = SORPRESA;
    }
    else {
        conversion = NORMAL;
    }

    return conversion;
}

void dibujaLineaHorizontalSuperior() {
    cout << CHAR_ESQUINA_SUPERIOR_IZQUIERDA;
    for (int k = 0; k < LONG_CARRETERA; k++) {
        cout << CHAR_LINEA_HORIZONTAL;
    }
    cout << CHAR_ESQUINA_SUPERIOR_DERECHA << endl;

    return;
}

void dibujaLineaHorizontalInferior() {
    cout << CHAR_ESQUINA_INFERIOR_IZQUIERDA;
    for (int k = 0; k < LONG_CARRETERA; k++) {
        cout << CHAR_LINEA_HORIZONTAL;
    }
    cout << CHAR_ESQUINA_INFERIOR_DERECHA << endl;

    return;
}

void dibujaCarril(const tCarretera carretera, const int posCoche) {
    cout << CHAR_LINEA_VERTICAL;
    for (int i = 0; i < LONG_CARRETERA; i++) {
        if (carretera[i] == CLAVO) {
            cout << CHAR_CLAVO;
        }
        else if (carretera[i] == SORPRESA) {
            cout << CHAR_SORPRESA;
        }
        else {
            cout << CHAR_NORMAL;
        }
    }
    cout << CHAR_LINEA_VERTICAL << endl;
    cout << CHAR_LINEA_VERTICAL;

    if (posCoche == LONG_CARRETERA - 1) {
        cout << ' ';
    }

    for (int i = 0; i < LONG_CARRETERA; i++) {
        if (i == posCoche) {
            cout << CHAR_COCHE;
        }
        else {
            cout << CHAR_NORMAL;
        }
    }

    cout << CHAR_LINEA_VERTICAL << endl;

    return;
}

void dibujaCarretera(const tCarretera carretera, int posCoche) {
    dibujaLineaHorizontalSuperior();
    dibujaCarril(carretera, posCoche);
    dibujaLineaHorizontalInferior();

    return;
}

bool esSorpresa(const tCarretera carretera, int posCoche) {
    return carretera[posCoche] == SORPRESA;
}

bool esClavo(const tCarretera carretera, int posCoche) {
    return carretera[posCoche] == CLAVO;
}

int buscaPosicionSorpresa(const tCarretera carretera, int posIni, int incr) {
    int posicion = 0;

    if (incr == -1) {
        for (int i = posIni - 1; i > 0; i--) {
            if (carretera[i] == SORPRESA) {
                posicion = i;
                break;
            }
        }
    }
    else if (incr == 1) {
        for (int i = posIni + 1; i < LONG_CARRETERA; i++) {
            if (carretera[i] == SORPRESA) {
                posicion = i;
                break;
            }
        }
    }

    return posicion;
}

int avanza(int posCoche) {
    int nueva_pos;

    int pasos;

    if (DEBUG) {
        cout << "Introduce un número de pasos : ";
        cin >> pasos;
    }
    else {
        cout << "Pulsa una tecla para continuar" << endl;
        getchar();
        pasos = 1 + rand() % MAX_PASOS;
        cout << "EL COCHE AVANZA " << pasos << " PASOS." << endl;
    }

    nueva_pos = posCoche + pasos;

    if (nueva_pos < 0) {
        nueva_pos = 0;
    }
    else if (nueva_pos >= LONG_CARRETERA) {
        nueva_pos = LONG_CARRETERA - 1;
    }

    return nueva_pos;
}

bool haLlegado(int posCoche) {
    if (posCoche >= LONG_CARRETERA - 1)
        return true;
    else
        return false;

    // return posCoche >= LONG_CARRETERA - 1;
}

bool calculaPosicion(const tCarretera carretera, int& posCoche, int& tiempoParado) {
    bool esSorpresa = false;

    if (carretera[posCoche] == CLAVO) {
        int turnos = 1 + rand() % MAX_PASOS;
        tiempoParado += turnos; // INCREMENTO ??
    }
    else if (carretera[posCoche] == SORPRESA) {
        cout << "POSICION SORPRESA." << endl;

        int valorRandom = rand() % 2 == CLAVO; // CLAVO ??
        int incr;

        if (DEBUG) {
            cout << "Introduce 0 (avanzar), 1 (retroceder): ";
            char avanzar;
            cin >> avanzar;
            if (avanzar == '0') {
                incr = 1;
            }
            else {
                incr = -1;
            }
        }
        else {
            if (valorRandom) {
                incr = 1;
            }
            else {
                incr = -1;
            }
        }

        posCoche = buscaPosicionSorpresa(carretera, posCoche, incr);

        if (incr == 1) {
            cout << "RETROCEDES HASTA LA SIGUIENTE SORPRESA EN LA POSICION " << posCoche << endl;
        }
        else {
            cout << "AVANZAS HASTA LA ANTERIOR SORPRESA EN LA POSICION " << posCoche << endl;
        }

        esSorpresa = true;
    }

    return esSorpresa;
}

void avanzaCarril(const tCarretera carretera, int& posCoche, int& tiempoParado) {
    if (haLlegado(posCoche)) {
        posCoche = LONG_CARRETERA;
    }
    else {
        dibujaCarretera(carretera, posCoche);
        if (calculaPosicion(carretera, posCoche, tiempoParado)) {
            dibujaCarretera(carretera, posCoche);
        }
    }

    return;
}

void simulaCarrera(const tCarretera carretera, int posCoche, int tiempoParado) {
    getchar();
    while (!haLlegado(posCoche)) {
        avanzaCarril(carretera, posCoche, tiempoParado);

        if (tiempoParado > 0) {
            cout << "EL COCHE HA PINCHADO. ESTARA INMOVILIZADO" << tiempoParado << "PASOS" << endl;
            while (tiempoParado != 0) {
                cout << "EL COCHE ESTA PINCHADO. LE QUEDAN " << tiempoParado << " PASOS PARA MOVERSE";
                tiempoParado--;
                if (DEBUG) {
                    cout << endl;
                }
                getchar();
            }
        }
        posCoche = avanza(posCoche);
    }
    dibujaCarretera(carretera, posCoche);

    return;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
