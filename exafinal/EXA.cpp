#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct Estudiante {
    string carne;
    string nombre;
    int edad;
    char sexo;
    int matematica;
    int ciencias;
    int computacion;
    int fisica;
    int idioma;
    int literatura;
};

void ingresarDatos(vector<Estudiante> &estudiantes) {
    int n;
    cout << "Ingrese el numero de estudiantes: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        Estudiante est;
        cout << "Ingrese los datos del estudiante " << i + 1 << ":\n";
        cout << "Carnet: "; cin >> est.carne;
        cout << "Nombre: "; cin.ignore(); getline(cin, est.nombre);
        cout << "Edad: "; cin >> est.edad;
        cout << "Sexo (M/F): "; cin >> est.sexo;
        cout << "Matematica: "; cin >> est.matematica;
        cout << "Ciencias: "; cin >> est.ciencias;
        cout << "Computacion: "; cin >> est.computacion;
        cout << "Fisica: "; cin >> est.fisica;
        cout << "Idioma: "; cin >> est.idioma;
        cout << "Literatura: "; cin >> est.literatura;

        estudiantes.push_back(est);
    }
}

void contarSexo(const vector<Estudiante> &estudiantes, int &hombres, int &mujeres) {
    hombres = mujeres = 0;
    for (const auto& est : estudiantes) {
        if (est.sexo == 'M') ++hombres;
        else if (est.sexo == 'F') ++mujeres;
    }
}

void alumnosMasJovenes(const vector<Estudiante> &estudiantes) {
    int menorEdad = numeric_limits<int>::max();
    for (const auto& est : estudiantes) {
        if (est.edad < menorEdad) {
            menorEdad = est.edad;
        }
    }
    cout << "Alumnos mas jovenes:\n";
    for (const auto& est : estudiantes) {
        if (est.edad == menorEdad) {
            cout << est.nombre << " (" << est.edad << " anios)\n";
        }
    }
}

void cursosReprobadosCarlosSuarez(const vector<Estudiante> &estudiantes) {
    for (const auto& est : estudiantes) {
        if (est.nombre == "Carlos Suarez") {
            int reprobados = 0;
            if (est.matematica < 61) ++reprobados;
            if (est.ciencias < 61) ++reprobados;
            if (est.computacion < 61) ++reprobados;
            if (est.fisica < 61) ++reprobados;
            if (est.idioma < 61) ++reprobados;
            if (est.literatura < 61) ++reprobados;

            cout << "Carlos Suarez reprobo " << reprobados << " cursos.\n";
            return;
        }
    }
}

void alumnosQueAprobaronTodosLosCursos(const vector<Estudiante> &estudiantes) {
    cout << "Alumnos que aprobaron todos los cursos:\n";
    for (const auto& est : estudiantes) {
        if (est.matematica >= 61 && est.ciencias >= 61 && est.computacion >= 61 &&
            est.fisica >= 61 && est.idioma >= 61 && est.literatura >= 61) {
            cout << est.nombre << endl;
        }
    }
}

double calcularPromedio(const Estudiante &est) {
    return (est.matematica + est.ciencias + est.computacion + est.fisica +
            est.idioma + est.literatura) / 6.0;
}

void alumnoConMayorPromedio(const vector<Estudiante> &estudiantes) {
    double maxPromedio = -1;
    vector<string> nombres;

    for (const auto& est : estudiantes) {
        double promedio = calcularPromedio(est);
        if (promedio > maxPromedio) {
            maxPromedio = promedio;
            nombres.clear();
            nombres.push_back(est.nombre);
        } else if (promedio == maxPromedio) {
            nombres.push_back(est.nombre);
        }
    }

    cout << "Alumnos con el promedio mas alto (" << maxPromedio << "):\n";
    for (const auto& nombre : nombres) {
        cout << nombre << endl;
    }
}

