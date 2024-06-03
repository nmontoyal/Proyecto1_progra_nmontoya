#include <iostream>
#include <conio.h>
#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;

// Definimos las constantes para las figuras
const char TRIANGULO = '^';
const char CUADRADO = '#';
const char RECTANGULO = '+';
const char CIRCULO = 'O';
const char LINEA = '-';
const char ROMBO = '*';
const char HEXAGONO = 'H';

// Definimos la constante para el m�ximo de la pantalla
const int ANCHO_PANTALLA = 120;
const int ALTO_PANTALLA = 20;

// Estructura para almacenar la posici�n del cursor
struct Posicion {
    int x;
    int y;
};

void limpiarPantalla() {
    system("cls");
}

// Funci�n para dibujar los bordes de un tri�ngulo hacia abajo
void dibujarTriangulo(Posicion inicio, int base) {
    int altura = base / 2 + 1;

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < base; j++) {
            int posX = (inicio.x + j + ANCHO_PANTALLA) % ANCHO_PANTALLA;
            int posY = (inicio.y + i + ALTO_PANTALLA) % ALTO_PANTALLA;

            if (j == altura - i - 1 || j == altura + i || i == altura - 1) {
                cout << "\033[" << posY + 1 << ";" << posX + 1 << "H" << TRIANGULO;
            }
        }
    }
}

// Funci�n para dibujar un cuadrado
void dibujarCuadrado(Posicion inicio, int lado) {
    for (int i = 0; i < lado; ++i) {
        for (int j = 0; j < lado; ++j) {
            int posX = (inicio.x + j + ANCHO_PANTALLA) % ANCHO_PANTALLA;
            int posY = (inicio.y + i + ALTO_PANTALLA) % ALTO_PANTALLA;

            if (i == 0 || i == lado - 1 || j == 0 || j == lado - 1) {
                cout << "\033[" << posY + 1 << ";" << posX + 1 << "H" << CUADRADO;
            }
        }
    }
}

// Funci�n para dibujar un rect�ngulo
void dibujarRectangulo(Posicion inicio, int ancho, int alto) {
    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            int posX = (inicio.x + j + ANCHO_PANTALLA) % ANCHO_PANTALLA;
            int posY = (inicio.y + i + ALTO_PANTALLA) % ALTO_PANTALLA;

            if (i == 0 || i == alto - 1 || j == 0 || j == ancho - 1) {
                cout << "\033[" << posY + 1 << ";" << posX + 1 << "H" << RECTANGULO;
            }
        }
    }
}

// Funci�n para dibujar los bordes de un c�rculo
void dibujarCirculo(Posicion centro, int radio) {
    for (int i = -radio; i <= radio; ++i) {
        for (int j = -radio; j <= radio; ++j) {
            if (i * i + j * j <= radio * radio + 1 && i * i + j * j >= radio * radio - 1) {
                int posX = (centro.x + j + ANCHO_PANTALLA) % ANCHO_PANTALLA;
                int posY = (centro.y + i + ALTO_PANTALLA) % ALTO_PANTALLA;

                cout << "\033[" << posY + 1 << ";" << posX + 1 << "H" << CIRCULO;
            }
        }
    }
}

// Funci�n para dibujar una l�nea en la orientaci�n especificada
void dibujarLinea(Posicion inicio, int longitud, char orientacion) {
    for (int i = 0; i < longitud; ++i) {
        int posX = inicio.x;
        int posY = inicio.y;

        switch (orientacion) {
            case '1': posY -= i; break; // Arriba
            case '2': posX += i; posY -= i; break; // Diagonal Derecha Arriba
            case '3': posY += i; break; // Abajo
            case '4': posX += i; posY += i; break; // Diagonal Derecha Abajo
            case '5': posX += i; break; // Derecha
            case '6': posX -= i; posY -= i; break; // Diagonal Izquierda Arriba
            case '7': posX -= i; break; // Izquierda
            case '8': posX -= i; posY += i; break; // Diagonal Izquierda Abajo
        }

        posX = (posX + ANCHO_PANTALLA) % ANCHO_PANTALLA;
        posY = (posY + ALTO_PANTALLA) % ALTO_PANTALLA;

        cout << "\033[" << posY + 1 << ";" << posX + 1 << "H" << LINEA;
    }
}

