#include <iostream>
#include <conio.h>
#include <cmath>
#include <cstdlib>
using namespace std;

// Definimos las constantes para las figuras
const char TRIANGULO = '^';
const char CUADRADO = '#';
const char RECTANGULO = '+';
const char CIRCULO = 'O';

// Definimos la constante para el máximo de la pantalla
const int ANCHO_PANTALLA = 20;
const int ALTO_PANTALLA = 10;

// Estructura para almacenar la posición del cursor
struct Posicion {
    int x;
    int y;
};

void limpiarPantalla() {
    system("cls");
}

// Función para dibujar los bordes de un triángulo  hacia abajo
void dibujarTriangulo(Posicion inicio, int base) {
    int altura = base / 2 + 1;

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < base; j++) {

            // se calcujlan las cordenadas ajustadas para la pantalla circular
            int posX = (inicio.x + j + ANCHO_PANTALLA) % ANCHO_PANTALLA;
            int posY = (inicio.y + i + ALTO_PANTALLA) % ALTO_PANTALLA;

            if (j == altura - i - 1 || j == altura + i || i == altura - 1) {
                // se dibuja el tirangulo segun los ajustes de las cordenadas
                cout << "\033[" << posY + 1 << ";" << posX + 1 << "H" << TRIANGULO;
            }
        }
    }
}

// Función para dibujar un cuadrado
void dibujarCuadrado(Posicion inicio, int lado) {
    for (int i = 0; i < lado; ++i) {
        for (int j = 0; j < lado; ++j) {
             // se calcujlan las cordenadas ajustadas para la pantalla circular
            int posX = (inicio.x + j + ANCHO_PANTALLA) % ANCHO_PANTALLA;
            int posY = (inicio.y + i + ALTO_PANTALLA) % ALTO_PANTALLA;

            if (i == 0 || i == lado - 1 || j == 0 || j == lado - 1) {
               // se dibuja el cuadrado segun los ajustes de las cordenadas
                cout << "\033[" << posY + 1 << ";" << posX + 1 << "H" << CUADRADO;
            }
        }
    }
}

// Función para dibujar un rectángulo
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

// Función para dibujar los bordes de un círculo
void dibujarCirculo(Posicion centro, int radio) {
    for (int i = -radio; i <= radio; ++i) {
        for (int j = -radio; j <= radio; ++j) {
            // Verificar si el punto (i, j) está dentro del círculo
            if (i * i + j * j <= radio * radio + 1 && i * i + j * j >= radio * radio - 1) {
                // se calculan  las coordenadas ajustadas para pantalla circular
                int posX = (centro.x + j + ANCHO_PANTALLA) % ANCHO_PANTALLA;
                int posY = (centro.y + i + ALTO_PANTALLA) % ALTO_PANTALLA;

                cout << "\033[" << posY + 1 << ";" << posX + 1 << "H" << CIRCULO;
            }
        }
    }
}

// Menú de opciones
char mostrarMenu() {
    limpiarPantalla();
    cout << "Menu:" << endl;
    cout << "1. Dibujar Triangulo" << endl;
    cout << "2. Dibujar Cuadrado" << endl;
    cout << "3. Dibujar Rectangulo" << endl;
    cout << "4. Dibujar Circulo" << endl;
    cout << "5. Salir" << endl;
    cout << "Seleccione una opcion: ";
    char opcion;
    cin >> opcion;
    return opcion;
}

