#include <fstream> // Para manejo de archivos
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream> // Para manejar cadenas de texto

using namespace std;

int main() {
    // Leer un archivo de texto
    ifstream inputFile("numeros_aleatorios.txt"); // Abre el archivo
    if (!inputFile) { // Verifica si se pudo abrir
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    cout << "Contenido del archivo:" << endl;
    string line;
    while (getline(inputFile, line)) { // Leer línea por línea
        cout << line << endl; // Imprimir línea
    }
    inputFile.close(); // Cierra el archivo

    // Inicializar el generador de números aleatorios con una semilla
    srand(time(NULL));

    // Capturar el tiempo inicial
    clock_t start = clock();

    // Captura el número que el usuario quiere buscar
    cout << "Ingrese un número del archivo para calcular su tiempo: ";
    int user_input;
    cin >> user_input;

    // Bloque de código que queremos medir
    const int NUM_RANDOMS = 1000000; // Número de valores a generar
    int sum = 0;

    clock_t min_time = LONG_MAX; // Inicializa con el valor más alto posible
    clock_t max_time = 0; // Inicializa con el valor más bajo posible
    int min_rand = 0; // Número que tomó menos tiempo
    int max_rand = 0; // Número que tomó más tiempo
    bool found = false; // Variable para verificar si el número fue encontrado

    for (int i = 0; i < NUM_RANDOMS; ++i) {
        clock_t num_start = clock(); // Captura el tiempo de inicio para este número
        int random_num = rand(); // Genera un número aleatorio
        sum += random_num; // Suma el número al total
        clock_t num_end = clock(); // Captura el tiempo de fin para este número
        
        clock_t time_taken = num_end - num_start; // Calcula el tiempo tomado para generar este número
        
        // Verifica si este tiempo es el mínimo o el máximo
        if (time_taken < min_time) {
            min_time = time_taken;
            min_rand = random_num; // Guarda el número que tomó menos tiempo
        }
        
        if (time_taken > max_time) {
            max_time = time_taken;
            max_rand = random_num; // Guarda el número que tomó más tiempo
        }

        // Verifica si el número generado es el que busca el usuario
        if (random_num == user_input && !found) {
            cout << "El número " << user_input << " se encontró en el archivo." << endl;
            cout << "Tiempo para generar el número " << user_input << ": " << time_taken << " milisegundos" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "El número " << user_input << " no se encontró en el archivo." << endl;
    }

    // Capturar el tiempo final
    clock_t end = clock();

    // Calcular el tiempo total en segundos
    double elapsed_time = double(end - start) / CLOCKS_PER_SEC;

    cout << "Tiempo de ejecucion total: " << elapsed_time << " segundos." << endl;
    cout << "El número que tomo menos tiempo fue: " << min_rand << " con un tiempo de: " << min_time << " milisegundos" << endl;
    cout << "El número que tomo más tiempo fue: " << max_rand << " con un tiempo de: " << max_time << " milisegundos" << endl;

    return 0;
}

