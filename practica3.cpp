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
const int TIEMPO_PARADO = 3;

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


const int NUM_CARRILES = 3;// numero de coches en la carrera
const int MAX_PODIUMS = 3;// nos dice el numero max de carreras

typedef enum { CLAVO, SORPRESA, NORMAL } tTipoPosicion;

typedef struct {
    int pos;
    int tiempoParado;
} tCoche;

typedef tTipoPosicion tArrayPosiciones[LONG_CARRETERA];

typedef struct {
    tCoche coche;
    tArrayPosiciones posiciones;
} tCarril;

typedef tCarril tCarretera[NUM_CARRILES];

typedef int tGanadores[NUM_CARRILES];

typedef struct {
    string idCarrera;
    tGanadores ganadores;
} tPodium;

typedef tPodium tArrayPodiums[MAX_PODIUMS];

typedef struct {
    int cont;
    tArrayPodiums lista;
} tListaPodiums;


tTipoPosicion stringToEnum(const string s);
void iniciaCoche(tCoche& coche);
void iniciaCarril(tCarril& carril);
void leeCarril(ifstream& archivo, tCarril& carril);
bool cargaCarretera(tCarretera carriles);
void iniciaCoches(tCarretera& carretera);
bool esSorpresa(const tArrayPosiciones pos, int p);
bool esClavo(const tArrayPosiciones pos, int p);
int buscaSiguientePosSorpresa(const tArrayPosiciones carril, int p);
int avanza(int posCoche);
bool haLlegado(int posCoche);
bool avanzaCarril(const tCarretera carretera, tCarril& carril, int nc);
void avanzaCarriles(tCarretera carretera, tGanadores ganadores, int& cMeta);
void simulaCarrera(tCarretera carretera, tGanadores ganadores);
void dibujaLineaHorizontalInferior();
void dibujaCarril(const tCarril& carril);
void dibujaLineaDiscontinua();
void dibujaLineaHorizontalSuperior();
void dibujaCarretera(const tCarretera carriles);
void iniciaListaPodiums(tListaPodiums& listaP);
void insertaPodium(tListaPodiums& listaP, const tPodium& podium);
void muestraGanadores(const tGanadores ganadores);
bool guardaListaPodiums(const tListaPodiums& podiums);


int main() {
    tCarretera carretera;
    tPodium podium;
    tListaPodiums listaPodiums;
    char continuarSimulacion;
    int numSimulaciones = 0;
    bool continuar = false;

   
    iniciaListaPodiums(listaPodiums);

    if (cargaCarretera(carretera) == true) {

        do {
            iniciaCoches(carretera);

            cout << "Dame un identificador para la carrera: ";
            cin >> podium.idCarrera;

            simulaCarrera(carretera, podium.ganadores);

            cout << "FIN DE LA SIMULACIÓN" << '\n' << '\n';

            muestraGanadores(podium.ganadores);

            insertaPodium(listaPodiums, podium);

            numSimulaciones++;
            if (numSimulaciones <= MAX_PODIUMS) {

                cout << "¿ Quieres repetir la simulación? (S/N): " << endl;
                cin >> continuarSimulacion;
                continuar = true;

            }
            else {
                continuar = false;
            }

        } while (continuarSimulacion == 'S' && continuar == true);

        guardaListaPodiums(listaPodiums);
    }


    return 0;
}


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

// ------------------------------------------------------------------ //
// Subprogramas para leer del archivo de texto y cargar la carretera. //
// ------------------------------------------------------------------ //

void iniciaCoche(tCoche& coche) {
    coche.pos = 0;
    coche.tiempoParado = 0;
}
void iniciaCarril(tCarril& carril) {
    iniciaCoche(carril.coche);

    for (int i = 0; i < LONG_CARRETERA; i++) {
        carril.posiciones[i] = NORMAL;
    }
}
void leeCarril(ifstream& archivo, tCarril& carril) {
    string valor;
    int numeroValores;
    int posicion;

    archivo >> valor;

    while (valor != "XX") {
        

        archivo >> numeroValores;

        for (int i = 0; i < numeroValores; i++) {
            archivo >> posicion;
            carril.posiciones[posicion] = stringToEnum(valor);
        }

        archivo >> valor;
    }
}
bool cargaCarretera(tCarretera carriles) {
    bool exito= false;
    string nombre;
    cout << "Introduce el nombre del archivo: ";
    cin >> nombre;// das por hecho que el usuario te pone .txt

    ifstream archivo;
    archivo.open(nombre);
    if (archivo.is_open()) {
        for (int i = 0; i < NUM_CARRILES; i++) {
            iniciaCarril(carriles[i]);
            leeCarril(archivo, carriles[i]);
        }
        exito = true;
        archivo.close();
    }
    else {
        cout << "Error al cargar el archivo :/" << endl;
        exito = false;
    }
    
    return exito;
}