void alumnoConMenorPromedio(const vector<Estudiante> &estudiantes) {
    double minPromedio = numeric_limits<double>::max();
    vector<string> nombres;

    for (const auto& est : estudiantes) {
        double promedio = calcularPromedio(est);
        if (promedio < minPromedio) {
            minPromedio = promedio;
            nombres.clear();
            nombres.push_back(est.nombre);
        } else if (promedio == minPromedio) {
            nombres.push_back(est.nombre);
        }
    }

    cout << "Alumnos con el promedio mas bajo (" << minPromedio << "):\n";
    for (const auto& nombre : nombres) {
        cout << nombre << endl;
    }
}

void promedioCursoMatematica(const vector<Estudiante> &estudiantes) {
    double suma = 0;
    for (const auto& est : estudiantes) {
        suma += est.matematica;
    }
    cout << "Promedio de Matematica: " << (suma / estudiantes.size()) << endl;
}

void mejorPromedioSexo(const vector<Estudiante> &estudiantes) {
    double maxPromedioM = -1, maxPromedioF = -1;
    string mejorM, mejorF;

    for (const auto& est : estudiantes) {
        double promedio = (est.matematica + est.computacion + est.fisica) / 3.0;
        if (est.sexo == 'M' && promedio > maxPromedioM) {
            maxPromedioM = promedio;
            mejorM = est.nombre;
        } else if (est.sexo == 'F' && promedio > maxPromedioF) {
            maxPromedioF = promedio;
            mejorF = est.nombre;
        }
    }

    cout << "Hombre con mejor promedio en Matematica, Computacion y Fisica: " << mejorM << " (" << maxPromedioM << ")\n";
    cout << "Mujer con mejor promedio en Matematica, Computacion y Fisica: " << mejorF << " (" << maxPromedioF << ")\n";
}

void alumnoConMasCursosReprobados(const vector<Estudiante> &estudiantes) {
    int maxReprobados = -1;
    string nombre;
    vector<string> cursos;

    for (const auto& est : estudiantes) {
        int reprobados = 0;
        vector<string> cursosReprobados;
        if (est.matematica < 61) { ++reprobados; cursosReprobados.push_back("Matematica"); }
        if (est.ciencias < 61) { ++reprobados; cursosReprobados.push_back("Ciencias"); }
        if (est.computacion < 61) { ++reprobados; cursosReprobados.push_back("Computacion"); }
        if (est.fisica < 61) { ++reprobados; cursosReprobados.push_back("Fisica"); }
        if (est.idioma < 61) { ++reprobados; cursosReprobados.push_back("Idioma"); }
        if (est.literatura < 61) { ++reprobados; cursosReprobados.push_back("Literatura"); }

        if (reprobados > maxReprobados) {
            maxReprobados = reprobados;
            nombre = est.nombre;
            cursos = cursosReprobados;
        }
    }

    cout << "Alumno con mas cursos reprobados: " << nombre << " (" << maxReprobados << ")\n";
    cout << "Cursos reprobados:\n";
    for (const auto& curso : cursos) {
        cout << curso << endl;
    }
}


int main() {
    char opcion;
    do {
        vector<Estudiante> estudiantes;
        ingresarDatos(estudiantes);

        int hombres, mujeres;
        contarSexo(estudiantes, hombres, mujeres);
        cout << "Hombres: " << hombres << ", Mujeres: " << mujeres << endl;

        alumnosMasJovenes(estudiantes);
        cursosReprobadosCarlosSuarez(estudiantes);
        alumnosQueAprobaronTodosLosCursos(estudiantes);
        alumnoConMayorPromedio(estudiantes);
        alumnoConMenorPromedio(estudiantes);
        promedioCursoMatematica(estudiantes);
        mejorPromedioSexo(estudiantes);
        alumnoConMasCursosReprobados(estudiantes);

        cout << "¿Desea evaluar otros alumnos? (S/N): ";
        cin >> opcion;
    } while (opcion == 'S' || opcion == 's');

    return 0;
}