// Función principal
int main() {
    char opcion;


    while (true) {
        opcion = mostrarMenu();

        switch (opcion) {
            case '1': {
                limpiarPantalla();

                int base;
                cout << "Ingrese el tamaño de la base del triangulo: ";
                cin >> base;

                // Posición inicial del cursor
                Posicion posicionCursor;
                posicionCursor.x = ANCHO_PANTALLA / 2; // Centrado horizontalmente
                posicionCursor.y = ALTO_PANTALLA / 2;  // Centrado verticalmente

                // se dibuja el triángulo en la posición actual del cursor
                dibujarTriangulo(posicionCursor, base);

                // Variable booleana  la cual sirve para controlar el bucle interno
                bool regresarAlMenu = false;

                // Mientras el usuario no presione ESC o la tecla para regresar al menú, permitirle mover el triángulo
                while (!regresarAlMenu) {
                    // Mover el cursor para la siguiente entrada de usuario
                    cout << "\033[" << ALTO_PANTALLA + 2 << ";0H"; // Mover el cursor a la parte inferior de la pantalla
                    cout << "Use las flechas para mover el cursor.";

                    // Esperar hasta que el usuario presione una tecla
                    char tecla = _getch();

                    // Proesar segun la tecla que presione el usuario
                    switch (tecla) {
                        case 72: // Flecha Arriba
                            if (posicionCursor.y > 0) {
                                posicionCursor.y--;
                            }
                            break;
                        case 80: // Flecha Abajo
                            if (posicionCursor.y < ALTO_PANTALLA - 1) {
                                posicionCursor.y++;
                            }
                            break;
                        case 75: // Flecha Izquierda
                            if (posicionCursor.x > 0) {
                                posicionCursor.x--;
                            }
                            break;
                        case 77: // Flecha Derecha
                            if (posicionCursor.x < ANCHO_PANTALLA - 1) {
                                posicionCursor.x++;
                            }
                            break;
                        case 27: // Tecla ESC (Escape)
                            regresarAlMenu = true;
                            break;
                        default:
                            continue; // Continuar esperando la entrada del usuario
                    }

                    // Limpiar la pantalla y dibujar el triángulo en la nueva posición del cursor
                    limpiarPantalla();
                    dibujarTriangulo(posicionCursor, base);
                }
                break; // Salir del switch
            }
            case '2': {
                limpiarPantalla();
                // Solicitar al usuario los datos para dibujar el cuadrado
                int lado;
                cout << "Ingrese el tamaño del lado del cuadrado: ";
                cin >> lado;

                // Posición inicial del cursor
                Posicion posicionCursor;
                posicionCursor.x = ANCHO_PANTALLA / 2; // Centrado horizontalmente
                posicionCursor.y = ALTO_PANTALLA / 2;  // Centrado verticalmente

                // se dibuja el cuadrado en la posición actual del cursor
                dibujarCuadrado(posicionCursor, lado);

                bool regresarAlMenu = false;

                // Mientras el usuario no presione ESC o la tecla para regresar al menú, permitirle mover el cuadrado
                while (!regresarAlMenu) {
                    // Mover el cursor para la siguiente entrada de usuario
                    cout << "\033[" << ALTO_PANTALLA + 2 << ";0H"; // Mover el cursor a la parte inferior de la pantalla
                    cout << "Use las flechas para mover el cursor.";


                    char tecla = _getch();


                    switch (tecla) {
                        case 72: // Flecha Arriba
                            if (posicionCursor.y > 0) {
                                posicionCursor.y--;
                            }
                            break;
                        case 80: // Flecha Abajo
                            if (posicionCursor.y < ALTO_PANTALLA - 1) {
                                posicionCursor.y++;
                            }
                            break;
                        case 75: // Flecha Izquierda
                            if (posicionCursor.x > 0) {
                                posicionCursor.x--;
                            }
                            break;
                        case 77: // Flecha Derecha
                            if (posicionCursor.x < ANCHO_PANTALLA - 1) {
                                posicionCursor.x++;
                            }
                            break;
                        case 27: // Tecla ESC (Escape)
                            regresarAlMenu = true;
                            break;
                        default:
                            continue; // Continuar esperando la entrada del usuario
                    }

                    // Limpiar la pantalla y dibujar el cuadrado en la nueva posición del cursor
                    limpiarPantalla();
                    dibujarCuadrado(posicionCursor, lado);
                }
                break; // Salir del switch
            }
            case '3': {
                limpiarPantalla();
                // Solicitar al usuario los datos para dibujar el rectángulo
                int ancho, alto;
                cout << "Ingrese el ancho del rectangulo: ";
                cin >> ancho;
                cout << "Ingrese el alto del rectangulo: ";
                cin >> alto;


                Posicion posicionCursor;
                posicionCursor.x = ANCHO_PANTALLA / 2; // Centrado horizontalmente
                posicionCursor.y = ALTO_PANTALLA / 2;  // Centrado verticalmente

                // se dibuja el rectángulo en la posición actual del cursor
                dibujarRectangulo(posicionCursor, ancho, alto);


                bool regresarAlMenu = false;

                // Mientras el usuario no presione ESC o la tecla para regresar al menú, permitirle mover el rectángulo
                while (!regresarAlMenu) {
                    // Mover el cursor para la siguiente entrada de usuario
                    cout << "\033[" << ALTO_PANTALLA + 2 << ";0H"; // Mover el cursor a la parte inferior de la pantalla
                    cout << "Use las flechas para mover el cursor.";

                    // Esperar hasta que el usuario presione una tecla
                    char tecla = _getch();


                    switch (tecla) {
                        case 72: // Flecha Arriba
                            if (posicionCursor.y > 0) {
                                posicionCursor.y--;
                            }
                            break;
                        case 80: // Flecha Abajo
                            if (posicionCursor.y < ALTO_PANTALLA - 1) {
                                posicionCursor.y++;
                            }
                            break;
                        case 75: // Flecha Izquierda
                            if (posicionCursor.x > 0) {
                                posicionCursor.x--;
                            }
                            break;
                        case 77: // Flecha Derecha
                            if (posicionCursor.x < ANCHO_PANTALLA - 1) {
                                posicionCursor.x++;
                            }
                            break;
                        case 27: // Tecla ESC (Escape)
                            regresarAlMenu = true;
                            break;
                        default:
                            continue; // Continuar esperando la entrada del usuario
                    }

                    // Limpiar la pantalla y dibujar el rectángulo en la nueva posición del cursor
                    limpiarPantalla();
                    dibujarRectangulo(posicionCursor, ancho, alto);
                }
                break; // Salir del switch
            }
            case '4': {
                limpiarPantalla();
                // Solicitar al usuario los datos para dibujar el círculo
                int radio;
                cout << "Ingrese el radio del circulo: ";
                cin >> radio;

                Posicion posicionCursor;
                posicionCursor.x = ANCHO_PANTALLA / 2; // Centrado horizontalmente
                posicionCursor.y = ALTO_PANTALLA / 2;  // Centrado verticalmente

                // se dibuja el círculo en la posición actual del cursor
                dibujarCirculo(posicionCursor, radio);

                // Variable booleana para controlar el bucle interno
                bool regresarAlMenu = false;

                // Mientras el usuario no presione ESC o la tecla para regresar al menú, permitirle mover el círculo
                while (!regresarAlMenu) {
                    // Mover el cursor para la siguiente entrada de usuario
                    cout << "\033[" << ALTO_PANTALLA + 2 << ";0H"; // Mover el cursor a la parte inferior de la pantalla
                    cout << "Use las flechas para mover el cursor.";

                    // Esperar hasta que el usuario presione una tecla
                    char tecla = _getch();


                    switch (tecla) {
                        case 72: // Flecha Arriba
                            if (posicionCursor.y > 0) {
                                posicionCursor.y--;
                            }
                            break;
                        case 80: // Flecha Abajo
                            if (posicionCursor.y < ALTO_PANTALLA - 1) {
                                posicionCursor.y++;
                            }
                            break;
                        case 75: // Flecha Izquierda
                            if (posicionCursor.x > 0) {
                                posicionCursor.x--;
                            }
                            break;
                        case 77: // Flecha Derecha
                            if (posicionCursor.x < ANCHO_PANTALLA - 1) {
                                posicionCursor.x++;
                            }
                            break;
                        case 27: // Tecla ESC (Escape)
                            regresarAlMenu = true;
                            break;
                        default:
                            continue; // Continuar esperando la entrada del usuario
                    }

                    // Limpiar la pantalla y dibujar el círculo en la nueva posición del cursor
                    limpiarPantalla();
                    dibujarCirculo(posicionCursor, radio);
                }
                break; // Salir del switch
            }
            case '5':
                // Salir del programa
                return 0;
            default:
                cout << "Opcion no valida." << endl;
                break;
        }
    }

    return 0;
}