// Funci�n para dibujar un rombo en la orientaci�n especificada
void dibujarRombo(Posicion inicio, int diagonal, char orientacion) {
    int mitad = diagonal / 2;

    for (int i = -mitad; i <= mitad; ++i) {
        for (int j = -mitad; j <= mitad; ++j) {
            if (abs(i) + abs(j) == mitad) {
                int posX = (inicio.x + j + ANCHO_PANTALLA) % ANCHO_PANTALLA;
                int posY = (inicio.y + i + ALTO_PANTALLA) % ALTO_PANTALLA;

                cout << "\033[" << posY + 1 << ";" << posX + 1 << "H" << ROMBO;
            }
        }
    }
}

// Funci�n para dibujar un hex�gono con lados iguales en la orientaci�n especificada
void dibujarHexagono(Posicion inicio, int lado, char orientacion) {
    int centroX = inicio.x; // Coordenada X del centro del hex�gono
    int centroY = inicio.y; // Coordenada Y del centro del hex�gono

    // Dibujar la mitad superior del hex�gono
    for (int i = 0; i < lado; ++i) {
        int espacios = lado - i - 1;
        int longitudLinea = lado + 2 * i;
        for (int j = 0; j < longitudLinea; ++j) {
            int x = centroX - (longitudLinea / 2) + j;
            int y = centroY - lado + i;
            int posX = (x + ANCHO_PANTALLA) % ANCHO_PANTALLA;
            int posY = (y + ALTO_PANTALLA) % ALTO_PANTALLA;
            if (j == 0 || j == longitudLinea - 1) {
                cout << "\033[" << posY + 1 << ";" << posX + 1 << "H" << HEXAGONO;
            }
        }
    }

    // Dibujar la mitad inferior del hex�gono
    for (int i = 0; i < lado; ++i) {
        int espacios = i;
        int longitudLinea = lado + 2 * (lado - i - 1);
        for (int j = 0; j < longitudLinea; ++j) {
            int x = centroX - (longitudLinea / 2) + j;
            int y = centroY + i + 1;
            int posX = (x + ANCHO_PANTALLA) % ANCHO_PANTALLA;
            int posY = (y + ALTO_PANTALLA) % ALTO_PANTALLA;
            if (j == 0 || j == longitudLinea - 1) {
                cout << "\033[" << posY + 1 << ";" << posX + 1 << "H" << HEXAGONO;
            }
        }
    }
}

// Funci�n para mover y dibujar figuras
void moverYdibujar(char figura, Posicion &posicion, int dim1, int dim2 = 0, char orientacion = '0') {
    limpiarPantalla();
    switch (figura) {
        case '1':
            dibujarTriangulo(posicion, dim1);
            break;
        case '2':
            dibujarCuadrado(posicion, dim1);
            break;
        case '3':
            dibujarRectangulo(posicion, dim1, dim2);
            break;
        case '4':
            dibujarCirculo(posicion, dim1);
            break;
        case '6':
            dibujarLinea(posicion, dim1, orientacion);
            break;
        case '7':
            dibujarRombo(posicion, dim1, orientacion);
            break;
        case '8':
            dibujarHexagono(posicion, dim1, orientacion);
            break;
    }
}

// Men� de opciones para seleccionar la figura
char mostrarMenu() {
   limpiarPantalla();
    cout << "Menu:" << endl;
    cout << "1. Dibujar Triangulo" << endl;
    cout << "2. Dibujar Cuadrado" << endl;
    cout << "3. Dibujar Rectangulo" << endl;
    cout << "4. Dibujar Circulo" << endl;
    cout << "5. Salir" << endl;
    cout << "6. Dibujar Linea" << endl;
    cout << "7. Dibujar Rombo" << endl;
    cout << "8. Dibujar Hexagono" << endl;
    cout << "Seleccione una opcion: ";
    char opcion;
    cin >> opcion;
    return opcion;
}