// ------------------------------------------------------------------ //
//  Subprogramas encargados de controlar la lógica de la simulación.  //
// ------------------------------------------------------------------ //

void iniciaCoches(tCarretera& carretera) {//XXX
    for (int i = 0; i < NUM_CARRILES; i++) {
        iniciaCoche(carretera[i].coche);
    }
}

bool esSorpresa(const tArrayPosiciones pos, int p) {// p es la posicion dentro del array
    bool sorpresa = false;
    if (pos[p] == SORPRESA) {
        sorpresa = true;
    }

    
    return sorpresa;


}

bool esClavo(const tArrayPosiciones pos, int p) {
    bool clavo = false;
    if (pos[p] == CLAVO) {
        clavo = true;

    }
    return clavo;
}

int buscaSiguientePosSorpresa(const tArrayPosiciones carril, int p) {
    int incremento = rand() % 2;
    int siguientePosSorpresa = 0;
    bool encontrado = false;

    // ################################################################### //
    if (incremento == 0) {
        cout << "Avanzas hasta la siguiente sorpresa ..." << endl;
        for (int i = p + 1; i < LONG_CARRETERA && !encontrado; i++) {
            if (esSorpresa(carril, i)) {
                siguientePosSorpresa = i;
                encontrado= true;
                
            }
            if (!encontrado) {
                siguientePosSorpresa = LONG_CARRETERA;
            }
        }
    }
    else if (incremento == 1) {
        cout << "Retrocedes hasta la sorpresa anterior ..." << endl;
        for (int i = p - 1; i ==0 && !encontrado; i--) {
            if (esSorpresa(carril, i)) {
                siguientePosSorpresa = i;
                encontrado = true;
            }
        }
        if (encontrado == false) {
            siguientePosSorpresa = 0;
        }
    }
    // ################################################################### //

    if (siguientePosSorpresa == 0) {
        cout << "Te toca empezar de nuevo, no había sorpresas en tu camino." << endl;
    }
    return siguientePosSorpresa;
}

// ==================================IGUAL================================ //
int avanza(int posCoche) {
    int pasos;

    if (DEBUG) {
        cout << "Introduce un número de pasos : ";
        cin >> pasos;

        if (posCoche < 0) {
            posCoche = 0;
        }
    }
    else {
        cout << "Pulsa una tecla para continuar";
        getchar();
        pasos = 1 + rand() % MAX_PASOS;
        cout << "El coche avanza " << pasos << " pasos." << endl;
    }

    posCoche += pasos;

    if (posCoche > LONG_CARRETERA) {
        posCoche = LONG_CARRETERA;
    }

    return posCoche;
}
// ==================================IGUAL================================ //

// ==================================IGUAL================================ //
bool haLlegado(int posCoche) {
    return posCoche >= LONG_CARRETERA;
}
// ==================================IGUAL================================ //


bool avanzaCarril(const tCarretera carretera, tCarril& carril, int nc) {
    //TANTOS DIBUJACARRILES??
    cout << "\n\nAvanzando en el carril " << nc << " ..." << endl;
    if (carril.coche.tiempoParado > 0) {
        // ?????????????????????????????????????????????????????????????????? //
        cout << "Quedan " << carril.coche.tiempoParado << " turnos para moverse" << endl;
        // ?????????????????????????????????????????????????????????????????? //
        carril.coche.tiempoParado -= 1;
        dibujaCarretera(carretera);
    }
    else {
        carril.coche.pos = avanza(carril.coche.pos);

        dibujaCarretera(carretera);

        if (esSorpresa(carril.posiciones, carril.coche.pos)) {
            cout << "Coche " << nc << " ha caído en una SORPRESA." << endl;
            carril.coche.pos = buscaSiguientePosSorpresa(carril.posiciones, carril.coche.pos);
            dibujaCarretera(carretera);// hace falta ponerlo otra vez?
        }
        else if (esClavo(carril.posiciones, carril.coche.pos)) {
            carril.coche.tiempoParado += TIEMPO_PARADO;
            // ?????????????????????????????????????????????????????????????????? //
            cout << "Coche " << nc << " pinchado durante " << TIEMPO_PARADO << " turnos." << endl;
            // ?????????????????????????????????????????????????????????????????? //
        }
    }

    return haLlegado(carril.coche.pos);
}

void avanzaCarriles(tCarretera carretera, tGanadores ganadores, int& cMeta) {
    for (int i = 0; i < NUM_CARRILES; i++) {
        if (!haLlegado(carretera[i].coche.pos)) {
            if (avanzaCarril(carretera, carretera[i], i)) {
                ganadores[cMeta] = i;// cMeta es el contador de coches que han llegado a la meta, te dice el orden de llegada y el array del carretera que identifica el cohe
                cMeta ++;
            }
        }
    }
}

