#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

// Función de partición para QuickSort
int particionar(double arreglo[], int inicio, int fin) {
    double pivote = arreglo[fin];
    int indice = inicio - 1;

    for (int j = inicio; j < fin; j++) {
        if (arreglo[j] < pivote) {
            indice++;
            swap(arreglo[indice], arreglo[j]);
        }
    }
    swap(arreglo[indice + 1], arreglo[fin]);
    return indice + 1;
}

// Implementación de QuickSort
void ordenarRapido(double arreglo[], int inicio, int fin) {
    if (inicio < fin) {
        int indicePivote = particionar(arreglo, inicio, fin);
        ordenarRapido(arreglo, inicio, indicePivote - 1);
        ordenarRapido(arreglo, indicePivote + 1, fin);
    }
}

// Función para introducir un retraso de aproximadamente 0.5 milisegundos
void retrasoMedioMilisegundo() {
    clock_t inicio = clock();
    while (true) {
        if ((clock() - inicio) * 1000.0 / CLOCKS_PER_SEC >= 0.5) {
            break;
        }
    }
}

// Implementación de búsqueda por interpolación
int busquedaPorInterpolacion(double arreglo[], int tamanio, double objetivo) {
    int inicio = 0, fin = tamanio - 1;

    while (inicio <= fin && objetivo >= arreglo[inicio] && objetivo <= arreglo[fin]) {
        // Calcular la posición estimada
        int posicion = inicio + ((objetivo - arreglo[inicio]) * (fin - inicio)) / (arreglo[fin] - arreglo[inicio]);

        // Introducir el retraso de 0.5 ms
        retrasoMedioMilisegundo();

        if (arreglo[posicion] == objetivo) {
            return posicion; // Número encontrado
        } else if (arreglo[posicion] < objetivo) {
            inicio = posicion + 1;
        } else {
            fin = posicion - 1;
        }
    }

    return -1; // Número no encontrado
}

int main() {
    // Leer el archivo
    ifstream archivo("numeros_aleatorios.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    // Contar cuántos números hay en el archivo
    string linea;
    int totalNumeros = 0;
    while (getline(archivo, linea)) {
        totalNumeros++;
    }

    // Reservar memoria para el arreglo dinámico
    double* numeros = new double[totalNumeros];

    // Volver al inicio del archivo para leer los números
    archivo.clear();
    archivo.seekg(0, ios::beg);

    int indice = 0;
    while (getline(archivo, linea)) {
        stringstream flujo(linea);
        flujo >> numeros[indice++];
    }
    archivo.close();

    // Mostrar números antes de ordenar
    cout << "Numeros antes de ordenar:" << endl;
    for (int i = 0; i < totalNumeros; i++) {
        cout << numeros[i] << " ";
    }
    cout << endl;

    // Ordenar los números
    ordenarRapido(numeros, 0, totalNumeros - 1);

    // Mostrar números después de ordenar
    cout << "Numeros despues de ordenar:" << endl;
    for (int i = 0; i < totalNumeros; i++) {
        cout << numeros[i] << " ";
    }
    cout << endl;

    // Pedir el número a buscar
    double numeroObjetivo;
    cout << "Ingrese el numero que desea buscar: ";
    cin >> numeroObjetivo;

    // Medir el tiempo de búsqueda
    clock_t tiempoInicio = clock();
    int posicion = busquedaPorInterpolacion(numeros, totalNumeros, numeroObjetivo);
    clock_t tiempoFin = clock();

    // Calcular tiempo de ejecución
    double duracionBusqueda = double(tiempoFin - tiempoInicio) / CLOCKS_PER_SEC;

    // Mostrar resultados
    if (posicion != -1) {
        cout << "El numero " << numeroObjetivo << " se encuentra en la posicion " << posicion << "." << endl;
    } else {
        cout << "El numero " << numeroObjetivo << " no se encuentra en el arreglo." << endl;
    }
    cout << "Tiempo de ejecucion de la busqueda: " << duracionBusqueda << " segundos." << endl;

    // Liberar memoria
    delete[] numeros;

    return 0;
}