// Men� de opciones para seleccionar la orientaci�n de la l�nea
char mostrarMenuOrientacionLinea() {
   limpiarPantalla();
    cout << "Seleccione la orientaci�n de la l�nea:" << endl;
    cout << "1. Arriba" << endl;
    cout << "2. Diagonal Derecha Arriba" << endl;
    cout << "3. Abajo" << endl;
    cout << "4. Diagonal Derecha Abajo" << endl;
    cout << "5. Derecha" << endl;
    cout << "6. Diagonal Izquierda Arriba" << endl;
    cout << "7. Izquierda" << endl;
    cout << "8. Diagonal Izquierda Abajo" << endl;
    cout << "Seleccione una opci�n: ";
    char orientacion;
    cin >> orientacion;
    return orientacion;
}

// Funci�n principal
int main() {
    char opcion;

    while (true) {
        opcion = mostrarMenu();
        Posicion posicionCursor = {ANCHO_PANTALLA / 2, ALTO_PANTALLA / 2};
        bool regresarAlMenu = false;

        switch (opcion) {
            case '1':
            case '2':
            case '3':
            case '4': {
                int dim1, dim2 = 0;
                if (opcion == '1') {
                    cout << "Ingrese el tama�o de la base del tri�ngulo: ";
                    cin >> dim1;
                } else if (opcion == '2') {
                    cout << "Ingrese el tama�o del lado del cuadrado: ";
                    cin >> dim1;
                } else if (opcion == '3') {
                    cout << "Ingrese el ancho del rect�ngulo: ";
                    cin >> dim1;
                    cout << "Ingrese el alto del rect�ngulo: ";
                    cin >> dim2;
                } else if (opcion == '4') {
                    cout << "Ingrese el radio del c�rculo: ";
                    cin >> dim1;
                }

                moverYdibujar(opcion, posicionCursor, dim1, dim2);

                while (!regresarAlMenu) {
                    cout << "\033[" << ALTO_PANTALLA + 2 << ";0H";
                    cout << "Use las flechas para mover el cursor.";
                    char tecla = _getch();

                    switch (tecla) {
                        case 72: if (posicionCursor.y > 0) posicionCursor.y--; break; // Arriba
                        case 80: if (posicionCursor.y < ALTO_PANTALLA - 1) posicionCursor.y++; break; // Abajo
                        case 75: if (posicionCursor.x > 0) posicionCursor.x--; break; // Izquierda
                        case 77: if (posicionCursor.x < ANCHO_PANTALLA - 1) posicionCursor.x++; break; // Derecha
                        case 27: regresarAlMenu = true; break; // ESC
                        default: continue;
                    }
                    moverYdibujar(opcion, posicionCursor, dim1, dim2);
                }
                break;
            }
            case '6': // Dibujar l�nea
            case '7': // Dibujar rombo
            case '8': // Dibujar hex�gono
            {
                int dim;
                char orientacion = '0';
                if (opcion == '6' || opcion == '7' || opcion == '8') {
                    if (opcion == '6') {
                        cout << "Ingrese la longitud de la l�nea: ";
                        cin >> dim;
                        orientacion = mostrarMenuOrientacionLinea();
                    } else if (opcion == '7') {
                        cout << "Ingrese el tama�o del rombo (diagonal): ";
                        cin >> dim;
                        orientacion = mostrarMenuOrientacionLinea();
                    } else if (opcion == '8') {
                        cout << "Ingrese el tama�o del hex�gono (lado): ";
                        cin >> dim;
                    }
                }

                moverYdibujar(opcion, posicionCursor, dim, 0, orientacion);

                while (!regresarAlMenu) {
                    cout << "\033[" << ALTO_PANTALLA + 2 << ";0H";
                    cout << "Use las flechas para mover el cursor.";
                    char tecla = _getch();

                    switch (tecla) {
                        case 72: if (posicionCursor.y > 0) posicionCursor.y--; break;
                        case 80: if (posicionCursor.y < ALTO_PANTALLA - 1) posicionCursor.y++; break;
                        case 75: if (posicionCursor.x > 0) posicionCursor.x--; break;
                        case 77: if (posicionCursor.x < ANCHO_PANTALLA - 1) posicionCursor.x++; break;
                        case 27: regresarAlMenu = true; break;
                        default: continue;
                    }
                    moverYdibujar(opcion, posicionCursor, dim, 0, orientacion);
                }
                break;
            }
            case '5':
                return 0;
            default:
                cout << "Opcion no valida." << endl;
                break;
        }
    }
    return 0;
}