void simulaCarrera(tCarretera carretera, tGanadores ganadores) {
    int cMeta = 0;

    // ?????????????????????????????????????????????????????????????????? //
    dibujaCarretera(carretera);
    getchar();
    // ?????????????????????????????????????????????????????????????????? //

    while (cMeta < NUM_CARRILES) {
        avanzaCarriles(carretera, ganadores, cMeta);
    }
}

// ------------------------------------------------------------------ //
//    Subprogramas encargados de dibujar el estado de la carrera.     //
// ------------------------------------------------------------------ //

void dibujaLineaHorizontalInferior() {
    cout << CHAR_ESQUINA_INFERIOR_IZQUIERDA;
    for (int k = 0; k < LONG_CARRETERA; k++) {
        cout << CHAR_LINEA_HORIZONTAL;
    }
    cout << CHAR_ESQUINA_INFERIOR_DERECHA << endl;

    return;
}

void dibujaCarril(const tCarril& carril) {
    cout << CHAR_LINEA_VERTICAL;
    for (int i = 0; i < LONG_CARRETERA; i++) {
        if (carril.posiciones[i] == CLAVO) {
            cout << CHAR_CLAVO;
        }
        else if (carril.posiciones[i] == SORPRESA) {
            cout << CHAR_SORPRESA;
        }
        else {// el relleno
            cout << CHAR_NORMAL;
        }
    }
    cout << CHAR_LINEA_VERTICAL << endl;
    cout << CHAR_LINEA_VERTICAL;

    for (int i = 0; i < LONG_CARRETERA; i++) {
        if (i == carril.coche.pos) {
            cout << CHAR_COCHE;
        }
        else {
            cout << CHAR_NORMAL;
        }
    }

    if (carril.coche.pos == LONG_CARRETERA) {
        cout << CHAR_COCHE;
    }

    cout << CHAR_LINEA_VERTICAL << endl;

    return;
}

void dibujaLineaDiscontinua() {
    cout << CHAR_LINEA_VERTICAL;
    for (int k = 0; k < LONG_CARRETERA; k++) {
        if (k % 2 == 0) {
            cout << CHAR_LINEA_HORIZONTAL;
        }
        else {
            cout << CHAR_NORMAL;
        }
    }
    cout << CHAR_LINEA_VERTICAL << endl;

    return;
}

void dibujaLineaHorizontalSuperior() {
    cout << CHAR_ESQUINA_SUPERIOR_IZQUIERDA;
    for (int k = 0; k < LONG_CARRETERA; k++) {
        cout << CHAR_LINEA_HORIZONTAL;
    }
    cout << CHAR_ESQUINA_SUPERIOR_DERECHA << endl;

    return;
}

void dibujaCarretera(const tCarretera carriles) {
    dibujaLineaHorizontalSuperior();

    for (int i = 0; i < NUM_CARRILES - 1; i++) {
        dibujaCarril(carriles[i]);
        dibujaLineaDiscontinua();
    }

    dibujaCarril(carriles[NUM_CARRILES - 1]);

    dibujaLineaHorizontalInferior();
}

// ------------------------------------------------------------------ //
//    Subprogramas encargados de gestionar y mostrar los pódiums.     //
// ------------------------------------------------------------------ //

void iniciaListaPodiums(tListaPodiums& listaP) {
    listaP.cont = 0;
}



void muestraGanadores(const tGanadores ganadores) {
    cout << "Clasificacion de la carrera" << endl;
    for (int i = 0; i < NUM_CARRILES; i++) {
        cout << "Puesto " << i << " :\tCoche en el carril " << ganadores[i] << endl;
    }
}
void insertaPodium(tListaPodiums& listaP, const tPodium& podium) {
    listaP.lista[listaP.cont] = podium;// a una posicion del array se le asigna los datos de un struct con los ganadores de una carrera
    listaP.cont += 1;
}

bool guardaListaPodiums(const tListaPodiums& podiums) {
    bool exito;

    ofstream archivo("ganadores.txt");

    if (archivo.is_open()) {
        for (int i = 0; i < podiums.cont; i++) {
            archivo << "Carrera con el id : " << podiums.lista[i].idCarrera << endl;
            for (int j = 0; j < NUM_CARRILES; j++) {
                archivo << "Puesto " << j << " :\tCoche en el carril " << podiums.lista[i].ganadores[j] << endl;
            }
        }
        cout << "Guardado!" << endl;
        exito = true;
    }
    else {
        cout << "No se pudo guardar la lista de podiums." << endl;
        exito = false;
    }

    return exito;
}
